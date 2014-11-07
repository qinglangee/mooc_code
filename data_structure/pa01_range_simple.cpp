
#include <iostream>
#include "Vector.h"


using namespace std;
int main(){
	int m , n;
    cin>>n;
    cin>>m;
    Vector<int> s;;
    int num;
    for(int i=0;i<n;i++){
        cin>>num;
        s.insert(num);
    }
    Vector<int> start; Vector<int> end;
    for(int i=0; i < m; i++){
        int num;
    	cin>>num;
        start.insert(num);
    	cin>>num;
        end.insert(num);
    }
    // for(int i = 0; i < s.size(); i++){
    //     cout<< s[i] << " ";
    // }
    // cout<<endl;
    for(int i = 0; i < m; i++){
    	int count = 0;
        int head = start[i];
        int tail = end[i];
        for(int j = 0; j < s.size(); j++){
            if(s[j] >= head && s[j]<= tail){
                count++;
            }
        }
    	cout<<count<<endl;
    }
}