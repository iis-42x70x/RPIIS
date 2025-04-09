"""
Программа для вычисления разности множеств с учетом кратных вхождений элементов
Разработчица: Баленкова Богдана Игоревна
Дата разработки: 05.04.2025
"""

import os


def ensure_input_file():
    """Создает файл input.txt, если он не существует."""
    if not os.path.exists("input.txt"):
        print("Файл input.txt не найден, создаем новый...")
        default_data = "A={1,2,3} B={2,3,4}\n"
        with open("input.txt", "w") as file:
            file.write(default_data)
        print(f"Создан файл input.txt с примером данных:\n{default_data}")
        return default_data
    return None


def overwrite_sets_in_file():
    """Перезаписывает множества в файл input.txt с проверкой на дубликаты"""
    while True:
        print("\nВведите два множества:")
        print("Пример 1: A={1,2,3} B={2,3,4}")
        print("Пример 2: <<1,2>,<3,4>> <<2,3>,<4,5>>")
        print("Пример 3: {a,b,c} {a,b}")
        user_data = input("Ваши данные: ").strip()

        # Проверяем формат ввода
        sets = user_data.split(maxsplit=1)
        if len(sets) != 2:
            print("Ошибка: требуется два множества.")
            continue

        set1_str, set2_str = sets
        set1_type = "unordered" if set1_str[0] == "{" else "ordered"
        set2_type = "unordered" if set2_str[0] == "{" else "ordered"

        # Парсим и проверяем множества
        set1, err1 = parse_set(set1_str)
        set2, err2 = parse_set(set2_str)

        if err1 or err2:
            print(f"Ошибка: {err1 if err1 else err2}")
            continue

        # Проверка на дубликаты для неупорядоченных множеств
        if set1_type == "unordered" and len(set1) != len(set(set1)):
            print("Ошибка: первое множество содержит дубликаты!")
            continue
        if set2_type == "unordered" and len(set2) != len(set(set2)):
            print("Ошибка: второе множество содержит дубликаты!")
            continue

        # Если все проверки пройдены, сохраняем
        try:
            with open("input.txt", "w") as file:
                file.write(user_data + "\n")
            print("Множества успешно записаны в файл input.txt.")
            return user_data
        except Exception as e:
            print(f"Ошибка записи в файл: {e}")
            return None


def read_input_file():
    """Считывает данные из файла input.txt"""
    try:
        with open("input.txt", "r") as file:
            lines = file.readlines()
            return lines[-1].strip()  # Берем последнюю строку
    except Exception as e:
        print(f"Ошибка чтения файла: {e}")
        return ""


def parse_set(set_str):
    """Парсинг множества с проверкой формата"""
    if len(set_str) < 2 or (set_str[0] not in "{<") or (set_str[-1] not in "}>"):
        return None, "Некорректный формат множества."

    elements = []
    current = ""
    in_nested = 0
    for char in set_str[1:-1]:
        if char in "{<":
            in_nested += 1
        elif char in "}>":
            in_nested -= 1

        if char == "," and in_nested == 0:
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


def set_difference(set1, set2):
    """Вычисление разности множеств с учетом кратных вхождений"""
    counts2 = count_elements(set2)
    result = []
    for elem in set1:
        if counts2.get(elem, 0) > 0:
            counts2[elem] -= 1
        else:
            result.append(elem)
    return result


def format_set(elements, set_type):
    """Форматирование множества в строку"""
    if set_type == "ordered":
        return "<" + ",".join(elements) + ">"
    else:
        return "{" + ",".join(elements) + "}"


def process_data(line):
    """Обработка строки с двумя множествами"""
    sets = line.split(maxsplit=1)
    if len(sets) != 2:
        return None, "Ошибка: требуется два множества."

    set1_str, set2_str = sets
    set1_type = "ordered" if set1_str[0] == "<" else "unordered"
    set2_type = "ordered" if set2_str[0] == "<" else "unordered"

    set1, err1 = parse_set(set1_str.strip())
    if err1:
        return None, f"Ошибка в первом множестве: {err1}"

    set2, err2 = parse_set(set2_str.strip())
    if err2:
        return None, f"Ошибка во втором множестве: {err2}"

    # Дополнительная проверка на дубликаты
    if set1_type == "unordered" and len(set1) != len(set(set1)):
        return None, "Первое множество содержит дубликаты!"
    if set2_type == "unordered" and len(set2) != len(set(set2)):
        return None, "Второе множество содержит дубликаты!"

    result = set_difference(set1, set2)
    return format_set(result, set1_type), None


def save_result_to_input(result):
    """Сохраняет результат в файл input.txt"""
    try:
        with open("input.txt", "a") as file:
            file.write(f"Результат: {result}\n")
        print("Результат сохранен в файл input.txt.")
    except Exception as e:
        print(f"Ошибка при сохранении результата: {e}")


def main():
    """Главная функция"""
    print("\nПрограмма для вычисления разности множеств с учетом кратных вхождений элементов:")
    ensure_input_file()

    while True:
        action = input(
            "\n1. Ввести новые множества\n2. Использовать сохраненные\n3. Выход\nВыберите действие: ").strip()

        if action == "1":
            input_data = overwrite_sets_in_file()
            if not input_data:
                continue
        elif action == "2":
            input_data = read_input_file()
            if not input_data:
                continue
        elif action == "3":
            break
        else:
            print("Неверный ввод. Попробуйте снова.")
            continue

        result, err = process_data(input_data)
        if err:
            print(f"\nОшибка: {err}")
            continue

        print(f"\nРезультат:\n{result}")
        save_result_to_input(result)


if __name__ == "__main__":
    main()
