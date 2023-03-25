from os.path import exists

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
from fastapi.exceptions import HTTPException

app = FastAPI()

origins = [
    "http://localhost",
    "http://localhost:8080",
    "http://localhost:8000",
    "http://localhost:3000",
    "http://127.0.0.1:8000"
] # разрешит связь с этими адресами

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

@app.get("/api")
def read_root():
    return {"message": "Hello World"}

@app.get(path="/image/{id}", tags=['images'], name='get Image', description='возвращает картинку амогуса')
def get_image(id : int):
    if exists(f'./imgs/image_{id}.png') : 
        return FileResponse(f'./imgs/image_{id}.png')
    else :
        raise HTTPException(status_code=404, detail="Image not found")