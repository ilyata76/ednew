import React, { useEffect, useReducer, useRef } from 'react';


const FORM_ACTIONS = {
    setName: "setName",
    setText: "setText",
    setRating: "setRating",
};

const reducer = (state, action) => {
    switch(action?.type) {
        case FORM_ACTIONS.setName :
            return { name : action.payload.name, text: "", rating: 0};
        case FORM_ACTIONS.setText :
            return { ...state, text: action.payload.text};
        case FORM_ACTIONS.setRating :
            return { ...state, rating: action.payload.rating};
        default:
            return state;
    }
};



const INITIAL_STATE = {
    name: "абоб",
    text: "тттт",
    rating: 10
}

const RouterForm = () => {

    const [state, dispatch] = useReducer(reducer, INITIAL_STATE);

    const onNameChange = (event) => dispatch(
        { type: FORM_ACTIONS.setName, payload: {name: event.target.value}}
    );

    const onTextChange = (event) => dispatch(
        { type: FORM_ACTIONS.setText, payload: {name: event.target.value}}
    );

    const onRatingChange = (event) => dispatch(
        { type: FORM_ACTIONS.setRating, payload: {name: event.target.value}}
    );


    const ref = useRef(); // {current: ...} для взаимодействия с DOM

    useEffect( // вызывает свою логику при изменении массива зависимостей
        () => {
            ref.current?.focus();

            return () => {}; // эта функция выполнится при следующем рендере
        }, 
        [] // пустой массив зависимостей значит, что только при первом рендере произойдёт
    );


    return (
        <div>
            <label>
                Name:
                <input 
                    ref={ref}
                    value={state.name}
                    onChange={onNameChange} // вызовет диспач с соотв эвентом, а тот редьюсер
                    type="text"
                />
            </label>
            <br/>
            <label>
                text:
                <input 
                    value={state.text}
                    onChange={onTextChange}
                    type="text"
                />
            </label>
            <br/>
            <label>
                rate:
                <input 
                    value={state.rating}
                    onChange={onRatingChange}
                    type="number"
                />
            </label>
        </div>
    )
}

export default RouterForm;