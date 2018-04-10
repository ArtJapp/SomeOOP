#include <iostream>
#include <fstream>
#include <cmath>
 
using namespace std;
 
class Point {
 
private:
    
    double x;
    double y;
 
public:
    
    //Сеттеры
 
    void setX(double coordx) {
        x = coordx;
    }
    void setY(double coordy) {
        y = coordy;
    }
 
    //Геттеры
 
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
 
    void printPointInfo() { //Метод вывода информации о точке на экран (можно не использовать, так как мы перегрузили вывод в консоль)
        cout << "Coordinate x = " << getX() << "\n";
        cout << "Coordinate y = " << getY() << "\n";
    }
 
    void savePointInfo() { //Метод вывода информации о точке в файл
        ofstream fout("output.txt");
        fout << "Information about point coords:\n";
        fout << "Coordinate x: " << getX() << "\n";
        fout << "Coordinate y: " << getY() << "\n";
        fout.close();
    }
 
    Point(double coordX, double coordY) { //Инициализирующий конструктор (конструктор с параметрами)
        setX(coordX);
        setY(coordY);
    }
 
    ~Point() { //Деструктор
        cout << "Point class destructor has been called!"
             << "\n";
    }
 
    friend ostream& operator<<(ostream&, const Point&); //Объявляем дружественную функцию (для перегрузки оператора вывода в консоль)
};
 
ostream& operator<<(ostream& out, const Point& obj) { //Функция перегрузки оператора вывода
    out << "Coordinate x: " << obj.x << "\n";
    out << "Coordinate y: " << obj.y;
    return out;
}
 
class Vector : public Point { //Наследуем родительский класс
 
public:
    double calculateVectorLength() { //Метод вычисления длины вектора
        return sqrt(getX() * getX() + getY() * getY());
    }
 
    Vector(double coordX, double coordY) : Point(coordX, coordY) { //Инициализирующий конструктор
    }
 
    void printVectorLength() { //Метод вывода информации о длине вектора на экран
        cout << "Vector length: " << calculateVectorLength() << "\n";
    }
 
    ~Vector() { //Деструктор
        cout << "Vector class destructor has been called!"
             << "\n";
    }
};
 
int main()
{
    Point* obj1 = new Point(3.5, 7.2); //Создаем объект класса Point
 
    cout << "Point class info:\n\n";
    cout << *obj1 << "\n"; //Перегружаем оператор вывода в консоль (<<), выводим координаты точки
    obj1->savePointInfo();
  //obj1->printPointInfo(); //Можно не использовать, так как мы перегрузили оператор вывода
    delete obj1; //Будет вызван деструктор базового класса
 
    cout << "\n";
 
    Vector* obj2 = new Vector(3, 4); //Создаем объект класса Vector
 
    cout << "Vector class info:\n\n";
    cout << *obj2 << "\n"; //Перегружаем оператор вывода в консоль (<<), выводим координаты точки
  //obj2->printPointInfo(); //Можно не использовать, так как мы перегрузили оператор вывода
    obj2->printVectorLength();
    delete obj2; //Будет вызван деструктор дочернего класса, а затем деструктор базового (это происходит при наследовании)
 
    system("pause");
    return 0;
}