import React from "react";
import {Link} from "react-router-dom";


const NavBar = () => {
    return (
        <nav>
            <ul>
                <li><Link to="/">root</Link></li>
                <li><Link to="/api">hello fast api</Link></li>
                <li><Link to="/canvas">canvas</Link></li>
                <li><Link to="/iframe">iframe</Link></li>
                <li><Link to="/hooks">custom hooks</Link></li>
                <li><Link to="/form">form with reducer</Link></li>
                <li><Link to="/css">css auto</Link></li>
            </ul>
        </nav>
    );
}

export default NavBar; 