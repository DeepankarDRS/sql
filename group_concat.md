# GROUP_CONCAT() in SQL Combine values from multiple rows of a single column into one string using GROUP_CONCAT().
## Syntax ```sql SELECT GROUP_CONCAT(column_name SEPARATOR 'separator')
FROM table_name [WHERE condition] [GROUP BY another_column]; ``` - 
SEPARATOR is optional (default is comma ,). 
- Works within aggregation (often with GROUP BY).
- ## Examples
- ### 1) Combine all values in a column into one string
- ```sql
   SELECT GROUP_CONCAT(name)
- AS all_names FROM employees; ```
- Result: ``` Alice,Bob,Charlie,David ```
- 
-  ### 2) Custom separator
-   ```sql
-   SELECT GROUP_CONCAT(name SEPARATOR ' | ')
-    AS all_names FROM employees;
-   ```
-   Result: ``` Alice | Bob | Charlie | David ```
-  ### 3) Combine per group
-   ```sql
    SELECT department_id, GROUP_CONCAT(name ORDER BY name ASC SEPARATOR ', ')
-  AS employees FROM employees GROUP BY department_id; ```
-  Result: |department_id|employees| |---|---| |1|Alice, Bob| |2|Charlie, David, Eve|
-   ### 4) Distinct values only
-   ```sql
     SELECT GROUP_CONCAT(DISTINCT skill ORDER BY skill SEPARATOR ', ')
-    FROM employee_skills;
-     ```
- Result: ``` C++, Java, Python ```
-  ## Notes - You can adjust the max length of the result with:
- ```sql SET SESSION group_concat_max_len = 1000000; ```
-  - GROUP_CONCAT is MySQL/MariaDB specific. - In PostgreSQL, use string_agg(), - In SQL Server, use STRING_AGG().```
