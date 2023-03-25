import React from "react";
import { useState, useEffect } from "react";

const INITIAL_STATE = "";

const Images = () => {
    let [image, setImage] = useState(INITIAL_STATE);

    const getImage = async () => {
        const requestOptions = {
            method: "GET",
            headers : {
              "Content-Type": "image/png"
            }
        };
        const response = await fetch('/image/1', requestOptions);
        
        if (!response.ok) {
            console.log(response.status);
        } else {
            const res = await response.blob();
            const imageObjectURL = URL.createObjectURL(res);
            console.log(response.status); 
            setImage(imageObjectURL);
        }
    };

    useEffect( () => {
        getImage();
    }, []);

    return (
        <div>
            <h2>Загруженная картинка с сервера</h2>
            <img src={image} alt="картиночка"/>
            <h2>просто обращение к серверу</h2>
            <img src="/image/2" alt="почему он ругается на слово имедж?"/>
        </div>
    );
}

export default Images;