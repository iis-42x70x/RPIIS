#include <iostream>
#include <string>
#include <fstream> 
#include <sstream>
using namespace std;
int main(void)
{
//Задание переменных
int i,j,k,t,c,X,w, orient=0,orient1=0, vzvesh=0;
int rows = 0, cols = 0, n=0;
int** a = nullptr;
//Выбор метода ввода матрицы смежности
cout << "Выберите метод заполнения графа:" << endl << "1.Выбрать один из предоставленных файлов" << endl 
<< "2.Ввести матрицу смежности графа с клавиатуры." << endl;
cin >> w;
cout << endl;
if(w==1){
//Заполнение матрицы смежности из файлов
string name;
int numberOfGraph;
cout << "Введите номер матрицы смежности графа(1-5) или вручную введите абсолютный путь к файлу(6): ";
cin >> numberOfGraph;
switch (numberOfGraph) {
    case 1: name = "graph1.txt"; break;
    case 2: name = "graph2.txt"; break;
    case 3: name = "graph3.txt"; break;
    case 4: name = "graph4.txt"; break;
    case 5: name = "graph5.txt"; break;
    case 6: cout << "Введите ваш путь:"; cin >> name; break;
    default: cout << "Некорректный номер файла." << endl; return 0;
}
ifstream file(name);
string line;
while (getline(file, line)) {
    stringstream ss(line);
    int value;
    int current_cols = 0;

    while (ss >> value) {
        current_cols++;
    }

    if (rows == 0) {
        cols = current_cols; 
    }
    rows++;
}
a = new int*[rows];
for (i = 0; i < rows; i++) {
    a[i] = new int[cols];
}
file.clear();
file.seekg(0, ios::beg);
i = 0, j = 0;
while (getline(file, line)) {
    stringstream ss(line);
    while (ss >> a[i][j]) {
        j++;
    }
    i++;
    j = 0; 
}
file.close();
if(rows!=cols){
    cout << "Неверная матрица смежности. Количество столбцов и строк не совпадает." << endl;
    return 0;
}
if(rows==0){
    cout << "Неверная матрица смежности. Количество точек равно 0. Вероятно что-то пошло не так!" << endl;
    return 0;
}
if(rows==1){
    cout << "Граф состоит из одной точки, дальнейшие расчёты не требуются." << endl;
    return 0;
}
}
else if(w==2){
//Заполнение матрицы смежности с клавиатуры
cout << "Введите количество точек" << endl;  
cin >> n;
a = new int*[n];
for (i = 0; i < n; i++) {
    a[i] = new int[n];
}
for(j=0;j<n;j++){
    for(i=0;i<n;i++){
        cout << "Заполните матрицу смежности: от точки " << j << " к точке " << i << " = "; cin >> a[i][j]; cout << " ";
        if(a[i][j]<0){
            cout << endl << "Неверный элемент матрицы смежности! Попробуйте ещё раз." << endl << endl;
            i=i-1;
        }
    }
    cout << endl;
} 
}
else{
    cout << "Некорректный метод ввода!" << endl;
    return 0;
}
//Задание вспомогательных переменных
int u=rows+n;
int distance[u];
string path[u];
while(true){
cout << "Введите точку начала(начиная с 0): ";  
cin >> X;
cout << endl;
if(X<0 || X>=u){
    cout << "Такой точки не существует. Попробуйте ещё раз." << endl;
}
else{
    break;
}
}
//Вывод об ориентированности и взвешенности графа
for(i = 0; i < u; i++) {  
    for(j = 0; j < u; j++){
        if(a[i][j]!=a[j][i]){
            if(a[i][j]==0 || a[j][i]==0){
                orient++;
            }
            else{
                cout << "Граф задан неверно." << endl;
                return 0;
            }
        }
        else if(a[i][j]==0){
            orient1++;
        }
        if(a[i][j]==1 || a[i][j]==0){
            vzvesh++;
        }
    }
}
if((orient+orient1)==(u*u)){
    cout << "Граф является ориетированным." << endl;
}
else if(orient==0){
    cout << "Граф является неориентированным." << endl;
}
else{
    cout << "Некоторые из дуг графа являются ориентированными." << endl;
}
if(vzvesh==(u*u)){
    cout << "Граф не является взвешенным." << endl;
}
else{
    cout << "Граф является взвешенным." << endl;
}
cout << endl;
//Вывод матрицы смежности
for(i = 0; i < u; i++) {  
    for(j = 0; j < u; j++)
        cout << a[i][j] << " ";
    cout << endl; 
}
cout << endl;
//Вспомогательные массивы
for(j=0;j<u;j++){
    distance[j]=9999999;
} 
distance[X]=0;
for(j=0;j<u;j++){
    path[j]=to_string(X);
} 
//Подсчёт расстояния и пути
for(k=0; k<(n+rows); k++){
    if(a[X][k]!=0){
        if(distance[k] > a[X][k]) {
            distance[k]= a[X][k];
            path[k]+= " --> " + to_string(k);       
    }
    }
}
for(t=0;t<u; t++){
for(k=0;k<u; k++){
    if(k!=X && distance[k]<9999999){
    for(c=0;c<u; c++){
    if(c!=k && a[k][c]!=0 && c!=X){
        if(distance[c]>distance[k]+a[k][c]){
            distance[c]=distance[k]+a[k][c];
            path[c]=path[k];
            path[c]+= " --> " + to_string(c);
        }
    }
    }
}
}
}
//Вывод расстояния и пути
for(j = 0; j <u; j++){
    if(distance[j]==9999999){
        cout << "Точка " << j << " не соединена с остальными точками." << endl << endl;
    }
    else if(j==X){
        cout << "Точка " << j << " была выбрана вами как точка начала" << endl << endl;
    }
    else{
    cout << "Расстояние до точки  " << j << " : " << distance[j] << endl << "Путь к точке  " << j << " : " << path[j] << endl << endl;
}
}
cout << endl;
}