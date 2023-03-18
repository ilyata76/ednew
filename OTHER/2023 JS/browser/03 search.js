"use strick";


{

    // получить элемент
    let elem = document.getElementById('elem');

    // сделать его фон красным
    elem.style.background = 'red';

}

{
    // <div id="elem">
    // <div id="elem-content">Элемент</div>
    // </div>
    elem.style.background = 'red'; // не рекомендуется
}

{ // CSS SELECTOR
    // <ul>
        // <li>Этот</li>
        // <li>тест</li>
    // </ul>
    // <ul>
        // <li>полностью</li>
        // <li>пройден</li>
    // </ul>

    let elements = document.querySelectorAll('ul > li:last-child');

    for (let elem of elements) {
      alert(elem.innerHTML); // "тест", "пройден"
    }
}

{
    // <a href="http://example.com/file.zip">...</a>
    // <a href="http://ya.ru">...</a>
    
    // может быть любая коллекция вместо document.body.children
    for (let elem of document.body.children) {
        if (elem.matches('a[href$="zip"]')) {
            alert("Ссылка на архив: " + elem.href );
        }
    } // matches проверяет, удовлетворяет ли селектор
}

{ // поиск ближайшего предка - closest


    // <h1>Содержание</h1>

    // <div class="contents">
    // <ul class="book">
    //     <li class="chapter">Глава 1</li>
    //     <li class="chapter">Глава 2</li>
    // </ul>
    // </div>    

    let chapter = document.querySelector('.chapter'); // LI

    alert(chapter.closest('.book')); // UL
    alert(chapter.closest('.contents')); // DIV
  
    alert(chapter.closest('h1')); // null (потому что h1 - не предок)

}

{
    // получить все элементы div в документе
    let divs = document.getElementsByTagName('div');    

    //
    let inputs = table.getElementsByTagName('input');

    for (let input of inputs) {
      alert( input.value + ': ' + input.checked );
    }
    // работает (если есть input)
    document.getElementsByTagName('input')[0].value = 5;
}

// все getElementsBy* - живая коллекция => можно изменять в реальном времени
// .