#include <iostream>
#include "ABS.h"

using namespace std;

int main()
{
    // int *test = new int[3];
    // test[1] = 20;
    // int test2 = test[1];

    // cout << test << endl;
    // cout << test2 << endl;

    ABS<int> abs(500);
    abs.push(20);
    abs.push(20);
    abs.push(20);
    abs.push(20);
    abs.pop();
    for (int i = 0; i < 4000; i++)
        abs.push(i);


    return 0;
}