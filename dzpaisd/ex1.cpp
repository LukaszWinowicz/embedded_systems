/* Zadanie 1 - sortowanie bąbelkowe jest jednym z najprostszych w implementacji algorytmów porządkujących dane. 
Złożoność tego sposobu sortowania jest rzędu O(n^2).


*/
#include <iostream>
using namespace std;

void bubble_sort(int tab[], int n){
    bool isSorted = false;
    while(!isSorted)
    {
        isSorted = true;
        for (int j= 0; j < n -1; j++)
        {
            if (tab[j] > tab[j+1])
            {
                int tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
                isSorted = false;
            }
        }
    }

    for (int i= 0; i < n; i++)
    {
        cout << tab[i] << " ";
    }
    cout << endl;
}

int main()
{
    int tab[] = {1,7,3,0,2};
    bubble_sort(tab, 5);
}