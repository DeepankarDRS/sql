MySQL RANK() Function: A Complete Guide
Table of Contents

Introduction
Basic Syntax
How RANK() Works
RANK() vs DENSE_RANK() vs ROW_NUMBER()
Advanced Usage
Performance Considerations
Common Pitfalls
Example Queries
References


Introduction
The RANK() function in MySQL is a window function used to assign a rank to each row within a partition of a result set. It is commonly used for ranking rows based on one or more columns, such as sales, scores, or any other metric.

Basic Syntax
RANK() OVER (
    [PARTITION BY partition_expression, ... ]
    ORDER BY sort_expression [ASC | DESC], ...
)

PARTITION BY: Divides the result set into partitions to which the function is applied.
ORDER BY: Determines the order in which the rows are ranked.


How RANK() Works

RANK() assigns the same rank to rows with equal values.
If two rows tie for a rank, the next rank(s) are skipped.
For example, if two rows are ranked 1, the next row is ranked 3.

Example:
SELECT
    name,
    score,
    RANK() OVER (ORDER BY score DESC) as rank
FROM students;
Alice951Bob951Carol903Dave854

RANK() vs DENSE_RANK() vs ROW_NUMBER()
RANK()Skips ranks1, 1, 3, 4DENSE_RANK()No gaps1, 1, 2, 3ROW_NUMBER()Unique numbers1, 2, 3, 4

Advanced Usage
1. Partitioning
You can rank rows within groups using PARTITION BY:
SELECT
    department,
    name,
    salary,
    RANK() OVER (PARTITION BY department ORDER BY salary DESC) as dept_rank
FROM employees;
2. Multiple Ordering
You can rank by multiple columns:
SELECT
    name,
    score,
    subject,
    RANK() OVER (PARTITION BY subject ORDER BY score DESC) as subject_rank
FROM exam_results;
3. Using with Other Window Functions
Combine with SUM(), AVG(), etc.:
SELECT
    name,
    score,
    RANK() OVER (ORDER BY score DESC) as rank,
    AVG(score) OVER () as avg_score
FROM students;

Performance Considerations

Indexing: Ensure columns used in ORDER BY and PARTITION BY are indexed for better performance.
Memory: Window functions can be memory-intensive for large datasets.
MySQL Version: RANK() is available in MySQL 8.0+.


Common Pitfalls

MySQL Version: Not available in versions before 8.0.
NULL Handling: NULL values are treated as equal and ranked together.
Performance: Avoid using window functions on very large tables without proper indexing.


Example Queries
Example 1: Simple Ranking
SELECT
    product_name,
    sales,
    RANK() OVER (ORDER BY sales DESC) as sales_rank
FROM products;
Example 2: Department-wise Ranking
SELECT
    department,
    employee_name,
    salary,
    RANK() OVER (PARTITION BY department ORDER BY salary DESC) as dept_salary_rank
FROM employees;
Example 3: Top N per Group
WITH ranked_products AS (
    SELECT
        category,
        product_name,
        sales,
        RANK() OVER (PARTITION BY category ORDER BY sales DESC) as rank
    FROM products
)
SELECT * FROM ranked_products WHERE rank <= 3;
