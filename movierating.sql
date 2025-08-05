-- # Write your MySQL query statement below
-- # t3 uniqye m_id Movies
-- #t2  unique u_id Users
-- #t1 unique mid_,u_id, MOvieRAting

--     -- Find the name of the user who has rated the greatest number of movies. In case of a tie, return the lexicographically smaller user name.
--     (select t2.name as results
--     from Movierating as t1
--     Inner join  Users as t2
--     Inner join Movies as t3
--     Where  t1.movie_id=t3.movie_id and t1.user_id=t2.user_id
--     group by t1.user_id
--     having max(t1.user_id)
--     order by t2.name
--     limit 1)
--     union
--     -- Find the movie name with the highest average rating in February 2020. In case of a tie, return the lexicographically smaller movie name.
-- --   select *
-- --     from Movierating as t1
-- --     Inner join  Users as t2
-- --     Inner join Movies as t3
-- --     Where  (t1.movie_id=t3.movie_id and
-- --     t1.user_id=t2.user_id and year(t1.created_at)=20     and month(t1.created_at)=2)
-- --     group by t3.title,t3.movie_id
-- --     having avg(t1.rating)#cannot nest the function in haing
-- --     order by t3.title
--     -- limit 1
-- (SELECT t3.title as results
-- FROM Movierating AS t1
-- INNER JOIN Users AS t2 ON t1.user_id = t2.user_id
-- INNER JOIN Movies AS t3 ON t1.movie_id = t3.movie_id
-- WHERE MONTH(t1.created_at) = 2
-- GROUP BY t3.title
-- HAVING AVG(t1.rating) = (
--     SELECT MAX(avg_rating)
--     FROM (
--         SELECT AVG(t1.rating) AS avg_rating
--         FROM Movierating AS t1
--         INNER JOIN Movies AS t3 ON t1.movie_id = t3.movie_id
--         WHERE MONTH(t1.created_at) = 2
--         GROUP BY t3.title
--     ) AS sub
-- )
-- ORDER BY t3.title
-- limit 1)
# Write your MySQL query statement below
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
