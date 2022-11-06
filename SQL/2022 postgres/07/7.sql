--- VIEW - как бы виртуальная таблица
--- запрос можно сохранять VIEW. VIEW может подменять настоящую таблицу
-- нельзя изменять столбцы (удалять, переименовать, порядок следования) в VIEW
-- можно только добавлять новые столбцы
-- на изменения наложены ограничения:
--      только одна таблица в FROM
--      нет оконных функций, агрегирующих функций
--      нет distinct, group by, having, union, intersect, except, limit


CREATE VIEW products_suppliers_categories AS
    SELECT product_name, quantity_per_unit, unit_price, units_in_stock, company_name, contact_name, phone, category_name, description
        FROM products
            JOIN suppliers 
                USING(supplier_id)
            JOIN categories
                USING(category_id)
; -- VIEW сохранится в БД (её заново создавать не нужно)
-- таблицу кстати также создавать можно CREATE TABLE .. AS SELECT ..

SELECT * FROM products_suppliers_categories; -- работает как таблица

SELECT * FROM products_suppliers_categories
    WHERE unit_price > 20
; -- 

DROP VIEW IF EXISTS products_suppliers_categories; -- удалили\


----- изменяемые VIEW?


CREATE VIEW heavy_orders AS
    SELECT *
        FROM orders
        WHERE freight > 50
;

SELECT *
    FROM heavy_orders
    ORDER BY freight
;

-- изменим VIEW

CREATE OR REPLACE VIEW heavy_orders AS
    SELECT *
        FROM orders
        WHERE freight > 100
;


-- а предыдущую?

CREATE OR REPLACE VIEW products_suppliers_categories AS
    SELECT product_name, quantity_per_unit, unit_price, 
    units_in_stock, company_name, contact_name, 
    phone, category_name, description, discontinued,
    country
        FROM products
            JOIN suppliers 
                USING(supplier_id)
            JOIN categories
                USING(category_id)
; -- будет ошибка! нельзя добавлять столбцы, т.к. есть ограничения

-- через VIEW можно изменять данные таблиц (кринж кстати)


-- можно накладывать ограничения, т.к. WHERE при создании не ограничивает
-- добавление через INSERT INTO ... VALUES


CREATE OR REPLACE VIEW heavy_orders AS  
    SELECT *
        FROM orders
        WHERE freight > 100
    WITH CHECK OPTION -- WITH CASCADE CHECK OPTION
; -- теперь будут проверяться



