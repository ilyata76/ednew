# ed.cpp.ws
WinSock2 TCP/IP
Заголовки парсятся, эндпоинт /a/b/c вычленяется
Логика прописывается в отдельной функции (или лямбда), которая будет параметром для Server{ip, port}.run;

докс майков: https://docs.microsoft.com/ru-ru/windows/win32/winsock/

OUTPUT:
```
raw: 

GET /asgd/sdfb HTTP/1.1
Host: localhost
Connection: keep-alive
sec-ch-ua: "Chromium";v="104", " Not A;Brand";v="99", "Yandex";v="22"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"
DNT: 1
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.114 YaBrowser/22.9.1.1095 Yowser/2.5 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: none
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Accept-Encoding: gzip, deflate, br
Accept-Language: ru,en;q=0.9
Cookie: _ym_uid=1660940117101254770; _ym_isad=1




processed: 

GET	-	/asgd/sdfb HTTP/1.1
Host	-	localhost
Connection	-	keep-alive
sec-ch-ua	-	"Chromium";v="104", " Not A;Brand";v="99", "Yandex";v="22"
sec-ch-ua-mobile	-	?0
sec-ch-ua-platform	-	"Windows"
DNT	-	1
Upgrade-Insecure-Requests	-	1
User-Agent	-	Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.114 YaBrowser/22.9.1.1095 Yowser/2.5 Safari/537.36
Accept	-	text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site	-	none
Sec-Fetch-Mode	-	navigate
Sec-Fetch-User	-	?1
Sec-Fetch-Dest	-	document
Accept-Encoding	-	gzip, deflate, br
Accept-Language	-	ru,en;q=0.9
Cookie	-	_ym_uid=1660940117101254770; _ym_isad=1



endpoint: /asgd/sdfb
```