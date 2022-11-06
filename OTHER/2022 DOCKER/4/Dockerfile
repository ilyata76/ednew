FROM python
WORKDIR /app


COPY . . 

# RUN команды слишком жирные (у нас изменение где-то в коде, а RUN команды не должны меняться)
# он их берёт из кэша


EXPOSE 3000
CMD ["python", "py.py"]



# docker run -d -p 3000:3000 <ID>
# запустить программу в фоновом режиме -d


# docker run -d -p 3000:3000 --name abobus <ID> # это с именем
# docker run -d -p 3000:3000 --name abobus --rm <ID> # он удалится после остановки docker stop abobus


# docker build -t abobus . # обозвали образ
# можно раскидываться тэгами - имя одно - версия как бы разная
# docker build -t abobus:abobversion .


# docker push nick/name - в докерхаб
# docker pull nick/name - из докерхаба


# можно посмотреть цепочку создания образа
# docker image inspect <ID>