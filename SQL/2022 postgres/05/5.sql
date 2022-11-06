-- DDL data definitial language
-- создание и измненение таблиц

CREATE TABLE student (
    student_id serial,
    first_name varchar,
    last_name varchar,
    birthday date,
    phone varchar
);

CREATE TABLE cathedra (
    cathedra_id serial,
    cathedra_name varchar,
    dean varchar
);

------------------ ALTER TABLE

--- ADD

ALTER TABLE student
    ADD COLUMN middle_name varchar
;

ALTER TABLE student
    ADD COLUMN rating float
;

ALTER TABLE student
    ADD COLUMN enrolled date
;

--- DROP

ALTER TABLE student
    DROP COLUMN middle_name
;

--- RENAME таблицы или столбца

ALTER TABLE cathedra
    RENAME TO chair
;

ALTER TABLE chair
    RENAME cathedra_id TO chair_id
;

ALTER TABLE chair
    RENAME cathedra_name TO chair_name
;


--- ALTER COLUMN SET DATA TYPE изменить тип данных

ALTER TABLE student
    ALTER COLUMN first_name SET DATA TYPE varchar(64)
;

ALTER TABLE student
    ALTER COLUMN lastname_name SET DATA TYPE varchar(64)
;

--- 

CREATE TABLE faculty (
    faculty_id serial,
    faculty_name varchar
);

--- serial может быть автоинкрементом
--- добавим в таблицу только по faculty

INSERT INTO faculty (faculty_name)
    VALUES 
        ('faculty 1'),
        ('faculty 2'),
        ('faculty 3')
;

SELECT * FROM faculty;

--- рестарт автоинкрементов при удалении данных из таблицы?
TRUNCATE TABLE faculty RESTART IDENTITY;
--- продолжить
TRUNCATE TABLE faculty CONTINUE IDENTITY;


--- удалим таблицу
DROP TABLE faculty;


------------------ PRIMARY KEY

DROP TABLE chair;

CREATE TABLE chair (
    char_id serial PRIMARY KEY, -- char_id UNIQUE NOT NULL,
    chair_name varchar,
    dean varchar
);

-- PRIMARY KEY - первоначальный уникальный ключ - он может быть только один в таблице
-- UNIQUE NOT NULL - тоже уникальный идентификатор, который может быть не один




------------------ ОГРАНИЧЕНИЯ 

-- у всех ограничений есть имена

SELECT constraint_name
    FROM infromation_schema.key_column_usage
    WHERE table_name = 'chair'
        AND table_schema = 'public'
        AND column_name = 'chair_id'
; -- должен вывести название для ограничения на chair_id


-- можно создавать CONSTRAINT:


CREATE TABLE chair (
    char_id serial PRIMARY KEY, -- char_id UNIQUE NOT NULL,
    chair_name varchar,
    dean varchar


    --CONSTRAINT PK_chair_char_id PRIMARY KEY (chair_id)
);

ALTER TABLE chair
    DROP CONSTRAINT chair_chair_id_key
;





------------------ ВНЕШНИЙ КЛЮЧ 

-- он будет ограничивать ссылку на другой ключ (тот должен существовать)
-- иначе без такого ограничения можно писать что угодно



CREATE TABLE public.publisher (
    publisher_id integer NOT NULL,
    publisher_name varchar(128) NOT NULL,
    address text NOT NULL,
    
	CONSTRAINT PK_publisher_id PRIMARY KEY(publisher_id)
);

CREATE TABLE public.book (
    book_id integer NOT NULL,
    title text NOT NULL,
    isbn character varying(32) NOT NULL,
    publisher_id integer NOT NULL,
	
	CONSTRAINT PK_book_book_id PRIMARY KEY(book_id)
);


--добавим немного данных в publisher
INSERT INTO publisher 
    VALUES 
        (1, 'Everyman''s Library', 'NY'),
        (2, 'Oxford University Press', 'NY'),
        (3, 'Grand Central Publishing', 'Washington'),
        (4, 'Simon & Schuster', 'Chicago');

--без FK мы можем пихать любые значения
INSERT INTO book
    VALUES  (1, 'The Diary of a Young Girl', '0199535566', 10); -- Everyman's Library

SELECT *
    FROM book
;

TRUNCATE TABLE book;

ALTER TABLE book
    ADD CONSTRAINT fk_books_publisher FOREIGN KEY(publisher_id) REFERENCES publisher(publisher_id);

-- теперь всякую дичь на вставить
INSERT INTO book
    VALUES 
        (1, 'The Diary of a Young Girl', '0199535566', 10);

--если хотим сразу задать ограничение при создании таблицы
DROP TABLE book;

CREATE TABLE public.book (
    book_id integer NOT NULL,
    title text NOT NULL,
    isbn character varying(32) NOT NULL,
    publisher_id integer NOT NULL,
	
	CONSTRAINT PK_book_book_id PRIMARY KEY(book_id),
	CONSTRAINT FK_book_publisher FOREIGN KEY (publisher_id) REFERENCES publisher(publisher_id)
);

--если хотим удалить ограничение
ALTER TABLE book
    DROP CONSTRAINT FK_book_publisher
;

------------------------------------------------ CHECK


-- позволяет создать ограничение с проверкой, т.е.

DROP TABLE IF EXISTS book;

CREATE TABLE public.book (
    book_id integer NOT NULL,
    title text NOT NULL,
    isbn character varying(32) NOT NULL,
    publisher_id integer NOT NULL,
	  
	CONSTRAINT PK_book_book_id PRIMARY KEY(book_id)
);


ALTER TABLE book
    ADD COLUMN price decimal CONSTRAINT CHK_book_price CHECK (price > 0)
;


INSERT INTO book
    VALUES
        (1, 'title', 'isbn', 1, -1.5)
;



------------------------------------------------ DEFAULT

-- значение по умолчанию (как бы ограничение)

CREATE TABLE customer(
	customer_id serial,
	full_name text,	
	status char DEFAULT 'r',
	
	CONSTRAINT PK_customer_id PRIMARY KEY(customer_id),
	CONSTRAINT CHK_customer_status CHECK (status = 'r' or status = 'p')
);

INSERT INTO customer
    VALUES
        (1, 'name')
;

SELECT *
    FROM customer
;

INSERT INTO customer
    VALUES
        (2, 'name', 'p')
;

ALTER TABLE customer
    ALTER COLUMN status DROP DEFAULT
;

ALTER TABLE customer
    ALTER COLUMN status SET DEFAULT 'r'
;

SELECT * 
    FROM customer
;




------------------------------------------------------ ПОСЛЕДОВАТЕЛЬНОСТИ (счётчики)

-- serial - это число из последовательности

-- создадим
CREATE SEQUENCE seq1;

-- взять следующее из последовательности
SELECT nextval('seq1');
-- взять текущее
SELECT currval('seq1');
-- последнее
SELECT lastval('seq1');

-- true - восходящая последовательность
SELECT satval('seq1', 16, true); -- 
SELECT currval('seq1'); -- 16
SELECT nextval('seq1'); -- 17


-- инкремент можно задавать

CREATE SEQUENCE IF NOT EXISTS seq1 INCREMENT 16;
SELECT nextval('seq2'); -- 1 + 16 = 17


-- и некоторые другие

CREATE SEQUENCE IF NOT EXISTS seq3 
    INCREMENT 16
    MINVALUE 0
    MAXVALUE 128
    START WITH 0
; -- после достижения 128 будет ОШИБКА

-- изменить последовательность и перезапустить её?

ALTER SEQUENCE seq3 RENAME TO seq4;
ALTER SEQUENCE seq4 RESTART WITH 16;

-- удалить

DROP SEQUENCE seq4;



------------ посл + таблицы

DROP TABLE IF EXISTS book;

CREATE TABLE book (
    book_id int NOT NULL, -- book_id serial NOT NULL, будет последовательность
    title text NOT NULL,
    isbn varchar(32) NOT NULL,
    publisher_id int NOT NULL,

    CONSTRAINT PK_book_book_id PRIMARY KEY(book_id)
);


-- создадим последовательность
CREATE SEQUENCE IF NOT EXISTS book_book_id_seq
    START WITH 1
    OWNED BY book.book_id
; -- НАЗНАЧАЕМ на поле book_id

-- но этого недостаточно! потому что нужно навесить CONSTRAINT DEFAULT, которая будет вызывать nextval('seql')

ALTER TABLE book
    ALTER COLUMN book_id SET DEFAULT nextval('book_book_id_seq')
;

INSERT INTO book(title, isbn, publisheR_id)
    VALUES
        ('title', 'isbn', 1)
;



------------------------------------------------------- сделать выборку и вставить туда данные в таблицу

SELECT *
    INTO best_authors
    FROM author
    WHERE rating >= 4.5
;


INSERT INTO best_authors
    SELECT *
    FROM author
    WHERE rating < 4.5
;







------------------------------------------------------- update delete

SELECT * from author;
-- изменить поля в таблице
UPDATE author
    SET fullname = 'Alias', rating = 5
    WHERE author_id = 1 -- уникально идентифицирует строчку
; -- обновим

-- удалиц
DELETE FROM author
    WHERE rating < 4.5
; -- без WHERE удалится всё (и запишутся логи в отличие от TRUNCATE)


-------------------------------------------------------------- returning

-- позволяет возвращать какие-то данные
INSERT INTO book (title, isbn, publisher_id)
    VALUES 
        ('title', 'isbn', 3)
    RETURNING *
;