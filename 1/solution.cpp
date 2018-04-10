#include <iostream>

using namespace std;

class Pair
{
private:
    static int& counter()
    {
        static int c(0);
        return c;
    }
  // требовалось реализовать класс-структуру
  struct {
    int x;
    int y;
  } pair;
public:
    Pair(int coord_x, int coord_y)
    {
        // конструктор пары
        counter()++;
        setX(coord_x);
        setY(coord_y);
    }
    ~Pair()
    {
        // деструктор пары
        counter()--;
    }
    //ряд сеттеров
    void setX(int coord_x)
    {
        pair.x = coord_x;
    }
    void setY(int coord_y)
    {
        pair.y = coord_y;
    }
    
    //ряд геттеров
    int getX() const
    {
        return pair.x;
    }
    int getY() const
    {
        return pair.y;
    }
    
    void print_data()
    {
        //выводит в консоль числа х и у
        cout << "coordinate x: " << getX() << endl;
        cout << "coordinate y: " << getY() << endl;
    }
    
    void print_count_of_objects()
    {       // функция нужна для того, чтобы показать количество созданных объектов
            cout << "Count of objects " << counter() << endl;
    }
    
    friend ostream& operator<<(ostream&, const Pair&); //Объявляем дружественную функцию (для перегрузки оператора вывода в консоль)
    friend istream& operator>>(istream&, const Pair&); //Объявляем дружественную функцию (для перегрузки оператора ввода в консоли)

    
    // определение операций сравнения
    bool operator < (const Pair &another) {
        // сравнение идет по тому, насколько далеко пара от начала координат
        return (this->getX() * this->getX() + this->getY() * this->getY()) < (another.getX() * another.getX() + another.getY() *another.getY());
    }
    
    bool operator > (const Pair &another) {
        // сравнение идет по тому, насколько далеко пара от начала координат
        return (this->getX() * this->getX() + this->getY() * this->getY()) > (another.getX() * another.getX() + another.getY() *another.getY());
    }
    
    bool operator == (const Pair &another) {
        // если координаты совпали, то вернется true
        return (this->getX() == another.getX()) && (this->getY() == another.getY());
    }

    
};

ostream& operator<<(ostream& out, const Pair& object) { //Функция перегрузки оператора вывода
    out << "Coordinate x: " << object.getX() << "\n";
    out << "Coordinate y: " << object.getY();
    return out;
}

istream& operator >> (istream &s, Pair &v) { //Функция перегрузки оператора ввода
    std::cout << "Введите пару\nX:";
    int x,y;
	std::cin >> x;
	std::cout << "\nY:";
	std::cin >> y;
	v.setX(x);
	v.setY(y);

	std::cout << endl;
	return s;
}

class Cursor : public Pair {
private:
    bool orient = false;       // если true, то курсор горизонтальный, иначе вертикальный
    unsigned short size = 2; // размер курсора - целое от 1 до 15
    bool visible = true;
public:

    using Pair::Pair; //воспользуемся конструктором и сеттерами родительского класса
    using Pair::setX;
    using Pair::setY;
    
    void setPosition(int x, int y)
    {   // если вдруг в качестве х и у придут отрицательные числа, программа их не пропустит
        x > 0 ? setX(x) : setX(1);  //координаты - целые положительные, а потому координата 0 недопустима
        y > 0 ? setY(y) : setY(1);
    }
    void setSize(int new_size)
    {
        if (new_size >=1 && new_size <= 15)
        {
            // по условию, размер курсора - целое положительное от 1 до 15
            size = new_size;
        }
    }
    int getSize()
    {
        return size;
    }
    void change_orientation()
    {   // из горизонтального в вертикальный и наоборот
        if (orient)
            cout << "Курсор был горизонтальным, ";
        else
            cout << "Курсор был вертикальным, ";
        orient = !orient; 
        if (orient)
            cout << "стал горизонтальным" << endl;
        else
            cout << "стал вертикальным" << endl;
    }
    void cursor_fade()
    {
        visible = false;
        cout << "курсор погашен" << endl;
    }
    void cursor_not_fade()
    {
        visible = true;
        cout << "курсор восстановлен" << endl;
    }
};

int main()
{
 //   static int counter = 0;
    Cursor cursor(5, 7);
    cursor.print_data();
    cout <<"Current size:" <<  cursor.getSize() << endl;

    cursor.setSize(4);
    cout <<"Current size:" <<  cursor.getSize() << endl;
    
    cursor.setPosition(9, 4);
    cursor.print_data();
    
    Cursor lursor(3, 6);
    Cursor dursor(2, 7);
    Cursor qursor(6, 4);
    Cursor kursor(9, 2);
    kursor.print_count_of_objects();
    lursor.print_count_of_objects(); //значения совпадут, потому что оба объекта имеют статическое поле с количеством
     
    cursor.cursor_fade();
    cursor.cursor_not_fade();
    
    cursor.change_orientation();
}