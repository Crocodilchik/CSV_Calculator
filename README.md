# CSV_Calculator
## Calculator for cells in csv files for YADRO

## Структура проекта:

	CSV_Calculator
	|
	|--README
	|
	|--Code
	|	|--CSV_calculator.h
	|	|--CSV_structure.h
	|	|--Includer.h
	|	|--Source.cpp
	|
	|Release
	|	|--CSV_Calc.exe
	|	|--Test.csv

Release - папка, содержащая исполняемый файл для windows и тестовый пример.  
Code - папка, содержащая исходный код проекта.  
	⋅⋅*CSV_calculator.h - класс для вычисления csv формы  
	⋅⋅*CSV_structure.h - класс для хранения csv формы  
	⋅⋅*Includer.h - файл для подключения библиотек  
	⋅⋅*Source.cpp - программа  

## Запуск для windows:  
	CSV_Calc.exe Test.csv  

## Компиляция и запуск для linux:  
	g++ Source.cpp -o csvcalc  
	./csvcalc Test.csv  

Почему плюсы, а не си?  
Ну, во-первых, особой разницы в скорости выполнения нет, а в плюсах все функции можно удобно обернуть в классы.  
А во-вторых, если честно, я не увидел, что нужно писать на си и по инерции написал на плюсах. А переписывать уже поздно.  
Прошу понять и простить. （πーπ）  
