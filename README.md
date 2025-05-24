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

<dl>
	<dt>Release - папка, содержащая исполняемый файл для windows и тестовый пример.</dt>
</dl>

 <dl>
  <dt>Code - папка, содержащая исходный код проекта.</dt>
  <dd>CSV_calculator.h - класс для вычисления csv формы </dd>
  <dd>CSV_structure.h - класс для хранения csv формы </dd>
  <dd>Includer.h - файл для подключения библиотек</dd>
  <dd>Source.cpp - программа  </dd>
</dl>

## Запуск для windows:  
	CSV_Calc.exe Test.csv  

## Компиляция и запуск для linux:  
	g++ Source.cpp -o csvcalc  
	./csvcalc Test.csv  

### Почему плюсы, а не си?  
Ну, во-первых, особой разницы в скорости выполнения нет, а в плюсах все функции можно удобно обернуть в классы.  
А во-вторых, если честно, я не увидел, что нужно писать на си и по инерции написал на плюсах. А переписывать уже поздно.  
Прошу понять и простить. （πーπ）  
