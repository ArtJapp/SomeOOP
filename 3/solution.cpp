
#include <fstream>
#include <iostream>

using namespace std;
class Queue {
public:
    Queue()
    {                               //инициализация очереди
        size = 3;                   //задается исходный размер равный 3
        current = 0;                //текущее количество элементов становится равным 0
        queue = new int[size];
    }
    ~Queue()
    {
        //при удалении экземпляра возникает необходимость в очистке памяти от массива, иначе от так и останется висеть в памяти
        delete[] queue;
    }
    
    void fileInput()
    {
        //функция ввода данных из файла file.txt
        fstream fin("file.txt");
        int temp;
        while(!fin.eof())
        {
            fin >> temp;
            push(temp);
        }
    }
    
    int getCurrentSize()
    {   //геттер значения текущего размера массива
        return size;
    }

    void push(int num)
    {
        if (getCurrentSize() - current < differCondition) {
            // если достигнуто условие перестройки массива, то есть осталось менее differCondition ячеек, то вызывается функция resize
            resize();
        }
        
        queue[current++] = num;
    }
    void print_all()
    {
        //функция безопасной печати всех значений очереди, то есть элементы НЕ извлекаются
        for (int i = 0; i < current; i++)
        {
            cout << queue[i] << " ";
        }
        cout << endl;
    }

    int pop()
    {
        // функция извлечения из очереди элемента
        int data = queue[0];
        for (int i = 0; i < current - 1; i++) {
            queue[i] = queue[i + 1];
        }
        current--;
        return data;
    }
    bool exchanger(int old_num, int new_num)
    {
        //функция замены значения старых элеметов на новое. Если старого значения в очереди нет, вернет false. При хотя бы 1 успешной замене вернет true
        bool ans = false;
        for (int i = 0; i < current; i++)
        {
            if (old_num == queue[i])
            {
                ans = true;
                queue[i] = new_num;
            }
        }
        return ans;
    }

private:
    void resize()
    {
        // функция перестраивания массива queue (именно эта функция обеспечивает динамическое расширение очереди)
        int * temp = new int[size + changer];
        for (int i = 0; i < size; i++) {
            temp[i] = queue[i];
        }
        delete[] queue;
        queue = temp;
        size += changer;
    }
    int size;
    int current;
    int* queue;
    const int changer = 5;         //на сколько ячеек увеличится очередь
    const int differCondition = 2; //сколько ячеек должно остаться перед увеличением очереди
};

int main()
{
    Queue ochered;
    ochered.fileInput();
    cout << "Введите числа, которые нужно заменить в формате: старое_число новое_число" << endl;
    int old_num, new_num;
    do{
        // ввод остановится только при введении числа, не входящего в состав очереди 
        cin >> old_num >> new_num;
    } while(ochered.exchanger(old_num, new_num));
    ochered.print_all();
}