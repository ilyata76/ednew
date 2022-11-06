-- селект - выборка из
-- по нордвинду


SELECT * FROM products;
SELECT product_name FROM products; -- выборочно

-- операторы
-- + - * /
-- ^ степень |/ квадратный корень

SELECT product_id, product_name, unit_price * units_in_stock;
FROM products; -- применили оператор

--------------------------------- DISTINCT

SELECT * FROM employees; -- увидели всё
SELECT city FROM employees; -- города (будут повторяться)
-- хотим без дубликаций

SELECT DISTINCT city FROM employees; -- не включили повторы в выборку - повторов не будет


SELECT city, country FROM employees; -- будут повторы опять по типу "London - UK"

-- теперь останется пять строчек уникальных строчек
SELECT DISTINCT city, country FROM employees;


--------------------------------- COUNT

SELECT * FROM orders; -- 830 строчек заказов

SELECT COUNT(*) FROM orders; -- получим число

-- но можно и к конкретному столбцу:
SELECT COUNT(country) FROM employees; -- будут дубликаты (9)
SELECT COUNT(DISTINCT country) FROM employees; -- дубликатов не будет (2)
-- дистинкт применяется перед столбцом



--------------------------------- WHERE

-- SELECT ... FROM ... WHERE <condition>

SELECT company_name, contact_name, phone
    FROM customers
    WHERE country = 'USA';


SELECT *
    FROM products
    WHERE unit_price > 20;

SELECT COUNT (*)
    FROM products
    WHERE unit_price > 20;

SELECT *
    FROM customers
    WHERE city <> 'Berlin'; -- не равно <>

SELECT *
    FROM orders
    WHERE order_date >= '1998-03-01';



--------------------------------- AND OR BETWEEN

-- SELECT .. FROM ... WHERE condition1 AND condition2
-- SELECT .. FROM ... WHERE condition1 OR condition2


SELECT *
    FROM orders
    WHERE shipped_date > '1998-04-30' AND (freight < 75 OR freight > 150);

SELECT COUNT(*)
    FROM orders
    WHERE freight BETWEEN 20 AND 40; -- BETWEEN: >= 20 AND <= 40 только для закрытых интервалов



--------------------------------- AND OR BETWEEN

SELECT * 
    FROM customers
    WHERE country = 'Mexico' OR country = 'Germany'; -- и так далее OR OR OR OR OR - плохо. улучшим с помощью IN


SELECT *
    FROM customers
    WHERE country IN ('Mexico', 'Germany', 'USA', 'Canada');

SELECT *
    FROM customers
    WHERE country NOT IN ('Mexico', 'Germany', 'USA', 'Canada');



--------------------------------- ORDER BY


SELECT DISTINCT country
    FROM customers
    ORDER BY country; -- по возрастанию

SELECT DISTINCT country
    FROM customers
    ORDER BY country ASC; -- по возрастанию

SELECT DISTINCT country
    FROM customers
    ORDER BY country DESC; -- по убыванию

-- можно по нескольким колонкам

SELECT DISTINCT country, city
    FROM customers
    ORDER BY country DESC, city DESC; -- внутри первой колонки сортировка второй колонки




--------------------------------- MIN MAX AVG


SELECT ship_city, order_date
    FROM orders
    WHERE ship_city = 'London'
    ORDER BY order_date;

SELECT MIN(order_date)
    FROM orders
    WHERE ship_city = 'London'
;

SELECT MAX(order_date)
    FROM orders
    WHERE ship_city = 'London'
;

SELECT AVG(unit_price)
    FROM products
    WHERE discontinued <> 1
;

SELECT SUM(units_in_stock)
    FROM products
    WHERE discontinued <> 1
;


--------------------------------- LIKE

-- искать строки похожие на заданный шаблон
-- % - placeholder
-- _ - 1 любой символ
--   LIKE 'U%' - строки, начинающиеся с U
--   LIKE '%a' - строки, кончающиеся на a
--   LIKE '%John%'
--   LIKE 'J%n'
--   LIKE '_oh_' - 1 & 4 любые символы
--   LIKE '_oh%'


SELECT last_name, first_name
    FROM employees
    WHERE first_name LIKE '%n'
;



--------------------------------- LIMIT

-- ограничить число выдаваемых строк

SELECT product_name, unit_price
    FROM products
    WHERE discontinued <> 1
    ORDER BY unit_price DESC
    LIMIT 10
;


--------------------------------- NULL-фильтрация

SELECT ship_city, ship_region, ship_country
    FROM orders
    WHERE ship_region IS NULL
;

-- IS NOT NULL



--------------------------------- GROUP BY


SELECT ship_country, COUNT(*)
    FROM orders
    WHERE freight > 50
    GROUP BY ship_country
    ORDER BY COUNT(*) DESC
;


SELECT category_id, SUM(units_in_stock) 
    FROM products
    GROUP BY category_id
    ORDER BY SUM(units_in_stock) DESC
    LIMIT 5
;

-- SQL требует, чтобы второй столбец был либо в GROUP BY, либо в агрегатной функции (например, сумма)



--------------------------------- HAVING постфильтрация


SELECT category_id, SUM(unit_price * units_in_stock)
    FROM products
    WHERE discontinued <> 1
    GROUP BY category_id
    HAVING SUM(unit_price * units_in_stock) > 5000
    ORDER BY SUM(unit_price * units_in_stock)
;



--------------------------------- UNION, INTERSECT, EXCEPT

SELECT country
    FROM customers
    UNION -- объединяет результаты двух селектор и устраняет дубликаты
        SELECT country 
        FROM employees
    -- UNION ALL не устраняет дубликаты
;

-- INTERSECT - это пересечение (и там, и там есть)

SELECT country
    FROM customers
    INTERSECT
        SELECT country 
        FROM suppliers
;

-- EXCEPT - наоборот

SELECT country
    FROM customers
    EXCEPT
        SELECT country 
        FROM suppliers
;

-- EXCEPT ALL работает по-другому. Он выбирает и те страны, для которых нет сопоставлений в другой таблице (USA - USA не пропишет) (USA - UK пропишет)

SELECT country
    FROM customers
    EXCEPT ALL
        SELECT country 
        FROM suppliers
;