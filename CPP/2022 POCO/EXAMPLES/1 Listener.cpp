// https://cadovvl.wordpress.com/2015/02/26/poco-http-server/

// делаем HTTP сервер

#include <Poco/Util/ServerApplication.h>;

#include <vector> 
#include <string> 
#include <iostream>

// переопределим функцию main нашего ServerApplication
// args это аргументы передачи из командной строки в C++ стиле
class Listener : public Poco::Util::ServerApplication {
	virtual int main(const std::vector<std::string>& args) override {
		std::cout << "Use ploho!" << std::endl;
		for (const auto& x : args) {
			std::cout << x << "\n";
		} std::cout << std::endl;
		waitForTerminationRequest();
		std::cout << "Ended normally" << std::endl;
		return 0;
	}
};

// POCO_SERVER_MAIN(Poco::Util::ServerApplication) // этот макрос как бы правильный для Main
// перепишем его ниже
int main(int argc, char** argv) {
	try {
		Listener app;
		return app.run(argc, argv);
	}
	catch (Poco::Exception& exc) {
		std::cerr << exc.displayText() << std::endl;
		return Poco::Util::Application::EXIT_SOFTWARE;
	}
}

// пример выполнения
//>  .\build\Debug\main.exe abobus
//Use ploho!
//abobus
//Ended normally (нажали CTRL+C)