# Лабораторная работа №2. Множества
## Цель работы
- Научиться работать с множествами.
- Научиться разрабатывать алгоритмы выполнения операций над множествами.
## Задачи
- Реализовать программу, формирующую без повторений всевозможные ориентированные
множества из элементов исходного неориентированного множества, количество
элементов в сформированных множествах должно быть равно исходному натуральному n.
- Разработать систему unit-тестов
## Список используемых при решении задачи понятий
- Множество – одно из ключевых понятий математики, представляющее собой набор, совокупность объектов любой природы.
- Элементы множества – объекты, составляющие множество.
- Объект принадлежит множеству тогда и только тогда, когда он является его элементом.
-  Ориентированное множество (или упорядоченное множество) — это структура, в которой порядок элементов имеет значение. 
( 𝑎 , 𝑏) ≠ (𝑏 , 𝑎)
- Поиск с возвратом, бэктрекинг (англ. backtracking) — общий метод нахождения решений задачи, в которой требуется полный перебор всех возможных вариантов в некотором множестве М.


### Алгоритмы:

#### Интерфейс, который отображает основные метод c описанием
```c#
namespace lab2;

public interface IFormOrientedSets
{
    /// <summary>
    /// Записывает данные в файл.
    /// </summary>
    /// <param name="input">Текст, который будет записан.</param>
    void WriteToFile(string input);

    /// <summary>
    /// Читает содержимое текстового файла и возвращает его как строку.
    /// </summary>
    /// <param name="fileName"> Название файла, который считываем</param>
    string ReadFile(string fileName);

    /// <summary>
    /// Формирует ориентированные множества
    /// </summary>
    /// <param name="set">Исходное множество.</param>
    /// <param name="n">Количество элементов в сформированных множествах.</param>
    void CreateOrientedSets(string set, uint n);
}
```

#### Класс, который реализует интерфейс
```c#
using System;
using System.Collections.Generic;
using System.IO;

namespace lab2
{
    public class FormOrientedSets : IFormOrientedSets
    {
        public void WriteToFile(string input)
        {
            try
            {   
                File.WriteAllText("set.txt", input); 
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка: {ex.Message}"); 
            }
        }

   
        public string ReadFile(string fileName)
        {
            try
            {
                
                string filePath = @"D:\RPIIS\sem2\lab2\set.txt";


                
                if (!File.Exists(filePath))
                {
                    Console.WriteLine($"Файл {fileName} не найден в {filePath}");
                    return string.Empty;
                }

                
                return File.ReadAllText(filePath);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при чтении файла: {ex.Message}");
                return string.Empty;
            }
        }

        public void CreateOrientedSets(string set, uint n)
        { 
            try
            {
                var elements = ParseSet(set);
        
                if (elements.Count == 0)
                    return;
                
                if (n > elements.Count)
                {
                    Console.WriteLine($"Ошибка: n = {n} больше количества элементов множества ({elements.Count})");
                    return;
                }
                
                
                var result = new List<List<string>>();
                void Backtrack(List<string> current, HashSet<int> used)
                {
                    if (current.Count == n)
                    {
                        result.Add(new List<string>(current));
                        return;
                    }

                    for (int i = 0; i < elements.Count; i++)
                    {
                        if (!used.Contains(i))
                        {
                            used.Add(i);
                            current.Add(elements[i]);

                            Backtrack(current, used);

                            current.RemoveAt(current.Count - 1);
                            used.Remove(i);
                        }
                    }
                }
                Backtrack(new List<string>(), new HashSet<int>());

        
                foreach (var o in result)
                {
                    Console.WriteLine("{" + string.Join(", ", o) + "}");
                }
                Console.WriteLine($"Всего комбинаций: {result.Count}");

            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка: {ex.Message}");
            }
        }

        /// <summary>
        /// Разбивает множество на элементы
        /// </summary>
        /// <param name="set"> Хранит информацию из файла</param>
        private List<string> ParseSet(string set)
        {
            set = set.Trim(); // удаляем пробелы в начале и в конце
            if (!set.StartsWith("{") || !set.EndsWith("}"))
                throw new ArgumentException("Множество должно быть в фигурных скобках.");

            set = set.Substring(1, set.Length - 2).Trim(); // удаляем внешние скобки, удаляем пробелы
            
            if (string.IsNullOrEmpty(set))
            {
                return new List<string>(); // Возвращаем пустой список, если set = ""
            }
            var elements = new List<string>();
            int level = 0, start = 0;
            
            for (int i = 0; i < set.Length; i++)
            {
                switch (set[i])
                {
                    case '{': 
                        level++;
                        break;
                    
                    case '}':
                        level--;
                        break;

                    case ',' when level == 0:
                    {
                        elements.Add(set.Substring(start, i - start).Trim());
                        start = i + 1;
                        break;
                    }
                }
            }
            elements.Add(set.Substring(start).Trim()); // заносим последний элемент, у которого в конце не будет запятой(старта и до конца)
            return elements;
        }
        
    }
}
```

**Основные функции:**
- WriteToFile - Записывает данные в файл.
- ReadFile - Читает содержимое текстового файла и возвращает его как строку.
- CreateOrientedSets - Формирует ориентированные множества(вызывает функцию backtrack)

**Вспомогательные функции:**
- ParseSet - Разбивает множество на элементы
- Backtrack — Перебираем все возможные варианты рекурсивно.


### Backtrack: ###
#### Саму суть поиска мы реализуем в этой части кода 
![image](https://github.com/user-attachments/assets/f64435be-8b3e-42d9-8b99-6c59beca570d)


- Мы создаем list result, который будем хранить массив массивов, то есть все возможные перестановки элементов исходного множества в формате string
- Далее в функции Backtrack прописывается вся логика. В ней мы уже закидываем полученные множества в **result**.
- Вызываем функцию в третьей строчке(скрин), передавая в нее пустой list string-ов ***current*** и коллекцию HashSet ***used***.
**Current** - будет хранить множество(уникальную комбинацию элементов), которое добавим в ***result***. В **used** - помечаем использованные элементы.
![image](https://github.com/user-attachments/assets/e17af7d5-1447-4ad9-93ba-52e3a52962a6)


## Пример работы
Реализуем библиотеку в программе:
```c#
    namespace lab2
    {
        class Program
        {
            static void Main()
            {
                var set = new FormOrientedSets();
                while (true) 
                {
                    Console.WriteLine("1 - Ввести множество");
                    Console.WriteLine("2 - Получить множество из файла");
                    Console.WriteLine("3 - Сформировать все возможные ориентированные множества");
                    Console.WriteLine("4 - Выйти");
                    byte t = Convert.ToByte(Console.ReadLine());

                  switch (t)
                  {
                      case 1:
                      {
                          Console.Write("Введите множество (используя {, }, ',') : ");
                          string input = Console.ReadLine();

                          Console.Write("Введи число элементов в итоговом множестве: ");
                          string num = Console.ReadLine();

                          if (!uint.TryParse(num, out uint n))
                          {
                              Console.WriteLine("Ошибка: нужно ввести корректное число.");
                              return;
                          }

                          set.WriteToFile(input);
                          set.CreateOrientedSets(input, n);
                          break;
                      }

                      case 2:
                      {
                          Console.Write("Введи число элементов в итоговом множестве: ");
                          string num = Console.ReadLine();

                          if (!uint.TryParse(num, out uint n))
                          {
                              Console.WriteLine("Ошибка: нужно ввести корректное число.");
                              return;
                          }

                          string input = set.ReadFile("set.txt");
                          set.CreateOrientedSets(input, n);
                          break;
                      }

                      case 3:
                      {
                          Console.Write("Введи число элементов в итоговом множестве: ");
                          string num = Console.ReadLine();

                          if (!uint.TryParse(num, out uint n))
                          {
                              Console.WriteLine("Ошибка: нужно ввести корректное число.");
                              return;
                          }
                          
                          string readSet = set.ReadFile("set.txt");
                          
                          set.CreateOrientedSets(readSet, n);
                          break;
                      }

                      case 4:
                          Console.WriteLine("Выход из программы...");
                          return;

                      default: Console.WriteLine("Неверная команда.");
                          break;
                          
                  }

                }   
            }
        }
    }
    
```

## Вот так работает:
### Введем такое множество через консоль
![image](https://github.com/user-attachments/assets/6c345aab-a86e-47a9-bf27-b77d1035dc57)

### И введем сколько хотим элементов видеть элементов в итоговых множествах и увидим такой результат:
![image](https://github.com/user-attachments/assets/4d0b4e62-d97f-4432-9ae6-6607562384bc)

***чем больше введенное число - тем больше количество комбинаций, которое может получиться***
### Это множество, которое мы ввели, записалось в файлик set.txt:
![image](https://github.com/user-attachments/assets/07d8fc9b-d3bd-4892-a88d-96de21cc3a91)

### Так же мы можем ввести в файлик множество, которое сможем прочитать в программе, сейчас так и сделаем
![image](https://github.com/user-attachments/assets/b8182082-fa56-432f-8482-6d4850e6153c)

Вот с одним элементом:
![image](https://github.com/user-attachments/assets/95054ac6-d9ca-44e3-a90a-f0ec93280902)

**Обработка ошибки**
![image](https://github.com/user-attachments/assets/2b2b3c79-4e2d-4213-87c3-1d5faf1b7718)


**Тут не все влезло, максимальное количество комибинаций для текущего множества** ![image](https://github.com/user-attachments/assets/d7bf3784-0298-484c-9ee7-71c74bd03a64)


## Тестирование:
**Были написаны простеньких 5 unit-тестов:**
### В этом тесте мы просто записываем текст в файлик и читаем его, проверя на корректность записи. Проверяем метод WriteToFile. То есть записываем строку в файлик с помощью нашей функции, далее считываем из файла строку, сравниваем строки. Если они совпали - все гуд, функция WriteToFile корректна
```c#
[Fact]
        public void WriteToFile_CorrectInput_WritesToFile()
        {
            // Arrange
            string input = "Test content";
            var writer = new FormOrientedSets();

            // Act
            writer.WriteToFile(input); // Запись в set.txt

            // Assert
            string fileContent = File.ReadAllText("set.txt");
            Assert.Equal(input, fileContent);
            
            File.Delete("set.txt");
        }
```


### В этом тесте мы проверяем метод ReadFile. Записываем в файлик строку, а потом читаем ее с помощью нашего метода ReadFile. Далее сравниваем строку, которую ввели, и строку, которую прочитали
```c#
public void ReadFile_FileExists_ReturnsContent()
        {
            // Arrange
            string filePath = @"D:\RPIIS\sem2\lab2\set.txt"; // Указываем конкретный путь к файлу
            string expectedContent = "Test file content";

            // Создаём файл и записываем в него содержимое
            File.WriteAllText(filePath, expectedContent);

            var formOrientedSets = new FormOrientedSets(); // Создаём объект для вызова метода

            // Act
            string actualContent = formOrientedSets.ReadFile(filePath);

            // Assert
            Assert.Equal(expectedContent, actualContent);

            // Cleanup
            File.Delete(filePath); // Удаляем файл после завершения теста
        }
```

### Тут мы пытаемся прочитать не существующий файлик( Path.GetRandomFileName() -- генерирует название файла, которого нету в нашем проекте). Так как файлика с таким именем не будет существовать, то функция должна вернуть пустую строку. В итоге мы сравниваем пустую строчку с тем, что возратил метод ReadFile. Если они равны, то функция ReadFile отработала корректна.
```c#
  public void ReadFile_FileDoesNotExist_ReturnsEmptyString()
        {
            // Arrange
            var formOrientedSets = new FormOrientedSets();

            // Act  
            var result = formOrientedSets.ReadFile(Path.GetRandomFileName());

            // Assert
            Assert.Equal(string.Empty, result);
        }
```

### В этом тесте проверяется корректность работы CreateOrientedSets. Вводим множество, число n = 2. Вызываем функцию и получаем выходные данные, сравниваем с ожидаемым результатом.
```c#
[Fact]
        public void CreateOrientedSets_ValidInput_GeneratesCombinations()
        {
            // Arrange
            var inputSet = "{a, b}";
            uint n = 2;
            var formOrientedSets = new FormOrientedSets();
            
            using (var consoleOutput = new StringWriter())
            {
                Console.SetOut(consoleOutput);

                // Act
                formOrientedSets.CreateOrientedSets(inputSet, n);

                // Assert
                var output = consoleOutput.ToString();
                Assert.Contains("{a, b}", output);
                Assert.Contains("{b, a}", output);
            }
        }
```
### Последний тест. Проверяем метод CreateOrientedSets на обработку пустого множества. Так же, как и в прошлом тесте, передаем в функцию параметры и сравниваем с ожидаемым результатом.
```c# [Fact]
        public void CreateOrientedSets_EmptySet_NoOutput()
        {
            // Arrange
            var inputSet = "{}";
            uint n = 2;
            var formOrientedSets = new FormOrientedSets();

            using (var consoleOutput = new StringWriter())
            {
                Console.SetOut(consoleOutput);

                // Act
                formOrientedSets.CreateOrientedSets(inputSet, n);

                // Assert
                var output = consoleOutput.ToString();
                Assert.Equal("", output); // Никаких комбинаций не должно быть
            }
        }
```

### Все тесты успешно пройдены ура:
![image](https://github.com/user-attachments/assets/ea65e1ba-6e78-49a6-822e-bca065976884)


## Вывод
В ходе данной лабораторной работы я научиться разрабатывать алгоритмы выполнения операций над множествами и разрабатывать Unit-тесты

