# ed.cpp.libpqxx

Надо дать CMake найти пусть до pg
```
>  cmake -DCMAKE_PREFIX_PATH=E:\PSQL ..
```

RESULT:
```
Connected to abobus_base


Andrew  Fuller  Vice President, Sales.
Anne    Dodsworth       Sales Representative.
Janet   Leverling       Sales Representative.
Laura   Callahan        Inside Sales Coordinator.
Margaret        Peacock Sales Representative.
Michael Suyama  Sales Representative.
Nancy   Davolio Sales Representative.
Robert  King    Sales Representative.
Steven  Buchanan        Sales Manager.



1       Davolio Nancy
2       Fuller  Andrew
3       Leverling       Janet
4       Peacock Margaret
5       Buchanan        Steven
6       Suyama  Michael
7       King    Robert
8       Callahan        Laura
9       Dodsworth       Anne



+————————————+———————————+——————————————————————————+
| first_name | last_name | title                    |
+————————————+———————————+——————————————————————————+
| Andrew     | Fuller    | Vice President, Sales    |
| Anne       | Dodsworth | Sales Representative     |
| Janet      | Leverling | Sales Representative     |
| Laura      | Callahan  | Inside Sales Coordinator |
| Margaret   | Peacock   | Sales Representative     |
| Michael    | Suyama    | Sales Representative     |
| Nancy      | Davolio   | Sales Representative     |
| Robert     | King      | Sales Representative     |
| Steven     | Buchanan  | Sales Manager            |
+————————————+———————————+——————————————————————————+
```