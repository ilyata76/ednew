{
    let age = 16; // возьмём для примера 16

    if (age < 18) {
      welcome();               // \   (выполнится)
                               //  |
      function welcome() {     //  |
        alert("Привет!");      //  |  Function Declaration доступно
      }                        //  |  во всём блоке кода, в котором объявлено
                               //  |
      welcome();               // /   (выполнится)
    
    } else {
    
      function welcome() {
        alert("Здравствуйте!");
      }
    }
    
    // здесь фигурная скобка закрывается,
    // поэтому Function Declaration, созданные внутри блока кода выше -- недоступны отсюда.
    
    welcome(); // Ошибка: welcome is not defined    
}

{
    let age = prompt("Сколько Вам лет?", 18);

    let welcome = (age < 18) ?
      function() { alert("Привет!"); } :
      function() { alert("Здравствуйте!"); };
    
    welcome(); // теперь всё в порядке    
}

{
    sayHi("Вася"); // Привет, Вася

    function sayHi(name) {
        alert( `Привет, ${name}` );
    }

    // sayHi("Вася"); // ошибка!

    // let sayHi = function(name) {  // (*) магии больше нет
    //     alert( `Привет, ${name}` );
    // };
}

{

  let sum = (a, b) => a + b;

  /* Эта стрелочная функция представляет собой более короткую форму:

  let sum = function(a, b) {
    return a + b;
  };
  */

  alert( sum(1, 2) ); // 3

}

{

  let age = prompt("Сколько Вам лет?", 18);

  let welcome = (age < 18) ?
    () => alert('Привет!') :
    () => alert("Здравствуйте!");

  welcome();

}

{

  let sum = (a, b) => {  // фигурная скобка, открывающая тело многострочной функции
    let result = a + b;
    return result; // если мы используем фигурные скобки, то нам нужно явно указать "return"
  };
  
  alert( sum(1, 2) ); // 3

}