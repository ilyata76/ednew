------------------- CASE


SELECT product_name, unit_price, units_in_stock,
    CASE -- пропишем в колонке что-то
        WHEN units_in_stock >= 100 THEN 'lots of'
        WHEN units_in_stock >= 50 AND units_in_stock < 100 THEN 'average'
        WHEN units_in_stock < 50 THEN 'low number'
        ELSE 'unknown'
    END -- закрыли кейс
        AS amount
    FROM products
    ORDER BY units_in_stock DESC
;

--
SELECT order_id, order_date,
    CASE 
        WHEN date_part('month', order_date) BETWEEN 3 and 5 THEN 'spring' 
        WHEN date_part('month', order_date) BETWEEN 6 and 8 THEN 'summer'
        WHEN date_part('month', order_date) BETWEEN 9 and 11 THEN 'autumn'
        ELSE 'winter'
    END 
        AS bla
    FROM orders
;


------------------------------ COALESCE

-- вместо NULL заменяет вторым аргументом при селектах

SELECT * 
    FROM orders
    LIMIT 10
;

SELECT order_id, order_date, COALESCE(ship_region, 'unknown')
    FROM orders
    LIMIT 10
;

-- а как исправить пустую строку? они не NULL, а пустая строка

-- NULLIF - если condition верно, то вернёт NULL
-- если не равны, то возвращает первый аргумент
SELECT contact_name, COALESCE(NULLIF(city, ''), 'Unknown') AS city
    FROM customers
;











