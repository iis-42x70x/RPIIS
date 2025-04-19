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
               
                HashSet<string> dublicate = new HashSet<string>();
                foreach (var item in elements)
                {
                    if (!dublicate.Add(item)) 
                    {
                        Console.WriteLine($"Ошибка: в множестве есть дубликат: {item}");
                        return;
                    }
                }

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
            HashSet<string> dublicate = new HashSet<string>();
            foreach (var item in elements)
            {
                if (!dublicate.Add(item)) 
                {
                    Console.WriteLine($"Ошибка: в множестве есть дубликат: {item}");
                    return new List<string>();
                }
            }
            return elements;
        }
        
    }
}