# SQL: Top 3 High Earners per Department

## Problem
Given two tables: **`Employee`** and **`Department`**, find employees who earn salaries in the **top 3 unique salaries** within their department.

**Tables:**
- **Employee**: `id`, `name`, `salary`, `departmentId` (**FK** to Department)
- **Department**: `id`, `name`

---

## Key SQL Concepts
- **`Correlated Subquery`** — Compare a row in the outer query with aggregated results from the same table.
- **`COUNT(DISTINCT ...)`** — Count unique values to handle salary ties.
- **`DENSE_RANK()`** — Assign rank without skipping numbers for ties.
- **`PARTITION BY`** — Group rankings independently for each department.

---

## Approach 1: Correlated Subquery
### Logic
1. **`JOIN`** `Employee` and `Department` to get department names.  
2. For each employee, **`COUNT(DISTINCT salary)`** greater than their salary **in the same department**.  
3. Keep employees where this count is `< 3`.

```sql
SELECT d.name AS Department, 
       e1.name AS Employee, 
       e1.salary AS Salary 
FROM Employee e1
JOIN Department d
  ON e1.departmentId = d.id 
WHERE 3 > (
    SELECT COUNT(DISTINCT e2.salary)
    FROM Employee e2
    WHERE e2.salary > e1.salary 
      AND e1.departmentId = e2.departmentId
);
```

**Pros:** Works without window functions.  
**Cons:** Slower on large datasets.

---

## Approach 2: Window Function with `DENSE_RANK()`
### Logic
1. Use **`DENSE_RANK()`** to rank salaries per department in descending order.  
2. Select rows where `rnk <= 3`.

```sql
WITH employee_department AS (
    SELECT d.id, 
           d.name AS Department, 
           e.salary AS Salary, 
           e.name AS Employee, 
           DENSE_RANK() OVER (
               PARTITION BY d.id 
               ORDER BY e.salary DESC
           ) AS rnk
    FROM Department d
    JOIN Employee e
      ON d.id = e.departmentId
)
SELECT Department, Employee, Salary
FROM employee_department
WHERE rnk <= 3;
```

**Pros:** Cleaner, more efficient for large datasets.  
**Cons:** Requires window function support.

---

## General Importance
- **Ranking functions** like `DENSE_RANK()` are essential for "Top N per group" queries.  
- **Correlated subqueries** provide compatibility for databases without window function support.  
- **Handling ties** ensures fairness — employees with the same salary receive the same rank.
