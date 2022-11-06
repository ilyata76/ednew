FROM python

WORKDIR /app

COPY . .

CMD ["python"]

# список контейнеров docker ps
# docker ps -a все контейнеры

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker : 02.10.2022 13:49:43
# >  docker ps -a
# CONTAINER ID   IMAGE          COMMAND             CREATED              STATUS                          PORTS     NAMES
# 490d74eab330   681a302ddbc3   "python index.py"   About a minute ago   Exited (0) About a minute ago             jovial_kowalevski
# ab5d17846f12   681a302ddbc3   "python index.py"   About a minute ago   Exited (0) About a minute ago             unruffled_black
# 96f22d9aa8e3   681a302ddbc3   "python index.py"   About a minute ago   Exited (0) About a minute ago             hopeful_proskuriakova
# 6c088ba3da3e   681a302ddbc3   "python index.py"   3 minutes ago        Exited (0) 3 minutes ago                  nice_brattain

# <--- их много потому что много раз писали docker run

# давайте их удалим (ненужные)
# docker rm <ID> <ID> <ID>

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker : 02.10.2022 13:54:55
# >  docker rm ab5d17846f12 96f22d9aa8e3 6c088ba3da3e
# ab5d17846f12
# 96f22d9aa8e3
# 6c088ba3da3e

# docker container prune УДАЛИТ ВСЕ ОСТАНОВЛЕННЫЕ КОНТЕЙНЕРЫ

# ну и всё они закончились

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker : 02.10.2022 13:55:07
# >  docker ps -a
# CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES


# docker build .

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker\2 : 02.10.2022 13:56:41
# >  docker images
# REPOSITORY   TAG       IMAGE ID       CREATED          SIZE
# <none>       <none>    547f57ced72d   11 seconds ago   921MB
# <none>       <none>    ab4ecebec0a3   7 minutes ago    921MB
# <none>       <none>    681a302ddbc3   10 minutes ago   921MB

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker\2 : 02.10.2022 13:57:00
# >  docker run -it 547f57ced72d
# Python 3.10.7 (main, Sep 13 2022, 14:31:33) [GCC 10.2.1 20210110] on linux
# Type "help", "copyright", "credits" or "license" for more information.
# >>> abobus
# Traceback (most recent call last):
#   File "<stdin>", line 1, in <module>
# NameError: name 'abobus' is not defined
# >>> попали в интерактив




# ОСТАНОВИТЬ
# docker stop <ID>


# УДАЛИТЬ

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker\2 : 02.10.2022 14:00:37
# >  docker rm 0f1275a14bc8
# 0f1275a14bc8

# удалим образ

# ilyat@DESKTOP : D:\CPP_2022\ed\ed.docker\2 : 02.10.2022 14:00:50
# >  docker rmi 547f57ced72d
# Deleted: sha256:547f57ced72d4e598d328814233fa91734216def5fa43cd04cc4b54c01ae69d2




