#include <iostream>
#include <ctime>
#include <cstdlib>

int getRandom(){
    return rand() % 10 + 1;
}

class List{
public:
    class Node{
    public:
        int data;
        Node *next = nullptr;
        Node *prev = nullptr;
    };
    Node *head = nullptr;
    Node *last = nullptr;

// functions
    bool isEmpty(){
        return head == nullptr;
    }
    
    void pushFront(int new_value)
    {
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }
        
        head->next = new_node;
        new_node->prev = head;
        head = new_node;
    }

    void pushLast(int new_value)
    {
        Node *new_node = new Node;
        new_node->data = new_value;

        if(isEmpty()){
            head = new_node;
            last = new_node;
            return;
        }

        last->prev = new_node;
        new_node->next = last;
        last = new_node;
    }
    
    void popFront()
    {
        Node *temp = head;
        head = head->prev;
        if(head)
            head->next = nullptr;
        else {
            last->next = nullptr;
            last = nullptr;
        }
        delete temp;
    }

    void popLast()
    {
        Node *temp = last;
        last = last->next;
        if(last)
            last->prev = nullptr;
        else {
            head->prev = nullptr;
            head = nullptr;
        }
        delete temp;
    }    

    void print()
    {
        Node *curr = last;
        while(curr){
            std::cout << curr->data << ' ';
            curr = curr->next;
        }
        std::cout << '\n';
    }

    void sort() 
    {    
        Node *curr;
        Node *sorted = last;
        bool swapped = true;
        while(swapped){
            swapped = false;
            curr = head;
            while(curr != sorted){
                if(curr->data > curr->prev->data){
                    std::swap(curr->data, curr->prev->data);
                    swapped = true;
                }
                curr = curr->prev;
            }
            sorted = sorted->next;
        }
    }
    
    bool find(int value)
    {
        Node *curr = head;
        while(curr){
            if(curr->data != value)
                curr = curr->prev;
            else
                return true;
        }
        return false;
    }

    void unification(List &first, List &second)
    {
        deleteAll();
        first.sort();
        second.sort();
        Node *curr_first = first.head;
        Node *curr_second = second.head;

        while (curr_first && curr_second) {
            if (curr_first->data < curr_second->data) {
                pushLast(curr_first->data);
                curr_first = curr_first->prev;
            } else if (curr_first->data > curr_second->data) {
                pushLast(curr_second->data);
                curr_second = curr_second->prev;
            } else {
                pushLast(curr_first->data);
                curr_first = curr_first->prev;
                curr_second = curr_second->prev;
            }
        }

        while (curr_first) {
            pushLast(curr_first->data);
            curr_first = curr_first->prev;
        }

        while (curr_second) {
            pushLast(curr_second->data);
            curr_second = curr_second->prev;
        }
    }
    
    void intersection(List &first, List &second)
    {
        first.sort();
        second.sort();
        Node *curr_first = first.head;
        Node *curr_second = second.head;

        while(curr_first && curr_second){
            if(curr_first->data == curr_second->data){
                pushFront(curr_first->data);
                curr_first = curr_first->prev;
                curr_second = curr_second->prev;
            }
            else 
                if(curr_first->data < curr_second->data)
                    curr_first = curr_first->prev;
                else
                    curr_second = curr_second->prev; 
        }
    }

    void deleteAll(){
        while(last)
            popLast();
    }

    ~List(){
        deleteAll();
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); 

    int whatToDo, value;
    List myList, uniList, interList, secList;

    std::cout << '\n';
    std::cout << "1 - push front\n"
                 "2 - push last\n"
                 "3 - delete first\n"
                 "4 - delete last\n"
                 "5 - view\n"
                 "6 - sort\n"
                 "7 - find\n"
                 "8 - unification\n"
                 "9 - intersection\n"
                 "0 - exit\n";

    bool stop = false;
    while(!stop){
        std::cout << "Enter the number of activity: ";
        std::cin >> whatToDo;

        switch (whatToDo)
        {
        // push
        case 1: case 2:
            std::cout << "Enter the value: ";   std::cin >> value;
            (whatToDo == 1) ? myList.pushFront(value) : myList.pushLast(value);
            std::cout << "Successfully\n";
            break;
        // pop
        case 3: case 4:
            if(myList.isEmpty()){
                std::cout << "List is empty\n";   
                break;
            }
            (whatToDo == 3) ? myList.popFront() : myList.popLast();
            std::cout << "Successfully\n";
            break;
        // print
        case 5:
            if(myList.isEmpty()){
                std::cout << "List is empty\n";
                break;
            }
            std::cout << "Your list:\n";
            myList.print();
            break;
        // sort
        case 6:
            if(myList.isEmpty()){
                std::cout << "List is empty\n";
                break;
            }

            myList.sort();
            std::cout << "Your list was sorted successfully:\n";
            myList.print();
            break;
        // find
        case 7:
            std::cout << "Enter the value to find: ";   std::cin >> value;
            if(myList.find(value))
                std::cout << "Value found\n";
            else
                std::cout << "Value not found\n";
            break;
        // unification
        case 8:
            std::cout << "First list: "; myList.print();
            secList.deleteAll();
            std::cout << "Enter 5 values for unification: ";
            for(int i = 0; i < 5; i++){
                std::cin >> value;
                secList.pushFront(value);
            }
            std::cout << "Second list: "; secList.print();

            uniList.deleteAll();
            uniList.unification(myList, secList);
            std::cout << "Unification: "; uniList.print();
            break;
        // intersection
        case 9:
            std::cout << "First list: "; myList.print();
            secList.deleteAll();
            std::cout << "Enter 5 values for intersection:";
            for(int i = 0; i < 5; i++){
                std::cin >> value;
                secList.pushFront(value);
            }
            std::cout << "Second list: "; secList.print();

            interList.deleteAll();
            interList.intersection(myList, secList);
            std::cout << "Intersection: "; interList.print();
            break;
        // exit
        case 0:
            stop = true;
            break;
        default:
            std::cout << "Incorrect input. Try again\n";
            break;
        }
        std::cout << '\n';
    }

    return 0;
}