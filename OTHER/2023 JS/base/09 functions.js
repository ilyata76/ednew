"use strick";

{
    let userName = 'Вася';

    function showMessage() {
        let message = 'Привет, ' + userName;
        alert(message);
    }

    showMessage(); // Привет, Вася
}

{
    let userName = 'Вася';

    function showMessage() {
    userName = "Петя"; // (1) изменяем значение внешней переменной

        let message = 'Привет, ' + userName;
        alert(message);
    }

    alert( userName ); // Вася перед вызовом функции

    showMessage();

    alert( userName ); // Петя, значение внешней переменной было изменено функцией
}

{
    let userName = 'Вася';

    function showMessage() {
      let userName = "Петя"; // объявляем локальную переменную
    
      let message = 'Привет, ' + userName; // Петя
      alert(message);
    }
    
    // функция создаст и будет использовать свою собственную локальную переменную userName
    showMessage();
    
    alert( userName ); // Вася, не изменилась, функция не трогала внешнюю переменную
}

{
    function showMessage(from, text) {

        from = '*' + from + '*'; // немного украсим "from"
      
        alert( from + ': ' + text );
      }
      
      let from = "Аня";
      
      showMessage(from, "Привет"); // *Аня*: Привет
      
      // значение "from" осталось прежним, функция изменила значение локальной переменной
      alert( from ); // Аня
}

{
    function showCount(count) {
        // если count равен undefined или null, показать "неизвестно"
        alert(count ?? "неизвестно");
    }
    showCount(0); // 0
    showCount(null); // неизвестно
    showCount(); // неизвестно
}

{
    function sum(a, b) {
        return a + b;
    }
      
      let result = sum(1, 2);
      alert( result ); // 3
}

{

    function doNothing() { /* пусто */ }

    alert( doNothing() === undefined ); // true

}

/*

return (
  some + long + expression
  + or +
  whatever * f(a) + f(b)
  )

*/