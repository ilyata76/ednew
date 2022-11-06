from dataclasses import dataclass # можно использовать для возвращемых значений
from datetime import datetime
from http.client import HTTPException
from typing import List, Optional
from pydantic import BaseModel

from fastapi import FastAPI, Query, APIRouter, Response

@dataclass
class User :
    id: int
    username: str
    first_name: str
    last_name: str
    age: int
    created_at: datetime

@dataclass
class UserList:
    count : int
    users: List[User]

class UserSchema(BaseModel) :
    id : int
    username : str
    first_name: str
    last_name: str
    age: int
    created_at: datetime

    class Config : # такой класс задаст пример возвращаемого значения
        schema_extra = {
            'example' : {
                'id' : 1,
                'username' : 'jonh1', 
                'first_name' : 'J',
                'last_name' : 'D',
                'age' : 3,
                'created_at' : datetime.now()
            }
        }

# если поля будут опциональные?
class UpdateUserSchema(BaseModel) :
    id : Optional[int]
    username: Optional[str]
    first_name: Optional[str]
    last_name: Optional[str]
    age: Optional[int]
    created_at: Optional[datetime]