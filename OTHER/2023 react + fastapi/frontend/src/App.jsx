import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom"

import Root from "./Root"
import Home from "./Home"
import NavBar from "./NavBar";

import CanvasVanilla from "./CanvasVanilla";
import KonvaCanvas from "./Konva";
import Images from "./Images";

const App = () => {
  return (
    <div>
      <Router>
        <NavBar />
        <p>То, что меняться не будет</p>
        <Routes>
          <Route exact path="/" element={<Root/>}/>
          <Route path='/home' element={<Home/>} />
          <Route path='/images' element={<Images/>} />
        </Routes>
      </Router>

      <CanvasVanilla/>
      <KonvaCanvas/>

    </div>
  );
}

export default App;