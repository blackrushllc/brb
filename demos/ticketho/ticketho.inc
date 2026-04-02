REM TICKETHO Core Library

#include "cgi.inc"

FUNC db_open%()
    // Try DB in script directory first
    db% = SQLITE_OPEN%("ticketho.db")
    IF db% == 0 THEN
        // Fallback to a writable temp dir
        tmp$ = ENV$("TMPDIR")
        IF LEN(tmp$) == 0 THEN tmp$ = ENV$("TEMP")
        IF LEN(tmp$) == 0 THEN tmp$ = ENV$("TMP")
        IF LEN(tmp$) == 0 THEN tmp$ = "/tmp"
        // Join path safely
        IF RIGHT$(tmp$, 1) == "/" OR RIGHT$(tmp$, 1) == "\\" THEN
            path$ = tmp$ + "ticketho.db"
        ELSE
            path$ = tmp$ + "/" + "ticketho.db"
        END IF
        db% = SQLITE_OPEN%(path$)
    END IF
    
    IF db% == 0 THEN RETURN 0
    
    // Initialize Schema
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT UNIQUE, password_hash TEXT, phone TEXT, avatar_path TEXT, email_verified_at TEXT, created_at TEXT, updated_at TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS teams (id INTEGER PRIMARY KEY AUTOINCREMENT, owner_id INTEGER, name TEXT, slug TEXT UNIQUE, created_at TEXT, updated_at TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS team_members (team_id INTEGER, user_id INTEGER, role TEXT, joined_at TEXT, PRIMARY KEY (team_id, user_id))")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS tickets (id INTEGER PRIMARY KEY AUTOINCREMENT, team_id INTEGER, reporter_user_id INTEGER, title TEXT, description TEXT, status_id INTEGER, notes TEXT, estimate INTEGER, time_spent INTEGER, created_at TEXT, updated_at TEXT, deleted_at TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS statuses (id INTEGER PRIMARY KEY AUTOINCREMENT, team_id INTEGER, name TEXT, color TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS public_intake_links (id INTEGER PRIMARY KEY AUTOINCREMENT, team_id INTEGER, token TEXT UNIQUE, label TEXT, active INTEGER DEFAULT 1, created_by INTEGER, created_at TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS email_login_tokens (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, token TEXT UNIQUE, purpose TEXT, team_id INTEGER, redirect_target TEXT, expires_at TEXT, used_at TEXT, created_at TEXT)")
    SQLITE_EXEC%(db%, "CREATE TABLE IF NOT EXISTS team_settings (id INTEGER PRIMARY KEY AUTOINCREMENT, team_id INTEGER, key TEXT, value TEXT)")

    // Seed Defaults
    seed_defaults%(db%)

    RETURN db%
END FUNC

FUNC seed_defaults%(db%)

    // Seed System User
    rows$ = SQLITE_QUERY2D$(db%, "SELECT id FROM users WHERE id = 1")
    print "SELECT id FROM users WHERE id = 1"

    if rows$ = null then
     print 'aaaaaaaaaaaaaaa'
     return 0


    IF ARRAY_ROWS%(rows$) == 0 THEN
        SQLITE_EXEC%(db%, "INSERT INTO users (id, name, email, created_at) VALUES (1, 'System', 'system@ticketho.demo', DATETIME('now'))")
    END IF

    // Seed Default Team
    rows$ = SQLITE_QUERY2D$(db%, "SELECT id FROM teams WHERE id = 1")
    IF ARRAY_ROWS%(rows$) == 0 THEN
        SQLITE_EXEC%(db%, "INSERT INTO teams (id, owner_id, name, slug, created_at) VALUES (1, 1, 'Default Team', 'default', DATETIME('now'))")
        SQLITE_EXEC%(db%, "INSERT INTO team_members (team_id, user_id, role, joined_at) VALUES (1, 1, 'owner', DATETIME('now'))")
    END IF

    // Seed Default Statuses
    rows$ = SQLITE_QUERY2D$(db%, "SELECT id FROM statuses LIMIT 1")
    IF ARRAY_ROWS%(rows$) == 0 THEN
        SQLITE_EXEC%(db%, "INSERT INTO statuses (name, color) VALUES ('Pending', '#ffc107')")
        SQLITE_EXEC%(db%, "INSERT INTO statuses (name, color) VALUES ('Approved', '#17a2b8')")
        SQLITE_EXEC%(db%, "INSERT INTO statuses (name, color) VALUES ('Declined', '#dc3545')")
        SQLITE_EXEC%(db%, "INSERT INTO statuses (name, color) VALUES ('Completed', '#28a745')")
        SQLITE_EXEC%(db%, "INSERT INTO statuses (name, color) VALUES ('On Hold', '#6c757d')")
    END IF

    RETURN 0
END FUNC

FUNC random_token$(length%)
    chars$ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    res$ = ""
    FOR i% = 1 TO length%
        idx% = INT(RND * LEN(chars$)) + 1
        res$ = res$ + MID$(chars$, idx%, 1)
    NEXT
    RETURN res$
END FUNC

FUNC get_current_user_id%()
    u$ = cookie$("auth_user_id")
    IF LEN(u$) == 0 THEN RETURN 0
    RETURN VAL(u$)
END FUNC

FUNC get_default_team_id%()
    LOADENV%()
    tid$ = ENV$("DEFAULT_TEAM_ID")
    IF LEN(tid$) > 0 THEN RETURN VAL(tid$)
    RETURN 1
END FUNC

FUNC get_user_role$(db%, team_id%, user_id%)
    rows$ = SQLITE_QUERY2D$(db%, "SELECT role FROM team_members WHERE team_id = " + STR$(team_id%) + " AND user_id = " + STR$(user_id%))
    IF ARRAY_ROWS%(rows$) > 0 THEN
        RETURN rows$(0,0)
    END IF
    RETURN ""
END FUNC
