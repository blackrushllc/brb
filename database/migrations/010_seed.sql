INSERT INTO languages (code, name, sort_order)
VALUES ('basic', 'Basic', 1),
       ('basil', 'Basil', 2),
       ('basicjs', 'Basic.JS', 3)
INSERT INTO feature_libraries (code, name, description)
VALUES ('standard', 'Standard Library', 'Core language / standard library.'),
       ('obj-audio', 'Audio / MIDI Module',
        'Audio / MIDI / DAW functions such as AUDIO_INPUTS$, AUDIO_OUTPUTS$, etc.'),
       ('obj-ai', 'AI Module', 'AI/LLM helpers and utilities.'),
       ('obj-sql', 'SQL Module', 'SQL client for MySQL and others.')
INSERT INTO categories (name, slug, description, sort_order)
VALUES ('Variables', 'variables', 'Variable declaration and assignment', 10),
       ('Flow Control', 'flow-control', 'IF, WHILE, SELECT CASE, loops', 20),
       ('File I/O and Filesystem', 'file-io', 'File and directory commands', 30),
       ('Logical Operators', 'logical-ops', 'Boolean operators and comparisons', 40),
       ('Audio', 'audio', 'Audio device management', 50),
       ('MIDI', 'midi', 'MIDI routing and devices', 60),
       ('Media', 'media', 'Media playback and recording', 70)
INSERT INTO categories (name, slug, description, sort_order)
VALUES ('Variables', 'variables', 'Variable declaration and assignment', 10),
       ('Flow Control', 'flow-control', 'IF, WHILE, SELECT CASE, loops', 20),
       ('File I/O and Filesystem', 'file-io', 'File and directory commands', 30),
       ('Logical Operators', 'logical-ops', 'Boolean operators and comparisons', 40),
       ('Audio', 'audio', 'Audio device management', 50),
       ('MIDI', 'midi', 'MIDI routing and devices', 60),
       ('Media', 'media', 'Media playback and recording', 70)
-- Example code (blocky)
INSERT INTO code_examples (title, style, body_md)
VALUES ('List audio inputs and outputs (blocky BASIC)',
        'blocky',
        '```basic
      REM List devices and defaults
      PRINTLN "== Outputs =="
      outs$[] = AUDIO_OUTPUTS$[]
      FOR i% = 0 TO LEN(outs$[]) - 1 BEGIN
        PRINT "  "; PRINT i%; PRINT ": "; PRINTLN outs$[](i%)
      END

      PRINTLN "== Inputs =="
      ins$[] = AUDIO_INPUTS$[]
      FOR i% = 0 TO LEN(ins$[]) - 1 BEGIN
        PRINT "  "; PRINT i%; PRINT ": "; PRINTLN ins$[](i%)
      END

      PRINT "Default rate: ";  PRINTLN AUDIO_DEFAULT_RATE%()
      PRINT "Default chans: "; PRINTLN AUDIO_DEFAULT_CHANS%()
      ```')

-- The same logic in curly style (rough sketch)
INSERT INTO code_examples (title, style, body_md)
VALUES ('List audio inputs and outputs (curly BASIC)',
        'curly',
        '```basil
      // List devices and defaults
      println "== Outputs =="
      let outs$[] = audio_outputs$()
      for (let i% = 0; i% < len(outs$); i%++) {
        print "  "; print i%; print ": "; println outs$[i%]
      }

      println "== Inputs =="
      let ins$[] = audio_inputs$()
      for (let i% = 0; i% < len(ins$); i%++) {
        print "  "; print i%; print ": "; println ins$[i%]
      }

      print "Default rate: ";  println audio_default_rate%()
      print "Default chans: "; println audio_default_chans%()
      ```')
-- AUDIO_INPUTS$
INSERT INTO keywords (keyword, slug, display_name, kind,
                      short_desc, long_desc_md,
                      feature_library_id, is_standard_lib, introduced_in_ver)
VALUES ('AUDIO_INPUTS$',
        'audio_inputs',
        'AUDIO_INPUTS$',
        'function',
        'Returns an array of audio input device names.',
        'Returns a string array of available audio input devices on this system.',
        (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
        0,
        'Basil 1.x')

-- AUDIO_OUTPUTS$
INSERT INTO keywords (keyword, slug, display_name, kind,
                      short_desc, long_desc_md,
                      feature_library_id, is_standard_lib, introduced_in_ver)
VALUES ('AUDIO_OUTPUTS$',
        'audio_outputs',
        'AUDIO_OUTPUTS$',
        'function',
        'Returns an array of audio output device names.',
        'Returns a string array of available audio output devices on this system.',
        (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
        0,
        'Basil 1.x')

-- AUDIO_DEFAULT_RATE%
INSERT INTO keywords (keyword, slug, display_name, kind,
                      short_desc, long_desc_md,
                      feature_library_id, is_standard_lib, introduced_in_ver)
VALUES ('AUDIO_DEFAULT_RATE%',
        'audio_default_rate',
        'AUDIO_DEFAULT_RATE%',
        'function',
        'Returns the default audio sample rate.',
        'Returns the default sample rate (Hz) for the selected audio device.',
        (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
        0,
        'Basil 1.x')

-- AUDIO_DEFAULT_CHANS%
INSERT INTO keywords (keyword, slug, display_name, kind,
                      short_desc, long_desc_md,
                      feature_library_id, is_standard_lib, introduced_in_ver)
VALUES ('AUDIO_DEFAULT_CHANS%',
        'audio_default_chans',
        'AUDIO_DEFAULT_CHANS%',
        'function',
        'Returns the default audio channel count.',
        'Returns the default channel count (e.g. 2 for stereo) for the selected audio device.',
        (SELECT id FROM feature_libraries WHERE code = 'obj-audio'),
        0,
        'Basil 1.x')
-- Assign languages (Basil only)
INSERT INTO keyword_languages (keyword_id, language_id)
SELECT k.id, l.id
FROM keywords k,
     languages l
WHERE l.code = 'basil'
  AND k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')

-- Assign categories Audio/MIDI/Media
INSERT INTO keyword_categories (keyword_id, category_id)
SELECT k.id, c.id
FROM keywords k,
     categories c
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND c.slug IN ('audio', 'midi', 'media')

-- Reuse the same examples for all of them
INSERT INTO keyword_examples (keyword_id, example_id, is_primary)
SELECT k.id, e.id, 1
FROM keywords k,
     code_examples e
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND e.id = 1; -- blocky example

INSERT INTO keyword_examples (keyword_id, example_id, is_primary)
SELECT k.id, e.id, 0
FROM keywords k,
     code_examples e
WHERE k.keyword IN ('AUDIO_INPUTS$', 'AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
  AND e.id = 2
-- curly example

-- See Also relationships
INSERT INTO keyword_relations (keyword_id, related_keyword_id, relation_type)
SELECT k1.id, k2.id, 'see_also'
FROM keywords k1
         JOIN keywords k2
              ON k2.keyword IN ('AUDIO_OUTPUTS$', 'AUDIO_DEFAULT_RATE%', 'AUDIO_DEFAULT_CHANS%')
WHERE k1.keyword = 'AUDIO_INPUTS$'

-- Symmetric or additional see-also can be added similarly
-- Guide sections
INSERT INTO guide_sections (slug, title, description, sort_order)
VALUES ('getting-started', 'Getting Started', 'Install Basil, Basic, and Basic.JS and run your first program.', 10),
       ('language-basics', 'Language Basics', 'Variables, expressions, and control flow.', 20),
       ('objects-classes', 'Classes and Objects', 'Object-oriented programming in Basil.', 30),
       ('exceptions', 'Exceptions and Error Handling', 'TRY/CATCH/FINALLY and RAISE.', 40),
       ('web-development', 'Web Site Development', 'CGI, HTTP, HTML output, and web apps.', 50),
       ('aws', 'Using Amazon AWS', 'AWS integration modules.', 60),
       ('ai', 'AI', 'Using AI helpers and obj-ai.', 70),
       ('compiler', 'Compiler Guide', 'Using the Basil compiler.', 80),
       ('encryption', 'Encryption', 'Crypto and security.', 90),
       ('smtp', 'Sending Email with SMTP', 'Using SMTP libraries.', 100)

-- Example "Hello World" beginner page
INSERT INTO guide_pages (section_id, parent_id, slug, title, abstract, body_md,
                         difficulty, language_filter, position, is_published)
VALUES ((SELECT id FROM guide_sections WHERE slug = 'getting-started'),
        NULL,
        'hello-world',
        'Hello World',
        'Your very first Basil / Basic / Basic.JS program.',
        '## Hello World

This is your first program in Basil.

```basic
REM Hello World in Basil
PRINTLN "Hello, world!"
```
',
        'beginner',
        'NULL',
        10,
        1)
