#include <iostream>
#include<ctime>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void printList(Node* head) 
{
    cout << "your spisok:\n";
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void insert(Node** head, int data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = (*head);
    newNode->prev = nullptr;

    if ((*head) != nullptr)
        (*head)->prev = newNode;
    (*head) = newNode;
}


void insert_mesto(Node** head, int data, int position) {
    cout << "Your old spisok:\n";
    printList(*head);
    Node* newNode = new Node();
    newNode->data = data;

    if (position == 0) {
        newNode->next = (*head);
        newNode->prev = nullptr;
        if ((*head) != nullptr)
            (*head)->prev = newNode;
        (*head) = newNode;
        printList(*head);
        return;
    }

    Node* current = *head;
    for (int i = 0; current != nullptr && i < position - 1; ++i) {
        current = current->next;
    }

    if (current == nullptr) {
        cout<< "Position wasn't found!" << endl;
        delete newNode;
        printList(*head);
        return;
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr)
        current->next->prev = newNode;
    current->next = newNode;
    cout << "Your new spisok:\n";
    printList(*head);
}

void clear(Node** head) {
    Node* current = *head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    *head = nullptr;
}


void generateRandomList(Node** head) {
    clear(head);
    srand(time(0));
    for (int i = 0; i < 15; ++i) {
        int randomValue = -20 + rand() % 41;
        insert(head, randomValue);
    }
    printList(*head);
}


bool search(Node* head, int key) 
{
    Node* current = head;
    while (current != nullptr) {
        if (current->data == key)
            return true;
        current = current->next;
    }
    return false;
}

void deleting(Node** head, int value) {
    Node* current = *head;
    while (current != nullptr && current->data != value) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Element with value " << value << " not found.\n";
        return;
    }
    if (*head == current) {
        *head = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    Node* temp = current;
    if (search(*head, value)) {
        deleting(head, value);
    }
    delete temp;
    cout << "Element with value " << value << " deleted successfully.\n";
    printList(*head);
}




void swap(Node* a, Node* b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
void Sort(Node* head)
{
    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;
    if (head == nullptr)
        return;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printList(head);
}


void merge(Node** head1, Node* head2) {
    cout << "Your lists:\n";
    printList(*head1);
    printList(head2);
    if (head1==nullptr){}
    Node* current = head2;

    while (current != nullptr) {
        Node* temp = *head1;
        bool found = false;
        while (temp != nullptr) {
            if (temp->data == current->data) {
                found = true;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            insert(head1, current->data);
        }

        current = current->next;
    }
    printList(*head1);

}



void per(Node** head1, Node* head2) {
    cout << "Your lists:\n";
    printList(*head1);
    printList(head2);
    Node* current1 = *head1;
    Node* current2 = head2;
    Node* newHead = nullptr;

    while (current1 != nullptr) {
        current2 = head2;
        bool found = false;
        while (current2 != nullptr) {
            if (current1->data == current2->data) {
                found = true;
                break;
            }
            current2 = current2->next;
        }
        if (found) {
            insert(&newHead, current1->data);
        }
        current1 = current1->next;
    }

    clear(head1);
    *head1 = newHead;
    printList(*head1);

}


void menu()
{
    cout << "\n\t1-show spisok1\n\t2-show spisok2\n\t11-generate spisok1\n\t12-generate spisok2\n\t21-delete el from spisok1\n\t22-delete el from spisok2\n\t31-Sort spisok1\n\t32-Sort spisok2\n\t41-poisk v spisok1\n\t42-poisk v spisok2\n\t5-obyeddinenie spisok1 spisok2\n\t6-peresechenie spisok1 spisok2\n\t71-vstavka v spisok1\n\t72-vstavka v spisok2\n\t0-exit\n\tYour choice:\t";
}
void vybor(int k, Node** head1, Node** head2) {
    switch (k) {
    case 1:
        printList(*head1);
        break;
    case 2:
        printList(*head2);
        break;
    case 11:
        generateRandomList(head1);
        break;
    case 12:
        generateRandomList(head2);
        break;
    case 21: {
        int s;
        cout << "What to delete?\n\tElement: ";
        cin >> s;
        deleting(head1, s);
        break;
    }
    case 22: {
        int s;
        cout << "What to delete?\n\tElement: ";
        cin >> s;
        deleting(head2, s);
        break;
    }
    case 31:
        Sort(*head1);
        break;
    case 32:
        Sort(*head2);
        break;
    case 41: {
        int f;
        cout << "What to find?\n: ";
        cin >> f;
        if (search(*head1, f)) { cout << "Element prisutstvuet!\n"; }
        else { cout << "Element otsutstvuet!\n"; }
        break;
    }
    case 42: {
        int f;
        cout << "What to find?\n: ";
        cin >> f;
        if (search(*head2, f)) { cout << "Element prisutstvuet!\n"; }
        else{cout << "Element otsutstvuet!\n";}
        break;
    }
    case 5:
        merge(head1, *head2);
        break;
    case 6:
        per(head1, *head2);
        break;
    case 71: {
        int i, m;
        cout << "What to insert?\n: ";
        cin >> i;
        cout << "Where to insert (position)?\n: ";
        cin >> m;
        insert_mesto(head1, i, m);
        break;
    }
    case 72: {
        int i, m;
        cout << "What to insert?\n: ";
        cin >> i;
        cout << "Where to insert (position)?\n: ";
        cin >> m;
        insert_mesto(head2, i, m);
        break;
    }
    case 0:
        clear(head1);
        clear(head2);
        exit(1);
        break;
    default:
        cout << "Try one more\n\t";
        break;
    }
}
