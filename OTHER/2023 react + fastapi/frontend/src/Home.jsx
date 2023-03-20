import React from "react";

import ApiHello from "./HelloApi";
import Hello from "./HelloWorld";

const Home = () => {
    return (
        <div>
            <Hello /> 
            <ApiHello />
        </div>
    )
}

export default Home;