
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Complex
{
    double Real;
    double Imaginary;
};

void Init(Complex &number)
{
    // вызов без особых аргументов => вещественная и мнимая части нулевые
    number.Real = 0;
    number.Imaginary = 0;
}

void Init(Complex &number, double a)
{
    // вызов с 1 аргументом, так как любое вещественное число a может быть представлено как a+0i
    number.Real = a;
    number.Imaginary = 0;
}

void Init(Complex &number, double a, double b)
{
    number.Real = a;
    number.Imaginary = b;
}

void Read(Complex &number)
{
    double a, b;
    cout << "Введите вещественную часть: ";
        while(!(cin>>a)) 
        {
            cout<<"Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
            cin.sync();// удаляет данные из буффера
            cout<<"Введите вещественную часть: ";
        }
        cout << "Введите мнимую часть: ";
        while(!(cin>>b)) 
        {
            cout<<"Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
            cin.sync();// удаляет данные из буффера
            cout<<"Введите мнимую часть: ";
        }
    Init(number, a, b);
}

string toString(Complex &number)
{
    //преобразование числа в строку
    string imaginary = to_string(number.Imaginary);
    if (number.Imaginary >= 0)
    {
        imaginary = "+" + imaginary;
    }
    return to_string(number.Real) + imaginary + "i";
}

void Display(Complex &number)
{
    //функция вывода числа на экран
    ostringstream str_r,str_i;
    str_r << number.Real;
    string real = str_r.str();
    
    string imaginary;
    
    if (number.Imaginary == 1)
    {
        imaginary = "+";
    } else
    {
        if (number.Imaginary == -1)
        {
            imaginary = "-";
        } else 
        {
            str_i << number.Imaginary;
            imaginary = str_i.str();
            if (number.Imaginary >= 0)
            {
                imaginary = "+" + imaginary;
            }
        }
    }
    
    cout << real << imaginary << "i" << endl;
    
}

// -------------------

void add(Complex &ans, Complex a, Complex b)
{
    //функция вычисления суммы
    ans.Real = a.Real + b.Real;
    ans.Imaginary = a.Imaginary + b.Imaginary;
}

void sub(Complex &ans, Complex a, Complex b)
{
    //функция вычисления разности
    ans.Real = a.Real - b.Real;
    ans.Imaginary = a.Imaginary - b.Imaginary;
}

void mul(Complex &ans, Complex a, Complex b)
{
    //функция вычисления произведения
    ans.Real = a.Real * b.Real - a.Imaginary * b.Imaginary;
    ans.Imaginary = a.Real * b.Imaginary + b.Real * a.Imaginary;
}

void div(Complex &ans, Complex a, Complex b)
{
    //функция вычисления частного
    ans.Real = a.Real * b.Real + a.Imaginary * b.Imaginary;
    ans.Imaginary = a.Imaginary * b.Real - a.Real * b.Imaginary;
    double coeff = b.Real * b.Real + b.Imaginary * b.Imaginary;
    ans.Real /= coeff;
    ans.Imaginary /= coeff;
}

bool equ(Complex a, Complex b)
{
    //функция сравнения чисел
    return a.Real == b.Real && a.Imaginary == b.Imaginary;
}

void conj(Complex &ans, Complex a)
{
    //функция вычисления сопряженного числа
    ans.Real = a.Real;
    if (a.Imaginary == 0.0)
    {
        // здесь нельзя было просто написать    ans.Imaginary = - a.Imaginary;
        // внезапно, ans.Imaginary становится равным отрицательному нулю
        ans.Imaginary = 0;
    }
    else
    {
        ans.Imaginary = - a.Imaginary;
    }
}
// ---------------------
int main()
{
    Complex num;
    Init(num);
    Read(num);
    Display(num);
    cout << toString(num) << endl;
    
    Complex num2;
    Init(num2);
    Read(num2);
    Display(num2);
    cout << toString(num2) << endl;
    
    cout << "Summa: ";
    Complex summa;
    add(summa, num, num2);
    Display(summa);
    cout << toString(summa) << endl;
    
    cout << "Difference: ";
    sub(summa, num, num2);
    Display(summa);
    cout << toString(summa) << endl;
    
    cout << "Multiplication: ";
    mul(summa, num, num2);
    Display(summa);
    cout << toString(summa) << endl;
    
    cout << "Division: ";
    div(summa, num, num2);
    Display(summa);
    cout << toString(summa) << endl;
    
    cout << "Equality: ";
    cout << equ(num, num2) << endl;
    
    cout << "Conjection: ";
    Complex conjected;
    conj(conjected, num2);
    Display(conjected);

    return 0;
}