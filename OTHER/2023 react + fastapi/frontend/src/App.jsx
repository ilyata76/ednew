import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom"

import RouterAPI from "./routes/api/RouterAPI.jsx";
import RouterRoot from "./routes/root/RouterRoot.jsx";
import RouterCanvas from "./routes/canvas/RouterCanvas.jsx";
import RouterIframe from "./routes/iframe/RouterIframe.jsx";
import RouterCustomHook from './routes/hooks/RouterCustomHook';
import RouterForm from "./routes/form/RouterForm.jsx";
import RouterCSS from "./routes/css/RouterCSS.jsx";

import NavBar from "./components/NavBar.jsx";


const IFRAME = "<iframe src='mamedzuka/index.html' height=500px width=600px>не поддерживается</iframe>";

const App = () => {
    return (
        <Router>
            <p>то, что не изменится</p>
            <NavBar/>
            <Routes>
                <Route exact path="/" element={<RouterRoot/>}/>
                <Route path="/api" element={<RouterAPI/>}/>
                <Route path="/canvas" element={<RouterCanvas/>}/>
                <Route path="/iframe" element={<RouterIframe iframe={IFRAME}/>}/>
                <Route path="/hooks" element={<RouterCustomHook/>}/>
                <Route path="/form" element={<RouterForm/>}/>
                <Route path="/css" element={<RouterCSS/>}/>
            </Routes>
        </Router>
    );
}

export default App;