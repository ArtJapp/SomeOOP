
#include <iostream>
#include <sstream>

using namespace std;

struct Num {
    double Real;
    double Imaginary;

    void Init()
    {
        // инициализация пустого (нулевого) числа
        Real = 0;
        Imaginary = 0;
    }
    void Init(double a)
    {
        // инициализация вещественного числа
        Real = a;
        Imaginary = 0;
    }
    void Init(double a, double b)
    {
        Real = a;
        Imaginary = b;
    }
    void Display()
    {
        // функция вывода числа в консоли
        cout << Real << " " << Imaginary << "i" << endl;
    }
    string toString()
    {
        //функция преобразования числа в строку
        ostringstream str_r, str_i;
        str_r << Real;
        string real = str_r.str();

        string imaginary;

        if (Imaginary == 1) {
            imaginary = "+";    //для того, чтобы получить не а+1i, a просто a+i
        }
        else {
            if (Imaginary == -1) {
                imaginary = "-";    //соответственно для получения а-i вместо a-1j
            }
            else {
                str_i << Imaginary;
                imaginary = str_i.str();
                if (Imaginary >= 0) {
                    imaginary = "+" + imaginary;
                }
            }
        }
        return (real + imaginary + "i");
    }
    void Read()
    {
        cout << "Введите вещественную часть: ";
        while (!(cin >> Real)) {
            cout << "Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, то есть поток становится "хорошим"
            cin.sync(); // удаляет данные из буфера
            cout << "Введите вещественную часть: ";
        }
        cout << "Введите мнимую часть: ";
        while (!(cin >> Imaginary)) {
            cout << "Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, то есть поток становится "хорошим"
            cin.sync(); // удаляет данные из буфера
            cout << "Введите мнимую часть: ";
        }
    }
};

class Complex {
public:
    // доступ к вещественной и мнимой частям будут осуществляться как имя.number.Real или имя.number.Imaginary
    Num number;
    Complex()
    {   
        // инициализация (и обнуление) вещественной и мнимой частей
        number.Init();
    }
    
    Complex add(Complex num)
    {
        //функция добавления к исходному числу числа number
        double a = number.Real + num.number.Real;
        double b = number.Imaginary + num.number.Imaginary;
        Complex ans;
        ans.number.Init(a, b);
        return ans;
    }
    
    Complex operator + (const Complex & a)  {
        return this->add(a);
    }
    
    Complex sub(Complex num)
    {
     //функция вычитания числа number из исходного числа 
     double real = number.Real - num.number.Real;
     double imag = number.Imaginary - num.number.Imaginary;
     Complex ans;
     ans.number.Init(real, imag);
     return ans;
    }
    
    Complex operator -(const Complex & number)
    {
     return this->sub(number);
    }
    
    Complex mul(Complex num)
    {
        // (a, b)
        double a = number.Real * num.number.Real - number.Imaginary * num.number.Imaginary;
        double b = number.Real * num.number.Imaginary + number.Imaginary * num. number.Real;
        Complex ans;
        ans.number.Init(a, b);
        return ans;
    }
    
    Complex operator *(Complex const & number)
    {
        return this->mul(number);
    }
    
    Complex div(Complex num)
    {
        // (a, b) / (c, d) = (ac + bd, bc - ad) / (c*c + d*d)
        // результат деления заносится в число (a, b)
        double a = number.Real * num.number.Real + number.Imaginary * num.number.Imaginary;
        double b = number.Imaginary * num.number.Real - number.Real * num.number.Imaginary;
        a /= (num.number.Real * num.number.Real + num.number.Imaginary * num.number.Imaginary);
        b /= (num.number.Real * num.number.Real + num.number.Imaginary * num.number.Imaginary);
        Complex ans;
        ans.number.Init(a, b);
        return ans;
    }
    
    Complex operator /(Complex const & number)
    {
        return this->div(number);
    }
    
    Complex conj()
    {
        //функция нахождения сопряженного числа
        Complex ans;
        ans.number.Init(number.Real, -number.Imaginary);
        return ans;
    }
    
    bool equ(Complex num)
    {
        //функция сравнения двух комплексных чисел
        return number.Real == num.number.Real && number.Imaginary == num.number.Imaginary;
    }
    
    bool operator ==(Complex const & number)
    {
        return this->equ(number);
    }
};

int main()
{
    Complex x;
    x.number.Display();
    x.number.Read();
    x.number.Display();
    cout << "Сумма  " << (x + x).number.toString() << endl;
    cout << "Разность  " << (x - x).number.toString() << endl;
    cout << "Произведение  " << (x * x).number.toString() << endl;
    cout << "Частное  " << (x / x).number.toString() << endl;
    cout << "Эквивалентность  " << (x == x) << endl;                            //эквивалентность самому себе)
    cout << "Сопряженное  " << x.conj().number.toString() << endl;
    
    return 0;   
}
