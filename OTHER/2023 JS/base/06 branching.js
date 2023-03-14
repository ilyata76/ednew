"use strick";

{
    let year = prompt('В каком году была опубликована спецификация ECMAScript-2015?', '');
    if (year == 2015) alert( 'Вы правы!' );
    if (year == 2015) {
        alert( "Правильно!" );
        alert( "Вы такой умный!" );
    }
    if (0) { // 0 is falsy
        null;
    }
    if (1) { // 1 is truthy
        undefined;    
    }

    let condition = (year == 2015); // преобразуется к true или false
    if (condition) {
        alert("A!");
    }

    if (year == 2015) {
        alert( 'Да вы знаток!' );
    } else {
        alert( 'А вот и неправильно!' ); // любое значение, кроме 2015
    }

    if (year < 2015) {
        alert( 'Это слишком рано...' );
    } else if (year > 2015) {
        alert( 'Это поздновато' );
    } else {
        alert( 'Верно!' );
    }
}

{
    let age = prompt('Возраст?', 18);
    let accessAllowed = (age > 18) ? true : false;
    let accessAllowedTheSame = age > 18;

    let message = (age < 3) ? 'Здравствуй, малыш!' :
        (age < 18) ? 'Привет!' :
        (age < 100) ? 'Здравствуйте!' :
        'Какой необычный возраст!';
    alert( message );

    let company = prompt('Какая компания создала JavaScript?', '');
    
    (company == 'Netscape') ?
        alert('Верно!') : alert('Неправильно.');
}
{
    let arg = prompt("Введите число?");
    switch (arg) {
        case '0':
        case '1':
            alert( 'Один или ноль' );
            break;

        case '2':
            alert( 'Два' );
            break;

        case 3:
            alert( 'Никогда не выполнится!' );
            break;
        default:
            alert( 'Неизвестное значение' );
    }
}