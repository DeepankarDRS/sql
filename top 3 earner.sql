/*  
========================================================
SQL: Top 3 High Earners per Department
========================================================
Problem:
Given two tables: Employee and Department, 
find employees who have salaries in the TOP 3 unique salaries 
within their department.

Tables:
Employee(id, name, salary, departmentId)
Department(id, name)

Key SQL Concepts:
- Correlated Subquery → Compare a row in outer query with related data in subquery.
- COUNT(DISTINCT ...) → Count unique values to handle ties in salaries.
- DENSE_RANK() → Rank rows without skipping numbers for equal values.
- PARTITION BY → Apply ranking per department separately.

--------------------------------------------------------
Approach 1: Correlated Subquery
--------------------------------------------------------
Logic:
1. Join Employee and Department to get department names.
2. For each employee, count distinct salaries higher than theirs in the same department.
3. Keep employees where that count is < 3 (means their salary is in top 3).
*/

SELECT 
    d.name AS Department,   -- Department name from Department table
    e1.name AS Employee,    -- Employee name from Employee table
    e1.salary AS Salary     -- Employee salary
FROM Employee e1
JOIN Department d
    ON e1.departmentId = d.id   -- Match each employee to their department
WHERE 3 > (                      -- Keep only employees with less than 3 higher salaries
    SELECT COUNT(DISTINCT e2.salary)   -- Count UNIQUE higher salaries
    FROM Employee e2
    WHERE e2.salary > e1.salary        -- Only salaries greater than current employee
      AND e1.departmentId = e2.departmentId  -- From the same department
);
/*
Pros: Works even without window functions.
Cons: Can be slower for large datasets due to repeated subquery execution.
*/

--------------------------------------------------------
-- Approach 2: Window Function with DENSE_RANK()
--------------------------------------------------------
/*
Logic:
1. Use DENSE_RANK() to assign salary ranks per department in descending order.
2. Select only rows where rank <= 3.
3. This avoids repeated subqueries and handles ties naturally.
*/

WITH employee_department AS (
    SELECT 
        d.id,                       -- Department ID
        d.name AS Department,       -- Department name
        e.salary AS Salary,         -- Employee salary
        e.name AS Employee,         -- Employee name
        DENSE_RANK() OVER (
            PARTITION BY d.id       -- Restart ranking for each department
            ORDER BY e.salary DESC  -- Higher salaries get lower rank numbers
        ) AS rnk
    FROM Department d
    JOIN Employee e
        ON d.id = e.departmentId
)
SELECT Department, Employee, Salary
FROM employee_department
WHERE rnk <= 3;   -- Keep only top 3 ranked salaries per department
/*
Pros: More readable and efficient for large datasets.
Cons: Requires database support for window functions.
*/

--------------------------------------------------------
-- General Importance
--------------------------------------------------------
-- Ranking functions like DENSE_RANK() are essential for "Top N per group" problems.
-- Correlated subqueries work in all SQL versions but may be slower.
-- Handling salary ties is important — both methods handle it correctly.
