# Gamora Pharmaceuticals Basil Demo

This is a polished demo website for the fictional company **Gamora Pharmaceuticals**, built as a showcase for the **Basil** framework.

## Features

- **Shared Layout:** Uses a central layout with header and footer partials.
- **Fred Directives:** Utilizes `@INCLUDE`, `@IF`, `@REQUEST`, and more for template logic.
- **Routing:** A single `index.basil` script handles all page routing and form submissions.
- **Working Contact Form:** A real Basil-backed contact form with POST handling and simple validation.
- **Persistence:** Submissions are stored locally in `submissions.txt`.
- **Flash Messaging:** Uses cookies to display success or error messages after redirection.

## Site Structure

- `/` (Home): Slick, sales-focused introduction to **Ophidiane®**.
- `/about` (About Gamora): Corporate culture, leadership, and mission statements (with subtle satire).
- `/contact` (Contact): A working demo of Basil's form handling capabilities.

## How to Run

1. Ensure you have a Basil CGI-compatible web server set up.
2. Place the `gamora` folder in your server's web root (or a sub-folder).
3. Access `index.basil` through your browser.

## Project Organization

- `index.basil`: The main router and POST handler.
- `cgi.inc`: A helper library for CGI headers and cookies.
- `css/site.css`: Custom CSS for the premium pharma aesthetic.
- `views/`:
  - `layout.html`: The base template.
  - `header.html` / `footer.html`: Reusable partials.
  - `home.html` / `about.html` / `contact.html`: Page-specific views.
- `images/`: Fictional image assets for products, leadership, and culture.
- `submissions.txt`: Data store for contact form submissions.

## Swapping Images

To replace images, simply update the files in the `images/` directory:
- `product/`: Product bottles and marketing shots.
- `leadership/`: Executive headshots.
- `team/`: Team photos.
- `culture/` / `office/` / `lab/`: Environment and lifestyle shots.

## Contact Form Submissions

Submissions are appended to `submissions.txt` in a human-readable format.
Example entry:
```text
--- SUBMISSION ---
Date: 2026-04-07 23:35
Name: Basil Enthusiast
Email: fan@example.com
Organization: Basil Labs
Department: Product Information
Subject: Inquiry about Ophidiane
Message: I would like to learn more about the stability benefits of Ophidiane.
```
