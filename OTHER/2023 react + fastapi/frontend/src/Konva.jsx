import React from "react";
import {Layer, Rect, Stage, Circle } from 'react-konva';

const KonvaCanvas = () => {
    
    return (
            // Stage - is a div wrapper
            // Layer - is an actual 2d canvas element, so you can have several layers inside the stage
            // Rect and Circle are not DOM elements. They are 2d shapes on canvas
        <div>
            <h2>KONVA canvas</h2>

            <Stage width={100} height={100}>
            <Layer>
                <Rect width={50} height={50} fill="red" />
                <Circle x={200} y={200} stroke="black" radius={50} />
            </Layer>
            </Stage>
            <p>---</p>
        </div>
      );
}

export default KonvaCanvas;