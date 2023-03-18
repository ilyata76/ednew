// NULL значит не существует

// <html> = document.documentElement
// <body> = document.body
// <head> = document.head

// Дети: childNodes, firstChild, lastChild

// elem.childNodes[0] === elem.firstChild
// elem.childNodes[elem.childNodes.length - 1] === elem.lastChild

for (let node of document.body.childNodes) { // это не массив !
    alert(node); // покажет все узлы из коллекции
}

alert( Array.from(document.body.childNodes).filter ); // сделали массив

// это работает только для чтения. изменять таким образом нельзя!

// для коллекции - for of

{}

// Соседи – это узлы, у которых один и тот же родитель.
// Следующий узел того же родителя (следующий сосед) – в свойстве nextSibling, а предыдущий – в previousSibling.
// Родитель доступен через parentNode.

// родителем <body> является <html>
alert( document.body.parentNode === document.documentElement ); // выведет true

// после <head> идёт <body>
alert( document.head.nextSibling ); // HTMLBodyElement

// перед <body> находится <head>
alert( document.body.previousSibling ); // HTMLHeadElement

{}

// children – коллекция детей, которые являются элементами.
// firstElementChild, lastElementChild – первый и последний дочерний элемент.
// previousElementSibling, nextElementSibling – соседи-элементы.
// parentElement – родитель-элемент.


while(elem = elem.parentElement) { // идти наверх до <html>
    alert( elem );
}


// Элемент <table>, в дополнение к свойствам, о которых речь шла выше, поддерживает следующие:
// table.rows – коллекция строк <tr> таблицы.
// table.caption/tHead/tFoot – ссылки на элементы таблицы <caption>, <thead>, <tfoot>.
// table.tBodies – коллекция элементов таблицы <tbody> (по спецификации их может быть больше одного).

// <thead>, <tfoot>, <tbody> предоставляют свойство rows:
// tbody.rows – коллекция строк <tr> секции.

// <tr>:
// tr.cells – коллекция <td> и <th> ячеек, находящихся внутри строки <tr>.
// tr.sectionRowIndex – номер строки <tr> в текущей секции <thead>/<tbody>/<tfoot>.
// tr.rowIndex – номер строки <tr> в таблице (включая все строки таблицы).
// <td> and <th>:
// td.cellIndex – номер ячейки в строке <tr>.