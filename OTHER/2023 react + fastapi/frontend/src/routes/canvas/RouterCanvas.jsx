import React from "react";

import CanvasVanilla from "./CanvasVanilla";
import KonvaCanvas from "./Konva";


const RouterCanvas = () => {
    return (
        <div>
            <CanvasVanilla/>
            <KonvaCanvas/>
        </div>
    );
}

export default RouterCanvas;