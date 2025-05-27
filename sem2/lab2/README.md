<h1>Лабораторная работа №2</h1>

## Цели:

* Изучить основные понятия, связанные с множествами
* Выполнить операции над множествами согласно поставленной задаче
* Уметь использовать основные свойства множеств

## Задачи:

* Разработать библиотеку для работы со множествами на любом императивном языке программирования
* Разработать тесты, которые демонстрирует работоспособность реализованной библиотеки

## Вариант 7:
Реализовать программу, формирующую без повторений всевозможные ориентированные
множества из элементов исходного неориентированного множества, количество
элементов в сформированных множествах должно быть равно исходному натуральному n.

## Понятия:

<h4>Множество – простейшая информационная конструкция и математическая структура,позволяющая рассматривать какие-то объекты как целое, связывая их.</h4>
<h4>Элементы множества – объекты, связываемые некоторым множеством.</h4>
<h4>Множества бывают:</h4>

* Ориентированными (важен порядок элементов во множестве)
* Неориентированными (порядок элементов во множестве не важен)

## Структура программы: 

main.cpp

lab2.cpp

lab2.h

input.txt

test_lab2.cpp


## Работа программы:
1. Разбираем строку на элементы. Возвращаем количество найденных элементов:

![image](https://github.com/user-attachments/assets/0249038f-dfa3-45b3-b814-cdc416798800)

2. Проверка элементов на уникальность:

![image](https://github.com/user-attachments/assets/7c090e7d-3963-4cb9-9432-432fa220307f)

3. Считываем данные из файла input.txt:

![image](https://github.com/user-attachments/assets/d9f464a1-d1bd-4f46-8480-9963589b3764)

4. Генерируем все возможные перестановки элементов и записываем их в файл output.txt

![image](https://github.com/user-attachments/assets/6e207505-9b65-41a7-8743-65caac89b399)


**Работа программы при считывании исходного множества из файла:**
Исходное неориентированное множество:

![image](https://github.com/user-attachments/assets/3dfb8518-0f96-4763-812b-5526fb642e18)

Результат работы программы:

![image](https://github.com/user-attachments/assets/a8b52c56-3a91-4fb4-9b37-5a8dc8c30fef)

**Тестирование ввода некорректных данных**

1 пример: 

![image](https://github.com/user-attachments/assets/355fdaab-f042-405b-95fb-9477f28f89e3)

![image](https://github.com/user-attachments/assets/f1cd909f-4cae-4fe2-9ff6-67cbfae617a0)


2 пример: 

![image](https://github.com/user-attachments/assets/ac64aa88-3d34-448f-a626-dfd7f32ca86f)

![image](https://github.com/user-attachments/assets/0643158a-3d12-40bb-9a9b-1504d95b2ace)

3 пример:

![image](https://github.com/user-attachments/assets/cad95035-c3c6-4185-a925-29368f2b3a00)

![image](https://github.com/user-attachments/assets/a2f39855-b448-45a2-8aa5-8571e38241ed)

4 пример:

![image](https://github.com/user-attachments/assets/87c906dc-ea83-41e9-b519-710efeb9abb5)

![image](https://github.com/user-attachments/assets/87fbc880-67b8-4f32-836e-25dc8ee31ed8)

5 пример:

![image](https://github.com/user-attachments/assets/de933e17-d5aa-4de2-be9a-72fea9c039f8)

![image](https://github.com/user-attachments/assets/7361ef80-c2f6-45d4-bfac-c6fbd34408b7)

6 пример: 

![image](https://github.com/user-attachments/assets/bc00a85b-32b2-4727-9a1c-db9d8574e6b5)

![image](https://github.com/user-attachments/assets/55ba79fa-5b82-40d3-9f46-e0c053c0ef00)

7 пример: 

![image](https://github.com/user-attachments/assets/fca50857-98ee-4fa4-97d4-d81888b9c243)

![image](https://github.com/user-attachments/assets/4d33909e-3682-4bfb-a976-1aac4e486195)

## Результат работы тестов
Тестирование программы осуществлялось с использованием модульных тестов , реализованных на основе библиотеки assert.

![image](https://github.com/user-attachments/assets/40ea66a8-c044-4db5-b466-92b13fef544a)


**Примеры тестов**

* Проверка работы функции isUnique() на примере уникального и неуникального набора элементов.

![image](https://github.com/user-attachments/assets/e1dfc231-739f-4439-a95f-8695f09cca71)

* testParseElementsWithAngleBrackets() проверяет, что парсер корректно обрабатывает элементы внутри угловых скобок.

![image](https://github.com/user-attachments/assets/86e53a44-9dd4-4fa1-af76-e84cf4589e96)

* testParseElementsWithCurlyBrackets() проверяет, что парсер корректно обрабатывает элементы внутри фигурных скобок.

![image](https://github.com/user-attachments/assets/1d761e36-8d23-4d38-a233-bb4a11065d0a)

* void testParseNestedBrackets() проверяет корректную работу парсера при наличии вложенных скобок .

![image](https://github.com/user-attachments/assets/fa5dd79b-a6c8-492b-8d67-1fb809d95429)

## Вывод

Я реализовала библиотеку, формирующую без повторений всевозможные ориентированные множества из элементов исходного неориентированного множества,

## Материалы и источники
* [Свободная энциклопедия "Википедия" Статья "Множество" [Электронный ресурс]-Режим доступа
https://ru.wikipedia.org/wiki/Множество](https://ru.wikipedia.org/wiki/%D0%9C%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%BE)

* [itmm.unn.ru - учебное пособие "Дискретная математика", В.Е. Алексеев.](https://itmm.unn.ru/wp-content/uploads/sites/19/2020/04/DM-MM-uchebnik.pdf)
