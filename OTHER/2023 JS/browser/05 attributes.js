"use strick";

{ // можем добавлять свои свойства DOM-объектам
    document.body.myData = {
        name: 'Caesar',
        title: 'Imperator'
      };
      
      alert(document.body.myData.title); // Imperator
}

{
    document.body.sayTagName = function() {
        alert(this.tagName);
      };
      
      document.body.sayTagName(); // BODY (значением "this" в этом методе будет document.body)
}

{ // и менять встроенные
    Element.prototype.sayHi = function() {
        alert(`Hello, I'm ${this.tagName}`);
      };
      
      document.documentElement.sayHi(); // Hello, I'm HTML
      document.body.sayHi(); // Hello, I'm BODY
}

{
    /* <body id="test" something="non-standard">
    <script>
        alert(document.body.id); // test
        // нестандартный атрибут не преобразуется в свойство
        alert(document.body.something); // undefined
    </script>
    </body> */


    // elem.hasAttribute(name) – проверяет наличие атрибута.
    // elem.getAttribute(name) – получает значение атрибута.
    // elem.setAttribute(name, value) – устанавливает значение атрибута.
    // elem.removeAttribute(name) – удаляет атрибут.


    {/* <body>
    <div id="elem" about="Elephant"></div>

    <script>

    </script>
    </body> */}

    alert( elem.getAttribute('About') ); // (1) 'Elephant', чтение

    elem.setAttribute('Test', 123); // (2), запись

    alert( elem.outerHTML ); // (3), посмотрим, есть ли атрибут в HTML (да)

    for (let attr of elem.attributes) { // (4) весь список
        alert( `${attr.name} = ${attr.value}` );
    }

}

{ // некоторые свойства синхронизированы


    let input = document.querySelector('input');

    // атрибут => свойство
    input.setAttribute('id', 'id');
    alert(input.id); // id (обновлено)
  
    // свойство => атрибут
    input.id = 'newId';
    alert(input.getAttribute('id')); // newId (обновлено)
}

{ // не все - строки
    alert(input.getAttribute('checked')); // значение атрибута: пустая строка
    alert(input.checked); // значение свойства: true
}

{
    // строка
    alert(div.getAttribute('style')); // color:red;font-size:120%

    // объект
    alert(div.style); // [object CSSStyleDeclaration]
    alert(div.style.color); // red
}

{
      // атрибут
  alert(a.getAttribute('href')); // #hello

  // свойство
  alert(a.href ); // полный URL в виде http://site.com/page#hello
}