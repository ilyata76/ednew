from pydantic import BaseModel
from http.client import HTTPException
from typing import List, Optional
from fastapi import FastAPI, Query, APIRouter, Response

from dataclasses import dataclass # можно использовать для возвращемых значений
from datetime import datetime

from routers.schemas import *

users = [
    User(id=1, username='andreq2', first_name='Andrew', last_name='Jonhs', age=23, created_at=datetime.now()),
    {
        'id' : 2,
        'username' : 'abobus', 
        'first_name' : 'Marti',
        'last_name' : 'Fleks', 
        'age' : 32,
        'created_at':datetime.now()
    }, 
    {
        'id' : 3,
        'username' : 'amuma', 
        'first_name' : 'Matew',
        'last_name' : 'Ko', 
        'age' : 82,
        'created_at':datetime.now()
    }
]

user_router = APIRouter(prefix='/users', tags=['Пользователи']) # для разделения логик
 
@user_router.get('/ppp', name="Все пользователи", response_model=List[UserSchema]) # можно и без схемы, если использовать @dataclass
def get_all_users() :
    return users



@user_router.get('/', name="Все пользователи", response_model=UserList)
def get_all_users() :
    return UserList(count=len(users), users=users)

@user_router.post('/', name="добавить пользователя", response_model=User)
def create_user(user : User) :
    users.append(user)
    return user



@user_router.get('/{user_id}', name="Получить пользователя", response_model=User)
def get_user(user_id : int) :
    for user in users :
        if user.id == user_id :
            return user
    raise HTTPException(status_code=404, detail="User not found")


@user_router.delete('/{user_id}', name='Удалить пользователы', response_class=Response)
def delete_user(user_id : int) :
    for i, user in enumerate(tuple(users)) :
        if user.id == user_id :
            del users[i]
            break
    return Response(status_code=204)


@user_router.put('/{user_id}', name="Обновить данные пользователя", response_model=User) 
def update_user(user_id : int, new_user_data: User) :
    for i in range(len(users)) :
        if users[i].id == user_id :
            users[i] = new_user_data
            break
    return new_user_data






@user_router.put('/put/{user_id}', name="обновить", response_model=User)
def update_user(user_id: int, new_user_data: UpdateUserSchema) :
    for i in range(len(users)) :
        if users[i].id == user_id :
            data = new_user_data.dict()
            for key in data:
                if data[key] is not None :
                    setattr(users[i], key, data[key])
            return users[i]
    raise HTTPException(status_code=404, detail="User not found")


