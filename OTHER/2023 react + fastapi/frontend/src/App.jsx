import React from "react";
import {BrowserRouter as Router, Routes, Route} from "react-router-dom"

import Home from "./Home"

const App = () => {
  return (
    <div>
      <Router>
      <Routes>
        <Route path='/home' element={<Home/>} />
      </Routes>
      </Router>
    </div>
  );
}

export default App;