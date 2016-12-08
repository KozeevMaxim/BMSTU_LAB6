#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;

struct Computer
{
    char company[64];
    float price;
    char country[64];
};

struct List
{
    Computer comp;
    List *pNext;
};

void addFirst(List *& pF, List* p)
{
    p->pNext = pF;
    pF = p;
}

List * delFirst(List *&pF)
{
    if (pF == 0) return 0;
    List *p = pF;
    pF = pF->pNext;
    return p;
}

bool add(List *&pF, List * pZad, List *p)
{
    if (pZad == pF)
    {
        p->pNext = pF;
        pF = p;
        return true;
    }

    List *pPred = pF;
    while (pPred->pNext != pZad && pPred->pNext)
        pPred = pPred->pNext;
    if (pPred->pNext == 0) return false;
    p->pNext = pZad;
    pPred->pNext = p;
    return true;
}

List * del(List*& pF, List *p)
{
    if (pF == 0) return 0;
    if (pF == p)
    {
        pF = pF->pNext;
        return p;
    }
    else
    {
        List *pPred = pF;
        while (pPred->pNext != p && pPred->pNext)
            pPred = pPred->pNext;
        if (pPred->pNext == 0) return 0;
        pPred->pNext = p->pNext;
        return p;
    }
    while(delFirst(pF));
}
int main(int argc, char* argv[])
{
    List *pF = 0;
    List *p;

    char Ex;
    do
    {
        p = (List *)malloc(sizeof(List));
        cout << "Company: ";
        cin.get();
        fflush(stdin);
        gets_s(p->comp.company, 63);

        cout << "Country: ";
        fflush(stdin);
        gets_s(p->comp.country, 63);

        cout << "Price: ";
        fflush(stdin);
        cin >> p->comp.price;

        addFirst(pF, p);
        printf("For continue press Y or y else any key! ");
        Ex = _getche();
        cin.clear();
        cout << endl;

    } while (Ex == 'Y' || Ex == 'y');
    cout << endl;

    for (List *pi = pF; pi; pi = pi->pNext)
        cout << pi->comp.company << " " << pi->comp.country << " " << pi->comp.price << endl;

    for (List *pi = pF; pi->pNext;)
    {

        double min = pi->comp.price;
        List *pmin = pi;
        for (List *pj = pi->pNext; pj; pj = pj->pNext)
            if (pj->comp.price<min)
            {
                min = pj->comp.price;
                pmin = pj;
            }
        if (pi != pmin)
        {
            del(pF, pmin);
            add(pF, pi, pmin);
        }
        else pi = pi->pNext;
    }

    cout << endl;
    cout << "Sorted: " << endl;
    for (List *pi = pF; pi; pi = pi->pNext)
        cout << pi->comp.company << " " << pi->comp.country << " " << pi->comp.price << endl;
    system("pause");
    return 0;
}