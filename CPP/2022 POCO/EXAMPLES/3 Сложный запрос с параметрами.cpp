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

// ТЕПЕРЬ УСЛОЖНИМ ДЛЯ сложных запросов

#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>

class MotherHandler : public Poco::Net::HTTPRequestHandler {
public:
	virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res) {
			
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
				return new MotherHandler(); // и создадим обработчик MotherHandler;
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

/*
В ИТОГЕ ПОЛУЧИЛИ:

ilyat@DESKTOP : C:\Users\ilyat : 29.09.2022 16:24:32
>  curl ‘http://localhost:8765/mother?presented-param=15&multi-param=17&multi-param=28’


StatusCode        : 200
StatusDescription : OK
Content           : {112, 114, 101, 115...}
RawContent        : HTTP/1.1 200 OK
					Connection: Close
					Date: Thu, 29 Sep 2022 13:24:35 GMT

					presented param is 15
					dummy param is default Dummy Param
					***************** All parametrs ****************
					presented-param	is	15
					multi-param	is	17
					multi-param	is	28
Headers           : {[Connection, Close], [Date, Thu, 29 Sep 2022 13:24:35 GMT]}
RawContentLength  : 164

*/