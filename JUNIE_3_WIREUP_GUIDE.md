Here’s a Junie-ready prompt you can paste into IntelliJ. It’s tailored to:

* Our Basil caveats,
* Existing `cgi.inc` / `db.inc`,
* And the upgraded `RENDER$` (second-arg dictionary + `@FOREACH`).

You can prepend your usual “use local docs as reference” preface above this.

---

### PROMPT FOR JUNIE – Wire up `guide.basil` (read-only, with RENDER$)

You are Junie Ultimate, working in an IntelliJ IDEA project that contains:

* Basil BASIC source files, including:

    * `cgi/index.basil`
    * `cgi/reference.basil`
    * `cgi/guide.basil` (currently a stub)
    * `cgi/cgi.inc` (common CGI helpers)
    * `cgi/db.inc` (MySQL/ORM bootstrap)
* The “website” example from the Basil repo (SQLite + cookies + CGI helpers).
* Markdown guide docs for SQL/ORM and for RENDER/Fred:

    * `SQL.md`
    * `ORM_SQL.md`
    * `RENDER_AND_FRED.md`

The Apache server routes:

* `/guide` → `cgi/guide.basil`
* `/guide/...` → `cgi/guide.basil` with `PATH_INFO` set and **already parsed into segments** via helpers in `cgi.inc`.
  (Follow the same pattern we used in `reference.basil`, and **reuse** any existing helpers rather than re-inventing them.)

The MySQL database `brb` is already created and populated with the tables we previously designed:

* `guide_sections`
* `guide_pages`
* And the reference tables (`keywords`, etc.) which you may **reference** for patterns but should not change in this prompt.

The **Reference** CGI is already live, DB-backed, and using the ORM from `db.inc`. We want to bring the **Guide** up to a similar standard.

---

## Important Basil caveats you MUST obey

The following are rules specific to this Basil dialect. Please **follow them exactly**:

1. **Function return types**
   All functions can return any type, including arrays.

    * Do **not** use `[]` or `[][]` to indicate array types in function *definitions*.
    * Return arrays just like any other value.

2. **Type suffixes on functions**
   Function names *may* use `$` or `%` suffixes by convention, but the runtime does not enforce this.

    * Use `$` for functions that usually return strings, `%` for integers, and no suffix for “generic” or array-returning functions if it feels natural.

3. **Array assignment syntax**
   On the **left-hand side**, do **not** use parentheses or `[]`. For example:

    * ❌ `A$() = MyArrayFunc()`
    * ✅ `A$ = MyArrayFunc()`
      Arrays are just variables whose value happens to be an array.

4. **Block delimiters**
   `BEGIN` and `END` are **optional and discouraged** in Blocky BASIC.

    * For multi-line blocks, use `END IF`, `END WHILE`, `END FUNCTION`, etc., or just `END`.
    * Do **not** mix `{`/`}` curly style in this file; stick with Blocky BASIC style.

5. **FUNC vs FUNCTION**
   `FUNC` and `FUNCTION` are synonyms. Use whichever you prefer, but be consistent within this file.

6. **ARRAY_ROWS% vs LEN**
   `ARRAY_ROWS%()` is for 2D arrays.

    * For **1D arrays**, use `LEN()` instead.

7. **LET**
   `LET` is optional. You may just use `x = 123`.

    * `DIM` is still required to declare arrays.

8. **Single-line IF**
   Single-line `IF ... THEN ...` **must not** be closed with `END` or `END IF`. That’s a syntax error.

    * Multi-line IFs must be ended.

9. **No ELSEIF**
   `ELSEIF` is not supported.

    * Use nested `IF` or, preferably, `SELECT CASE` instead.

10. **Variables are not yet local to functions**
    Variables inside functions are not truly local.

    * Avoid reusing common names like `i%` across many functions; prefer more specific names to avoid global collisions.

Please examine the existing Basil files (especially `index.basil` and `reference.basil`) and **match their style and patterns**.

---

## RENDER$ and Fred (very important)

We have a new built-in function `RENDER$` described in `RENDER_AND_FRED.md`. Key points you must respect:

1. **Signature**
   `RENDER$` accepts:

    * First argument: the template string (usually the result of `READFILE$()`).
    * Second argument: a **dictionary object** that defines variables for use inside the template.

   Example:

   ```basic
   REM Pseudocode for building variables dictionary
   DIM vars@    REM dictionary object
   REM populate vars@ with keys/values

   html$ = RENDER$(READFILE$("views/guide/page.html"), vars@)
   PRINT html$
   ```

2. **Variable naming from dictionary**

    * Dictionary keys become variable names in the RENDER context.
    * If you pass a key `"title"` with value `"Hello"`, RENDER$ will make `title$` (or `title`) available, appending `$`/`%` automatically for strings/ints unless your key already has them.

3. **User-defined functions**

    * Function calls like `{{ MyFunc$(x$) }}` work inside templates as long as `MyFunc$` is defined before calling `RENDER$`.

4. **Fred directives**
   You must use the **current implementation**, which includes:

    * `@IF`, `@ELSE`, `@END` etc. for conditionals.
    * `@INCLUDE("file.html")` for partials.
    * `@FOREACH(... ) ... @ENDFOREACH` for loops, with:

        * Support for dictionaries, lists, and arrays.
    * `@ELSEFOREACH` to define fallback content when the loop has zero iterations.

   For example, with a dictionary `pet@`:

   ```fred
   @FOREACH (key$ IN pet@)
     {{ pet@[key$] }}
   @ENDFOREACH

   @ELSEFOREACH
     <p>No pets found.</p>
   @ENDFOREACH
   ```

Please use `@FOREACH` in the **Guide templates** to render lists of sections and pages as much as possible, instead of concatenating giant HTML strings in Basil.

---

## Your task in this prompt

Your goal: **implement Phase 1 – Wiring up the Guide (read-only, with RENDER$)**

Specifically:

1. **Update `cgi/guide.basil`** to:

    * Include `cgi.inc` and `db.inc` like the other CGI files.
    * Read `PATH_INFO` and segments using the same helpers/patterns we used in `reference.basil`.
    * Route:

        * `/guide` or `/guide/` → Guide index.
        * `/guide/{slug}` → Specific Guide page.
    * Query real data from the `brb` MySQL DB using the ORM / DB objects defined in `db.inc`.
    * Build **lightweight data structures** (arrays/dictionaries) to pass into `RENDER$` as the second argument.

2. **Create the Guide view templates** under `views/guide/` using Fred:

    * `views/guide/layout.html`
      Shared layout used by the Guide pages. It should:

        * Render a `<head>` with a `<title>` using a variable like `pageTitle$`.
        * Render a `<header>` with:

            * Site title “Basil / Basic / Basic.JS Documentation”
            * Simple nav links: Home (`/`), Guide (`/guide`), Reference (`/reference`).
        * Render a two-column `<main>`:

            * `<aside>`: side navigation (`guideNav`), rendered via `@FOREACH` from a variable (e.g. a list of sections and their pages).
            * `<section>`: main content (`pageContentHtml$`).
        * Use `@INCLUDE` to split head/footer into partials if you see a clear reuse, but **don’t overcomplicate**.

    * `views/guide/index.html`
      The Guide index page. It should:

        * `@INCLUDE("layout.html")` or otherwise extend it, using variables set from `guide.basil`.
        * Display:

            * A “Welcome to the Guide” intro.
            * A list of beginner pages (e.g. pages with `difficulty='beginner'`) in the main content area.
        * Use `@FOREACH` loops over arrays/lists passed via the dictionary to build these lists.

    * `views/guide/page.html`
      The individual Guide page template. It should:

        * Use `layout.html` as the base.
        * Show:

            * The page title (`pageTitle$`).
            * Optional metadata: section title (e.g. “Section: Getting Started”), difficulty.
            * The Guide page body, which will initially be **Markdown** text. For now:

                * You may either output it as `<pre>` or as a `<div id="doc-md">{{ pageBodyMd$ }}</div>`.
                * Leave an HTML comment near this area explaining that a JS Markdown renderer (like `marked.js`) will be wired in later.

3. **Database behavior for the Guide**

In `guide.basil`:

* For the **Guide index** (`/guide`):

    * Query all `guide_sections` ordered by `sort_order`.
    * Query all `guide_pages` where `is_published = 1`, ordered by `section_id` and `position`.
    * Build a structure suitable for RENDER$, for example:

        * `sections@` – a dictionary keyed by section slug or id containing:

            * Section title
            * A list/array of pages (slug + title)
        * `beginnerPages[]` – a list of “beginner” pages for the main content.
    * Construct a dictionary `vars@` for RENDER$ with keys such as:

        * `"pageTitle"` → `"Guide"`
        * `"guideNav"` → a list/dict describing sections & pages (for `@FOREACH` in the template).
        * `"pageContentHtml"` or `"beginnerPages"` → for `index.html` to loop over.

* For the **Guide page detail** (`/guide/{slug}`):

    * Look up the corresponding `guide_pages` row by `slug` and `is_published=1`. Include the section title via a join to `guide_sections`.
    * If not found, render a simple 404 within the Guide layout.
    * If found:

        * Load:

            * `title`
            * `section_title`
            * `body_md`
            * `difficulty`
        * Use the **same nav data** as the index (sections + pages) so the sidebar stays consistent.
        * Put the Markdown text into a variable, e.g. `pageBodyMd$`, and pass it to the template via `vars@`.
        * Set `pageTitle$` in the template context to the page title.

4. **Use RENDER$(template$, vars@) consistently**

When rendering:

* Do **not** rely on global variables magically appearing; instead:

    * Create a dictionary object (however dictionaries are commonly created in this project—e.g. `DICT_NEW@()` or similar, follow existing patterns).
    * For each variable you want exposed to the template, set an entry in the dictionary.

For example (pseudo-Basil):

```basic
DIM vars@

REM put vars into dictionary; syntax here should follow existing dict examples in the repo
DictSet$(vars@, "pageTitle", pageTitle$)
DictSet$(vars@, "guideNav", guideNavData@)
DictSet$(vars@, "pageBodyMd", pageBodyMd$)

html$ = RENDER$(READFILE$("views/guide/page.html"), vars@)
PRINT html$
```

Inside `page.html`, use Fred to loop over `guideNav` and to output `pageBodyMd$`.

5. **Routing in `guide.basil`**

Match the routing logic from `reference.basil`:

* Use the environment/segments helpers from `cgi.inc` (do **not** re-implement them) to get the path segments for `PATH_INFO` after `/guide`.

    * If the path is `/guide` → index.
    * If the path is `/guide/{slug}` → page detail.
* Include a `render_guide_not_found@()` function similar to the 404 in `reference.basil`, but styled with the Guide layout and nav.

6. **HTTP headers**

At the top of `MAIN` in `guide.basil`, print the CGI headers like in the other scripts:

```basic
PRINTLN "Content-Type: text/html; charset=utf-8";
PRINTLN "";
```

Then call your router/handler function.

---

## Constraints and style

* Follow the **existing style** of `index.basil` and `reference.basil` as much as possible:

    * Naming conventions.
    * How `cgi.inc` and `db.inc` are included.
    * How environment variables are read (e.g. `env$("PATH_INFO")` wrappers).
* Prefer clear function names like:

    * `GuideHandleRequest@()`
    * `GuideRenderIndex@()`
    * `GuideRenderPage@(slug$)`
    * `GuideBuildNav@(OUT navData@)` or similar.
* Use **Fred `@FOREACH`** in templates to render lists of sections/pages instead of concatenating large HTML strings in Basil where reasonable.

---

## Output expectation

At the end of this task, you must:

1. **Update `cgi/guide.basil`** with:

    * Routing for `/guide` and `/guide/{slug}`.
    * Real DB queries to `guide_sections` and `guide_pages`.
    * RENDER$ integration using a dictionary second argument.
2. **Create the following template files** (or update them if they already exist):

    * `views/guide/layout.html`
    * `views/guide/index.html`
    * `views/guide/page.html`
3. Ensure the code is syntactically valid Basil under the caveats above and compiles/runs in the existing CGI environment.

When you present your answer, show the **full contents** of:

* `cgi/guide.basil`
* `views/guide/layout.html`
* `views/guide/index.html`
* `views/guide/page.html`

each in its own code block with an appropriate language tag (`basic` for Basil, `html` for templates).

Do not modify other files in this prompt.
