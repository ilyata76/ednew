import React from "react";
import { useState, useLayoutEffect } from "react";

const INITIAL_STATE = "";

const HelloAPI = () => {
    let [message, setMessage] = useState(() => {return INITIAL_STATE;});

    const getWelcomeMessage = async () => {
      const requestOptions = {
        method: "GET",
        headers : {
          "Content-Type": "application/json"
        }
      };
      const response = await fetch('/api', requestOptions);
  
      if (!response.ok) {
        console.log(response.status);
      } else {
        const data = await response.json();
        setMessage(data.message);
      }
    };
  
    // useEffect(() => {
    //   getWelcomeMessage();
    // }, []);

    useLayoutEffect(() => {
      getWelcomeMessage();
    }, []);

    return (   
        (Boolean(message) && <p>{message} from fastAPI</p>) || <p>а где ответ</p>
    );
};

export default HelloAPI;