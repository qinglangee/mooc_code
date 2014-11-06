#include <iostream>
#include "Vector.h"


using namespace std;
int main(){
	int m , n;
    cin>>n;
    cin>>m;
    Vector<int> s;;
    for(int i=0;i<n;i++){
        cin>>s[i];
    }
    Vector<int> start; Vector<int> end;
    for(int i=0; i < m; i++){
    	cin>>start[i];
    	cin>>end[i];
    }

    s.sort();
    for(int i = 0; i < m; i++){
    	int count = 0;
    	int startIndex = s.insertBinSearch(start[i]);
    	int endIndex = s.insertBinSearch(end[i]);
    	cout<<startIndex<<" "<<endIndex<<endl;
    	count = endIndex - startIndex;
    	cout<<count<<endl;
    }
}