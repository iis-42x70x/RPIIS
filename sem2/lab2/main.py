import os
def ensure_input_file():
    """Создает файл input.txt с примерами, если он не существует."""
    if not os.path.exists("input.txt"):
        print("Файл input.txt не найден. Создаем новый с примером данных...")
        default_data = "{1,2,3,3} {2,3,4}\n"  # Пример данных
        try:
            with open("input.txt", "w") as file:
                file.write(default_data)
            print(f"Файл создан с примером: {default_data}")
            return True
        except Exception as e:
            print(f"Ошибка при создании файла: {e}")
            return False
    return True


def show_file_content():
    """Показывает содержимое файла"""
    try:
        with open("input.txt", "r") as file:
            content = file.read()
            print("\nТекущее содержимое файла:")
            print(content)
    except Exception as e:
        print(f"Ошибка чтения файла: {e}")


def overwrite_sets_in_file():
    """Перезаписывает множества в файл"""
    print("\nФормат ввода:")
    print("1. Для обычных множеств: {элемент1,элемент2} {элемент3,элемент4}")
    print("2. Для упорядоченных множеств: <элемент1,элемент2> <элемент3,элемент4>")
    print("Пример: {a,b,c,c} {a,b,d} или <1,2,3> <2,3,4>")

    while True:
        user_input = input("\nВведите два множества: ").strip()
        if not user_input:
            print("Ввод не может быть пустым!")
            continue

        # Проверка наличия двух множеств
        sets = user_input.split(maxsplit=1)
        if len(sets) != 2:
            print("Ошибка: нужно ввести ровно два множества!")
            continue

        # Проверка формата
        set1, set2 = sets
        if (set1[0] not in ['{', '<'] or set1[-1] not in ['}', '>'] or
                set2[0] not in ['{', '<'] or set2[-1] not in ['}', '>']):
            print("Ошибка: множества должны начинаться и заканчиваться на { } или < >")
            continue

        # Запись в файл
        try:
            with open("input.txt", "w") as file:
                file.write(user_input + "\n")
            print("Данные успешно записаны в файл!")
            show_file_content()
            return user_input
        except Exception as e:
            print(f"Ошибка записи в файл: {e}")
            return None


def read_sets_from_file():
    """Чтение множеств из файла с проверкой формата"""
    try:
        with open("input.txt", "r") as file:
            lines = [line.strip() for line in file if line.strip()]

        if not lines:
            print("Файл пуст! Сначала добавьте данные.")
            return None

        # Берем последнюю строку без "Результат:"
        data_line = None
        for line in reversed(lines):
            if not line.startswith("Результат:"):
                data_line = line
                break

        if not data_line:
            print("В файле нет данных о множествах!")
            return None

        return data_line
    except Exception as e:
        print(f"Ошибка чтения файла: {e}")
        return None


def parse_set(set_str):
    """Парсинг множества с обработкой вложенных структур"""
    if len(set_str) < 2:
        return None, "Слишком короткая строка множества"

    delimiter_open = set_str[0]
    delimiter_close = '}' if delimiter_open == '{' else '>'

    if set_str[-1] != delimiter_close:
        return None, f"Несоответствие скобок: ожидалось {delimiter_close}"

    elements = []
    current = ""
    nested_level = 0

    for char in set_str[1:-1]:
        if char in '{<':
            nested_level += 1
        elif char in '}>':
            nested_level -= 1

        if char == ',' and nested_level == 0:
            elem = current.strip()
            if elem:
                elements.append(elem)
            current = ""
        else:
            current += char

    if current.strip():
        elements.append(current.strip())

    return elements, None


def count_elements(elements):
    """Подсчет количества вхождений элементов"""
    counts = {}
    for elem in elements:
        counts[elem] = counts.get(elem, 0) + 1
    return counts


def multiset_difference(set1, set2):
    """Вычисление разности с учетом кратностей"""
    counts2 = count_elements(set2)
    result = []

    for elem in set1:
        if counts2.get(elem, 0) > 0:
            counts2[elem] -= 1
        else:
            result.append(elem)

    return result


def format_result(elements, original_set):
    """Форматирование результата в тот же стиль, что и входное множество"""
    if original_set.startswith('<'):
        return '<' + ','.join(elements) + '>'
    else:
        return '{' + ','.join(elements) + '}'


def save_result(result):
    """Сохранение результата в файл"""
    try:
        with open("input.txt", "a") as file:
            file.write(f"Результат: {result}\n")
        print("Результат сохранен в файл.")
    except Exception as e:
        print(f"Ошибка сохранения: {e}")


def main():
    """Основная функция программы"""
    print("\nПрограмма для вычисления разности множеств с учетом кратных вхождений")

    # Проверяем/создаем файл
    if not ensure_input_file():
        print("Не удалось работать с файлом данных. Программа завершена.")
        return

    while True:
        print("\nМеню:")
        print("1. Ввести новые множества")
        print("2. Использовать сохраненные множества")
        print("3. Показать содержимое файла")
        print("4. Выход")

        choice = input("Выберите действие: ").strip()

        if choice == '1':
            # Ввод новых данных
            data = overwrite_sets_in_file()
            if not data:
                continue

            # Парсинг и обработка
            set1, err1 = parse_set(data.split()[0])
            set2, err2 = parse_set(data.split()[1])

            if err1 or err2:
                print(f"Ошибка: {err1 or err2}")
                continue

            result = multiset_difference(set1, set2)
            formatted_result = format_result(result, data.split()[0])

            print("\nРезультат:", formatted_result)
            save_result(formatted_result)

        elif choice == '2':
            # Использование сохраненных данных
            data = read_sets_from_file()
            if not data:
                continue

            print("\nИспользуемые данные:", data)

            # Парсинг и обработка
            parts = data.split(maxsplit=1)
            if len(parts) < 2:
                print("Ошибка: в файле недостаточно данных")
                continue

            set1, err1 = parse_set(parts[0])
            set2, err2 = parse_set(parts[1])

            if err1 or err2:
                print(f"Ошибка: {err1 or err2}")
                continue

            result = multiset_difference(set1, set2)
            formatted_result = format_result(result, parts[0])

            print("\nРезультат:", formatted_result)
            save_result(formatted_result)

        elif choice == '3':
            # Показать содержимое файла
            show_file_content()

        elif choice == '4':
            # Выход
            print("Завершение программы...")
            break

        else:
            print("Неверный ввод. Попробуйте снова.")


if __name__ == "__main__":
    main()
