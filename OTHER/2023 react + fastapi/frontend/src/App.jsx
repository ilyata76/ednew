// jsx - js внутри html блоков

import React, {useState, useEffect} from "react";

const App = () => {
  const [message, setMessage] = useState(""); // react фича, храним состояние

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
  }, []); // ещё один react hook

  return (
    <div>
      <h1>{message}</h1>
      <p>ура</p>
    </div>
  );
}

export default App;
