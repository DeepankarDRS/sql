
# SQL Interview Notes: CTE vs Subquery

## 1. Basics
- **Subquery**: Query inside another query, used in `WHERE`, `FROM`, or `SELECT`.
- **CTE (Common Table Expression)**: Temporary named result set defined with `WITH`, available only during the main query.

---

## 2. Syntax

### CTE
```sql
WITH cte_name AS (
  SELECT ...
)
SELECT * FROM cte_name;
````

### Subquery

```sql
SELECT ...
FROM (SELECT ... ) AS subquery;
```

---

## 3. When to Use

### ✅ Subquery

* Filtering in `WHERE` with `IN`, `EXISTS`, `=`, `<`, etc.
* Creating computed columns inside `SELECT`.
* One-off lookups (e.g., value vs. average).
* **Correlated subqueries** → inner query depends on the outer query.

### ✅ CTE

* Improves **readability** in multi-step queries.
* **Reuse** query results multiple times.
* Required for **recursive queries** (hierarchies, org charts).
* Easier debugging (test step by step).

---

## 4. Examples

### Subquery in WHERE

```sql
SELECT artist_name
FROM concerts
WHERE concert_revenue > (
  SELECT AVG(concert_revenue) FROM concerts
);
```

### CTE for Clarity

```sql
WITH genre_revenue AS (
  SELECT genre, SUM(concert_revenue) AS total
  FROM concerts
  GROUP BY genre
)
SELECT g.genre, g.total
FROM genre_revenue g;
```

### Recursive CTE

```sql
WITH RECURSIVE org_chart AS (
  SELECT employee_id, manager_id 
  FROM employees 
  WHERE manager_id IS NULL

  UNION ALL

  SELECT e.employee_id, e.manager_id
  FROM employees e
  JOIN org_chart o ON e.manager_id = o.employee_id
)
SELECT * FROM org_chart;
```

---

## 5. Key Interview Points

* **Performance**:

  * Subqueries may be recomputed → less efficient.
  * CTEs don’t guarantee faster queries, but improve readability.
* **Correlated Subqueries**:

  * Executed once per row → powerful but can be slow.
* **Recursive Queries**:

  * Only possible with CTEs (`WITH RECURSIVE`).
* **Best Practice**:

  * Use subqueries for inline conditions/aggregations.
  * Use CTEs for modular, recursive, or multi-use queries.

---

## 6. Mnemonics

* **CTE → Clarity, Testing, Extension**
* **Subquery → Single-use, Inline, Filter**

---

## 7. Sample Interview Answer

*"I’d use a CTE if the query is complex, recursive, or reused multiple times.
I’d use a subquery if it’s a one-off inline calculation or filter.
Both compile down similarly, so the main difference is readability and maintainability."*

---

## 8. Visual Reference

**CTE Flow (step by step):**

```
WITH step1 AS ( ... )
WITH step2 AS ( SELECT ... FROM step1 )
SELECT ... FROM step2;
```

**Subquery Flow (nested inline):**

```
SELECT ...
FROM (SELECT ... FROM table) AS sub;
```

```

---
