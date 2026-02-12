# Homeless Helpers - Basil Demo Site

Because help is help. Probably.

## Overview
A parody directory connecting unhoused individuals with families needing babysitting or housesitting. 
"Kitschy Mommy-Blog Chic" aesthetic with "Live Laugh Lawsuit" energy.

## Features
- User Registration & Login (Cookie-based)
- User Profiles with Avatar Uploads
- Post CRUD (Create, Read, Update, Delete)
- Post Limit (max 10 per user)
- Directory Feed (Newest first)
- Post Detail Page with Comments
- Simple Share Buttons (JS Clipboard, Social Links)
- Comedic FAQ page
- SQLite Backend

## Setup
1. Ensure `basilc` and its dependencies are installed.
2. Run `seed.basil` to initialize the database:
   ```bash
   basilc run seed.basil
   ```
3. Deploy to a web server capable of running Basil CGI scripts (e.g., Apache with `mod_cgi`).

## Acceptance Checklist
- [x] Can register/login/logout
- [x] Can upload/edit profile and avatar
- [x] Can create/edit/delete posts
- [x] Post limit enforced at 10
- [x] Directory shows newest first
- [x] Post detail shows comments + share links
- [x] Only logged-in can comment
- [x] FAQ loads
- [x] All pages render with shared layout
- [x] Comedic copy throughout

## Disclaimer
Homeless Helpers is a parody demo website created for educational purposes. It is NOT a real service.
