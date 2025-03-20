from lab1 import BinarySearchTree

def main():
    bst = BinarySearchTree()
    
    # Вставка элементов
    elements = [50, 30, 70, 20, 40, 60, 80]
    print(f"Вставка элементов: {elements}")
    bst.build_from_array(elements)
    
    # Обход дерева (симметричный)
    print("Обход дерева (inorder):", bst.inorder())
    
    # Поиск узла
    search_key = 40
    print(f"Поиск узла с ключом {search_key}:", "Найден" if bst.search(search_key) else "Не найден")
    
    # Удаление узла
    delete_key = 30
    print(f"Удаление узла с ключом {delete_key}")
    bst.delete(delete_key)
    print("Обход дерева после удаления:", bst.inorder())

if __name__ == "__main__":
    main()
