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

// теперь попробуем что-то посложнее, чем просто запуск приложения - попробуем сервер
// для работы сервера нужен набор обработчиков, фабрика, которая будет создавать новый обработчик, а также
//			всё сопутствующее к этому

// опишем обработчик дял какого-то конкретного случая, который определим потом

class MotherHandler : public Poco::Net::HTTPRequestHandler {
public:
	virtual void handleRequest(Poco::Net::HTTPServerRequest& req,
		Poco::Net::HTTPServerResponse& res) {
			
			// просто вывод в консольнку
			std::cout << "Mother request was called" << std::endl;
			// .send() можно вызывать ТОЛЬКО ОДИН РАЗ
			std::ostream& reply = res.send();
			
			// сюда можно записывать наш результат
			reply << "U have called Mother request" << std::endl;

			// установим статус ОК (200)
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
			// вычленим URI
			if (request.getURI() == "/mother") {
				return new MotherHandler(); // и создадим обработчик MotherHandler;
			}
			else std::cout << request.getURI();

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

ilyat@DESKTOP : C:\Users\ilyat : 29.09.2022 16:05:03
>  curl ‘http://localhost:8765/mother’


StatusCode        : 200
StatusDescription : OK
Content           : {85, 32, 104, 97...}
RawContent        : HTTP/1.1 200 OK
					Connection: Close
					Date: Thu, 29 Sep 2022 13:05:04 GMT

					U have called Mother request

Headers           : {[Connection, Close], [Date, Thu, 29 Sep 2022 13:05:04 GMT]}
RawContentLength  : 29

*/