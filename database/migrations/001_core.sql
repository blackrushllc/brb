-- 001_core.sql

CREATE TABLE languages
(
    id         INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    code       VARCHAR(32)  NOT NULL UNIQUE, -- 'basic', 'basil', 'basicjs'
    name       VARCHAR(64)  NOT NULL,        -- 'Basic', 'Basil', 'Basic.JS'
    sort_order INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

CREATE TABLE feature_libraries
(
    id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    code        VARCHAR(64)  NOT NULL UNIQUE, -- 'standard', 'obj-audio', 'obj-ai'
    name        VARCHAR(128) NOT NULL,
    description TEXT         NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

CREATE TABLE categories
(
    id          INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    name        VARCHAR(128) NOT NULL,
    slug        VARCHAR(128) NOT NULL UNIQUE, -- 'audio', 'midi', 'variables'
    description TEXT         NULL,
    sort_order  INT UNSIGNED NOT NULL DEFAULT 0
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;
