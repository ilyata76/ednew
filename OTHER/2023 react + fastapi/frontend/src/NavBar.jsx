import React from "react";
import {Link} from "react-router-dom";


const NavBar = () => {
    return (
        <nav>
            <ul>
                <li><Link to="/home">home</Link></li>
                <li><Link to="/">root</Link></li>
            </ul>
        </nav>
    );
}

export default NavBar; 