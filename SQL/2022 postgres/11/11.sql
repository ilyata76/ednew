-- ИНДЕКСЫ позволяют оптимизировать и ускорять выборку данных
-- сам по себе индекс это структура данных

------ обычный ИНДЕКС B-tree
-- индекс может поддерживать < > <= >= = 
-- индексирует NULL
-- поддерживает LIKE 'abs%'
-- сложность поиска O(logN)

-- ХЕШИРОВАННЫЙ ИНДЕКС
-- поддерживает только оператор =
-- сложность поиска О(1)
-- не рекомендуется
-- не отражается в журналах

--------------------

CREATE TABLE perf_test(
    id int,
    reason text COLLATE "C", -- collation показывает как сравнивать строки
    annotation text COLLATE "C",
); -- primary key сам создаёт индекс

/*
Сначала небольшое введение о том, что же такое Collation. 
В SQL Server параметр Collation указывает серверу, как 
нужно сортировать и сравнивать строки. Вот, например, строки 
“Apple” и “apple”. Они разные или нет? Это зависит от указанного 
Collation. Если с регистром все более менее понятно, то что делать 
с примером “елка” и “ёлка”? Считать их как одинаковые или как разные? 
Это все тоже в Collation.
*/



INSERT INTO perf_test(id, reason, annotation)
    SELECT s.id, md5(random()::text), null
    FROM generate_series(1, 10000000) AS s(id)
    ORDER BY random()
; -- заполнили рандомом до 10 млн строк

UPDATE perf_test
    SET annotation = md5(UPPER(random()::text))
;

SELECT * FROM perf_test
    LIMIT 10
; -- селект долгий занимает > 1 sec

-- создадим индекс

CREATE INDEX idx_perf_test_id ON perf_test(id); -- даст индексный поиск по id
CREATE INDEX idx_perf_test_reason_annotation ON perf_test(reason, annotation);
-- даст индексное сканированиек по reason, annotation и reason (но нe по annotation!)

-- укажет что делает
EXPLAIN
SELECT * FROM perf_test
    LIMIT 10
;

-- укажет что делает и немного ускорит
EXPLAIN ANALYZE
SELECT * FROM perf_test
    LIMIT 10
    WHERE annotation LIKE 'ab%'
;


-- попробуем
SELECT * FROM perf_test
    WHERE annotation LIKE 'ab%' AND reason LIKE 'bc%'
; -- 68 миллисекунд!