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