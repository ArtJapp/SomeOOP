#include <iostream>
#include <fstream>

using namespace std;

struct List
{
    int key;
    int count;
    List * next;
};

List * init()
{
    return NULL;
}

void pushList(List *& list, int key)
{
    List * cur = list, * prev = NULL;
    while (cur != NULL)
    {
        if (cur->key == key)
        {
            cur->count++;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    // не найден элемент с данным ключом, нужно создать новый 
        List * temp = new List;
        temp->key = key;
        temp->count = 1;
        temp->next = NULL;
        if (prev)
        {
            //добавляется в непустой список
            prev->next = temp;
        }
        else 
        {
            //добавляется в пустой список
            list = temp;
        }
}

int summator(int ** array, int n, int index)
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += array[i][index];
    }
    return ans;
}

bool checker(int ** array, int n)
{
    List * list = init();
    for (int i = 0; i < n; i++)
    {
        pushList(list, summator(array, n, i));
    }
    List * cur = list;
    
    while (cur)
    {
        if (cur->count > 1)
        {
            delete list;
            return true;
        }
        cur = cur->next;
    }
    delete list;
    return false;
    
}

void inputer(int **& array, int & size)
{
    // здесь производится ввод размерности квадратной матрицы и сами ее элементы
    ifstream fin("file.txt");
    fin >> size;
    array = new int*[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = new int[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        { 
            fin >> array[i][j];  
        }
    }
}

void printer(int ** array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int ** array;
    int size;
    
    inputer(array, size);
    printer(array, size);
    
    cout << "Содержит ли матрица столбцы с одинаковыми суммами? : ";
    checker(array, size) ? cout <<"да, содержит" : cout << "нет, не содержит";
    cout << endl;
}