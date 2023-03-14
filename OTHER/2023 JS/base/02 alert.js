"use strict"; // "современный режим"


let message;
message = 'Hello'; // let message = 'Hello!';

let user = 'John', age = 25, message1 = 'Hello';

// let и const ведут себя одинаково по отношению к лексическому окружению, области видимости.
// Для «var» не существует блочной области видимости, только - в функции(!)
// «var» допускает повторное объявление
// «var» обрабатываются в начале запуска функции
if (true) {
    var test = true;
} alert(test);

alert(message);

/*
    коммент
*/

// коммент

const CONSTANT = '18.04.1982';
//CONSTANT = '01.01.2001'; // ошибка, константу нельзя перезаписать!

alert( 1 / 0 ); // Infinity
alert( Infinity ); // Infinity
alert( "не число" / 2 ); // NaN, такое деление является ошибкой
alert( NaN + 1 ); // NaN
alert( 3 * NaN ); // NaN
alert( "не число" / 2 - 1 ); // NaN

const bigInt = 1234567890123456789012345678901234567890n;

let str = "Привет";
let str2 = 'Одинарные кавычки тоже подойдут';
let phrase = `Обратные кавычки позволяют встраивать переменные ${str}`;

let name1 = "Иван";

// Вставим переменную
alert( `Привет, ${name1}!` ); // Привет, Иван!

// Вставим выражение
alert( `результат: ${1 + 2}` ); // результат: 3

alert( "результат: ${1 + 2}" ); // ничего

let isGreater = 4 > 1;

alert( isGreater ); // true (результатом сравнения будет "да")

let age1 = null; // это - отдельный объект
age1 = undefined;

// Обычно null используется для присвоения переменной «пустого» или «неизвестного» значения, а undefined – для проверок, была ли переменная назначена.


typeof undefined // "undefined"

typeof 0 // "number"

typeof 10n // "bigint"

typeof true // "boolean"

typeof "foo" // "string"

typeof Symbol("id") // "symbol"

typeof Math // "object"  (1)

typeof null // "object"  (2)

typeof alert // "function"  (3)