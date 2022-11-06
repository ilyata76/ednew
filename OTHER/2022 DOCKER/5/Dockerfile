FROM python
WORKDIR /app
COPY . . 

# создадим ENV переменную
ENV PORT 4200

# и используем его
EXPOSE ${PORT}

# если мы удалим контейнер - то удалятся и все остальные, например, базы данных и пр.
# МОЖНО создать docker volume - какую-то общую папку, к которой докер-контейнер будет только лишь иметь доступ

VOLUME ["/app/data"]
#docker run -d -p 1:2 -v logs:/app/data
# дали имя logs
# volume хранится где-то внутри докера и к нему может иметь доступ любой контейнер
# docker volume для управления ими


CMD ["python", "py.py"]

# docker run -d -p 3000:4200 -e PORT=80 -e ABOBUS=10 --rm --name abobus_name(имя конт) abobus_name:abobus_version(образ)

# можно подцепить .env файл
# --env-file ./path/to/.env


# make-file круто


# https://youtu.be/QF4ZF857m44
# -v первый путь на хостовой машине: второй путь внутри контейнера
# -v имя volume: путь внутри контейнера