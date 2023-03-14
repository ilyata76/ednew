"use strick";

{ // ||

    // result = a || b;
    alert( true || true );   // true
    alert( false || true );  // true
    alert( true || false );  // true
    alert( false || false ); // false

    if (1 || 0) { // работает как if( true || false )
        alert( 'truthy!' );
    }

    let hour = 9;

    if (hour < 10 || hour > 18) {
        alert( 'Офис закрыт.' );
    }

    let isWeekend = true;

    if (hour < 10 || hour > 18 || isWeekend) {
        alert( 'Офис закрыт.' ); // это выходной
    }

    // result = value1 || value2 || value3;

    alert( 1 || 0 ); // 1
    alert( true || 'no matter what' ); // true

    alert( null || 1 ); // 1 (первое истинное значение)
    alert( null || 0 || 1 ); // 1 (первое истинное значение)
    alert( undefined || null || 0 ); // 0 (поскольку все ложно, возвращается последнее значение)


    let currentUser = null;
    let defaultUser = "John";
    let name = currentUser || defaultUser || "unnamed";
    alert( name ); // выбирается "John" – первое истинное значение

    let x;
    true || (x = 1);
    alert(x); // undefined, потому что (x = 1) не вычисляется Если бы первый аргумент имел значение false, то || приступил бы к вычислению второго и выполнил операцию присваивания:

    {
        let x;
        false || (x = 1);
        alert(x); // 1
    }

}


{
    // result = a && b;

    alert( true && true );   // true
    alert( false && true );  // false
    alert( true && false );  // false
    alert( false && false ); // false

    let hour = 12;
    let minute = 30;

    if (hour == 12 && minute == 30) {
        alert( 'The time is 12:30' );
    }

    if (1 && 0) { // вычисляется как true && false
        alert( "не сработает, так как результат ложный" );
    }


    // Если первый операнд истинный,
    // И возвращает второй:
    alert( 1 && 0 ); // 0
    alert( 1 && 5 ); // 5

    // Если первый операнд ложный,
    // И возвращает его. Второй операнд игнорируется
    alert( null && 5 ); // null
    alert( 0 && "no matter what" ); // 0


    alert( 1 && 2 && null && 3 ); // null
    alert( 1 && 2 && 3 ); // 3

    let x = 1;
    (x > 0) && alert( 'Greater than zero!' );

    if (x > 0) {
        alert( 'Greater than zero!' );
    }
}

{
    // result = !value;

    alert( !true ); // false
    alert( !0 ); // true

    alert( !!"non-empty string" ); // true
    alert( !!null ); // false

    alert( Boolean("non-empty string") ); // true
    alert( Boolean(null) ); // false

}

{   
    // result = a ?? b
    // result = (a !== null && a !== undefined) ? a : b;

    let user;
    alert(user ?? "Аноним"); // Аноним (user не существует)

    user = "Иван";
    alert(user ?? "Аноним"); // Иван (user существует)

    let firstName = null;
    let lastName = null;
    let nickName = "Суперкодер";
    // показывает первое значение, которое определено:
    alert(firstName ?? lastName ?? nickName ?? "Аноним"); // Суперкодер

    let height = 0;
    alert(height || 100); // 100
    alert(height ?? 100); // 0

    let x = (1 && 2) ?? 3; // 
    alert(x); // 2  

    // будет height=100, если переменная height равна null или undefined
    height = height ?? 100;
}