#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

using namespace std;

int main(){
    char a;
    fread(&a, 1, 1, stdin);
    int b = atoi(&a);
    cout<<b<<endl;
} 
