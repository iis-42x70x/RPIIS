# Лабораторная работа №2
### Цели лабораторной работы💡:
1. Разработать программу работы с множествами на выбранном языке программирования (например, C/C++, Java, Golang).
2. Научиться работать с множествами.
3. Научиться разрабатывать алгоритмы выполнения операций над множествами.
   
**Вариант №6** [методичка](https://drive.google.com/drive/folders/1_xy849HXgTDetxSMlFd0KikTBo8-xalN). Нужно реализовать алгоритм вычисления декртова произведения N множеств.

## Основные задачи: 
1. Выбрать язык программирования для реализации программы в соответствии с индивидуальным заданием.
2. Написать тестовую программу, которая демонстрирует декартовое произведение N множеств.
## Список используемых понятий:
- Множество – одно из ключевых понятий математики, представляющее собой набор, совокупность объектов любой природы.
- Элементы множества – объекты, составляющие множество.
- Объект принадлежит множеству тогда и только тогда, когда он является его элементом.
- Говорят, что если объект принадлежит множеству, то существует вхождение этого элемента в множество. Допускается неограниченное количество вхождений
одного объекта в какое-либо множество.
- Например, есть множество _S = {a, b, a, a, c}_. В нём элементы _a_, _b_ и _c_ принадлежат множеству _S_, причём множество _S- Например, есть множество _S = {a, b, a, a, c}_. В нём элементы _a_, _b_ и _c_ принадлежат множеству _S_, причём множество _S_ имеет три вхождения элемента _a_ (_S|a|_ = 3) и по одному вхождению элементов _b_ и _c_ (_S|b|_ = _S|c|_ = 1).
- Множеством с кратными вхождениями элементов называют множество _S_ тогда и только тогда, когда существует _x_ такой, что истинно _S|x|_ > 1._ имеет три вхождения элемента _a_ (_S|a|_ = 3) и по одному вхождению элементов _b_ и _c_ (_S|b|_ = _S|c|_ = 1).
- Множеством с кратными вхождениями элементов называют множество _S_ тогда и только тогда, когда существует _x_ такой, что истинно _S|x|_ > 1.
- _Декартовым произведением_ неориентированных множеств A и B называют
неориентированное множество S тогда и только тогда, когда для любого z истинно: если
S|z| > 0, то z = <x, y>; S|z| = A|x|*B|y| и наоборот.
### Разбор кода:
Поскольку множетва помимо обычных элементов могут в себе содержать еще и подмножества, я создал тип пустового интерфейса, принимающего любой тип данных, и создал структуру, поле которой является переменная любого типа.
1. **В этом коде мы имеем тип "Element" и структуру "Set"**

```go
type Element interface{}

type Set struct {
	Elements []Element
}
```
2. **Конструктор создания нового множества, для заполнения**

```go
func NewSet() *Set {
	return &Set{Elements: []Element{}}
}
```
3. **Метод добавления элементов в множество**   

   Этот метод добавляет любые элементы множества.
```go
func (s *Set) Add(element Element) {
	for _, el := range s.Elements {
		if fmt.Sprintf("%v", el) == fmt.Sprintf("%v", element) {
			return
		}
	}
	s.Elements = append(s.Elements, element)
}
```
4. **Функция парсинга строки**

```go
func ParseSet(input string) *Set {
	input = strings.TrimSpace(input)

	// Проверка на сбалансированность скобок
	if strings.Count(input, "{") != strings.Count(input, "}") {
		fmt.Println("Ошибка: Несбалансированные фигурные скобки")
		return nil
	}

	// Проверка на пустое множество
	if input == "{}" {
		fmt.Println("Ошибка: Множество не должно быть пустым!")
		return nil
	}

	if len(input) < 2 || input[0] != '{' || input[len(input)-1] != '}' {
		fmt.Println("Ошибка: Некорректный формат множества. Пример: {a, b, {c, d}}")
		return nil
	}

	input = input[1 : len(input)-1]
	set := NewSet()
	element := ""
	depth := 0

	for i := 0; i < len(input); i++ {
		switch input[i] {
		case '{':
			if depth > 0 {
				element += string(input[i])
			}
			depth++
		case '}':
			depth--
			if depth == 0 {
				if element == "" {
					set.Add(NewSet())
				} else {
					nestedSet := ParseSet("{" + element + "}")
					if nestedSet == nil {
						fmt.Println("Ошибка: Некорректное вложенное множество")
						return nil
					}
					set.Add(nestedSet)
				}
				element = ""
			} else {
				element += string(input[i])
			}
		case ',':
			if depth == 0 {
				if strings.TrimSpace(element) != "" {
					set.Add(strings.TrimSpace(element))
				}
				element = ""
			} else {
				element += string(input[i])
			}
		default:
			element += string(input[i])
		}
	}

	if strings.TrimSpace(element) != "" {
		set.Add(strings.TrimSpace(element))
	}

	// Проверка, что множество не пустое после парсинга
	if len(set.Elements) == 0 {
		fmt.Println("Ошибка: Множество не содержит элементов")
		return nil
	}

	return set
}
```
6. **Функция декартового произведения множества**

```go
func CartesianProduct(sets ...*Set) [][]Element {
	if len(sets) == 0 {
		return nil
	}

	result := [][]Element{{}}
	for _, set := range sets {
		var temp [][]Element
		for _, res := range result {
			for _, el := range set.Elements {
				temp = append(temp, append(append([]Element{}, res...), el))
			}
		}
		result = temp
	}
	return result
}
```
7. **Функция чтения множеств с файла sets.txt**
```go
func ReadSetsFromFile(filename string) ([]*Set, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var sets []*Set
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		set := ParseSet(line)
		if set == nil {
			fmt.Printf("Ошибка при разборе множества в строке: %q\n", line)
			continue
		}
		sets = append(sets, set)
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}

	// Проверка на пустые множества из файла
	for _, set := range sets {
		if len(set.Elements) == 0 {
			fmt.Println("Ошибка: Файл содержит пустое множество")
			return nil, fmt.Errorf("найдено пустое множество")
		}
	}

	return sets, nil
}
```
## Вывод:

В ходе данной лабораторной работы я:
- Научился работать с множествами
- Научиться разрабатывать алгоритмы выполнения операций над множествами.

