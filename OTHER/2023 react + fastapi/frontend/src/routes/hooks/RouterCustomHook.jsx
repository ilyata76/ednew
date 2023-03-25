import React from 'react';
import useCount from '../../hooks/useCount.jsx';

const RouterCustomHook = () => {

    let [count, decrement, increment] = useCount(() => { return 0; });

    return (
        <div>
            <button onClick={decrement}>-</button>
            {count}
            <button onClick={() => {increment()}}>+</button>
        </div>
    );
}


export default RouterCustomHook;