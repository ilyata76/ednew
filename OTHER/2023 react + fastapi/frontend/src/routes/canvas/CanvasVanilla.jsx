import React from "react";
import { useEffect } from "react";


const CanvasVanilla = () => {

    const canvasRef = React.useRef(null);

    useEffect(() => {
       const context = canvasRef.current.getContext("2d"); 
       context.fillRect(0, 0, 300, 300);
    });

    return (
        <>
            <h2>Ванильный canvas</h2>
            <canvas ref={canvasRef} />
            <p>---</p>
        </>
    );
}

export default CanvasVanilla;