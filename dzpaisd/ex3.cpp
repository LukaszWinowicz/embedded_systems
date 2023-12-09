#include <iostream>
#include <string>

using namespace std;

//zwieksz rozmiar tablicy do newSize
int* _realoc(int *tab, int cnt, int newSize)
{
    int *tmpTab = new int[newSize];
    for (int i = 0; i < cnt; i++)
    {
        tmpTab[i] = tab[i];
    }
    delete tab;
    return tmpTab;
}
int main()
{
    int *tab = new int[10];

    for (int i =0; i < 10; i++)
    {
        tab[i] = i;
    }

    tab = _realoc(tab,10, 20);

    for (int i =0; i < 10; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;
    delete[] tab;
}
