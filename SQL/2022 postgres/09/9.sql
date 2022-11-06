-- функции круто
-- могут состоять из набора утверждений
-- могут содержать SELECT INSERT UPDATE DELETE
-- функции транзакционны сами по себе (BEGIN END действуют как сейвпоинты)
-- 
-- делятся на
-- -- SQL функции
-- -- процедурные
-- -- серверные функции (написанные на C)
-- -- собственные C-функции

-- $$ конец и начало функции
-- CREATE FUNCTION имя(аргументы) RETURNS тип AS $$ тело_функции $$ LANGUAGE lang
-- lang либо SQL либо для постгрескл Pl/pgSQL

-- CREATE OR REPLACE ....

-- создадим первую

SELECT *
    FROM customers
; -- посмотрели есть NULL

--
SELECT *
    INTO tmp_customers
    FROM customers
;

SELECT *
    FROM tmp_customers
;

UPDATE tmp_customers
    SET region = 'unknown'
    WHERE region IS NULL
; -- давайте завернём её в функцию


CREATE OR REPLACE FUNCTION fix_customers_region() RETURNS void 
    AS $$
        UPDATE tmp_customers
            SET region = 'unknown'
            WHERE region IS NULL
    $$ LANGUAGE SQL
; -- создали функцию

-- теперь сделаем то, что нам надо
SELECT fix_customers_region();
SELECT *
    FROM tmp_customers
;


------------------------------------------------------ теперь посложнее


CREATE OR REPLACE FUNCTION get_total_number_of_goods() RETURNS bigint
    AS $$
        SELECT SUM(units_in_stock)
            FROM products
    $$ LANGUAGE SQL
;

SELECT get_total_number_of_goods() AS total_goods;

CREATE OR REPLACE FUNCTION get_avg_price() RETURNS float8
    AS $$
        SELECT AVG(unit_price)
            FROM products
    $$ LANGUAGE SQL
;

SELECT get_avg_price() AS avg_price;


--------------------------------------------- теперь функции посложнее

--- IN входящие аргументы
--- OUT исходящие аргументы. клиентский код получит эти значения в качестве возвращаемого значения
--- INOUT - и тот, и др.
--- VARIADIC - массив входящих параметров (можно передавать в функцию столько, сколько захочется аргументов)
---     DEFAULT value по умолчанию


CREATE OR REPLACE FUNCTION get_product_price_by_name(prod_name varchar) RETURNS real
    AS $$
        SELECT unit_price
            FROM products
            WHERE product_name = prod_name
    $$ LANGUAGE SQL
;

SELECT get_product_price_by_name('Chocolade') AS price;
-- работает


-- хотим теперь вернуть наименьшую цену и наибольшую
-- можем использовать OUT аргументы

CREATE OR REPLACE FUNCTION get_price_boundaries(OUT max_price real, OUT min_price real) -- заметим, что нет RETURNS !
    AS $$
        SELECT MAX(unit_price), MIN(unit_price) -- в той же последовательности, в которой идут аргументы OUT
            FROM products
    $$ LANGUAGE SQL
;


SELECT get_price_boundaries(); -- получим кортеж
SELECT * FROM get_price_boundaries(); -- получим табличку


------------------------------------------------------------------------------------------ посложнее

CREATE OR REPLACE FUNCTION get_price_boundaries_by_discontinuity(IN is_discontinued integer DEFAULT 1, OUT max_price real, OUT min_price real) -- заметим, что нет RETURNS !
    AS $$
        SELECT MAX(unit_price), MIN(unit_price) -- в той же последовательности, в которой идут аргументы OUT
            FROM products
            WHERE discontinued = is_discontinued
    $$ LANGUAGE SQL
;

SELECT * FROM get_price_boundaries_by_discontinuity(1);
-- max среди 
-- и min среди всех дисконтиньюед


------------------------------------------------------------------------------------------ возвращать множество строк 
-- RETURNS SETOF data_type - возврат n-значений типа data_type
-- RETURNS SETOF table
-- RETURNS SETOF record - это кортеж (как в get_price_boundaries)
-- RETURNS TABLE (указываем колонки, ...)


CREATE OR REPLACE FUNCTION get_average_pricec_by_prod_categories()
    RETURNS SETOF double precision 
        AS $$
            SELECT AVG(unit_price)
                FROM products
                GROUP BY category_id -- GROUP BY даст несколько строчек
        $$ LANGUAGE SQL
;

SELECT * FROM get_average_pricec_by_prod_categories();

--- можем вернуть несколько столбов с SETOF record
CREATE OR REPLACE FUNCTION get_average_pricec_by_prod_cats(OUT sum_price real, OUT avg_price double precision)
    RETURNS SETOF RECORD
        AS $$
            SELECT SUM(unit_price), AVG(unit_price)
                FROM products
                GROUP BY category_id
        $$ LANGUAGE SQL
;

SELECT sum_price FROM get_average_pricec_by_prod_cats();
SELECT sum_price AS sum_of, avg_price AS in_avg FROM get_average_pricec_by_prod_cats();

----------------------------------------- теперь вернём таблицу


CREATE OR REPLACE FUNCTION get_customers_by_country(IN customers_country varchar)
    RETURNS TABLE(char_code char, company_name varchar)
    AS $$
        SELECT customer_id, company_name
            FROM customers
            WHERE country = customers_country
    $$ LANGUAGE SQL
;

SELECT * FROM get_customers_by_country('USA');


