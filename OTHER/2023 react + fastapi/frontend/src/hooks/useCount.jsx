import { useCallback, useState } from 'react';

const useCount = (initial_state) => {
    let [count, setCount] = useState(initial_state);

    const decrement = useCallback( // чтобы функция не пересоздавалась
        () => {setCount(count - 1)},
        [count]
    );

    const increment = useCallback(
        () => {setCount(count + 1)},
        [count]
    );

    return [count, decrement, increment];
};

export default useCount;