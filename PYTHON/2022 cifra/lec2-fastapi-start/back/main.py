from fastapi import FastAPI, Query
from routers.user_router import user_router

app = FastAPI()

@app.get("/")
def ping() :
    return "pong"

@app.get(path="/hello",
    tags=['hello'],
    name='Печатай Hello, world!',
    description='Возвращает типовое приветствие'
    )
def print_hello() :
    return {"msg" : "Hello, world!"}

@app.get("/world")
def print_world() :
    return {"msg" : "World, hello!"}

@app.get("/print") 
def print_something(s : str = Query(default='трава', title='Строка поиска')) : # запрос типа http://127.0.0.1:8000/print?s=kak%20tvoi%20dela%3F
    return {"msg" : f"Печатаю что-то {s}"} 

@app.get("print2/{something}")
def print2_something(something: int) :
    return {"msg" : f"Печатаю что-то {something}"} 

# router позволяет изолировать всякие штуки


app.include_router(user_router) # добавили в приложние роутер