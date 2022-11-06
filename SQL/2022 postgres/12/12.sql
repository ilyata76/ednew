--- ОКОННЫЕ ФУНКЦИИ


/*
Синтаксис примерно такой:
    функция OVER окно
    
Окно — это некоторое выражение, описывающее набор строк, которые будет обрабатывать функция и порядок этой обработки.
Причем окно может быть просто задано пустыми скобками (), т.е. окном являются все строки результата запроса.



*/

SELECT     id,     section,     header,     score,     row_number() OVER ()  AS num
    FROM news; -- здесь добавится row_number как num к селекту в окне всех строк
/*
 id | section |  header   | score | num 
----+---------+-----------+-------+-----
  1 |       2 | Заголовок |    23 |   1
  2 |       1 | Заголовок |     6 |   2
  3 |       4 | Заголовок |    79 |   3
  4 |       3 | Заголовок |    36 |   4
  5 |       2 | Заголовок |    34 |   5
  6 |       2 | Заголовок |    95 |   6
  7 |       4 | Заголовок |    26 |   7
  8 |       3 | Заголовок |    36 |   8
*/

-- В оконное выражение можно добавить ORDER BY, тогда можно изменить порядок обработки.

SELECT id,     section,     header,     score,     row_number() OVER (ORDER BY score DESC)  AS rating
    FROM news
    ORDER BY id; -- теперь row_number будет даваться по score, а вывод всё равно по id

/*
 id | section |  header   | score | rating 
----+---------+-----------+-------+--------
  1 |       2 | Заголовок |    23 |      7
  2 |       1 | Заголовок |     6 |      8
  3 |       4 | Заголовок |    79 |      2
  4 |       3 | Заголовок |    36 |      4
  5 |       2 | Заголовок |    34 |      5
  6 |       2 | Заголовок |    95 |      1
  7 |       4 | Заголовок |    26 |      6
  8 |       3 | Заголовок |    36 |      3
*/


-- В оконное выражение можно добавить слово PARTITION BY [expression],
-- например row_number() OVER (PARTITION BY section), тогда подсчет будет идти в каждой группе отдельно:

SELECT     id,     section,     header,      score,     row_number() OVER (PARTITION BY section ORDER BY score DESC) AS rating_in_section
    FROM news
    ORDER BY section, rating_in_section; -- тепрь в каждой партиции section Будет даваться один row_number


/*
 id | section |  header   | score | rating_in_section 
----+---------+-----------+-------+-------------------
  2 |       1 | Заголовок |     6 |                 1
  6 |       2 | Заголовок |    95 |                 1
  5 |       2 | Заголовок |    34 |                 2
  1 |       2 | Заголовок |    23 |                 3
  4 |       3 | Заголовок |    36 |                 1
  8 |       3 | Заголовок |    36 |                 2
  3 |       4 | Заголовок |    79 |                 1
  7 |       4 | Заголовок |    26 |                 2
*/


SELECT
    transaction_id,
    change,
    sum(change) OVER (ORDER BY transaction_id) as balance, -- указание ORDER BY говорит о том что считать sum надо построчно
    sum(change) OVER () as result_balance, -- sum() для всех строк сразу
    round(
        100.0 * sum(change) OVER (ORDER BY transaction_id)  /  sum(change) OVER (),
        2
    ) AS percent_of_result, -- друг другу не мешают
    count(*) OVER () as transactions_count
        
    FROM balance_change
    ORDER BY transaction_id;

--  transaction_id | change | balance | result_balance | percent_of_result | transactions_count 
-- ----------------+--------+---------+----------------+-------------------+--------------------
--               1 |   1.00 |    1.00 |          10.50 |              9.52 |                  5
--               2 |  -2.00 |   -1.00 |          10.50 |             -9.52 |                  5
--               3 |  10.00 |    9.00 |          10.50 |             85.71 |                  5
--               4 |  -4.00 |    5.00 |          10.50 |             47.62 |                  5
--               5 |   5.50 |   10.50 |          10.50 |            100.00 |                  5
