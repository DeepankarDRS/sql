 ##DELETE Statement Basics

    Purpose: Remove one or more rows from a table.

    Syntax:

    DELETE FROM table_name
    WHERE condition;

    Key Points:

        Without WHERE → Deletes all rows (table remains, schema intact).

        Always backup or test with SELECT first before deleting.

        Cannot delete from a view unless it’s updatable.

2. Delete All Rows

DELETE FROM Employees;

    Removes all rows from Employees.

    Slower than TRUNCATE (which resets identity & is non-logged in most DBs).

    Use when you want to log each row deletion (e.g., for rollback).

3. Delete with WHERE Clause

DELETE FROM Employees
WHERE department = 'HR';

    Deletes rows that match a condition.

    Condition can use =, >, <, BETWEEN, IN, LIKE, IS NULL, etc.

4. Delete with Multiple Conditions

DELETE FROM Orders
WHERE status = 'Cancelled'
  AND order_date < '2024-01-01';

    Multiple conditions combined with AND / OR.

5. Delete Using Subquery

DELETE FROM Employees
WHERE id IN (
    SELECT id FROM Employees
    WHERE salary < 30000
);

    Useful for deleting based on complex logic or another table’s data.

6. Delete with Joins

(Vendor-specific, works in MySQL, SQL Server, PostgreSQL with slight syntax changes)

MySQL:

DELETE e
FROM Employees e
JOIN Departments d ON e.dept_id = d.id
WHERE d.name = 'IT';

SQL Server:

DELETE e
FROM Employees e
JOIN Departments d ON e.dept_id = d.id
WHERE d.name = 'IT';

PostgreSQL:

DELETE FROM Employees
USING Departments
WHERE Employees.dept_id = Departments.id
  AND Departments.name = 'IT';

7. Delete with GROUP BY and HAVING

    DELETE itself doesn’t allow GROUP BY, but you can use a subquery:

DELETE FROM Orders
WHERE id IN (
    SELECT id
    FROM Orders
    GROUP BY customer_id
    HAVING COUNT(*) > 5
);

    Deletes orders from customers with more than 5 orders.

8. Delete with LIMIT / TOP

    MySQL:

DELETE FROM Logs
WHERE log_type = 'Debug'
ORDER BY created_at ASC
LIMIT 100;

    SQL Server:

DELETE TOP (100)
FROM Logs
WHERE log_type = 'Debug';

9. Delete Duplicates

DELETE t1
FROM Employees t1
JOIN Employees t2
ON t1.email = t2.email
AND t1.id > t2.id;

    Keeps the lowest id row for each duplicate email.

10. Delete with EXISTS

DELETE FROM Customers c
WHERE EXISTS (
    SELECT 1 FROM Orders o
    WHERE o.customer_id = c.id
      AND o.status = 'Cancelled'
);

    Deletes customers having cancelled orders.

11. Cascade Deletes (Foreign Keys)

ALTER TABLE Orders
ADD CONSTRAINT fk_customer
FOREIGN KEY (customer_id) REFERENCES Customers(id)
ON DELETE CASCADE;

    Deleting a customer automatically deletes related orders.

12. Safety Tips

    Always test with:

SELECT * FROM table_name WHERE condition;

Wrap in transactions when possible:

    BEGIN TRAN;
    DELETE FROM Employees WHERE dept_id = 5;
    ROLLBACK; -- Undo if needed
    COMMIT;   -- Finalize

✅ Summary Table:
| Use Case          | Example Snippet                                       |
| ----------------- | ----------------------------------------------------- |
| Delete all rows   | `DELETE FROM T;`                                      |
| With condition    | `DELETE FROM T WHERE id=1;`                           |
| Multi-condition   | `DELETE FROM T WHERE A=1 AND B>5;`                    |
| Subquery          | `DELETE FROM T WHERE id IN (SELECT ...)`              |
| Join-based delete | `DELETE T1 FROM T1 JOIN T2 ...`                       |
| Grouped condition | `DELETE FROM T WHERE id IN (SELECT ... GROUP BY ...)` |
| Limited rows      | `DELETE FROM T LIMIT 10;`                             |
| Duplicates        | `DELETE T1 FROM T1 JOIN T2 ON ...`                    |
| Exists check      | `DELETE FROM T WHERE EXISTS (...)`                    |
| Cascade           | `ON DELETE CASCADE`                                   |
