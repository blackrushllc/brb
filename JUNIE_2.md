You’ve got a *lot* of the hard stuff done already—DB schema, CGI routing, real reference pages, and now RENDER$ + Fred on top. Very nice foundation.

Let’s treat this in three chunks, matching what you said:

1. Wire up the **Guide** (read-only, using RENDER$).
2. **Phase 2 – Admin + Markdown UX.**
3. **Phase 3 – Search + CSV.**

I’ll walk through what each should look like and then give you a concrete “next move” you can hand to Junie.

---

## 1. Wiring up the Guide (read-only, with RENDER$)

You already have:

* `guide_sections` / `guide_pages` tables.
* `cgi/guide.basil` stubbed and routing from `/guide` and `/guide/{slug}`.
* `cgi.inc` and `db.inc` for shared helpers and ORM/SQL.
* RENDER$ + Fred templates, which:

    * Allow `{{ expr }}` interpolation of global variables/functions.
    * Support inline helpers and conditionals (`@IF`, `@CASE`, etc.).

But: RENDER$ v1 doesn’t yet have loops like `@FOREACH` (they’re listed as a *future* extension). So list rendering should mostly be done in Basil, with RENDER$ handling layout and simple substitutions/conditionals.

### 1.1 URL patterns

Let’s standardize:

* `/guide` → Guide index (site intro + beginner chapters list).
* `/guide/{slug}` → Specific page (chapter or advanced topic).

You can add `/guide/section/{slug}` later if you want a multi-level nav, but for now `slug` at the page level is enough.

### 1.2 Template strategy with RENDER$

Add some view files, for example:

* `views/layout.html` – common shell (header, nav, footer).
* `views/guide/index.html` – main Guide index content.
* `views/guide/page.html` – individual Guide page.

Because RENDER$ runs expressions in the context of globals/functions, you can follow this pattern:

* In `guide.basil`, build strings like:

    * `guideNavHtml$` – the nested section/page nav.
    * `guideBodyHtml$` – either index or specific page body.
    * `pageTitle$`, `pageSlug$`, etc.

* Then call:

  ```basic
  PRINT RENDER$(READFILE$("views/guide/page.html"))
  ```

And in your template you use:

```html
<!-- views/layout.html, for example -->
<html>
<head>
  <title>{{ pageTitle$ }} – Basil Docs</title>
  @INCLUDE("partials/head.html")
</head>
<body>
  <header>
    <h1>Basil / Basic / Basic.JS Documentation</h1>
    <nav>
      <a href="/">Home</a>
      <a href="/guide">Guide</a>
      <a href="/reference">Reference</a>
    </nav>
  </header>

  <main class="layout">
    <aside class="sidebar">
      {{ guideNavHtml$ }}
    </aside>

    <section class="content">
      {{ guideBodyHtml$ }}
    </section>
  </main>

  @INCLUDE("partials/footer.html")
</body>
</html>
```

Then `views/guide/index.html` might simply be:

```html
@INCLUDE("layout.html")
```

and you let `guideBodyHtml$` contain the specific index page content for that request.

### 1.3 Guide index: DB queries

In `guide.basil`, for `/guide`:

* Load sections:

  ```sql
  SELECT id, slug, title, description, sort_order
  FROM guide_sections
  ORDER BY sort_order;
  ```

* Load pages:

  ```sql
  SELECT id, section_id, slug, title, abstract, position
  FROM guide_pages
  WHERE is_published = 1
  ORDER BY section_id, position;
  ```

Then construct:

* `guideNavHtml$` – nested `<ul>` of sections and pages.
* `guideBodyHtml$` – maybe a welcome message + list of beginner chapters (e.g. pages whose `difficulty='beginner'`).

You can generate HTML in Basil like:

```basic
guideNavHtml$ = "<ul>";

REM loop sections and pages; build list elements into guideNavHtml$

guideNavHtml$ = guideNavHtml$ + "</ul>";
```

Then set `pageTitle$ = "Guide"` and call `RENDER$(READFILE$("views/guide/index.html"))`.

### 1.4 Guide page detail

For `/guide/{slug}`:

* Load the page:

  ```sql
  SELECT p.*, s.title AS section_title
  FROM guide_pages p
  JOIN guide_sections s ON s.id = p.section_id
  WHERE p.slug = ? AND p.is_published = 1
  LIMIT 1;
  ```

* Build:

    * `pageTitle$ = p.title`.
    * `guideBodyHtml$` = some combination of:

        * An H1 with page title.
        * An optional small “Section: Getting Started” label.
        * The Markdown body (see below).

#### Markdown rendering

RENDER$ doesn’t do Markdown; it just interprets template logic and interpolation.

So for Phase 2’s “Markdown UX,” I’d keep it simple:

**Option A – client-side Markdown:**

* Store `body_md` in DB.

* Server side:

    * Wrap the raw Markdown in a `<textarea>` or `<div data-md="...">`.
    * Or just inject it as `<div id="doc-md">{{ pageBodyMd$ }}</div>` where `pageBodyMd$` is your raw Markdown.

* In the template, include `marked.js` (or similar) and a small script:

  ```js
  const el = document.getElementById("doc-md");
  if (el) {
    const md = el.textContent;
    el.innerHTML = marked.parse(md);
  }
  ```

This keeps Basil free of Markdown work in the short term and keeps all the actual view logic in HTML/CSS/JS + RENDER$.

**Option B – later:** Basil-side Markdown module that you call in `guide.basil` to pre-render `body_md` to HTML (`pageBodyHtml$`).

I’d do Option A first and move on to admin/search; Option B is a nice later upgrade.

---

## 2. Phase 2 – Admin + Markdown UX

Once the Guide and Reference are both DB-driven and templated, Phase 2 is:

* **Admin backend** for Guide + Reference.
* Cleaning up UX around Markdown editing/preview.

### 2.1 Admin routes

Use a separate namespace:

* `/admin/login` – sign in.
* `/admin/logout` – clear cookie.
* `/admin` – dashboard.
* `/admin/guide` – list/CRUD guide pages.
* `/admin/reference/keywords` – list/CRUD keywords.
* Later: `/admin/reference/examples`, `/admin/reference/categories`.

You already have `website.zip` with SQLite/cookies + `users.inc`; even though I can’t see it, it sounds like you’ve got patterns for:

* Creating sessions.
* Setting/reading cookies.
* Checking “current user.”

So for the new admin:

* Create `admin.basil` (or `admin_login.basil`, `admin_dashboard.basil`) that reuse those helpers from `cgi.inc`/`users.inc`.
* Wrap the admin UI in RENDER$ templates (`views/admin/*.html`), same pattern as front-end.

### 2.2 Admin for Guide

Minimum features:

* List all `guide_sections` + their pages.
* Click a page to edit:

    * Title
    * Section
    * Slug
    * Abstract
    * Body (Markdown)
    * Difficulty
    * Language filter (optional)
    * Position
    * is_published

UX suggestions:

* **Editor**: `<textarea>` for Markdown plus a “Preview” pane that uses the same JS markdown renderer as the public site.
* “Save” writes directly to `guide_pages`.
* “New page” form that lets you pick section/difficulty.

All of these pages can be RENDER$ templates (e.g. `views/admin/guide_edit.html`) that interpolate `formActionUrl$`, `pageTitle$`, etc., and use `@IF` blocks for conditional messaging.

### 2.3 Admin for Reference (keywords)

You don’t have to build the full beast in one shot. You can phase it:

**Step 1 (minimal):**

* `/admin/reference/keywords`:

    * Table with keyword, short_desc, languages, feature library, and edit link.

* `/admin/reference/keywords/edit?slug=XYZ`:

    * Form for:

        * keyword, slug
        * short_desc, long_desc_md (Markdown)
        * languages (multi-select or checkboxes)
        * feature library (select)
        * is_standard_lib
        * introduced/deprecated versions

**Step 2:**

* Add UI for:

    * Categories (multi-select).
    * “See Also” (search box where you type part of another keyword and click “Add”).
    * Attach existing examples (checkbox list).
    * Inline edit of code examples.

Again, keep HTML in `views/admin/reference_keywords_edit.html` and fill it via RENDER$ using globals set in your Basil code.

---

## 3. Phase 3 – Search + CSV

### 3.1 Search CGI

Create `cgi/search.basil` and route `/search` there.

**Behavior:**

* Reads `q$` from query string.
* Optional filters:

    * `scope` = `guide` | `reference` | `all` (default).
    * `lang` = `basil` | `basic` | `basicjs`.

**DB side:**

Use FULLTEXT indexes:

* On `keywords.short_desc` + `keywords.long_desc_md`.
* On `guide_pages.title` + `guide_pages.abstract` + `guide_pages.body_md`.

Example approach:

* For **reference** results:

  ```sql
  SELECT 'keyword' AS src,
         k.slug     AS slug,
         k.keyword  AS title,
         k.short_desc AS snippet,
         MATCH(k.short_desc, k.long_desc_md)
           AGAINST (? IN NATURAL LANGUAGE MODE) AS score
  FROM keywords k
  LEFT JOIN keyword_languages kl ON kl.keyword_id = k.id
  LEFT JOIN languages l ON l.id = kl.language_id
  WHERE MATCH(k.short_desc, k.long_desc_md)
      AGAINST (? IN NATURAL LANGUAGE MODE)
    AND (? IS NULL OR l.code = ?);
  ```

* For **guide** results:

  ```sql
  SELECT 'guide' AS src,
         g.slug   AS slug,
         g.title  AS title,
         g.abstract AS snippet,
         MATCH(g.title, g.abstract, g.body_md)
           AGAINST (? IN NATURAL LANGUAGE MODE) AS score
  FROM guide_pages g
  WHERE g.is_published = 1
    AND MATCH(g.title, g.abstract, g.body_md)
      AGAINST (? IN NATURAL LANGUAGE MODE);
  ```

Combine results in Basil, sort by `score`, then feed to a `views/search/results.html` template rendered via RENDER$.

### 3.2 CSV export/import (keywords)

**Export:**

* Route: `/admin/reference/keywords/export`.

* Query all keywords and flatten:

    * keyword
    * display_name
    * kind
    * short_desc
    * long_desc_md
    * languages (comma-separated codes)
    * categories (comma-separated slugs)
    * feature_library (code)
    * is_standard_lib
    * introduced_in_ver
    * deprecated_in_ver
    * see_also (comma-separated keyword names)

* Output `Content-Type: text/csv` and emit CSV lines.

**Import:**

* Route: `/admin/reference/keywords/import`.
* Upload CSV.
* For each row:

    * `SELECT` keyword by `keyword` or `slug`; if it exists, update; else insert.
    * For languages/categories/see-alsos:

        * Clear existing relations for that keyword, then insert new ones based on CSV.
        * Look up codes/slugs to IDs via `languages`/`categories` tables.

Design it so that:

* There’s a “Dry Run” checkbox to show changes without committing.
* The CSV format is stable enough to reuse for AI training data export, etc.

---

## 4. Concrete *next step* I’d recommend

Since Reference is already live and DB-backed, and RENDER$ is in place, the most natural next step is:

> **Implement DB-backed Guide with RENDER$ layout (Phase 1.5).**

Specifically:

1. Create `views/layout.html`, `views/guide/index.html`, `views/guide/page.html` as described.
2. Update `guide.basil` to:

    * Query `guide_sections` + `guide_pages`.
    * Build `guideNavHtml$` and `guideBodyHtml$` for:

        * `/guide` (index view).
        * `/guide/{slug}` (page detail).
    * Set globals like `pageTitle$`, `guideNavHtml$`, `guideBodyHtml$`.
    * `PRINT RENDER$(READFILE$("views/guide/index.html"))` or `"page.html"`.

If you’d like, I can write a Junie prompt tailored to your Basil caveats and your current includes that says:

* “Update `guide.basil` to use DB + RENDER$ with these specific function names and global variables,”
* Plus a first pass at the `views/guide/*.html` templates using Fred directives.

Or, if you’d rather, I can draft the actual Basil + HTML skeletons here for you to paste in and refine.
