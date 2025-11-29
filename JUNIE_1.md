**PROMPT FOR JUNIE (Basil CGI skeleton: `index.basil` + `reference.basil`)**

You are Junie, an AI coding assistant working inside a JetBrains IDE (PhpStorm / RustRover) on the **Basil** project.

We are going to be doing work in a programming language called **Basil** (a dialect of BASIC).

This project already includes:

+ The Basil example website under examples/website.
+ The Basil guides (e.g. docs/guides/BASIL_REFERENCE.md, FILE_IO.md, SQL.md, ORM.md, ORM_SQL.md, LIBRARY_OBJECTS.md).
+ When designing the CGI scripts, prefer to:
  + Follow any existing CGI or website patterns from examples/website.
  + Keep style and idioms consistent with the other Basil example programs in this repo.
+ You may reference these local files for naming conventions, DB helpers, and HTML output style when generating cgi/index.basil and cgi/reference.basil.


Here are some resources for you to reference:

A simple Website using Basil with CGI can be found in /docs/examples/website

Many examples of Basil code can be found in /docs/examples/

Full Basil Language Reference: /docs/guides/BASIL_REFERENCE.md
File I/O: /docs/guides/FILE_IO.md
SQL: /docs/guides/SQL.md
ORM: /docs/guides/ORM.md
More ORM: /docs/guides/ORM_SQL.md
CSV, JSON and other Basil extensions: https://github.com/blackrushllc/basil/blob/development/docs/guides/LIBRARY_OBJECTS.md

The full project overview is in README.md in the root of this project.

Here is the task that I would like you do complete in the context of the above resources:

We are building a documentation website for **Basil / Basic / Basic.JS** using **Basil CGI** on the backend with MySQL, and plain HTML/CSS/JS on the front-end.

Your task in this prompt is to **create CGI skeletons** for:

* `cgi/index.basil`
* `cgi/reference.basil`

These should be **real, compilable Basil programs** that:

* Run as CGI scripts (print correct HTTP headers).
* Parse `PATH_INFO` and (where applicable) `QUERY_STRING`.
* Have clear, structured routing.
* Output basic HTML pages (no templating engine yet, but factor out helpers).
* Have DB-access stubs that we can wire to the real MySQL/ORM later.

We are **not** fully implementing database queries yet. For now, you’ll stub out functions that return hard-coded arrays / sample data and put clear TODOs where SQL/ORM logic will eventually go.

Use **blocky BASIC style** (no line numbers) consistent with the Basil examples, e.g.:

```basic
FOR i% = 0 TO LEN(outs$[]) - 1 BEGIN
  PRINTLN outs$[](i%)
END
```

Use comments like `REM ...` or `// ...` as appropriate.

---

## 1. General CGI and coding conventions

For both `index.basil` and `reference.basil`, please:

1. **Print CGI headers** at the very top of `MAIN`:

   ```basic
   PRINTLN "Content-Type: text/html; charset=utf-8"
   PRINTLN "";  REM blank line after headers
   ```

2. Create a **`main`-style entry point** that:

    * Reads `PATH_INFO` and `QUERY_STRING` from the environment.
    * Routes to handler functions.
    * Wraps response HTML with a minimal layout (header/footer).

3. Provide small helper functions, for example:

    * `env$(name$)` — safely read environment variables (return `""` if missing).
    * `url_decode$(s$)` — simple URL-decoding (can be minimal, just enough for QUERY_STRING).
    * `parse_query_params@(...)` — parse `QUERY_STRING` into a simple key/value dictionary object or parallel arrays.
    * `html_escape$(s$)` — basic HTML escaping.

These helpers can live at the top or bottom of each file for now. Later we may factor them into a shared library file.

---

## 2. `cgi/index.basil`

This script will act as the **front-controller for the root** of the documentation site.

### 2.1 Behavior

* If `PATH_INFO` is empty or `/`, render a **landing page** with:

    * Site title (e.g. “Basil / Basic / Basic.JS Documentation”).
    * Short description.
    * Big links to:

        * `/guide`
        * `/reference`
    * A small search form that submits to `/search` (GET) with a `q` field (just static HTML; we’ll implement the search CGI later).

* For now:

    * If `PATH_INFO` starts with `/guide`:

        * Just print a simple placeholder like: “Guide will live here.” and link back to `/`.
    * If `PATH_INFO` starts with `/reference`:

        * Option A: show a short message and a link to `/reference` (which will map to `reference.basil`).
        * Option B: issue an HTTP redirect to `/reference`. (If you choose redirect, you must print correct headers for a redirect.)

Either approach is acceptable; pick one and comment it clearly.

### 2.2 Structure

Implement at least these functions in `index.basil`:

* `SUB MAIN()` or equivalent entry point:

    * Get `pathInfo$ = env$("PATH_INFO")`.
    * Normalize it (e.g., if it’s `""` then treat as `/`).
    * Print HTTP headers.
    * Call a router function like `handle_request@(pathInfo$)`.

* `SUB handle_request@(pathInfo$)`:

    * If `pathInfo$ = "/"` or `pathInfo$ = ""` → `render_home_page@()`.
    * Else IF it starts with `/guide` → `render_guide_placeholder@()`.
    * Else IF it starts with `/reference` → `render_reference_link_or_redirect@()`.
    * Else → `render_not_found@()`.

* `SUB render_home_page@()`:

    * Print a complete HTML document:

        * `<html>`, `<head>`, `<body>`.
        * A simple `<header>` with the site logo/title stub.
        * A `<main>` with:

            * An `<h1>` title.
            * Two prominent `<a>` links: `/guide` and `/reference`.
            * A search `<form>` with `<input name="q">`.
        * A `<footer>` stub.

* `SUB render_guide_placeholder@()`:

    * Simple HTML explaining the Guide will be implemented later.

* `SUB render_reference_link_or_redirect@()`:

    * Either:

        * Print a simple HTML stub linking to `/reference`.
    * Or:

        * Print `Status: 302 Found` and `Location: /reference` in the headers (plus blank line) then simple fallback HTML.

* `SUB render_not_found@()`:

    * Print a simple 404 page (you can also emit a `Status: 404 Not Found` header).

Include helper functions:

* `FUNCTION env$(name$)` → String.
* Anything else you need for cleanliness.

---

## 3. `cgi/reference.basil`

This script is responsible for the **Reference** section. We assume the server is configured so that requests to `/reference` and `/reference/...` are routed to this script.

### 3.1 Routes

Use `PATH_INFO` relative to the script. Design a **small router** that supports:

1. **Reference index page** (no extra path):

    * `PATH_INFO = ""` or `/` → `render_reference_index@()`.

   This page should:

    * Show a main heading: “Language Reference”.
    * Show:

        * A block with **Alphabetical index** links (A–Z and, later, Operators/Symbols).
        * A block with **Category list** links (e.g. “Audio”, “MIDI”, “Media”, etc.).
    * For now, get letters and categories from stub functions returning hard-coded arrays. Later these will query MySQL.

   Suggested URIs for these links (relative to `/reference`):

    * `/reference/alpha/A`
    * `/reference/category/audio`
    * `/reference/keyword/audio_inputs` (slug based).

2. **Alphabetical list**:

    * `PATH_INFO` like `/alpha/A`:

        * Letter = `A` (case-insensitive).
        * Handler: `render_alpha_listing@(letter$)`.

   For now:

    * Use a stub function like `get_keywords_for_letter$[][](letter$)` that returns a 2D array or a list of simple objects/records with fields:

        * `keyword`, `slug`, `short_desc`.
    * Render a page:

        * Heading: “Keywords starting with A”.
        * A list of links (e.g. `<a href="/reference/keyword/audio_inputs">AUDIO_INPUTS$</a> – short description`).
        * Include “Back to Reference Index” link.

3. **Category listing**:

    * `PATH_INFO` like `/category/audio`:

        * `categorySlug$ = "audio"`.
        * Handler: `render_category_listing@(categorySlug$)`.

   For now:

    * Use stubs:

        * `get_category_display_name$(categorySlug$)` → “Audio”.
        * `get_keywords_for_category$[][](categorySlug$)` → similar structure as for letter.
    * Render a page:

        * Heading: “Category: Audio”.
        * List of keywords in that category with links to their detail pages.

4. **Keyword detail page**:

    * `PATH_INFO` like `/keyword/audio_inputs`:

        * `keywordSlug$ = "audio_inputs"`.
        * Handler: `render_keyword_detail@(keywordSlug$)`.

   For now:

    * Implement a stub `load_keyword_detail@(...)` or `get_keyword_detail@(...)` that:

        * IF `keywordSlug$ = "audio_inputs"`:

            * Return a sample “keyword detail” structure with:

                * `keyword = "AUDIO_INPUTS$"`
                * `short_desc = "Returns an array of audio input device names."`
                * `long_desc_md` stub text.
                * `languages` = `["Basil"]`.
                * `categories` = `["Audio", "MIDI", "Media"]`.
                * `feature_library = "obj-audio"`.
                * `examples` = two sample code blocks (blocky and curly).
                * `see_also` = `["AUDIO_OUTPUTS$", "AUDIO_DEFAULT_RATE%", "AUDIO_DEFAULT_CHANS%"]`.
        * Else:

            * Return `NULL`/empty and let the handler show a 404-style keyword-not-found page.

    * Render HTML for:

        * Keyword name and a short description at the top.
        * badges/labels for languages and feature library.
        * Categories list.
        * “See Also” links.
        * Code examples:

            * Use `<pre><code>...</code></pre>` blocks.
            * Add a “Copy” button for each example (hooked to a simple JS function using `navigator.clipboard.writeText`).
        * Later, we will plug in the Markdown renderer; for now, you can:

            * Either print `long_desc_md` as-is.
            * Or treat it as plain text with `<p>` tags.

5. **Fallback / unknown routes**:

    * Any path not matching the above patterns → `render_reference_not_found@()`.

### 3.2 `reference.basil` structure

Please implement the following general structure:

* Entry point:

  ```basic
  SUB MAIN()
    LET pathInfo$ = env$("PATH_INFO")
    IF pathInfo$ = "" THEN
      pathInfo$ = "/"
    END

    PRINTLN "Content-Type: text/html; charset=utf-8"
    PRINTLN ""

    handle_reference_request@(pathInfo$)
  END
  ```

* Router:

  ```basic
  SUB handle_reference_request@(pathInfo$)
    REM Normalize, strip trailing slashes except root
    pathInfo$ = normalize_path$(pathInfo$)

    REM If "/", show index
    IF pathInfo$ = "/" THEN
      render_reference_index@()
      RETURN
    END

    REM Split on "/" into segments[] (e.g. ["", "alpha", "A"])
    LET segments$[] = split_path_segments$[](pathInfo$)

    IF LEN(segments$[]) >= 2 THEN
      IF segments$ = "alpha" THEN
        REM Expect /alpha/{letter}
        IF LEN(segments$[]) >= 3 THEN
          render_alpha_listing@(segments$)
        ELSE
          render_reference_not_found@()
        END
        RETURN
      END

      IF segments$ = "category" THEN
        IF LEN(segments$[]) >= 3 THEN
          render_category_listing@(segments$)
        ELSE
          render_reference_not_found@()
        END
        RETURN
      END

      IF segments$ = "keyword" THEN
        IF LEN(segments$[]) >= 3 THEN
          render_keyword_detail@(segments$)
        ELSE
          render_reference_not_found@()
        END
        RETURN
      END
    END

    render_reference_not_found@()
  END
  ```

* **Helper functions** to implement in this file:

    * `FUNCTION normalize_path$(path$)` — e.g. remove trailing slash if not root.
    * `FUNCTION split_path_segments$[](path$)` — returns array of segments without empty leading `""` where appropriate (or with; just be consistent with how you index them).
    * `FUNCTION env$(name$)` — like in `index.basil`.
    * `FUNCTION html_escape$(s$)` — minimal escaping: replace `<`, `>`, `&`, maybe `"`.
    * Stub data providers:

        * `FUNCTION get_alpha_letters$[]()` — returns something like `["A","B","C","D","E"]` for now.
        * `FUNCTION get_all_categories$[][]()` — list of category slug + display name pairs.
        * `FUNCTION get_keywords_for_letter$[][](letter$)`
        * `FUNCTION get_keywords_for_category$[][](slug$)`
        * `SUB get_keyword_detail@(slug$, OUT ok%, OUT keyword$, OUT shortDesc$, OUT longDescMd$, OUT languages$[], OUT categories$[], OUT featureLib$, OUT examples$[][], OUT seeAlso$[])`

  These stub functions should return **hard-coded sample data** (e.g. include the AUDIO_* family as an example), and contain clear `REM TODO: Replace with MySQL/ORM query` comments.

* **Renderer functions**:

    * `SUB render_reference_index@()`
    * `SUB render_alpha_listing@(letter$)`
    * `SUB render_category_listing@(categorySlug$)`
    * `SUB render_keyword_detail@(keywordSlug$)`
    * `SUB render_reference_not_found@()`

Each of these should print a full or partial HTML document. For now, you can have a simple wrapper:

* A helper `SUB html_head@(title$)` that prints `<html><head>...` and opens `<body>`.
* A helper `SUB html_foot@()` that closes `</body></html>`.

Use very simple but structured HTML:

* `<header>` with site title and “Home / Guide / Reference” links.
* `<nav>` on reference pages with a small side index stub (you can reuse the alpha and category lists).
* `<main>` for page content.

---

## 4. No real database yet (but ready for it)

When writing the data stub functions, please:

* Use **clear TODO comments** where queries will go, e.g.:

  ```basic
  REM TODO: Replace with SELECT DISTINCT UPPER(LEFT(keyword,1)) FROM keywords ORDER BY 1
  ```

* For now, return small fixed arrays like:

  ```basic
  FUNCTION get_alpha_letters$[]()
    DIM letters$[5]
    letters$[0] = "A"
    letters$[1] = "B"
    letters$[2] = "C"
    letters$[3] = "D"
    letters$[4] = "E"
    RETURN letters$[]
  END
  ```

* For keyword detail, hard-code **AUDIO_INPUTS$** and a couple of related keywords as examples, using the example code already described in our conversations:

    * Categories: Audio, MIDI, Media.
    * Languages: Basil only.
    * Feature library: obj-audio.
    * See Also: AUDIO_OUTPUTS$, AUDIO_DEFAULT_RATE%, AUDIO_DEFAULT_CHANS%.

Include at least one blocky example and one curly example in the stubbed data, and render both in `<pre><code>` blocks.

---

## 5. Output

Please:

1. **Create or overwrite** `cgi/index.basil` and `cgi/reference.basil` with the full Basil CGI code matching the above specs.
2. Ensure both scripts:

    * Are syntactically valid Basil (no line numbers).
    * Have `MAIN`/entry code that prints HTTP headers.
    * Contain routing logic and stubbed content.
3. Add enough comments so that a human can clearly see where to plug in:

    * MySQL connection / ORM calls.
    * Real data for alphabet letters, categories, and keywords.
    * Real Markdown rendering later.

Do *not* add any other files in this prompt; focus just on these two CGI scripts.

When you’re done, show the full contents of both files in the answer, each in its own ` ```basic ` code block, labeled with the filename as a comment at the top.
