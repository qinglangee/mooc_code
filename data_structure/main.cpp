#include <iostream>
#include "Vector.h"

using namespace std;
int main(){
	Vector<int> v;
	long int a , b;
    char op;
    // cin>>a;
    // while(a==' '){
    //     cin>>a;
    // }
    v.disordered();
    cout<<v.size();
    return 0;
}