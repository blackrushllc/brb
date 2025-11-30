Caveats to Correct Common Mistakes that AI makes in Basil BASIC:

1. All functions can return any data type, including arrays. Do not use [] or [][] to indicate array return types in function definitions.

2. Function names can be typed with "$" for strings or "%" for integers, but these semantics are not enforced. Conventionally we will use no type identifier for functions which return arrays.

3. Array assignments do not use empty parenthesis or [] or [][] for the left side argument.  For instance, A$()=MyArrayFunc() is invalid.  The correct syntax would be A$=MyArrayFunc().

4. We no longer require BEGIN and END for code blocks. BEGIN and END are optional and discouraged in Blocky BASIC to avoid confusion, whereas { and } are recommended in Curly BASIC for readability.

5. All multi-line code structures such as IF..THEN, WHILE, FUNC, FUNCTION, SUB, SELECT, etc can be closed with just the keyword END however using the optional second identifier is encouraged for readability, such as "END IF", "END WHILE", "END FUNC", "END FUNCTION", "END SELECT", etc.

6. "FUNC" and "FUNCTION" are synonyms.

7. ARRAY_ROWS%() requires a 2 dimensional array as an argument.  For 1 dimensional arrays use LEN().

8. LET is optional.  Variables can be assigned without LET, however DIM is required to declare arrays.

9. IF..THEN statements contained within a single line do not required "END" or "END IF".  In fact, doing so is an error.

10. ELSEIF is not supported, use SELECT CASE instead.

11. Variables inside functions are not currently local. This should be corrected but it is the current state of the interpreter. A common variable such as i% inside of a function will redefine the variable globally leading to unexpected bugs.