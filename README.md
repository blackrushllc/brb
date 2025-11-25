Here’s a first-pass *architecture + schema + concrete next steps* that should be enough to actually start building this in Basil/CGI.

---

## 1. Big picture: what we’re building

**Tech stack**

* **Frontend:** Plain HTML + CSS + JS (no framework required; we can add a light JS helper layer).
* **Backend:** Basil CGI (following `examples/website` pattern) talking to **MySQL** using Basil SQL/ORM.
* **Content storage:**

    * **Guide:** Wiki-style chapters stored as **Markdown** in MySQL.
    * **Reference:** Keywords, categories, examples, etc. all stored relationally in MySQL.

**Top-level site structure**

* `/` — Landing page (short “What is Basil / Basic / Basic.JS” + big buttons).
* `/guide` — Guide wiki.
* `/reference` — Language reference.
* `/search` — Cross-site search.
* `/admin` — Admin backend (CRUD, CSV import/export).

---

## 2. Data model (MySQL schema)

I’ll split this into:

1. Core lookup tables (languages, feature libs, categories).
2. **Reference** tables (keywords, examples, relations).
3. **Guide** tables (wiki chapters/pages).
4. Admin users.

You can drop all of these into migration files like `001_core.sql`, `002_reference.sql`, etc.

### 2.1 Core lookups

```sql
-- 001_core.sql

CREATE TABLE languages (
  id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  code        VARCHAR(32) NOT NULL UNIQUE,   -- 'basic', 'basil', 'basicjs'
  name        VARCHAR(64) NOT NULL,          -- 'Basic', 'Basil', 'Basic.JS'
  sort_order  INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE feature_libraries (
  id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  code        VARCHAR(64) NOT NULL UNIQUE,   -- 'standard', 'obj-audio', 'obj-ai'
  name        VARCHAR(128) NOT NULL,
  description TEXT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE categories (
  id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  name        VARCHAR(128) NOT NULL,
  slug        VARCHAR(128) NOT NULL UNIQUE,  -- 'audio', 'midi', 'variables'
  description TEXT NULL,
  sort_order  INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

### 2.2 Reference: keywords, examples, relations

```sql
-- 002_reference_keywords.sql

CREATE TABLE keywords (
  id                  INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  keyword             VARCHAR(64) NOT NULL,          -- AUDIO_INPUTS$, LET, +
  slug                VARCHAR(128) NOT NULL UNIQUE,  -- audio_inputs, let, plus
  display_name        VARCHAR(128) NULL,             -- optional pretty name
  kind                VARCHAR(32) NOT NULL DEFAULT 'keyword',
      -- 'keyword', 'function', 'operator', 'symbol', etc.
  short_desc          VARCHAR(255) NOT NULL,
  long_desc_md        MEDIUMTEXT NULL,               -- full Markdown description
  feature_library_id  INT UNSIGNED NULL,
  is_standard_lib     TINYINT(1) NOT NULL DEFAULT 1,
  introduced_in_ver   VARCHAR(32) NULL,              -- e.g. 'Basil 1.2'
  deprecated_in_ver   VARCHAR(32) NULL,
  created_at          DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at          DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
                        ON UPDATE CURRENT_TIMESTAMP,
  CONSTRAINT fk_keywords_feature_lib
    FOREIGN KEY (feature_library_id)
    REFERENCES feature_libraries(id)
    ON DELETE SET NULL,
  INDEX idx_keywords_keyword (keyword),
  FULLTEXT INDEX ft_keywords_text (short_desc, long_desc_md)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE keyword_languages (
  keyword_id   INT UNSIGNED NOT NULL,
  language_id  INT UNSIGNED NOT NULL,
  PRIMARY KEY (keyword_id, language_id),
  CONSTRAINT fk_kw_lang_keyword
    FOREIGN KEY (keyword_id) REFERENCES keywords(id) ON DELETE CASCADE,
  CONSTRAINT fk_kw_lang_language
    FOREIGN KEY (language_id) REFERENCES languages(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE keyword_categories (
  keyword_id   INT UNSIGNED NOT NULL,
  category_id  INT UNSIGNED NOT NULL,
  PRIMARY KEY (keyword_id, category_id),
  CONSTRAINT fk_kw_cat_keyword
    FOREIGN KEY (keyword_id) REFERENCES keywords(id) ON DELETE CASCADE,
  CONSTRAINT fk_kw_cat_category
    FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

**Code examples** (reusable across multiple keywords, with both blocky and curly styles):

```sql
-- 003_reference_examples.sql

CREATE TABLE code_examples (
  id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  title       VARCHAR(255) NOT NULL,
  style       ENUM('blocky', 'curly') NOT NULL,
  body_md     MEDIUMTEXT NOT NULL,         -- Markdown-wrapped code block
  notes       TEXT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE keyword_examples (
  keyword_id  INT UNSIGNED NOT NULL,
  example_id  INT UNSIGNED NOT NULL,
  is_primary  TINYINT(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (keyword_id, example_id),
  CONSTRAINT fk_kw_ex_keyword
    FOREIGN KEY (keyword_id) REFERENCES keywords(id) ON DELETE CASCADE,
  CONSTRAINT fk_kw_ex_example
    FOREIGN KEY (example_id) REFERENCES code_examples(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

**See-also / related relations:**

```sql
-- 004_reference_relations.sql

CREATE TABLE keyword_relations (
  keyword_id          INT UNSIGNED NOT NULL,
  related_keyword_id  INT UNSIGNED NOT NULL,
  relation_type       VARCHAR(32) NOT NULL DEFAULT 'see_also',
  PRIMARY KEY (keyword_id, related_keyword_id, relation_type),
  CONSTRAINT fk_kw_rel_keyword
    FOREIGN KEY (keyword_id) REFERENCES keywords(id) ON DELETE CASCADE,
  CONSTRAINT fk_kw_rel_related
    FOREIGN KEY (related_keyword_id) REFERENCES keywords(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

This lets you:

* Show “See also …” for each keyword.
* Reuse the same example across multiple keywords.

### 2.3 Guide (Wiki) tables

```sql
-- 005_guide.sql

CREATE TABLE guide_sections (
  id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  slug        VARCHAR(128) NOT NULL UNIQUE,    -- 'getting-started', 'aws'
  title       VARCHAR(255) NOT NULL,
  description TEXT NULL,
  sort_order  INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE guide_pages (
  id              INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  section_id      INT UNSIGNED NOT NULL,
  parent_id       INT UNSIGNED NULL,  -- for nesting if needed
  slug            VARCHAR(128) NOT NULL UNIQUE,
  title           VARCHAR(255) NOT NULL,
  abstract        TEXT NULL,          -- short intro / teaser for search
  body_md         MEDIUMTEXT NOT NULL,
  difficulty      ENUM('beginner','intermediate','advanced','mixed')
                    NOT NULL DEFAULT 'beginner',
  language_filter VARCHAR(64) NULL,
     -- e.g. 'basil', 'basic', 'basil,basicjs', or NULL = all
  position        INT UNSIGNED NOT NULL DEFAULT 0,
  is_published    TINYINT(1) NOT NULL DEFAULT 0,
  created_at      DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at      DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
                    ON UPDATE CURRENT_TIMESTAMP,
  CONSTRAINT fk_guide_pages_section
    FOREIGN KEY (section_id) REFERENCES guide_sections(id) ON DELETE CASCADE,
  CONSTRAINT fk_guide_pages_parent
    FOREIGN KEY (parent_id) REFERENCES guide_pages(id) ON DELETE SET NULL,
  FULLTEXT INDEX ft_guide_text (title, abstract, body_md)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

This lets you:

* Build a “chapters” tree for the Guide.
* Store Markdown for content.
* Filter / tag pages by target language(s).

### 2.4 Admin users

```sql
-- 006_admin.sql

CREATE TABLE admin_users (
  id             INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
  email          VARCHAR(191) NOT NULL UNIQUE,
  password_hash  VARCHAR(255) NOT NULL,
  display_name   VARCHAR(128) NOT NULL,
  is_superadmin  TINYINT(1) NOT NULL DEFAULT 0,
  created_at     DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  updated_at     DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
                    ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

(You can implement login/session using Basil CGI + cookies later.)

---

## 3. Sample data (seed SQL)

You can put this in `010_seed.sql` for convenience.

### 3.1 Languages

```sql
INSERT INTO languages (code, name, sort_order) VALUES
  ('basic',   'Basic',     1),
  ('basil',   'Basil',     2),
  ('basicjs', 'Basic.JS',  3);
```

### 3.2 Feature libraries

```sql
INSERT INTO feature_libraries (code, name, description) VALUES
  ('standard',   'Standard Library', 'Core language / standard library.'),
  ('obj-audio',  'Audio / MIDI Module',
     'Audio / MIDI / DAW functions such as AUDIO_INPUTS$, AUDIO_OUTPUTS$, etc.'),
  ('obj-ai',     'AI Module', 'AI/LLM helpers and utilities.'),
  ('obj-sql',    'SQL Module', 'SQL client for MySQL and others.');
```

### 3.3 Categories

```sql
INSERT INTO categories (name, slug, description, sort_order) VALUES
  ('Variables',              'variables',      'Variable declaration and assignment', 10),
  ('Flow Control',           'flow-control',   'IF, WHILE, SELECT CASE, loops',       20),
  ('File I/O and Filesystem','file-io',        'File and directory commands',         30),
  ('Logical Operators',      'logical-ops',    'Boolean operators and comparisons',   40),
  ('Audio',                  'audio',          'Audio device management',             50),
  ('MIDI',                   'midi',           'MIDI routing and devices',            60),
  ('Media',                  'media',          'Media playback and recording',        70);
```

### 3.4 AUDIO_* keyword examples

````sql
-- Example code (blocky)
INSERT INTO code_examples (title, style, body_md) VALUES
(
  'List audio inputs and outputs (blocky BASIC)',
  'blocky',
  '```basic
REM List devices and defaults;
PRINTLN "== Outputs ==";
outs$[] = AUDIO_OUTPUTS$[];
FOR i% = 0 TO LEN(outs$[]) - 1 BEGIN
  PRINT "  "; PRINT i%; PRINT ": "; PRINTLN outs$[](i%);
END

PRINTLN "== Inputs ==";
ins$[] = AUDIO_INPUTS$[];
FOR i% = 0 TO LEN(ins$[]) - 1 BEGIN
  PRINT "  "; PRINT i%; PRINT ": "; PRINTLN ins$[](i%);
END

PRINT "Default rate: ";  PRINTLN AUDIO_DEFAULT_RATE%();
PRINT "Default chans: "; PRINTLN AUDIO_DEFAULT_CHANS%();
```'
);

-- The same logic in curly style (rough sketch)
INSERT INTO code_examples (title, style, body_md) VALUES
(
  'List audio inputs and outputs (curly BASIC)',
  'curly',
  '```basil
// List devices and defaults
println "== Outputs ==";
let outs$[] = audio_outputs$();
for (let i% = 0; i% < len(outs$); i%++) {
  print "  "; print i%; print ": "; println outs$[i%];
}

println "== Inputs ==";
let ins$[] = audio_inputs$();
for (let i% = 0; i% < len(ins$); i%++) {
  print "  "; print i%; print ": "; println ins$[i%];
}

print "Default rate: ";  println audio_default_rate%();
print "Default chans: "; println audio_default_chans%();
```'
);
````

Assume these got IDs `1` (blocky) and `2` (curly).

Now seed **AUDIO_INPUTS$** and friends:

```sql
-- AUDIO_INPUTS$
INSERT INTO keywords (
  keyword, slug, display_name, kind,
  short_desc, long_desc_md,
  feature_library_id, is_standard_lib, introduced_in_ver
) VALUES (
  'AUDIO_INPUTS$',
  'audio_inputs',
  'AUDIO_INPUTS$',
  'function',
  'Returns an array of audio input device names.',
  'Returns a string array of available audio input devices on this system.',
  (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
  0,
  'Basil 1.x'
);

-- AUDIO_OUTPUTS$
INSERT INTO keywords (
  keyword, slug, display_name, kind,
  short_desc, long_desc_md,
  feature_library_id, is_standard_lib, introduced_in_ver
) VALUES (
  'AUDIO_OUTPUTS$',
  'audio_outputs',
  'AUDIO_OUTPUTS$',
  'function',
  'Returns an array of audio output device names.',
  'Returns a string array of available audio output devices on this system.',
  (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
  0,
  'Basil 1.x'
);

-- AUDIO_DEFAULT_RATE%
INSERT INTO keywords (
  keyword, slug, display_name, kind,
  short_desc, long_desc_md,
  feature_library_id, is_standard_lib, introduced_in_ver
) VALUES (
  'AUDIO_DEFAULT_RATE%',
  'audio_default_rate',
  'AUDIO_DEFAULT_RATE%',
  'function',
  'Returns the default audio sample rate.',
  'Returns the default sample rate (Hz) for the selected audio device.',
  (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
  0,
  'Basil 1.x'
);

-- AUDIO_DEFAULT_CHANS%
INSERT INTO keywords (
  keyword, slug, display_name, kind,
  short_desc, long_desc_md,
  feature_library_id, is_standard_lib, introduced_in_ver
) VALUES (
  'AUDIO_DEFAULT_CHANS%',
  'audio_default_chans',
  'AUDIO_DEFAULT_CHANS%',
  'function',
  'Returns the default audio channel count.',
  'Returns the default channel count (e.g. 2 for stereo) for the selected audio device.',
  (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
  0,
  'Basil 1.x'
);
```

Make them **Basil only** and assign categories + examples:

```sql
-- Assign languages (Basil only)
INSERT INTO keyword_languages (keyword_id, language_id)
SELECT k.id, l.id
FROM keywords k, languages l
WHERE l.code = 'basil'
  AND k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%');

-- Assign categories Audio/MIDI/Media
INSERT INTO keyword_categories (keyword_id, category_id)
SELECT k.id, c.id
FROM keywords k, categories c
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND c.slug IN ('audio', 'midi', 'media');

-- Reuse the same examples for all of them
INSERT INTO keyword_examples (keyword_id, example_id, is_primary)
SELECT k.id, e.id, 1
FROM keywords k, code_examples e
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND e.id = 1;  -- blocky example

INSERT INTO keyword_examples (keyword_id, example_id, is_primary)
SELECT k.id, e.id, 0
FROM keywords k, code_examples e
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND e.id = 2;  -- curly example

-- See Also relationships
INSERT INTO keyword_relations (keyword_id, related_keyword_id, relation_type)
SELECT k1.id, k2.id, 'see_also'
FROM keywords k1
JOIN keywords k2
  ON k2.keyword IN ('AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
WHERE k1.keyword = 'AUDIO_INPUTS$';

-- Symmetric or additional see-also can be added similarly
```

### 3.5 Guide sections/pages sample

````sql
-- Guide sections
INSERT INTO guide_sections (slug, title, description, sort_order) VALUES
  ('getting-started', 'Getting Started', 'Install Basil, Basic, and Basic.JS and run your first program.', 10),
  ('language-basics', 'Language Basics', 'Variables, expressions, and control flow.', 20),
  ('objects-classes', 'Classes and Objects', 'Object-oriented programming in Basil.', 30),
  ('exceptions', 'Exceptions and Error Handling', 'TRY/CATCH/FINALLY and RAISE.', 40),
  ('web-development', 'Web Site Development', 'CGI, HTTP, HTML output, and web apps.', 50),
  ('aws', 'Using Amazon AWS', 'AWS integration modules.', 60),
  ('ai', 'AI', 'Using AI helpers and obj-ai.', 70),
  ('compiler', 'Compiler Guide', 'Using the Basil compiler.', 80),
  ('encryption', 'Encryption', 'Crypto and security.', 90),
  ('smtp', 'Sending Email with SMTP', 'Using SMTP libraries.', 100);

-- Example "Hello World" beginner page
INSERT INTO guide_pages (
  section_id, parent_id, slug, title, abstract, body_md,
  difficulty, language_filter, position, is_published
) VALUES (
  (SELECT id FROM guide_sections WHERE slug = 'getting-started'),
  NULL,
  'hello-world',
  'Hello World',
  'Your very first Basil / Basic / Basic.JS program.',
  '## Hello World

This is your first program in Basil.

```basic
REM Hello World in Basil
PRINTLN "Hello, world!";
````

In Basic.JS, the same program might look like:

```javascript
print("Hello, world!");
```

We''ll explain how to run these programs in the next section.',
'beginner',
NULL,  -- visible for all languages
10,
1
);

````

---

## 4. How the **Reference UI** maps to this schema

### 4.1 Alphabetical index

- To generate “A, B, C, …” dynamically:

```sql
SELECT DISTINCT UPPER(LEFT(keyword, 1)) AS initial
FROM keywords
ORDER BY initial;
````

* To get all keywords under a given letter:

```sql
SELECT *
FROM keywords
WHERE UPPER(LEFT(keyword, 1)) = 'A'
ORDER BY keyword;
```

* For operators / symbols (e.g. `+`, `-`, `==`):

    * Use `kind='operator'` and maybe put them under an “Operators & Symbols” group, or assign a fake “letter” like `'#'` and special-case in the UI.

### 4.2 Category index

* To get the list of categories (only ones with at least one keyword):

```sql
SELECT c.*
FROM categories c
JOIN keyword_categories kc ON kc.category_id = c.id
GROUP BY c.id
ORDER BY c.sort_order, c.name;
```

* To get all keywords in a category (for `/reference/category/{slug}`):

```sql
SELECT k.*
FROM keywords k
JOIN keyword_categories kc ON kc.keyword_id = k.id
JOIN categories c ON c.id = kc.category_id
WHERE c.slug = 'audio'
ORDER BY k.keyword;
```

### 4.3 Keyword detail page

For `/reference/keyword/{slug}` you can load:

* The keyword itself (`keywords`).
* Its languages (`keyword_languages` + `languages`).
* Its categories (`keyword_categories` + `categories`).
* Its examples (`keyword_examples` + `code_examples`).
* Its see-also list (`keyword_relations` + `keywords` again).

---

## 5. How the **Guide (Wiki)** maps to the schema

* Side navigation shows sections and their published pages:

```sql
SELECT s.id, s.slug, s.title,
       p.id AS page_id, p.slug AS page_slug, p.title AS page_title
FROM guide_sections s
LEFT JOIN guide_pages p
  ON p.section_id = s.id AND p.is_published = 1
ORDER BY s.sort_order, p.position;
```

* Each page page at `/guide/{slug}`:

```sql
SELECT *
FROM guide_pages
WHERE slug = :slug AND is_published = 1;
```

* You store Markdown in `body_md`, and then:

    * **Phase 1:** Use a client-side JS Markdown renderer (e.g. `marked.js`) to render on the fly. Basil just outputs the raw Markdown into a `<div data-markdown="...">` or `<textarea>`.

    * **Phase 2:** Add a Basil markdown renderer (either a small native mod or some “call out to external program” approach) and store the rendered HTML in a cache column if you like.

---

## 6. Search design

**Basic plan:**

* Use MySQL FULLTEXT on:

    * `keywords.short_desc`, `keywords.long_desc_md`.
    * `guide_pages.title`, `guide_pages.abstract`, `guide_pages.body_md`.

Example query for “global search” with optional language filter:

```sql
-- Keyword hits
SELECT 'keyword' AS src,
       k.slug     AS slug,
       k.keyword  AS title,
       k.short_desc AS snippet,
       MATCH(k.short_desc, k.long_desc_md) AGAINST (:q IN NATURAL LANGUAGE MODE) AS score
FROM keywords k
LEFT JOIN keyword_languages kl ON kl.keyword_id = k.id
LEFT JOIN languages l ON l.id = kl.language_id
WHERE MATCH(k.short_desc, k.long_desc_md) AGAINST (:q IN NATURAL LANGUAGE MODE)
  AND (:lang IS NULL OR l.code = :lang)

UNION ALL

-- Guide hits
SELECT 'guide' AS src,
       g.slug   AS slug,
       g.title  AS title,
       g.abstract AS snippet,
       MATCH(g.title, g.abstract, g.body_md) AGAINST (:q IN NATURAL LANGUAGE MODE) AS score
FROM guide_pages g
WHERE g.is_published = 1
  AND MATCH(g.title, g.abstract, g.body_md) AGAINST (:q IN NATURAL LANGUAGE MODE)
  AND (:lang IS NULL OR g.language_filter IS NULL OR FIND_IN_SET(:lang, g.language_filter))
ORDER BY score DESC
LIMIT 50;
```

The UI can let users choose:

* Scope: Guide / Reference / Both.
* Language filter: Basil / Basic / Basic.JS.

---

## 7. CSV import/export strategy

### 7.1 Export

For export, start with **one CSV for keywords** (flat-ish), then later add separate CSVs for relations if needed.

Example columns for `keywords.csv`:

* `keyword`
* `display_name`
* `kind`
* `short_desc`
* `long_desc_md`
* `languages` (comma-separated codes: `basil,basicjs`)
* `categories` (comma-separated slugs: `audio,midi,media`)
* `feature_library` (`standard`, `obj-audio`, etc.)
* `is_standard_lib` (`1` or `0`)
* `introduced_in_ver`
* `deprecated_in_ver`
* `see_also` (comma-separated keyword names: `AUDIO_OUTPUTS$,AUDIO_DEFAULT_RATE%`)

Your Basil admin CGI can:

* `SELECT` from `keywords` and join through categories/languages/relations.
* Flatten into CSV lines.
* Send `Content-Type: text/csv` with `Content-Disposition: attachment`.

### 7.2 Import

When importing:

* For each row, look up existing keyword by `keyword` or `slug`.
* If not found, **insert** a new keyword.
* If found, **update** its fields.
* For languages, categories, and see-alsos:

    * Clear current relations, then re-insert from CSV.
    * For see-alsos, you may want to insert only one direction; or, if you want symmetric relationships, insert both ways.

You can implement this in Basil/ORM as an `/admin/keywords/import` endpoint that:

* Accepts a file upload.
* Parses CSV in Basil.
* Runs inside a transaction per file.

---

## 8. Basil/CGI code layout & implementation plan

### 8.1 Project layout

One possible structure:

```text
cgi/
  index.basil           # front controller / router
  guide.basil           # /guide and guide page rendering
  reference.basil       # /reference and keyword pages
  search.basil          # search endpoint
  admin/
    login.basil
    dashboard.basil
    guide_pages.basil
    keywords.basil
    csv_import.basil
lib/
  db.basil              # open MySQL connection, helpers
  orm.basil             # wrappers around Basil ORM if you want
  markdown.basil        # (later) markdown render wrapper
  templates.basil       # simple HTML templating helpers
templates/
  layout.html
  guide/
    index.html
    page.html
  reference/
    index.html
    keyword.html
  admin/
    layout.html
    guide_form.html
    keyword_form.html
```

**Routing idea:** `index.basil` examines `PATH_INFO`:

* `/guide` → call `render_guide_index()`.
* `/guide/{slug}` → call `render_guide_page(slug)`.
* `/reference` → call `render_reference_index()`.
* `/reference/alpha/{letter}` → A-Z list.
* `/reference/category/{slug}` → category list.
* `/reference/keyword/{slug}` → detail page.
* `/search` → search handler.

### 8.2 DB access via Basil

Using the Basil SQL/ORM guides, you can:

* Create a reusable `get_db_connection()` function in `lib/db.basil`.
* In each CGI script, call:

```basic
REM pseudocode-ish Basil
LET db@ = DB_CONNECT_MYSQL$("hostname", "user", "pass", "basil_docs_db");
```

* Then use either:

    * ORM-style models (classes that map to tables), or
    * Raw SQL queries for now, wrapped in small helper functions.

For performance, you can use connection pooling if Basil’s SQL module supports it; otherwise a single connection per CGI request is fine to start.

### 8.3 Markdown rendering

**Phase 1 (simple):**

* Store Markdown in DB.
* Basil outputs it into HTML like:

```html
<div class="doc" data-markdown="...escaped markdown here..."></div>
```

* On the frontend, include a JS Markdown library (e.g. `marked.js`) and run:

```js
document.querySelectorAll('[data-markdown]').forEach(el => {
  const md = el.getAttribute('data-markdown');
  el.innerHTML = marked.parse(md);
});
```

This keeps Basil’s backend simple while still giving you Markdown storage.

**Phase 2:**

* Either:

    * Add a small Basil module that wraps a Rust Markdown library.
    * Or call out to a CLI and cache HTML.

---

## 9. Admin UX (minimum viable)

Start small and iterative:

1. **Login** page:

    * Check `admin_users`.
    * Store session token in cookie.
2. **Guide admin:**

    * List pages by section.
    * Create/edit page form with:

        * Title, section, difficulty, language filter, abstract, body_md, position, is_published.
3. **Keyword admin:**

    * List keywords with filters by language, category, feature lib.
    * Create/edit keyword form:

        * Core fields.
        * Multi-select for categories and languages.
        * Dropdown for feature library.
        * Multi-select for “See Also” (AJAX search on keyword name).
        * Section for attaching existing examples (with checkboxes for primary) and editing example body_md.
4. **CSV import/export:**

    * Buttons:

        * “Export all keywords (CSV)”.
        * “Import CSV (update existing / create new)”.

You don’t need fancy UI to start – just clean HTML forms and a bit of JS for multi-select and search.

---

## 10. Suggested implementation phases

Here’s a realistic sequence that keeps you shipping value early:

### Phase 1 – Foundations

* Create the MySQL database and run all migrations.
* Seed:

    * `languages`, `feature_libraries`, `categories`.
    * A handful of keywords (e.g. `LET`, `DIM`, `PRINTLN`, the AUDIO_* family).
    * A handful of guide pages (`Hello World`, `Variables`, `Loops`).
* Build a minimal Basil CGI front controller + db connection helper.
* Implement **read-only**:

    * `/guide` + `/guide/{slug}`.
    * `/reference` index with:

        * Dynamic A–Z listing.
        * Dynamic category listing.
    * `/reference/keyword/{slug}` detail page (with examples and see-also).

### Phase 2 – Admin + Markdown UX

* Implement admin login + sessions.
* Add CRUD for:

    * Guide pages.
    * Keywords (basic fields + languages + categories).
* Wire in Markdown rendering on the frontend via JS so you can happily edit Markdown in the admin and see rendered HTML.
* Add “Copy to Clipboard” buttons for example code using JS (`navigator.clipboard.writeText`).

### Phase 3 – Search + CSV

* Implement `/search` with FULLTEXT queries as above.
* Add search options:

    * scope (Guide / Reference / Both).
    * language filter (Basil / Basic / Basic.JS).
* Implement CSV export for keywords.
* Implement CSV import with:

    * Dry-run mode (show what would change).
    * Real import mode.

### Phase 4 – Polishing & Basic.JS integration

* Add nicer UI (collapsible sidebar, sticky navigation, dark mode).
* Integrate a Basic.JS terminal component:

    * Add “Run in Browser” button on examples where language includes `basicjs`.
    * Reuse your YoBASIC runtime pattern.
* Consider adding:

    * Version info badges for each keyword (Basil / Basic / Basic.JS).
    * Feature library badges (“Standard”, “obj-audio”, etc.).

---

If you’d like, next step I can:

* Sketch the **actual Basil CGI skeleton** for `index.basil` + `reference.basil` (with real PRINTLN of headers and routing).
* Or draft the **CSV layout spec** and helper functions in pseudocode Basil for import/export.
