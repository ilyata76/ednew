import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom"

import Root from "./Root"
import Home from "./Home"
import NavBar from "./NavBar";
import Iframe from "./Iframe";

import CanvasVanilla from "./CanvasVanilla";
import KonvaCanvas from "./Konva";
import Images from "./Images";

const IFRAME = "<iframe src='mamedzuka/index.html' height=500px width=1600px>не поддерживается</iframe>";

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
          <Route path='/iframe' element={<Iframe iframe={IFRAME}/>} />
        </Routes>
      </Router>

      <CanvasVanilla/>
      <KonvaCanvas/>

    </div>
  );
}

export default App;