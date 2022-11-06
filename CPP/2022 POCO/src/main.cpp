// https://cadovvl.wordpress.com/2015/02/26/poco-http-server/

// делаем HTTP сервер

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>

#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>

#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>

class MotherHandler : public Poco::Net::HTTPRequestHandler {
	public:
		virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
			Poco::Net::HTTPServerResponse& res) override {
			
			// здесь нужнот научиться из request'a отбирать параметры (путь - в фабрике)

			Poco::Net::HTMLForm form(req); // это хранилище ключ-значение
			std::ostream& reply = res.send(); // готовим наш ответ?

			if (form.has("presented-param")) { // если в форме (т.е. в параметрах) есть какой-то параметр
				reply << "presented param is " << form.get("presented-param") << std::endl; // получили
				// если вдруг не найдётся, то выбросится исключение
			}

			reply << "dummy param is "
				<< form.get("dummy-param", "default Dummy Param") // если вдруг не найдётся dummy-param, то выдаст default-значение
				<< std::endl;

			// ну и в конце выведем все параметры через rb-for
			
			reply << "***************** All parametrs ****************" << std::endl;

			for (auto i : form) {
				reply << i.first << "\tis\t" << i.second << std::endl;
			}

			// установим 200 статус
			res.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);
	}
};

class FatherHandler : public Poco::Net::HTTPRequestHandler {
	public:
		virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
			Poco::Net::HTTPServerResponse& res) override {
			
			std::ostream& reply = res.send();
			std::ifstream file;
			file.open("jpeg.jpg", std::ios::binary);

			res.setContentType("image/jpeg");
			
			//reply << "<pre>абобус		 текста</pre>"; это для чёткого отображения текста

			Poco::StreamCopier::copyStream(file, reply);

			std::cout << res.operator[]("Content-Type");
			
			res.setStatus(Poco::Net::HTTPServerResponse::HTTP_OK);

		}
};

// создадим обработчик-фабрику
class CommonRequestHandler : public Poco::Net::HTTPRequestHandlerFactory {
	public:
		CommonRequestHandler() {};

		// переопределим виртуальную функцию, которая будет создавать конкретный обработчик
		virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override {

			// так, из request можно вычленять нужную нам информацию - и метод, и всё остальное
			// вычленим URI и запишем его в отдельную переменную

			Poco::URI uri(request.getURI());

			if (uri.getPath() == "/mother") { // вычленим только путь без параметров
				return new MotherHandler{}; // и создадим обработчик MotherHandler;
			} else if (uri.getPath() == "/father") {
				return new FatherHandler{};
			}

			return nullptr;
		};

};

// переобределим Listener
// переопределим функцию main нашего ServerApplication
// args это аргументы передачи из командной строки в C++ стиле
class Listener : public Poco::Util::ServerApplication {
	virtual int main(const std::vector<std::string>& args) override {
		// создадим объект описывающих параметры HTTP сервера
		Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams();
		// укажем максимальное количество клиентов и потоков для них
		params->setMaxQueued(50);
		params->setMaxThreads(4);

		// захардкодим порт, создадим вебсокет для нашего сервера
		Poco::Net::ServerSocket socket(8765);

		// теперь создадим сервер
		Poco::Net::HTTPServer server(new CommonRequestHandler(), socket, params);
			// где CommonRequestsHandler - CommonRequestHandler() - обработчик-ФАБРИКА, создающая 
			//		обработчик для каждого типа

		// теперь запустим
		server.start();
		waitForTerminationRequest(); // -- ОБЯЗАТЕЛЬНО
		server.stop(); // как только убили - остановили сервер нормально

		return 0; // выход
	}
};




// POCO_SERVER_MAIN(Poco::Util::ServerApplication) // этот макрос как бы правильный для Main
// перепишем его ниже
int main(int argc, char** argv) {                                   
	try {                              
		Listener app;  
		return app.run(argc, argv); 
	} catch (Poco::Exception& exc) {                               
		std::cerr << exc.displayText() << std::endl;    
		return Poco::Util::Application::EXIT_SOFTWARE;  
	}                               
}