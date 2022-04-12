// Work on bugs RK1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

struct Node
{
    Node* prev;
    Node* next;
    int element;
    int size;
};
class LinkedList
{
private:
    Node* Head;
    Node* Tail;
    unsigned int length = 0;
public:
    LinkedList();
    ~LinkedList();
    void AddFirst(int number);
    void Show();
    void WriteToFile(const char* fileName);
    void Insert(int index, int number);
};

LinkedList::LinkedList()
{
    Head = Tail = NULL;
}
LinkedList::~LinkedList()
{
    while (Head)
    {
        Tail = Head->next;
        delete Head;
        Head = Tail;
    }
}

void LinkedList::AddFirst(int number)
{
    Node* temp = new Node;
    temp->element = number;
    if (Head == NULL)
    {
        temp->next = Tail;
        Tail = temp;
    }
    else
    {
        temp->next = Head;
        Head->prev = temp;
    }
    Head = temp;
    Head->prev = NULL;
    length++;
}
void LinkedList::Show()
{
    if (Head != NULL)
    {

        Node* temp = Head;
        while (temp != NULL)
        {
            cout << temp->element << endl;
            temp = temp->next;
        }


    }
    else
    {
        cout << "Empty" << endl;
    }
    cout << endl;
}
void LinkedList::Insert(int index, int number)
{
    if (index > length)
    {
        return;
    }
    if (index == 0)
    {
        AddFirst(number);
        return;
    }
    Node* temp = new Node;
    temp->element = number;
    Node* it = Head;
    for (int i = 0; i <= index; i++)
    {
        if (i == index)
        {
            temp->next = it;
            if (it != NULL)
            {
                temp->prev = it->prev;
                it->prev->next = temp;
                it->prev = temp;
            }
            else
            {
                Tail->next = temp;
                temp->prev = Tail;
                Tail = temp;
            }
            length++;
        }
        else
        {
            it = it->next;
        }
    }
}
void LinkedList::WriteToFile(const char* fileName)
{
    FILE* f1;
    f1 = fopen(fileName, "w");
    Node* tempHead = Head;
    Node* tempTail = Tail;
    while (tempHead != NULL)
    {
        fprintf(f1, "%d ", tempHead->element);
        tempHead = tempHead->next;
    }
    fprintf(f1, "\n");
    while (tempTail != NULL)
    {
        fprintf(f1, "%d ", tempTail->element);
        tempTail = tempTail->prev;
    }
    fclose(f1);
}

void task1() 
{
    ifstream f;
    f.open("inputfile.txt", ios_base::in); 
    f.seekg(0, ios::end);
    int fileSize = f.tellg();
    vector<char> fileData;
    fileData.resize(fileSize);
    f.seekg(0, ios::beg);
    f.read(&fileData[0], fileSize);
    int ar[256];
    memset(&ar[0], 0x00, sizeof(int) * 256);

    for (int i = 0; i < fileData.size(); i++) {
        ar[fileData[i]]++;
    }
    f.close();
    ofstream f2("inputfile.txt", ios_base::out);
    for (int i = 0; i < 256; i++) {
        if (ar[i] != 0)
            f2 << char(i) << " - " << ar[i] << "\n";
    }
    f2.close();
    return;
}

void task2(int num) {
    char binNumb[32];
    bool isLeadZero = 1;
    int firstNonZero = 0;
    cout << "binary: ";
    for (int i = 31; i >= 0; i--)
    {
        binNumb[i] = ((num & (1 << i)) >> i) + 0x30;
        if (isLeadZero && (binNumb[i] == 0x31))
        {
            isLeadZero = 0;
            firstNonZero = i;
        }
        if (!isLeadZero)
        {
            cout << binNumb[i];
        }
    }
    cout << endl;
}

void task3(const string bin, int length)
{
    int num = 0;
    for (int i = 0; i < length; i++)
    {

        if (bin[i] == 0x31)
        {
            num++;
        }
        if (i != length - 1)
        {
            num = num << 1;
        }
        cout << num;
    }
}

void task5(int** ar, const int n, const int m)
{
    float midstr = 0;
    float* res = new float[n];
    for (int i = 0; i < n; i++)
    {
        float summ = 0;
        for (int j = 0; j < m; j++)
        {
            summ += ar[i][j];
        }
        summ /= m;
        res[i] = summ;
    }
    cout << "Mean: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " string: " << res[i] << endl;
    }
}

void task6()
{
    LinkedList lst;
    bool b = 1;
    cout << "1 - Add element to the beginning." << endl;
    cout << "2 - Insert an element to the specified location." << endl;
    cout << "3 - Display the list." << endl;
    cout << "4 - Write list to file." << endl;
    cout << "5 - Exit" << endl;
    while (b)
    {
        int op;
        cout << "Select an operation: ";
        cin >> op;
        switch (op)
        {
        case 1:
            int number;
            cout << "Enter number: ";
            cin >> number;
            lst.AddFirst(number);
            break;
        case 2:
            int num;
            int index;
            cout << "Enter number: ";
            cin >> num;
            cout << "Enter sequence number: ";
            cin >> index;
            lst.Insert(index - 1, num);
            break;
        case 3:
            lst.Show();
            break;
        case 4:
            lst.WriteToFile("outputfile.txt");
            break;
        case 5:
            b = 0;
            break;
        }
    }
}
    int main()
    {
        string bin = "";
        int count = 0;
        int c = 0;
        do
        {
            cout << endl;
            cout << "Task number (2, 5, 6): ";
            cin >> c;
            cout << endl;

            switch (c)
            {
            case 1:
                task1();
                c = 0;
                break;

            case 2:
                int dec;
                cout << "decimal: ";
                cin >> dec;
                cout << endl;
                task2(dec);
                c = 0;
                break;

            case 3:
                cin >> bin;
                task3(bin, bin.size());
                c = 0;
                break;

            case 4:
                //   Task4();
                c = 0;
                break;

            case 6:
                task6();
                cout << endl;
                c = 0;
                break;
            case 7:
                //  task7();
                c = 0;
                break;
            case 8:
                //task8();
                c = 0;
                break;

            case 5:
                int n, m;
                cout << "String count: ";
                cin >> n;
                cout << "Column count: ";
                cin >> m;
                cout << "Matrix: " << endl;
                int** ar = new int* [n];
                for (int i = 0; i < n; i++)
                {
                    ar[i] = new int[m];
                }
                srand(time(nullptr));

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        ar[i][j] = rand();
                    }
                }
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        cout << ar[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
                task5(ar, n, m);
                cout << endl;
                c = 0;
                break;
            }
        } while (c < 1 || c > 8);
    }

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
