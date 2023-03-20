import React from "react";
import { useState, useEffect } from "react";

const INITIAL_STATE = "";

const ApiHello = () => {
    let [message, setMessage] = useState(INITIAL_STATE);

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
  
    useEffect(() => {
      getWelcomeMessage();
    }, []);

    return (   
        <p>{message} from API</p>
    );
};

export default ApiHello;