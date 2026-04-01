#include "ticketho.inc"

FUNC layout_start(title$)
    SITE_TITLE$ = "TICKETHO"
    user_id% = get_current_user_id%()
    
    PRINT "<!doctype html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>" + HTML$(title$) + " - " + HTML$(SITE_TITLE$) + "</title>\n"
    PRINT "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    PRINT "<link rel=\"stylesheet\" href=\"css/site.css\">\n"
    PRINT "</head>\n<body>\n"
    
    // Navbar
    PRINT "<header class=\"top\">\n<div class=\"wrap\">\n"
    PRINT "<div class=\"nav-brand\"><a href=\"index.basil\">" + HTML$(SITE_TITLE$) + "</a></div>\n"
    PRINT "<nav class=\"nav-links\">\n"
    PRINT "<a href=\"index.basil#features\">Features</a>\n"
    PRINT "<a href=\"index.basil#how-it-works\">How It Works</a>\n"
    
    IF user_id% > 0 THEN
        PRINT "<a href=\"dashboard.basil\">Dashboard</a>\n"
        PRINT "<a href=\"logout.basil\">Logout</a>\n"
    ELSE
        PRINT "<a href=\"login.basil\">Login</a>\n"
        PRINT "<a href=\"register.basil\" class=\"btn-primary\">Get Started</a>\n"
    END IF
    
    PRINT "</nav>\n</div>\n</header>\n<main class=\"wrap\">\n"
    RETURN 0
END FUNC

FUNC layout_end()
    PRINT "</main>\n<footer class=\"foot\">\n<div class=\"wrap\">\n"
    PRINT "<div class=\"footer-grid\">\n"
    PRINT "<div><h4>TICKETHO</h4><p>Friendly team ticketing.</p></div>\n"
    PRINT "<div><h4>Links</h4><ul>\n"
    PRINT "<li><a href=\"index.basil\">Home</a></li>\n"
    PRINT "<li><a href=\"login.basil\">Login</a></li>\n"
    PRINT "<li><a href=\"register.basil\">Register</a></li>\n"
    PRINT "<li><a href=\"intake.basil\">Submit a Ticket</a></li>\n"
    PRINT "</ul></div>\n"
    PRINT "<div><h4>Community</h4><ul>\n"
    PRINT "<li><a href=\"https://syndorela.com\">Syndorela Kingdom</a></li>\n"
    PRINT "</ul></div>\n"
    PRINT "</div>\n"
    PRINT "<hr>\n"
    PRINT "<div class=\"footer-bottom\"><p>&copy; 2026 Syndorela Kingdom Educational Initiative. Built with Basil.</p></div>\n"
    PRINT "</div>\n</footer>\n"
    PRINT "<script src=\"js/site.js\"></script>\n</body>\n</html>\n"
    RETURN 0
END FUNC
