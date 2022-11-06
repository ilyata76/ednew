#include <iostream>

#include <string>
#include <iostream>
#include <pqxx/pqxx>

// наши таблички
#include <prettytables.hpp>

// C++17 обязательно иначе ошибок навыдаёт

int main() {
    try {
        // зададим параметры подключения
        std::string connectionString = "host=localhost port=5432 dbname=abobus_base user=postgres password=wrong_password";

        // создадим подключение
        pqxx::connection c{ connectionString };

        std::cout << "Connected to " << c.dbname() << "\n\n\n";
        
        // рабочая область
        pqxx::work tx{ c };
        
        // tupples, можно много
        for (auto [fn, ln, title] : tx.query<std::string, std::string, std::string>
            ("SELECT first_name, last_name, title FROM employees ORDER BY first_name")
        ) {
            std::cout << fn << "\t" << ln << "\t" << title << ".\n";
        }

        // также можно вернуть структуру result
        pqxx::result res = tx.exec("SELECT * FROM employees");
        std::cout << "\n\n\n";
        for (size_t i = 0; i < res.size(); ++i) {
            std::cout << res[i][0] << "\t" << res[i][1] << "\t" << res[i][2] << "\n";
        }


        // подключим наши pretty-tables
        Table prettytable; std::cout << "\n\n\n";
        prettytable.set_headers(Row{ {"first_name", "last_name", "title"} });
        for (auto [fn, ln, title] : tx.query<std::string, std::string, std::string>
            ("SELECT first_name, last_name, title FROM employees ORDER BY first_name")
        ) {
            prettytable.add_row(Row{ {fn, ln, title} });
        } std::cout << prettytable;

    } catch (std::exception e) {
        std::cout << e.what();
    }
    //abort();
    return 0;
}