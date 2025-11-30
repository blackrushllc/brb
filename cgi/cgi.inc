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
    FOR EACH param_kv$ IN REQUEST$()
        param_eq% = INSTR(param_kv$, "=")
        IF param_eq% > 0 THEN
            param_k$ = LEFT$(param_kv$, param_eq%)
            param_v$ = MID$(param_kv$, param_eq%+2)
            IF param_k$ == name$ THEN
                RETURN param_v$
            END IF
        END IF
    NEXT
    RETURN ""
END FUNC

FUNC cookie$(name$)
    cookie_raw$ = ENV$("HTTP_COOKIE")
    IF LEN(cookie_raw$) == 0 THEN RETURN ""
    cookie_s$ = cookie_raw$
    cookie_i% = 1
    WHILE cookie_i% <= LEN(cookie_s$)
        cookie_semi% = INSTR(cookie_s$, ";", cookie_i%-1)
        IF cookie_semi% == 0 THEN cookie_semi% = LEN(cookie_s$)
        cookie_part$ = TRIM$(MID$(cookie_s$, cookie_i%, cookie_semi% - cookie_i% + 1))
        cookie_eq% = INSTR(cookie_part$, "=")
        IF cookie_eq% > 0 THEN
            cookie_ck$ = LEFT$(cookie_part$, cookie_eq%)
            cookie_cv$ = MID$(cookie_part$, cookie_eq%+2)
            IF cookie_ck$ == name$ THEN RETURN cookie_cv$
        END IF
        cookie_i% = cookie_semi% + 2
    END WHILE
    RETURN ""
END FUNC

FUNCTION env$(name$)
    env_v$ = ENV$(name$)
    IF LEN(env_v$) = 0 THEN RETURN ""
    RETURN env_v$
END FUNCTION

FUNCTION normalize_path$(path$)
    IF LEN(path$) = 0 THEN RETURN "/"
    norm_p$ = path$
    IF RIGHT$(norm_p$, 1) = "/" AND LEN(norm_p$) > 1 THEN
        norm_p$ = LEFT$(norm_p$, LEN(norm_p$) - 1)
    END IF
    RETURN norm_p$
END FUNCTION

FUNCTION starts_with%(s$, prefix$)
    IF LEN(prefix$) = 0 THEN RETURN -1
    IF LEN(s$) < LEN(prefix$) THEN RETURN 0
    IF LEFT$(s$, LEN(prefix$)) = prefix$ THEN RETURN -1
    RETURN 0
END FUNCTION

FUNCTION html_escape$(s$)
  html_out$ = ""
  FOR html_e% = 1 TO LEN(s$)
    html_ch$ = MID$(s$, html_e%, 1)
    SELECT CASE html_ch$
        CASE "&"
            html_out$ = html_out$ + "&amp;"
        CASE "<"
            html_out$ = html_out$ + "&lt;"
        CASE ">"
            html_out$ = html_out$ + "&gt;"
        CASE "\""
            html_out$ = html_out$ + "&quot;"
        CASE ELSE
            html_out$ = html_out$ + html_ch$
    END SELECT
  NEXT html_e%
  RETURN html_out$
END FUNCTION

REM Minimal URL decoding for '+' and %XX (hex)
REM but we already have a builtin URLDECODE$()
FUNCTION url_decode$(s$)
    url_out$ = ""
    url_d% = 1
    WHILE url_d% <= LEN(s$)
        url_ch$ = MID$(s$, url_d%, 1)
        SELECT CASE url_ch$
            CASE "+"
                url_out$ = url_out$ + " "
                url_d% = url_d% + 1
            CASE "%" AND url_% + 2 <= LEN(s$)
                url_h1$ = MID$(s$, url_d%+1, 1)
                url_h2$ = MID$(s$, url_d%+2, 1)
                url_n% = hex2int%(url_h1$, url_h2$)
                IF url_n% >= 0 THEN
                    url_out$ = url_out$ + CHR$(url_n%)
                ELSE
                    url_out$ = url_out$ + url_ch$
                END
                url_d% = url_d% + 3
            CASE ELSE
               url_out$ = url_out$ + url_ch$
               url_d% = url_d% + 1
        END SELECT
    END WHILE
    RETURN url_out$
END FUNCTION

FUNCTION hex2int%(a$, b$)
    hex_v1% = hex1%(a$)
    hex_v2% = hex1%(b$)
    IF hex_v1% < 0 OR hex_v2% < 0 THEN RETURN -1
    RETURN hex_v1% * 16 + hex_v2%
END FUNCTION

FUNCTION hex1%(c$)
    hex_u$ = UCASE$(c$)
    IF hex_u$ >= "0" AND hex_u$ <= "9" THEN RETURN ASC(hex_u$) - ASC("0")
    IF hex_u$ >= "A" AND hex_u$ <= "F" THEN RETURN 10 + (ASC(hex_u$) - ASC("A"))
    RETURN -1
END FUNCTION

