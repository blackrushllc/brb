REM Basil/Basic CGI Library Include File

FUNC send_header_ok_html()
    //PRINT "Status: 200 OK\r\n"
    //PRINT "Content-Type: text/html; charset=utf-8\r\n"
    //PRINT "Cache-Control: no-store\r\n\r\n"
    RETURN 0
END FUNC

FUNC header_flush()
    PRINT "\r\n"
    RETURN 0
END FUNC

FUNC set_cookie(name$, value$)
    PRINT "Set-Cookie: " + name$ + "=" + value$ + "; Path=/; HttpOnly\r\n"
    RETURN 0
END FUNC

FUNC send_header_redirect(loc$)
    PRINT "Status: 302 Found\r\n"
    PRINT "Location: " + loc$ + "\r\n\r\n"
    RETURN 0
END FUNC

FUNC cookie$(name$)
    raw$ = ENV$("HTTP_COOKIE")
    IF LEN(raw$) == 0 THEN RETURN ""
    s$ = raw$
    i% = 1
    WHILE i% <= LEN(s$)
        semi% = INSTR(s$, ";", i%)
        IF semi% == 0 THEN semi% = LEN(s$) + 1
        part$ = TRIM$(MID$(s$, i%, semi% - i%))
        eq% = INSTR(part$, "=")
        IF eq% > 0 THEN
            ck$ = LEFT$(part$, eq% - 1)
            cv$ = MID$(part$, eq% + 1)
            IF ck$ == name$ THEN RETURN cv$
        END IF
        i% = semi% + 1
    END WHILE
    RETURN ""
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