#include <iostream>
#include "Node.h";
#include "bor.h";
using namespace std;

void add_string(string s, Node* root){
	Node* current = root;
	Node* ptr;
	int j;
	bool fnd;
	for (int i = 0; i < s.size(); i++){
		fnd = false;
		for (j = 0; j < current->front_ptrs.size(); j++){
			ptr = current->front_ptrs[j];
			if (ptr != nullptr){
				if (s[i] == ptr->c){
					current = current->front_ptrs[j];
					fnd = true;
					break;
				}
			}
		}
		if (fnd == false){
			if (current->front_ptrs[0] == nullptr)
				current->front_ptrs[current->num] = new Node(s[i]);
			else
				current->front_ptrs.push_back(new Node(s[i]));
			current->num++;
			ptr = current->front_ptrs[current->num - 1];
			ptr->back_ptr = current;
			current = current->front_ptrs[current->num - 1];
		}
		if (i == s.size() - 1)
			current->terminal = true;
	}
	cout << "Строка была добавлена!" << endl << endl;
}
int delete_string(string s, Node* root){
	Node* current = root;
	Node* ptr;
	int i, j;
	bool fnd = false;
	for (i = 0; i < s.size(); i++){
		for (j = 0; j < current->front_ptrs.size(); j++){

			ptr = current->front_ptrs[j];
			if (ptr == nullptr){
				cout << "Строка не найдена" << endl << endl;
				return 1;
			}
			if (s[i] == ptr->c){
				current = current->front_ptrs[j];
				fnd = true;
				break;
			}
		}
		if (fnd == false){
			cout << "Строка не найдена" << endl << endl;
			return 1;
		}
	}
	if (current->terminal != true){
		cout << "Строка не найдена" << endl << endl;
		return 1;
	}
	for (i = s.size() - 1; i >= 0; i--){
		if ((current->num < 1 && current->terminal == false) || (i == s.size() - 1 && current->num < 1)){
			current = current->back_ptr;
			for (j = 0; j < current->front_ptrs.size(); j++){
				ptr = current->front_ptrs[j];
				if (s[i] == ptr->c){
					delete current->front_ptrs[j];
					current->front_ptrs.erase(current->front_ptrs.begin() + j);
					break;
				}
			}
			current->num--;
		}
		else{
			if (i == s.size() - 1)
				current->terminal = false;
			break;
		}
	}
	cout << "Строка была удалена!" << endl << endl;
	return 0;
}
void recursive(Node* current, string word){
	int i;
	for (i = 0; i < current->front_ptrs.size(); i++){
		if (current->front_ptrs[i] != nullptr){
			current = current->front_ptrs[i];
			if (current->is_root == false){
				word.push_back(current->c);
				if (current->terminal == true){
					cout << word << endl;
				}
			}
			recursive(current, word);
		}
	}
}

void view_bor(Node* root){
	Node* current = root->back_ptr;
	string word;
	recursive(current, word);
	cout << endl;
}

int search_string(string s, Node* root){
	Node* current = root;
	Node* ptr;
	int i, j;
	bool fnd = false;
	for (i = 0; i < s.size(); i++){
		for (j = 0; j < current->front_ptrs.size(); j++){
			ptr = current->front_ptrs[j];
			if (ptr == nullptr){
				cout << "Строка не найдена" << endl << endl;
				return 1;
			}
			if (s[i] == ptr->c){
				current = current->front_ptrs[j];
				fnd = true;
				break;
			}
		}
		if (fnd == false){
			cout << "Строка не найдена" << endl << endl;
			return 1;
		}
	}
	if (current->terminal == true){
		cout << "Строка найдена" << endl << endl;
		return 0;
	}
	else{
		cout << "Строка не найдена" << endl << endl;
		return 1;
	}
}
void delete_bor(Node* root){
	int i;
	if (root != nullptr)
		for (i = 0; i < root->front_ptrs.size(); i++){
			if (root->front_ptrs[i])
			{
				delete_bor(root->front_ptrs[i]);
			}
		}
	delete root;
}