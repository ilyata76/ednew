import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom"

import Root from "./Root"
import Home from "./Home"
import NavBar from "./NavBar";

const App = () => {
  return (
    <div>
    
      <p>То, что меняться не будет</p>
      

      
      <Router>
        <NavBar />
        <Routes>
          <Route exact path="/" element={<Root/>}/>
          <Route path='/home' element={<Home/>} />
        </Routes>
      </Router>

    </div>
  );
}

export default App;