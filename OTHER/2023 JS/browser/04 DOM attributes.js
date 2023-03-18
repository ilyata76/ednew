"use strick";

{ // сложное наследование
    alert( document.body instanceof HTMLBodyElement ); // true
    alert( document.body instanceof HTMLElement ); // true
    alert( document.body instanceof Element ); // true
    alert( document.body instanceof Node ); // true
    alert( document.body instanceof EventTarget ); // true

    alert( document.body.constructor.name ); // HTMLBodyElement
    alert( document.body ); // [object HTMLBodyElement]
}

{ // nodeType старомодно
    let elem = document.body;

    // давайте разберёмся: какой тип узла находится в elem?
    alert(elem.nodeType); // 1 => элемент
  
    // и его первый потомок...
    alert(elem.firstChild.nodeType); // 3 => текст
  
    // для объекта document значение типа -- 9
    alert( document.nodeType ); // 9
}

{ // nodename для не-элементов (коммент и текст, например)
    alert( document.body.nodeName ); // BODY
    alert( document.body.tagName ); // BODY

    // для комментария
    alert( document.body.firstChild.tagName ); // undefined (не элемент)
    alert( document.body.firstChild.nodeName ); // #comment
    
    // for document
    alert( document.tagName ); // undefined (не элемент)
    alert( document.nodeName ); // #document
}

{ // innerHTML - содержимое без тега
    alert( document.body.innerHTML ); // читаем текущее содержимое
    document.body.innerHTML = 'Новый BODY!'; // заменяем содержимое
} // можно менять

{ // outerHTML - не изменяет сам элемент, лишь во внешнем контексте
    alert(elem.outerHTML); // <div id="elem">Привет <b>Мир</b></div>
}

{ // nodeValue || data - для других узлов
    let text = document.body.firstChild;
    alert(text.data); // Привет

    let comment = text.nextSibling;
    alert(comment.data); // Комментарий
}

{ // textContent только текст без тэгов
    // <div id="news">
    //  <h1>Срочно в номер!</h1>
    //  <p>Марсиане атаковали человечество!</p>
    // </div>
      // Срочно в номер! Марсиане атаковали человечество!
    alert(news.textContent);
}

{   // hidden
    // как display: none;
}

{
    // другое встроенное
}