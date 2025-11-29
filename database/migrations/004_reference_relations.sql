-- 004_reference_relations.sql

CREATE TABLE keyword_relations
(
    keyword_id         INT UNSIGNED NOT NULL,
    related_keyword_id INT UNSIGNED NOT NULL,
    relation_type      VARCHAR(32)  NOT NULL DEFAULT 'see_also',
    PRIMARY KEY (keyword_id, related_keyword_id, relation_type),
    CONSTRAINT fk_kw_rel_keyword
        FOREIGN KEY (keyword_id) REFERENCES keywords (id) ON DELETE CASCADE,
    CONSTRAINT fk_kw_rel_related
        FOREIGN KEY (related_keyword_id) REFERENCES keywords (id) ON DELETE CASCADE
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
