#include <iostream>
#include <string>

using namespace std;

void sortowanie (int tab[], int cnt)
{
    bool is_sorted = false;
    while (!is_sorted)
    {
        is_sorted = true;
        for (int i = 1; i < cnt; i++)
        {
            if (tab[i] < tab[i-1])
            {
                is_sorted = false;
                int tmp = tab[i];
                tab[i] = tab[i-1];
                tab[i-1] = tmp;
            }
        }
    }
    for (int i = 0; i < cnt; i++)
    {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

void binarySearch(int tab[], int cnt, int liczba)
{
    int middle = tab[cnt/2];
    int index = cnt/2;
    int start = 0;
    int stop = 0;
    string site = " na srodku";

    if (liczba < middle)
    {
        site = " po lewej";
        stop = cnt/2;
    }
    else
    {
        site = " po prawej";
        start = cnt/2;
        stop = cnt;
    }
    for (int i = start; i < stop; i++)
    {
        if (tab[i] == liczba)
        {
            index = i;
            break;
        }
    }
    std::cout << "liczba " << liczba << " znaleziona na pozycji " << index
              << site << endl;
}

int main()
{
    int tab[] = {0,2,6,8,9,10,13};

    binarySearch(tab,7,10);
    return 0;
}