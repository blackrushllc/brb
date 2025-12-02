REM Basil/Basic Database Library Include File

LET b% = LOADENV%(); // defaults to .env

REM  Get the DSN from the environment and create a DB and ORM objects

LET dsn$ = ENV$("DB_DSN")
DIM db@ AS DB_MYSQL(dsn$)
DIM orm@ AS ORM(db@)


REM  PRINTLN db@.Execute("CREATE TABLE IF NOT EXISTS test2 (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(50))")
REM  PRINTLN db@.Execute("INSERT INTO test2 (name) VALUES (?)", "Alice")
REM  PRINTLN db@.Execute("INSERT INTO test2 (name) VALUES (?)", "Bob")
REM  PRINTLN db@.Query$("SELECT id, name FROM test2 WHERE name LIKE ?", "A%")

 orm@.ModelFromTable$("keywords")
 orm@.ModelFromTable$("languages")
 orm@.ModelFromTable$("categories")
 orm@.ModelFromTable$("feature_libraries")
 orm@.ModelFromTable$("keyword_languages")
 orm@.ModelFromTable$("keyword_categories")
 orm@.ModelFromTable$("code_examples")
 orm@.ModelFromTable$("keyword_examples")
 orm@.ModelFromTable$("keyword_relations")
 orm@.ModelFromTable$("guide_sections")
 orm@.ModelFromTable$("categories")
 orm@.ModelFromTable$("guide_pages")
 orm@.ModelFromTable$("admin_users")



FUNCTION DbGetOrm@()
  RETURN orm@
END

FUNCTION DbGetMysql@()
  RETURN db@
END


REM DIM A$(12)

REM  Create a model

REM    LET A$(0)="id%"
REM    LET A$(1)="keyword$"
REM    LET A$(2)="slug$"
REM    LET A$(3)="display_name$"
REM    LET A$(4)="kind$"
REM    LET A$(5)="short_desc$"
REM    LET A$(6)="long_desc_md$"
REM    LET A$(7)="feature_library_id%"
REM    LET A$(8)="is_standard_lib$"
REM    LET A$(9)="introduced_in_ver$"
REM    LET A$(10)="deprecated_in_ver$"
REM    LET A$(11)="created_at$"
REM    LET A$(12)="updated_at$"

REM We don't support this syntax yet :(
REM orm@.Model("users", ["id%","name$","email$"], "id%")

REM Instantiate the model
REM orm@.Model("keywords", A$, "id%")

REM Set values and save the model
REM LET u@ = orm@.New("keywords")
REM LET u@.Name$="Bob"
REM LET u@.Email$="bob@example.com"
REM u@.Save()

REM  Query the database
REM PRINTLN orm@.Table("keywords").Where$("name$","LIKE","B%").OrderBy$("id%","ASC").ToJson$()
REM PRINTLN orm@.Table("keywords").Where$("id%",">","1").OrderBy$("id%","ASC").ToJson$()






















FUNCTION get_user_by_id%(user_id%)
    DIM user_rec@ AS RECORD
    user_rec@ = orm@.find_by_pk("users", user_id%)
    RETURN user_rec@
END FUNCTION
