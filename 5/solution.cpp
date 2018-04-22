/*
    Диапазон значений элементов массива - от -100 до 100. 
    Размерность массива определяется в начале выполнения программы как 
    случайное число в диапазоне 50-200. Заменить каждый элемент 
    на среднее арифметическое его и его соседей слева и справа. 
    В тексте программы запрещается применять операцию индексации
*/

#include <iostream>

using namespace std;

struct List 
{
    double number;
    List * next, * prev;
};

List * init()
{
    return NULL;
}

void pushList(List *& list, double key)
{
    List * temp = new List;

    temp->number = key;
    temp->next = NULL;
    
    List * cur = list, * prev = NULL;
    while (cur)
    {
        prev = cur;
        cur = cur->next;
    }
    
    temp->prev = prev;
    
    if (prev == NULL)
    {
        // лист был пуст
        list = temp;
    }
    else 
    {
        prev->next = temp;
    }
}

double average(List * prev, List * now, List * next)
{
    // функция нахождения среднего арифметического среди трех элементов
    double ans = now->number;
    if (prev)   //если текущий элемент первый, то прев по определению отсутствует. тогда он считается равным 0 и не учитывается
        ans += prev->number;
    if (next)   //если текущий элемент последний, то некст по определению отсутствует. тогда он считается равным 0 и не учитывается
        ans += next->number;
    
    return ans/3;
}

void changer(List * list)
{
    List * newList = init();
    List * cur = list;
    
    while (cur)
    {
        pushList(newList, average(cur->prev, cur, cur->next));
        cur = cur->next;
    }
    while (newList)
    {
        cout << newList->number << " ";
        newList = newList->next;
    }
}

int main()
{
    srand(time(0));
    int size = rand()%150 + 50;
    cout << "Размер массива: " << size << endl;
    
    List * list = init();
    
    cout << "Исходный массив: ";
    for (int i = 0; i < size; i++)
    {
        int num = rand()%201 - 100;
        cout << num << "  ";
        pushList(list, num);
    }
    cout << endl;
    
    cout << "Полученный массив: ";
    changer(list);
}