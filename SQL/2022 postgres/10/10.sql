------------- напишем функцию как функцию постгрес


CREATE OR REPLACE FUNCTION get_total_number_of_goods() 
    RETURNS bigint
    AS $$
        BEGIN
            RETURN sum(units_in_stock)
                FROM products
            ;
        END;
    $$ LANGUAGE plpgsql
;


SELECT get_total_number_of_goods();

--- ещё одну

CREATE OR REPLACE FUNCTION get_max_price_from_discontinued() 
    RETURNS real
    AS $$
        BEGIN
            RETURN max(unit_price)
                FROM products
                WHERE discontinued = 1
            ;
        END;
    $$ LANGUAGE plpgsql
;


SELECT get_max_price_from_discontinued();


-------------- с OUT параметрами?

CREATE OR REPLACE FUNCTION get_price_boundaries(OUT max_price real, OUT min_price real)
    AS $$
        BEGIN
            -- max_price это обычная переменная в рамках plpgsql
            max_price := MAX(unit_price) FROM products; -- можно и = но = также используется для сравнения
            min_price := MIN(unit_price) FROM products;
        END;
    $$ LANGUAGE plpgsql
;

SELECT * FROM get_price_boundaries;


CREATE OR REPLACE FUNCTION get_sum(x int, y int, out result int)
    AS $$
        BEGIN
            result := x + y; -- всё как обычно
            RETURN; -- принудительный выход
        END;
    $$ LANGUAGE plpgsql
;

SELECT get_sum(1, 2);

------------------------------------- вернём теперь таблицу customers

DROP FUNCTION IF EXISTS get_customers_by_country;
CREATE FUNCTION get_customers_by_country(customer_country varchar)
	RETURNS SETOF customers
    AS $$
        BEGIN
            RETURN QUERY
                SELECT * 
                    FROM customers
                    WHERE country = customer_country;
        END;
    $$ LANGUAGE plpgsql;

SELECT * FROM get_customers_by_country('USA');


-------------------------------------------------------------------- DECLARE ?

CREATE OR REPLACE FUNCTION get_square(IN ab real, IN bc real, IN ac real)
    RETURNS real
    AS $$
        DECLARE
            perimeter real;
        BEGIN
            perimeter = (ab + bc + ac) / 2;
            RETURN SQRT(perimeter * (perimeter - ab) * (perimeter - bc) * (perimeter - ac));
        END;

    $$ LANGUAGE plpgsql
;

SELECT get_square(6.0, 6.0, 6.0);



--------------------------------------------------------------------- ВЕТВЛЕНИЯ


CREATE OR REPLACE FUNCTION convert_temp_to(temperature real, to_celsius boolean DEFAULT true)
    RETURNS real
    AS $$
        DECLARE 
            result_temp real;
        BEGIN
            IF to_celsius THEN
                result_temp = (5.0/9.0) * (temperature-32);
            ELSE
                result_temp = (9 + temperature + (32 * 5)) / 5.0;
            END IF;
            RETURN result_temp;
        END;
    $$ LANGUAGE plpgsql
;

SELECT convert_temp_to(80);
SELECT convert_temp_to(26.667, false);

---------------------------------------------------- ELSE IF elsif
DROP FUNCTION IF EXISTS get_season;
CREATE OR REPLACE FUNCTION get_season(month_number int) 
    RETURNS text
    AS $$
        DECLARE
            season text;
        BEGIN
            IF month_number BETWEEN 3 and 5 THEN
                season = 'Spring';
            ELSIF month_number BETWEEN 6 and 8 THEN
                season = 'Summer';
            ELSIF month_number BETWEEN 9 and 11 THEN
                season = 'Autumn';
            ELSE
                season = 'Winter';
            END IF;
            
            RETURN season;
        END;
    $$ LANGUAGE plpgsql
;
SELECT get_season(12);





-------------------------------------------------------------- циклы while, for

-- создадим с вайлом

CREATE OR REPLACE FUNCTION fib(n int)
    RETURNS int
    AS $$
        DECLARE
            counter int = 0;
            i int = 0;
            j int = 1;
        BEGIN
            IF n < 1 THEN
                RETURN 0;
            END IF;

            WHILE counter < n
                LOOP
                    counter = counter + 1;
                    SELECT j, i + j INTO i, j; -- 
                END LOOP;
            
            RETURN i;
        END;
    $$ LANGUAGE plpgsql
;

SELECT fib(3);

/*
ещё можно (абсолютно то же самое)

LOOP
    EXIT WHEN counter = n + 1;
    ...
END LOOP;
*/

-- for?

DO $$ -- анонимный вызов функции
BEGIN
    FOR counter IN 1..5
    LOOP
        RAISE NOTICE 'Counter: %', counter;
    END LOOP;
END $$;


----------------------------------------------- RETURN NEXT
-- накапливание записи в результирующем наборе
-- построчно накапливает

CREATE OR REPLACE FUNCTION return_ints() 
    RETURNS SETOF int 
    AS $$
        BEGIN
            RETURN NEXT 1;
            RETURN NEXT 2;
            RETURN NEXT 3;
        END;
    $$ LANGUAGE plpgsql
;


