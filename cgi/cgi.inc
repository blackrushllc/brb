REM Basil/Basic CGI Library Include File

FUNC send_header_ok_html()
    PRINT "Status: 200 OK\r\n"
    PRINT "Content-Type: text/html; charset=utf-8\r\n"
    PRINT "Cache-Control: no-store\r\n\r\n"
    RETURN 0
END FUNC

FUNC header_flush()
    PRINT "\r\n"
    RETURN 0
END FUNC

FUNC set_cookie(name$, value$)
    PRINT "Set-Cookie: " + name$ + "=" + value$ + "; Path=/; HttpOnly\r\n"
    RETURN 0
END

FUNC send_header_redirect(loc$)
    PRINT "Status: 302 Found\r\n"
    PRINT "Location: " + loc$ + "\r\n\r\n"
    RETURN 0
END FUNC

FUNC param$(name$)
    FOR EACH kv$ IN REQUEST$()
        eq% = INSTR(kv$, "=")
        IF eq% > 0 THEN
            k$ = LEFT$(kv$, eq%)
            v$ = MID$(kv$, eq%+2)
            IF k$ == name$ THEN
                RETURN v$
            END IF
        END IF
    NEXT
    RETURN ""
END FUNC

FUNC cookie$(name$)
    raw$ = ENV$("HTTP_COOKIE")
    IF LEN(raw$) == 0 THEN RETURN ""
    s$ = raw$
    i% = 1
    WHILE i% <= LEN(s$)
        semi% = INSTR(s$, ";", i%-1)
        IF semi% == 0 THEN semi% = LEN(s$)
        part$ = TRIM$(MID$(s$, i%, semi% - i% + 1))
        eq% = INSTR(part$, "=")
        IF eq% > 0 THEN
            ck$ = LEFT$(part$, eq%)
            cv$ = MID$(part$, eq%+2)
            IF ck$ == name$ THEN RETURN cv$
        END IF
        i% = semi% + 2
    END WHILE
    RETURN ""
END FUNC

FUNCTION env$(name$)
    v$ = ENV$(name$)
    IF LEN(v$) = 0 THEN RETURN ""
    RETURN v$
END FUNCTION

FUNCTION normalize_path$(path$)
    IF LEN(path$) = 0 THEN RETURN "/"
    p$ = path$
    IF RIGHT$(p$, 1) = "/" AND LEN(p$) > 1 THEN
        p$ = LEFT$(p$, LEN(p$) - 1)
    END IF
    RETURN p$
END FUNCTION

FUNCTION starts_with%(s$, prefix$)
    IF LEN(prefix$) = 0 THEN RETURN -1
    IF LEN(s$) < LEN(prefix$) THEN RETURN 0
    IF LEFT$(s$, LEN(prefix$)) = prefix$ THEN RETURN -1
    RETURN 0
END FUNCTION

FUNCTION html_escape$(s$)
  out$ = ""
  FOR i% = 1 TO LEN(s$)
    ch$ = MID$(s$, i%, 1)
    SELECT CASE ch$
        CASE "&"
            out$ = out$ + "&amp;"
        CASE "<"
            out$ = out$ + "&lt;"
        CASE ">"
            out$ = out$ + "&gt;"
        CASE "\""
            out$ = out$ + "&quot;"
        CASE ELSE
            out$ = out$ + ch$
    END SELECT
  NEXT i%
  RETURN out$
END FUNCTION

REM Minimal URL decoding for '+' and %XX (hex)
FUNCTION url_decode$(s$)
    out$ = ""
    i% = 1
    WHILE i% <= LEN(s$)
        ch$ = MID$(s$, i%, 1)
        SELECT CASE ch$
            CASE "+"
                out$ = out$ + " "
                i% = i% + 1
            CASE "%" AND i% + 2 <= LEN(s$)
                h1$ = MID$(s$, i%+1, 1)
                h2$ = MID$(s$, i%+2, 1)
                n% = hex2int%(h1$, h2$)
                IF n% >= 0 THEN
                    out$ = out$ + CHR$(n%)
                ELSE
                    out$ = out$ + ch$
                END
                i% = i% + 3
            CASE ELSE
               out$ = out$ + ch$
               i% = i% + 1
        END SELECT
    END WHILE
    RETURN out$
END FUNCTION

FUNCTION hex2int%(a$, b$)
    v1% = hex1%(a$)
    v2% = hex1%(b$)
    IF v1% < 0 OR v2% < 0 THEN RETURN -1
    RETURN v1% * 16 + v2%
END FUNCTION

FUNCTION hex1%(c$)
    u$ = UCASE$(c$)
    IF u$ >= "0" AND u$ <= "9" THEN RETURN ASC(u$) - ASC("0")
    IF u$ >= "A" AND u$ <= "F" THEN RETURN 10 + (ASC(u$) - ASC("A"))
    RETURN -1
END FUNCTION

