-- 005_guide.sql

CREATE TABLE guide_sections
(
    id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    slug        VARCHAR(128) NOT NULL UNIQUE, -- 'getting-started', 'aws'
    title       VARCHAR(255) NOT NULL,
    description TEXT         NULL,
    sort_order  INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4

CREATE TABLE guide_pages
(
    id              INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    section_id      INT UNSIGNED NOT NULL,
    parent_id       INT UNSIGNED NULL, -- for nesting if needed
    slug            VARCHAR(128) NOT NULL UNIQUE,
    title           VARCHAR(255) NOT NULL,
    abstract        TEXT         NULL, -- short intro / teaser for search
    body_md         MEDIUMTEXT   NOT NULL,
    difficulty      ENUM ('beginner','intermediate','advanced','mixed')
                                 NOT NULL DEFAULT 'beginner',
    language_filter VARCHAR(64)  NULL,
    -- e.g. 'basil', 'basic', 'basil,basicjs', or NULL = all
    position        INT UNSIGNED NOT NULL DEFAULT 0,
    is_published    TINYINT(1)   NOT NULL DEFAULT 0,
    created_at      DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at      DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP,
    CONSTRAINT fk_guide_pages_section
        FOREIGN KEY (section_id) REFERENCES guide_sections (id) ON DELETE CASCADE,
    CONSTRAINT fk_guide_pages_parent
        FOREIGN KEY (parent_id) REFERENCES guide_pages (id) ON DELETE SET NULL,
    FULLTEXT INDEX ft_guide_text (title, abstract, body_md)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
