/*
Создать файл целых чисел. Заполнить квадратную матрицу заданного размера 
числами из этого файла. Проверить, есть ли в сформированной матрице столбцы 
с одинаковой суммой элементов
*/
#include <iostream>
#include <fstream>

using namespace std;

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
    int * massive = new int[n];  //тут хранятся все суммы столбцов
    
    for (int i = 0; i < n; i++)
    {
        massive[i] = summator(array, n, i);
    }
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (massive[i] == massive[j])
                return true;
        }
    }
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