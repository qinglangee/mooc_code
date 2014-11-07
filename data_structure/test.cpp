#include <iostream>
#include <stdlib.h>
#include "Vector.h"

using namespace std;

int main() {
    Vector<int> v;
    v.insert(1);
    v.insert(3);
    v.insert(7);
    v.insert(9);
    v.insert(11);
    int i4 = v.insertBinSearch(4);
    cout<<i4<<endl;
    return 0;
}
