Method 1 :
SELECT sell_date,
       COUNT(sell_date) AS num_sold,
       GROUP_CONCAT(product ORDER BY product SEPARATOR ',') AS products
FROM (
    SELECT sell_date, product
    FROM Activities
    GROUP BY sell_date, product
) AS t1
GROUP BY sell_date;


Method 2: Cleaner with DISTINCT

SELECT sell_date,
       COUNT(DISTINCT product) AS num_sold,
       GROUP_CONCAT(DISTINCT product ORDER BY product SEPARATOR ',') AS products
FROM Activities
GROUP BY sell_date;
