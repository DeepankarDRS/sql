Table: Movies

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| movie_id      | int     |
| title         | varchar |
+---------------+---------+
movie_id is the primary key (column with unique values) for this table.
title is the name of the movie.

 

Table: Users

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| user_id       | int     |
| name          | varchar |
+---------------+---------+
user_id is the primary key (column with unique values) for this table.
The column 'name' has unique values.

Table: MovieRating

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| movie_id      | int     |
| user_id       | int     |
| rating        | int     |
| created_at    | date    |
+---------------+---------+
(movie_id, user_id) is the primary key (column with unique values) for this table.
This table contains the rating of a movie by a user in their review.
created_at is the user's review date. 

 

Write a solution to:

    Find the name of the user who has rated the greatest number of movies. In case of a tie, return the lexicographically smaller user name.
    Find the movie name with the highest average rating in February 2020. In case of a tie, return the lexicographically smaller movie name.

The result format is in the following example.

 

Example 1:

Input: 
Movies table:
+-------------+--------------+
| movie_id    |  title       |
+-------------+--------------+
| 1           | Avengers     |
| 2           | Frozen 2     |
| 3           | Joker        |
+-------------+--------------+
Users table:
+-------------+--------------+
| user_id     |  name        |
+-------------+--------------+
| 1           | Daniel       |
| 2           | Monica       |
| 3           | Maria        |
| 4           | James        |
+-------------+--------------+
MovieRating table:
+-------------+--------------+--------------+-------------+
| movie_id    | user_id      | rating       | created_at  |
+-------------+--------------+--------------+-------------+
| 1           | 1            | 3            | 2020-01-12  |
| 1           | 2            | 4            | 2020-02-11  |
| 1           | 3            | 2            | 2020-02-12  |
| 1           | 4            | 1            | 2020-01-01  |
| 2           | 1            | 5            | 2020-02-17  | 
| 2           | 2            | 2            | 2020-02-01  | 
| 2           | 3            | 2            | 2020-03-01  |
| 3           | 1            | 3            | 2020-02-22  | 
| 3           | 2            | 4            | 2020-02-25  | 
+-------------+--------------+--------------+-------------+
Output: 
+--------------+
| results      |
+--------------+
| Daniel       |
| Frozen 2     |
+--------------+
Explanation: 
Daniel and Monica have rated 3 movies ("Avengers", "Frozen 2" and "Joker") but Daniel is smaller lexicographically.
Frozen 2 and Joker have a rating average of 3.5 in February but Frozen 2 is smaller lexicographically.
# My approach summary
## 🐞 SQL Debug Notes: Fixing INVALID Error in JOIN + GROUP BY + HAVING Query

❌ Problematic SQL Query

SELECT *
FROM Movierating AS t1
INNER JOIN Users AS t2
INNER JOIN Movies AS t3
WHERE (
    t1.movie_id = t3.movie_id AND
    t1.user_id = t2.user_id AND
    MONTH(t1.created_at) = 2 AND
    MONTH(t1.created_at) = 2
)
GROUP BY t3.title
HAVING MAX(AVG(t1.rating))
ORDER BY t3.title;

🔍 Issues Identified
Type	Issue Description
❌ Syntax	HAVING MAX(AVG(...)) is invalid SQL syntax. Nested aggregates are not allowed like this.
⚠️ Logic	MONTH(t1.created_at) = 2 is repeated unnecessarily.
❌ JOINs	JOINs are missing proper ON conditions.
❗ GROUP BY	Not all selected columns are either aggregated or grouped.
✅ Corrected SQL Query

    Goal: Fetch movie titles rated in February, and return only those with the highest average rating, sorted alphabetically.

SELECT t3.title, AVG(t1.rating) AS avg_rating
FROM Movierating AS t1
INNER JOIN Users AS t2 ON t1.user_id = t2.user_id
INNER JOIN Movies AS t3 ON t1.movie_id = t3.movie_id
WHERE MONTH(t1.created_at) = 2
GROUP BY t3.title
HAVING AVG(t1.rating) = (
    SELECT MAX(avg_rating)
    FROM (
        SELECT AVG(t1.rating) AS avg_rating
        FROM Movierating AS t1
        INNER JOIN Movies AS t3 ON t1.movie_id = t3.movie_id
        WHERE MONTH(t1.created_at) = 2
        GROUP BY t3.title
    ) AS sub
)
ORDER BY t3.title;

🧠 Explanation

    ✅ INNER JOIN ... ON ... used correctly.

    ✅ Filtered created_at to February.

    ✅ GROUP BY on title to aggregate ratings.

    ✅ Subquery computes MAX average rating across movies.

    ✅ Outer query filters only those movies that match the max average.

💡 Tip for Debugging SQL

    Always validate JOIN conditions.

    Avoid using SELECT * when grouping — be specific.

    Nested aggregates like MAX(AVG(...)) must be handled using subqueries.

    Use HAVING only with aggregate functions.

#optimal Answer
(SELECT name AS results
FROM MovieRating JOIN Users USING(user_id)
GROUP BY name
ORDER BY COUNT(*) DESC, name
LIMIT 1)

UNION ALL

(SELECT title AS results
FROM MovieRating JOIN Movies USING(movie_id)
WHERE EXTRACT(YEAR_MONTH FROM created_at) = 202002
GROUP BY title
ORDER BY AVG(rating) DESC, title
LIMIT 1);
# learnings
do not use join as soon as you see multiple table  
having doesn't work on nested aggegate functions
take 5 min to think for multiple approaches
