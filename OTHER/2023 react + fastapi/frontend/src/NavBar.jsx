import React from "react";
import {Link} from "react-router-dom";


const NavBar = () => {
    return (
        <nav>
            <ul>
                <li><Link to="/home">home</Link></li>
                <li><Link to="/">root</Link></li>
                <li><Link to="/images">images</Link></li>
                <li><Link to="/iframe">IFRAME</Link></li>
            </ul>
        </nav>
    );
}

export default NavBar; 