-- ПОДЗАПРОС
-- можно и через соединения (JOIN), и через подзапросы


-------------------------------------------------- ПОДЗАПРОСЫ

SELECT company_name
    FROM supplier
    WHERE country IN ('...', '...')
; -- долго и сложно, вставим подзапрос


SELECT company_name
    FROM suppliers
    WHERE country IN (
        SELECT DISTINCT country
            FROM customers
    )
; -- а теперь с JOIN?

SELECT DISTINCT suppliers.company_name
    FROM suppliers
    JOIN customers
        USING(country)
;


SELECT category_name, SUM(units_in_stock)
    FROM products
    INNER JOIN categories USING(category_id)
    GROUP BY category_name
    ORDER BY SUM(units_in_stock) DESC
    LIMIT (SELECT MIN(product_id) + 4
        FROM products    
    )
;

SELECT product_name, units_in_stock
    FROM products
    WHERE units_in_stock > (SELECT AVG(units_in_stock)
                                FROM products
                        )
    ORDER BY units_in_stock
;

-------------------------------------------------- WHERE EXISTS

-- выбирает строку, если в подзапросе была возвращена хотя бы одна строка

SELECT company_name, contact_name
    FROM customers
    WHERE EXISTS (SELECT customer_id 
                    FROM orders
                    WHERE 
                        orders.customer_id = customers.customer_id
                        AND
                        orders.freight BETWEEN 50 AND 100 
            )
; -- для каждой строчки в customers должна существовать строчка в orders с условиями


SELECT product_name
    FROM products
    WHERE NOT EXISTS (SELECT orders.order_id
                        FROM orders
                        JOIN order_details
                            USING(order_id)
                        WHERE 
                            order_details.product_id = product_id
                            AND 
                            order_date BETWEEN '1995-02-01' AND '1995-02-15'
    )
;



-------------------------------------------------- ПОДЗАПРОСЫ с квалификаторами ANY, ALL


SELECT DISTINCT company_name
    FROM customers
    -- фильтруем по заказам
    JOIN orders 
        USING(customer_id)
    JOIN order_details
        USING(order_id)
    WHERE quantity > 40
; -- это с JOIN
-- а теперь с подзапросом?

-- это у нас подзапрос
SELECT customer_id
    FROM orders
    JOIN order_details
        USING(order_id)
    WHERE quantity > 40
; -- объединим его с

SELECT DISTINCT company_name
    FROM customers
    WHERE customer_id = ANY( -- там где кастомер_айди совпадает с какой-либо записью из подзапроса
                                SELECT customer_id
                                    FROM orders
                                    JOIN order_details
                                        USING(order_id)
                                    WHERE quantity > 40
    )
;

-- подзапрос
SELECT AVG(quantity)
    FROM order_details
;
-- запрос с подзапросом

SELECT DISTINCT product_name, quantity
    FROM products
    JOIN order_details
        USING(product_id)
    WHERE quantity > (SELECT AVG(quantity)
                        FROM order_details
                    )
    ORDER BY quantity DESC
;


-- подзапрос

SELECT AVG(quantity)
    FROM order_details
    GROUP BY product_id
;

-- запрос

SELECT DISTINCT product_name, quantity
    FROM products
    JOIN order_details
        USING(product_id)
    WHERE quantity > ALL ( -- больше всех средних значений, полученных из подзапроса
                        SELECT AVG(quantity)
                            FROM order_details
                            GROUP BY product_id
    )
;










