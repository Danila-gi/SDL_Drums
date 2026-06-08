# Приложение с запуском вращения барабанов

Код написан с использованием стандарта C++23. Сборка осуществляется через cmake.

## Необходимые библиотеки

Нужно установить библиотеку SDL с поддержкой шрифтов.

```sudo apt install libsdl2-dev```

```sudo apt install libsdl2-ttf-dev```

## Запуск

1. Сделать исполняемым файл run.sh: ```chmod +x run.sh```
2. Запустить скрипт: ```./run.sh```

## Проверка работы памяти приложения

Проверить можно через valgrind. Для данного приложения приводится следующая статистика:

```==9555== Memcheck, a memory error detector
==9555== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==9555== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==9555== Command: ./game
==9555== 
==9555== 
==9555== HEAP SUMMARY:
==9555==     in use at exit: 272,298 bytes in 3,453 blocks
==9555==   total heap usage: 236,441 allocs, 232,988 frees, 87,976,475 bytes allocated
==9555== 
==9555== LEAK SUMMARY:
==9555==    definitely lost: 0 bytes in 0 blocks
==9555==    indirectly lost: 0 bytes in 0 blocks
==9555==      possibly lost: 0 bytes in 0 blocks
==9555==    still reachable: 272,298 bytes in 3,453 blocks
==9555==         suppressed: 0 bytes in 0 blocks
==9555== Rerun with --leak-check=full to see details of leaked memory
==9555== 
==9555== For lists of detected and suppressed errors, rerun with: -s
==9555== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)```