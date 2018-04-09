#include <iostream>
#include <sstream>

using namespace std;

class Complex
{
public:
    Complex()
    { 
        // инициализация экземпляра класса без параметров
        Real = 0;
        Imaginary = 0;
    };
   Complex(double a)
    {
        // инициализация экземпляра класса с 1 параметром - вещественной частью числа.
        // чтобы сделать то же самое с мнимой частью, нужно явно указать, что вещественная часть равна 0 
        //Для чего это нужно? чтобы написать Complex num = 4; и иметь комплексное число 4 + 0i
        Real = a;
        Imaginary = 0;
    }; 
    Complex(double a, double b)
    {
        Real = a;
        Imaginary = b;
    };
    void Read()
    {
        cout << "Введите вещественную часть: ";
        while(!(cin>>Real)) 
        {
            cout<<"Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
            cin.sync();// удаляет данные из буффера
            cout<<"Введите вещественную часть: ";
        }
        cout << "Введите мнимую часть: ";
        while(!(cin>>Imaginary)) 
        {
            cout<<"Некорректный ввод !\n";
            cin.clear(); // сбрасывает все биты потока, тоесть поток становится "хорошим"
            cin.sync();// удаляет данные из буффера
            cout<<"Введите мнимую часть: ";
        }
    }
    void Display()
    {
        cout << Real << " " << Imaginary << "i\n";
    };
    string toString()
    {
        ostringstream str_r,str_i;
    str_r << Real;
    string real = str_r.str();
    
    string imaginary;
    
    if (Imaginary == 1)
    {
        imaginary = "+";
    } else
    {
        if (Imaginary == -1)
        {
            imaginary = "-";
        } else 
        {
            str_i << Imaginary;
            imaginary = str_i.str();
            if (Imaginary >= 0)
            {
                imaginary = "+" + imaginary;
            }
        }
    }
    return (real + imaginary + "i");
    }
    
    Complex add(Complex number)
    {
        //функция добавления к исходному числу числа number
        double a = Real + number.Real;
        double b = Imaginary + number.Imaginary;
        Complex ans(a, b);
        return ans;
    }
    
    Complex operator + (const Complex & a)  {
        return this->add(a);
    }
    
    Complex sub(Complex number)
    {
        //функция вычитания числа number из исходного числа 
        double real = Real - number.Real;
        double imag = Imaginary - number.Imaginary;
        return Complex(real, imag);
    }
    
    Complex operator -(const Complex & number)
    {
        return this->sub(number);
    }
    
    Complex mul(Complex number)
    {
        // (a, b)
        double a = Real * number.Real - Imaginary * number.Imaginary;
        double b = Real * number.Imaginary + Imaginary * number.Real;
        return Complex(a, b);
    }
    
    Complex operator *(Complex const & number)
    {
        return this->mul(number);
    }
    
    Complex div(Complex number)
    {
        // (a, b) / (c, d) = (ac + bd, bc - ad) / (c*c + d*d)
        // результат деления заносится в число (a, b)
        double a = Real * number.Real + Imaginary * number.Imaginary;
        double b = Imaginary * number.Real - Real * number.Imaginary;
        a /= (number.Real * number.Real + number.Imaginary * number.Imaginary);
        b /= (number.Real * number.Real + number.Imaginary * number.Imaginary);
        return Complex(a, b);
    }
    
    Complex operator /(Complex const & number)
    {
        return this->div(number);
    }
    
    Complex conj()
    {
        return Complex(Real, -Imaginary);
    }
    
    bool equ(Complex number)
    {
        return Real == number.Real && Imaginary == number.Imaginary;
    }
    
    bool operator ==(Complex const & number)
    {
        return this->equ(number);
    }
private:
    double Real;
    double Imaginary;
};

int main()
{
    Complex test1(3, 5);
    Complex test2(2, -1);
    
    cout << "Summa: \n";
    Complex plus = test1 + test2;
    plus.Display();
    cout << (test1.add(test2)).toString() << endl;
    
    cout << "Difference: \n";
    Complex minus = test1 - test2;
    minus.Display();
    cout << (test1.sub(test2)).toString() << endl;
    
    cout << "Multiplication: \n";
    Complex umnoj = test1 * test2;
    umnoj.Display();
    cout << (test1.mul(test2)).toString() << endl;
    
    cout << "Division: \n";
    Complex delen = test1 / test2;
    delen.Display();
    cout << (test1.div(test2)).toString() << endl;
    
    cout << "Conjection: \n";
    Complex con = test1.conj();
    con.Display();
    cout << "Conjection of conjected: \n";
    con = con.conj();
    con.Display();
    
    cout << "Equality: \n";
    if (test1 == test2)
    {
        cout << test1.toString() << " is equal to " << test2.toString();
    }
    else 
    {
        cout << test1.toString() << " is non equal to " << test2.toString();
    }
    cout << endl << test1.equ(test2) << endl;
}