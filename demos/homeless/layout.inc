#include "cgi.inc"
#include "db.inc"

SITE_TITLE$ = "Homeless Helpers"

FUNC layout_start(title$)
    user$ = cookie$("user")
    
    PRINT "<!doctype html>\n"
    PRINT "<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n"
    PRINT "<title>" + HTML$(title$) + " | " + HTML$(SITE_TITLE$) + "</title>\n"
    PRINT "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    PRINT "<link rel=\"stylesheet\" href=\"css/site.css\">\n"
    // Google fonts for that handwritten feel
    PRINT "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">\n"
    PRINT "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>\n"
    PRINT "<link href=\"https://fonts.googleapis.com/css2?family=Cherry+Bomb+One&family=Short+Stack&display=swap\" rel=\"stylesheet\">\n"
    PRINT "</head>\n<body>\n"
    
    PRINT "<header class=\"site-header\">\n"
    PRINT "  <div class=\"wrap\">\n"
    PRINT "    <div class=\"logo-area\">\n"
    PRINT "      <a href=\"index.basil\" class=\"logo\">🏠❤️🛒 " + HTML$(SITE_TITLE$) + "</a>\n"
    PRINT "      <span class=\"tagline\">Because help is help. Probably.</span>\n"
    PRINT "    </div>\n"
    PRINT "    <nav class=\"main-nav\">\n"
    PRINT "      <a href=\"index.basil\">Home</a>\n"
    PRINT "      <a href=\"directory.basil\">Directory</a>\n"
    PRINT "      <a href=\"faq.basil\">FAQ</a>\n"
    
    IF LEN(user$) > 0 THEN
        PRINT "      <a href=\"user_home.basil\">Dashboard</a>\n"
        PRINT "      <a href=\"profile.basil\">Profile</a>\n"
        PRINT "      <a href=\"logout.basil\" class=\"btn-sm\">Logout</a>\n"
    ELSE
        PRINT "      <a href=\"login.basil\">Login</a>\n"
        PRINT "      <a href=\"register.basil\" class=\"btn-sm\">Join Us!</a>\n"
    END IF
    
    PRINT "    </nav>\n"
    PRINT "  </div>\n"
    PRINT "</header>\n"
    
    // Flash messages
    msg$ = cookie$("flash_msg")
    IF LEN(msg$) > 0 THEN
        PRINT "<div class=\"flash-msg wrap\">" + HTML$(msg$) + "</div>\n"
        // Clear cookie by setting it to empty with past date
        // Actually, just setting to empty usually works for simple cases, 
        // but Basil set_cookie doesn't have expiry support. 
        // I'll just set it to empty.
        _ = set_cookie("flash_msg", "")
    END IF
    
    PRINT "<main class=\"wrap main-content\">\n"
    RETURN 0
END FUNC

FUNC layout_end()
    PRINT "</main>\n"
    
    PRINT "<footer class=\"site-footer\">\n"
    PRINT "  <div class=\"wrap\">\n"
    PRINT "    <div class=\"footer-grid\">\n"
    PRINT "      <div class=\"footer-brand\">\n"
    PRINT "        <h3>" + HTML$(SITE_TITLE$) + "</h3>\n"
    PRINT "        <p>Live, Laugh, Locksmith.</p>\n"
    PRINT "      </div>\n"
    PRINT "      <div class=\"footer-disclaimer\">\n"
    PRINT "        <p class=\"disclaimer-text\"><strong>LEGALLY-ISH SPEAKING:</strong> Homeless Helpers is a parody demo site for Basil. Not a real service. We are not responsible for emotional damage, property damage, or learning experiences. By using this site, you agree that sometimes things happen and that’s just life. Lower your expectations.</p>\n"
    PRINT "      </div>\n"
    PRINT "    </div>\n"
    PRINT "    <div class=\"footer-bottom\">\n"
    PRINT "      <small>&copy; 2026 Homeless Helpers &bull; Built with Basil &bull; It's fine. Probably.</small>\n"
    PRINT "    </div>\n"
    PRINT "  </div>\n"
    PRINT "</footer>\n"
    
    PRINT "<script src=\"js/site.js\"></script>\n"
    PRINT "</body></html>\n"
    RETURN 0
END FUNC

FUNC flash(msg$)
    _ = set_cookie("flash_msg", msg$)
    RETURN 0
END FUNC
