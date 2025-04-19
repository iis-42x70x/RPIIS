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
    