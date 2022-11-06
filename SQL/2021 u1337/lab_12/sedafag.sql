CREATE TABLE courses AS
 SELECT "ТЭЦ" AS course, 14 AS h, 0 AS m, 80 AS len UNION
 SELECT "ГП" , 13 , 30 , 80 UNION
 SELECT "ЯМП" , 12 , 30 , 50 UNION
 SELECT "ВВС" , 12 , 30 , 110 UNION
 SELECT "Матан" , 13 , 30 , 45 UNION
 SELECT "ПсиМыш" , 13 , 0 , 50;
CREATE TABLE locations AS
 SELECT "ТЭЦ" AS name, "7 корпус" AS loc UNION
 SELECT "ГП" , "Ковёркинг" UNION
 SELECT "ЯМП" , "7 корпус" UNION
 SELECT "Матан" , "Башня" UNION
 SELECT "ПсиМыш" , "Башня";

