-- 003_reference_examples.sql

CREATE TABLE code_examples
(
    id      INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    title   VARCHAR(255)             NOT NULL,
    style   ENUM ('blocky', 'curly') NOT NULL,
    body_md MEDIUMTEXT               NOT NULL, -- Markdown-wrapped code block
    notes   TEXT                     NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4

CREATE TABLE keyword_examples
(
    keyword_id INT UNSIGNED NOT NULL,
    example_id INT UNSIGNED NOT NULL,
    is_primary TINYINT(1)   NOT NULL DEFAULT 0,
    PRIMARY KEY (keyword_id, example_id),
    CONSTRAINT fk_kw_ex_keyword
        FOREIGN KEY (keyword_id) REFERENCES keywords (id) ON DELETE CASCADE,
    CONSTRAINT fk_kw_ex_example
        FOREIGN KEY (example_id) REFERENCES code_examples (id) ON DELETE CASCADE
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
