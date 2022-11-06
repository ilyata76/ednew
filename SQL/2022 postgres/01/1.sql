DROP TABLE IF EXISTS book CASCADE; -- каскад для зависимых от этой таблицы таблиц
DROP TABLE IF EXISTS publisher CASCADE; -- если существует
DROP TABLE IF EXISTS new_book CASCADE;
DROP TABLE IF EXISTS new_publisher CASCADE;




CREATE TABLE publisher (
    publisher_id integer PRIMARY KEY, -- это УНИКАЛЬНЫЙ КЛЮЧ
	org_name varchar(128) NOT NULL,
	adress text NOT NULL
);

CREATE TABLE book (
    book_id int PRIMARY KEY,
    title text NOT NULL,
    isbn varchar(32) NOT NULL
);

INSERT INTO book VALUES -- вносим данные в таблицу
(1, 'a', '123'),
(2, 'b', '142'),
(3, 'c', '111');

INSERT INTO publisher VALUES
(1, 'adsfdsaf''s', 'sfdag'),
(2, 'sadf', 'bbbb'),
(3, 'dsfag', 'cccc');

ALTER TABLE book ADD COLUMN fk_publisher_id integer; -- таблицы можно модифицировать

-- fk_publisher_id ещё никак не заполнено

SELECT * FROM publisher; -- вывод всех
SELECT * FROM book;

CREATE TABLE new_publisher (
    publisher_id integer PRIMARY KEY, 
	org_name varchar(128) NOT NULL,
	adress text NOT NULL
);

CREATE TABLE new_book (
    book_id int PRIMARY KEY,
    title text NOT NULL,
    isbn varchar(32) NOT NULL,
    fk_publisher_id int REFERENCES publisher(publisher_id) NOT NULL -- ссылаемся на таблицу паблишер и столбец паблишер_айди
);

INSERT INTO new_book VALUES -- теперь прописываем ссылки на паблишеров
(1, 'a', '123', 1),
(2, 'b', '142', 2),
(3, 'c', '111', 3);

INSERT INTO new_publisher VALUES 
(1, 'adsfdsaf''s', 'a'),
(2, 'sadf', 'b'),
(3, 'dsfag', 'c');

SELECT * FROM new_book;