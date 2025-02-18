#include "list.h"
#include <iostream>

using namespace std;


int main(){
	List<int> A_list;
  List<int> B_list;

  int a, b, temp; 

  cout << "Enter list size A - ";
  cin >> a;
  for (int i{0}; i < a; i++){
    cout << "Element " << i << "#: ";
    cin >> temp;
    A_list.Add(temp);
  }

  cout << "Enter list size B - ";
  cin >> b;
  for (int i{0}; i < b; i++){
    cout << "Element " << i << "#: ";
    cin >> temp;
    B_list.Add(temp);
  }
  
  cout << "list A:\n";
  A_list.View();

  cout << "Delete element with index - ";
  cin >> temp;
  A_list.Del(temp);

  cout << "list A:\n";
  A_list.View();

  cout << "list B:\n";
  B_list.View();

  B_list.Sort();
  cout << "Sort list B:\n";
  B_list.View();

  cout << "Search element with data - ";
  cin >> temp;
  cout << B_list.Search(temp) << endl;

  cout << "Search element with index - ";
  cin >> temp;
  cout << B_list[temp] << endl;

  List<int> result;
  result = A_list + B_list;
  cout << "A union B:\n";
  result.View();

  result = A_list ^ B_list;
  cout << "A intersection B:\n";
  result.View();
}
