-- различают несколько джоинов
-- проходят они по ключам


----------------------------------------- INNER JOIN

SELECT product_name, suppliers.company_name, units_in_stock
    FROM products
    INNER JOIN suppliers -- внутреннее соединение с suppliers
        ON products.supplier_id = suppliers.supplier_id -- после ON по какому столбу производим соединение
    ORDER BY units_in_stock DESC
;


SELECT category_name, SUM(units_in_stock)
    FROM products
    INNER JOIN categories 
        ON products.category_id = categories.category_id
    GROUP BY category_name
    ORDER BY SUM(units_in_stock) DESC
    LIMIT 5
;

SELECT categories.category_name, SUM(products.units_in_stock)
    FROM products
    INNER JOIN categories 
        ON products.category_id = categories.category_id
    GROUP BY category_name
    ORDER BY SUM(products.units_in_stock) DESC
    LIMIT 5
;


SELECT category_name, SUM(unit_price * units_in_stock)
    FROM products
    INNER JOIN categories
        ON products.category_id = categories.category_id
    WHERE discontinued <> 1
    GROUP BY category_name
    HAVING SUM(unit_price * units_in_stock) > 5000
    ORDER BY SUM(unit_price * units_in_stock) ASC
;


-- множественное соединение

SELECT order_date, product_name, ship_country, products.unit_price, quantity, discount
    FROM orders
    INNER JOIN order_details 
        ON orders.order_id = order_details.order_id
    INNER JOIN products 
        ON order_details.product_id = products.product_id
;



----------------------------------------- LEFT RIGHT JOIN


-- всем ключам есть соответствия - такой же результат, что и с INNER
SELECT company_name, product_name
    FROM suppliers
    LEFT JOIN products
        ON products.supplier_id = suppliers.supplier_id
    ORDER BY units_in_stock DESC
;

-- а вот если не всем есть соответствия
-- посмотрим на INNER JOIN
SELECT company_name, order_id
    FROM customers
    JOIN orders 
        ON orders.customer_id = customers.customer_id
    WHERE order_id IS NULL
; -- таблица пустая

SELECT company_name, order_id
    FROM customers
    LEFT JOIN orders 
        ON orders.customer_id = customers.customer_id
    WHERE order_id IS NULL
; -- а теперь будут целых две записи у кастомеров, у которых нет ордер_айди


SELECT last_name, order_id
    FROM employees
    LEFT JOIN orders 
        ON orders.employee_id = employees.employee_id
    WHERE order_id is NULL
; -- ничего нет, все работники заняты заказами

SELECT COUNT(*)
    FROM employees
    LEFT JOIN orders 
        ON orders.employee_id = employees.employee_id
    WHERE order_id is NULL
; -- 0


-- RIGHT JOIN - взяли лефт и поменяли местами

SELECT company_name, order_id
    FROM orders
    RIGHT JOIN customers 
        ON orders.customer_id = customers.customer_id
    WHERE order_id IS NULL
; -- два нулла. а если не менять местами таблицы, ничего не будет


----------------------------------------- CROSS JOIN

-- каждой строчке из левой таблицы сопоставляет каждая строчка из правой




----------------------------------------- SELF JOIN
-- построить иерархию

-- (в другой DB)

CREATE TABLE employee (
	employee_id int PRIMARY KEY,
	first_name varchar(256) NOT NULL,
	last_name varchar(256) NOT NULL,
	manager_id int,
        FOREIGN KEY (manager_id) REFERENCES employee(employee_id);
); -- один эмплои на другой ссылается как на своего менеджера



INSERT INTO employee 
    (employee_id, first_name, last_name, manager_id)
    VALUES 
        (1, 'Windy', 'Hays', NULL),
        (2, 'Ava', 'Christensen', 1),
        (3, 'Hassan', 'Conner', 1),
        (4, 'Anna', 'Reeves', 2),
        (5, 'Sau', 'Norman', 2),
        (6, 'Kelsie', 'Hays', 3),
        (7, 'Tory', 'Goff', 3),
        (8, 'Salley', 'Lester', 3)
;

-- здесь таблица ссылается на себя же, здесь нужно SELF(LEFT) JOIN

SELECT -- || служит для объединения столбиков в один
    e.first_name || ' ' || e.last_name AS employee, -- название столбиков
    m.first_name || ' ' || m.last_name AS manager, -- а тут manager-столбик
    FROM employee e -- e это алиас
    LEFT JOIN employee m ON m.employee_id = e.manager_id -- а здесь m
    ORDER BY manager
;




----------------------------------------- USING

SELECT company_name, order_id
    FROM orders
    RIGHT JOIN customers 
        USING(customer_id) -- если одинаковые наименования, можно использовать USING(столбец)
    WHERE order_id IS NULL
; -- два налла, правильно


----------------------------------------- NATURAL JOIN
-- соединяет по всем столбцам, у которых одинаковое название

SELECT order_id, customer_id, first_name, last_name, title
    FROM orders
    NATURAL JOIN employees
; -- ИСПОЛЬЗОВАТЬ НЕЛЬЗЯ


----------------------------------------- AS псевдонимы

SELECT category_id, SUM(unit_price * units_in_stock) AS total_price
    FROM products
    WHERE discontinued <> 1
    GROUP BY category_id
    HAVING SUM(unit_price * units_in_stock) > 5000
    ORDER BY total_price DESC
;




