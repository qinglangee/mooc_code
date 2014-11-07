#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"


using namespace std;
int main(){
	int m , n;
    scanf("%d", &n);
    scanf("%d", &m);
    Vector<int> s;;
    int num;
    for(int i=0;i<n;i++){
        scanf("%d", &num);
        s.insert(num);
    }
    Vector<int> start; Vector<int> end;
    for(int i=0; i < m; i++){
        int num;
        scanf("%d", &num);
        start.insert(num);
        scanf("%d", &num);
        end.insert(num);
    }
    // for(int i = 0; i < s.size(); i++){
    //     cout<< s[i] << " ";
    // }
    // cout<<endl;
    s.sort();
    for(int i = 0; i < m; i++){
    	int count = 0;
        int a = s.insertBinSearch(start[i]);
        int b = s.insertBinSearch(end[i], a, s.size());
    	// cout<<a<<" "<<b<<endl;

        if(start[i] != s[a] || a == -1 || a == s.size()){
            count = b - a;
        }else{
            count = b - a + 1;
        }

        // cout<<a<<" "<<b<<endl;
        count = count < 0 ? 0 : count;
    	cout<<count<<endl;
    }
}