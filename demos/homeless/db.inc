REM Database helpers for Homeless Helpers

FUNC db_open%()
    db% = SQLITE_OPEN%("homeless.db")
    RETURN db%
END FUNC

FUNC get_posts@(db%)
    DIM rows$(0,0)
    rows$() = SQLITE_QUERY2D$(db%, "SELECT p.*, u.username FROM posts p JOIN users u ON p.user_id = u.id ORDER BY p.created_at DESC")
    RETURN rows$()
END FUNC

FUNC get_post_by_id@(db%, id%)
    DIM rows$(0,0)
    rows$() = SQLITE_QUERY2D$(db%, "SELECT p.*, u.username FROM posts p JOIN users u ON p.user_id = u.id WHERE p.id = " + id%)
    RETURN rows$()
END FUNC

FUNC get_comments_for_post@(db%, post_id%)
    DIM rows$(0,0)
    rows$() = SQLITE_QUERY2D$(db%, "SELECT c.*, u.username FROM comments c JOIN users u ON c.user_id = u.id WHERE c.post_id = " + post_id% + " ORDER BY c.created_at ASC")
    RETURN rows$()
END FUNC
