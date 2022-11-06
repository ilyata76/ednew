from hashlib import sha256

from fastapi import FastAPI, HTTPException
from dataclasses import dataclass

from typing import List

import time

# pgsql
import psycopg2 # psycopg2-binary


from prettytable import from_db_cursor

# для рандомной солевой строчки
from string import ascii_lowercase, digits
from random import sample
#

import jwt

from fastapi import Depends, status
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm

# 


app = FastAPI()

LENGHT_OF_RANDOM_STRING : int = 16

ACCESS_TOKEN_EXPIRE_MINUTES = 30  # min
JWT_SECRET = "ABOBUS"
JWT_ALGORITHM = "HS256"

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login", scheme_name="JWT")

def generate_random_string(LENGHT_OF_RANDOM_STRING : int) :
    s : str = ascii_lowercase + digits
    return ''.join(sample(s, LENGHT_OF_RANDOM_STRING))

class DB :
    def __init__(self, dbname : str, user : str, password : str, host : str) :
        self.connection = psycopg2.connect(dbname=dbname, user=user, password=password, host=host)
        self.cursor = self.connection.cursor()

    def getConnection(self) :
        return self.connection

    def getCursor(self) :
        return self.cursor

    # def select(self, what : str, where : str) :
    #     self.cursor.execute(f"SELECT {what} FROM authme {where}")

    def execute(self, fstring : str) :
        self.cursor.execute(fstring)

    def commit(self) :
        self.connection.commit()

    def close(self) :
        self.cursor.close()
        return self.connection.close()

    def __str__(self) :
        return str(from_db_cursor(self.cursor))

#################

@dataclass
class User :
    id : int
    username : str
    realname : str
    regdate : int
    lastlogin : int

@dataclass
class UserList :
    count : int
    users: List[User]

@dataclass
class TokenPayload:
    user : User

@dataclass
class Token:
    access_token : str

#################

def tokenResponse(token : str):
    return Token(access_token=token)

def signJWT(user : User):
    #payload = TokenPayload(user=user).__dict__
    payload = user.__dict__
    token = jwt.encode(payload, JWT_SECRET, algorithm=JWT_ALGORITHM)
    return tokenResponse(token)

def decodeJWT(token: str):
    try:
        decoded_token = jwt.decode(token, JWT_SECRET, algorithms=[JWT_ALGORITHM])
        return decoded_token
    except:
        return {}

async def get_current_user(token: str = Depends(oauth2_scheme)):
    user = decodeJWT(token=token)#.get("user")
    return user

async def get_current_active_user(current_user: User = Depends(get_current_user)):
    # проверка: не истёк ли токен TODO
    return current_user

def getUserOAuth(username : str, password : str) :
    postgres_session : DB = DB("authme", "authme", "12345", "localhost")
    postgres_session.execute(
        f"SELECT authme.id, authme.username, authme.realname, authme.regdate, authme.lastlogin, authme.password \
            FROM authme \
            WHERE authme.username = '{username.lower()}';"
    ) # username is primary key
    user_info = postgres_session.getCursor().fetchone() # ui[0] == id
    password_template : str = str(user_info[5])
    salt = password_template.split('$')[2]
    hashed_password = password_template.split('$')[3]

    if password_template.split('$')[1] == "SHA" :
        current_password : str = sha256((sha256(password.encode('utf-8')).hexdigest() + salt).encode('utf-8')).hexdigest()
        print(current_password)
        if hashed_password == current_password :
            return User(user_info[0], user_info[1], user_info[2], user_info[3], 0 if user_info[4] is None else user_info[4]) # TODO return scheme
    return None

#################

@app.get("/users", name="Пользователи", response_model=UserList)
async def getUsers() :
    try :
        users = []
        postgres_session : DB = DB("authme", "authme", "12345", "localhost") # если вынести за пределы, всё рушится (?!)
        postgres_session.execute(f"SELECT authme.id, authme.username, authme.realname, authme.regdate, authme.lastlogin FROM authme;")

        for row in postgres_session.getCursor() :
            users.append(User(row[0], row[1], row[2], row[3], 0 if row[4] is None else row[4]))

        postgres_session.commit()
        postgres_session.close()

        if len(users) != 0 :
            return UserList(count=len(users), users=users)
        else : 
            raise HTTPException(status_code=404, detail="Not found")
    
    except HTTPException as error:
        raise HTTPException(status_code=error.status_code, detail=error.detail) 
    # except:
    #     raise HTTPException(status_code=500, detail="Internal Server Error")

@app.post('/registernotsafe', name="Зарегистрировать", description="Пароль и соль хешируются и генерируются на сервере", response_model=User)
async def registerNotSafe(login : str, password : str) : # нет проверок на то что уже существует
    try :
        postgres_session : DB = DB("authme", "authme", "12345", "localhost")
      
        salt : str = generate_random_string(16)
        hashed_password : str = sha256((sha256(password.encode('utf-8')).hexdigest() + salt).encode('utf-8')).hexdigest()
        pasword_template : str = f"$SHA${salt}${hashed_password}"
        
        current_time : int = int(round(time.time() * 1000))
        current_ip : str = '0.0.0.0' # # todo request.ip ?
        
        try :
            postgres_session.execute(
                                        f"INSERT INTO authme (username, realname, password, regdate, regip) VALUES \
                                            ('{login.lower()}', '{login}', '{pasword_template}', {current_time}, '{current_ip}');"
            ) 
        except :
            raise HTTPException(status_code=500, detail="There is already a user")
            
        postgres_session.commit()

        postgres_session.execute(f"SELECT authme.id, authme.username, authme.realname, authme.regdate, authme.lastlogin FROM authme WHERE username='{login.lower()}';")

        server_user_info = postgres_session.getCursor().fetchone()

        postgres_session

        return User(server_user_info[0], server_user_info[1], server_user_info[2], server_user_info[3], 0 if server_user_info[4] is None else server_user_info[4])

    except HTTPException as error:
        raise HTTPException(status_code=error.status_code, detail=error.detail)
    except:
        raise HTTPException(status_code=500, detail="Internal Server Error")

@app.post("/login", response_model=Token)
async def login_for_access_token(form_data: OAuth2PasswordRequestForm = Depends()):
    user = getUserOAuth(form_data.username, form_data.password)
    if user is not None:
        return signJWT(user)
    else :
        raise HTTPException(status_code=404, detail="что-то пошло не так")

@app.get("/users/me/", response_model=User)
async def read_users_me(current_user: User = Depends(get_current_active_user)):
    return current_user

################













