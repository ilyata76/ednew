.read fa19_u1337.sql

CREATE TABLE obedience AS
  SELECT seven, instructor FROM students;

CREATE TABLE smallest_int AS
  SELECT time, smallest FROM students WHERE smallest > 2 ORDER BY smallest LIMIT 20;

CREATE TABLE matchmaker AS
  SELECT st1.pet, st1.song, st1.color, st2.color 
        FROM students AS st1, students AS st2 WHERE st1.pet = st2.pet and st1.song = st2.song and st1.time < st2.time ORDER BY st1.time;

CREATE TABLE smallest_int_having AS
  SELECT time, smallest FROM students GROUP BY smallest HAVING count(*) = 1;

CREATE TABLE fa19favpets AS
  SELECT pet, count(pet) FROM students GROUP BY pet HAVING count(pet) > 1 ORDER BY count(pet) DESC, pet DESC;

CREATE TABLE fa19dog AS
  SELECT pet, count(pet) FROM students GROUP BY pet HAVING pet = "собака";

CREATE TABLE obedienceimages AS
  SELECT seven, instructor, count(instructor) FROM students WHERE seven = "7" GROUP BY instructor;