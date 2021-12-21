#!/bin/bash

echo "  Testing cat.c:"
echo "---Программа компилируется с опциями компиляции такими же, как в ежаже---"
echo " "
gcc -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm cat.c

echo "    Test 1:"
echo "---Вывод файла test_cat/a---"
echo "---./a.out test_cat/a---"
echo "---На экране:---"
./a.out test_cat/a
echo "---correct answer---"
echo " "

echo "    Test 2:"
echo "---Вывод файлов(их можно сколько угодно раз, test_cat/a test_cat/a test_cat/c) с флагом -n---"
echo "---./a.out -n test_cat/a test_cat/a test_cat/c---"
echo "---На экране:---"
./a.out -n test_cat/a test_cat/a test_cat/c
echo "---correct answer---"
echo " "

echo "    Test 3:"
echo "---Проверка на верно введенный флаг (-na)---"
echo "---./a.out -na test_cat/a test_cat/a test_cat/c---"
echo "---На экране:---"
./a.out -na test_cat/a test_cat/a test_cat/c
echo "---correct answer---"
echo " "

echo "    Test 4:"
echo "---Проверка на несуществующий файл test_cat/d---"
echo "---./a.out -n test_cat/d---"
echo "---На экране:---"
./a.out -n test_cat/d
echo "---correct answer---"
echo " "

echo "    Test 5:"
echo "---Проверка на пустой файл test_cat/b---"
echo "---./a.out test_cat/b---"
echo "---На экране:---"
./a.out test_cat/b
echo "---correct answer---"
echo " "

echo "    Test 6:"
echo "---Проверка на отсутствие аргументов---"
echo "---./a.out---"
echo "---На экране:---"
./a.out
echo "---correct answer---"
echo " "

echo "    Test 7:"
echo "---Проверка на пустой файл test_cat/b с флагом -n---"
echo "---./a.out -n test_cat/b---"
echo "---На экране:---"
./a.out -n test_cat/b
echo "---correct answer---"
echo " "

echo "  Testing cp.c:"
echo "---Программа компилируется с опциями компиляции такими же, как в ежаже---"
echo " "
gcc -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm cp.c

echo "    Test 1:"
echo "---Проверка на создание копии (test_cp/d) файла test_cp/а и сразу ls---"
echo "---./a.out test_cp/a test_cp/d---"
echo "---ls test_cp---"
echo "---На экране:---"
./a.out test_cp/a test_cp/d
ls test_cp
echo "---А затем сравним их с помощью команды cmp test_cp/a test_cp/d---"
echo "---cmp test_cp/a test_cp/d---"
echo "---На экране:---"
cmp test_cp/a test_cp/d
echo "---correct answer---"
echo " "

echo "    Test 2:"
echo "---Проверка на уже существующий файл test_cp/c с названием копии test_cp/c---"
echo "---./a.out test_cp/a test_cp/c---"
echo "---На экране:---"
./a.out test_cp/a test_cp/c
echo "---correct answer---"
echo " "

echo "    Test 3:"
echo "---Проверка на отсутствие аргументов---"
echo "---./a.out---"
echo "---На экране:---"
./a.out
echo "---correct answer---"
echo " "

echo "    Test 4:"
echo "---Проверка на отсутствие название файла, куда копировать---"
echo "---./a.out test_cp/a---"
echo "---На экране:---"
./a.out test_cp/a
echo "---correct answer---"
echo " "

echo "    Test 5:"
echo "---Проверка на неверный файл test_cp/e, с которого происходит копирование---"
echo "---./a.out test_cp/e---"
echo "---На экране:---"
./a.out test_cp/e
echo "---correct answer---"
echo " "

echo "    Test 6:"
echo "---Копирование пустого файла test_cp/b---"
echo "---./a.out test_cp/b test_cp/g и сразу ls---"
echo "---ls test_cp---"
echo "---На экране:---"
./a.out test_cp/b test_cp/g
ls test_cp
echo "---А затем сравним их с помощью команды cmp test_cp/b test_cp/g---"
echo "---cmp test_cp/b test_cp/g---"
echo "---На экране:---"
cmp test_cp/b test_cp/g
echo "---correct answer---"
echo " "

echo "  Testing grep.c:"
echo "---Программа компилируется с опциями компиляции такими же, как в ежаже---"
echo " "
gcc -O2 -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11 -lm grep.c

echo "    Test 1:"
echo "---Вызовем функцию grep с аргументами fg test_grep/a---"
echo "---./a.out fg test_grep/a---"
echo "---На экране:---"
./a.out fg test_grep/a
echo "---correct answer---"
echo " "

echo "    Test 2:"
echo "---Вызовем функцию grep с аргументами fg test_grep/a и флагом -v ---"
echo "---./a.out -v fg test_grep/a---"
echo "---На экране:---"
./a.out -v fg test_grep/a
echo "---correct answer---"
echo " "

echo "    Test 3:"
echo "---Проверка на отсутствие аргументов---"
echo "---./a.out---"
echo "---На экране:---"
./a.out
echo "---correct answer---"
echo " "

echo "    Test 4:"
echo "---Проверка на неверный флаг -vb---"
echo "---./a.out -vb fg test_grep/a---"
echo "---На экране:---"
./a.out -vb fg test_grep/a
echo "---correct answer---"
echo " "

echo "    Test 5:"
echo "---Проверка на отсутствие подстроки среди аргументов---"
echo "---./a.out test_grep/a---"
echo "---На экране:---"
./a.out test_grep/a
echo "---correct answer---"
echo " "

echo "    Test 6:"
echo "---Проверка на пустой файл test_cp/b с подстрокой 1---"
echo "---./a.out 1 test_cp/b---"
echo "---На экране:---"
./a.out 1 test_cp/b
echo "---correct answer---"
echo " "

echo "    Test 7:"
echo "---Проверка на двойное упоминание подстроки a в строке файла test_grep/a---"
echo "---./a.out a test_grep/a---"
echo "---На экране:---"
./a.out a test_grep/a
echo "---correct answer---"
