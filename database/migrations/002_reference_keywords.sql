-- 002_reference_keywords.sql

CREATE TABLE keywords
(
    id                 INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    keyword            VARCHAR(64)  NOT NULL,        -- AUDIO_INPUTS$, LET, +
    slug               VARCHAR(128) NOT NULL UNIQUE, -- audio_inputs, let, plus
    display_name       VARCHAR(128) NULL,            -- optional pretty name
    kind               VARCHAR(32)  NOT NULL DEFAULT 'keyword',
    -- 'keyword', 'function', 'operator', 'symbol', etc.
    short_desc         VARCHAR(255) NOT NULL,
    long_desc_md       MEDIUMTEXT   NULL,            -- full Markdown description
    feature_library_id INT UNSIGNED NULL,
    is_standard_lib    TINYINT(1)   NOT NULL DEFAULT 1,
    introduced_in_ver  VARCHAR(32)  NULL,            -- e.g. 'Basil 1.2'
    deprecated_in_ver  VARCHAR(32)  NULL,
    created_at         DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at         DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP,
    CONSTRAINT fk_keywords_feature_lib
        FOREIGN KEY (feature_library_id)
            REFERENCES feature_libraries (id)
            ON DELETE SET NULL,
    INDEX idx_keywords_keyword (keyword),
    FULLTEXT INDEX ft_keywords_text (short_desc, long_desc_md)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4

CREATE TABLE keyword_languages
(
    keyword_id  INT UNSIGNED NOT NULL,
    language_id INT UNSIGNED NOT NULL,
    PRIMARY KEY (keyword_id, language_id),
    CONSTRAINT fk_kw_lang_keyword
        FOREIGN KEY (keyword_id) REFERENCES keywords (id) ON DELETE CASCADE,
    CONSTRAINT fk_kw_lang_language
        FOREIGN KEY (language_id) REFERENCES languages (id) ON DELETE CASCADE
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4

CREATE TABLE keyword_categories
(
    keyword_id  INT UNSIGNED NOT NULL,
    category_id INT UNSIGNED NOT NULL,
    PRIMARY KEY (keyword_id, category_id),
    CONSTRAINT fk_kw_cat_keyword
        FOREIGN KEY (keyword_id) REFERENCES keywords (id) ON DELETE CASCADE,
    CONSTRAINT fk_kw_cat_category
        FOREIGN KEY (category_id) REFERENCES categories (id) ON DELETE CASCADE
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
