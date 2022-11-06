pwd # текущая директория
ls # список всего
ls -l # подробный список свойств файлов


# -rw-r--r-- 1 ilyata ilyata 41 Oct 13 14:26 1
# -rw-r--r-- 1 ilyata ilyata 70 Oct 13 14:27 1.bash
# маска прав   поль   гр. польз
# 10 значений
# 1: d/- директория/файл
# 2-4: rwx - read write execute


touch test_file_1 # создать файл

chmod +x test_file_1 # теперь файл станет исполняемым

bash test_file_1 # !

cp test_file_1 test_file_2 # копирование

mv <> <> # переместить или переименовать

# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± cp test_file_1 test_file_2
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± ls
# test_2  test_file_1  test_file_2
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± mv test_file_1 test
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± ls
# test  test_2  test_file_2
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± mv test_file_2 ../
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± ls ..
# 1  1.bash  test_1  test_file_2


ls -la # плюс скрытые файлы

less # ограничивает вывод

echo "less, head, tail" > test_file_3 # в файл
cat ../test_file_2 test_file_3 > test_file_4 # объединить выводы

head test_file_4 # первые строчки (10)
tail test_file_4 # последние 10 строчек
# ОНО РАБОТАЕТ В РЕАЛЬНОМ ВРЕМЕНИ\

grep "less" test_file_3 # ПОИСК ШАБЛОНОВ
# ╭─ilyata at DESKTOP-SO73M2P in ~/workdir/ed.cifra/bash/test_1 on master✘✘✘
# ╰─± grep "less" test_file_3
# less, head, tail