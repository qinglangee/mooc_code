#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ZStack.h"

using namespace std;

void pStack(ZStack<int>& s){
	cout<<"print stack: ";
	for(int i=0;i<s.size(); i++){
		cout<<s[i]<<" ";
	}
	cout<<endl;
}

int main(){

	int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    ZStack<int> sTemp(n);
    ZStack<int> sA(n);
    ZStack<int> sB(n);
    ZStack<int> action(n * 2);
    ZStack<int> sS(m);
    for(int i = 0; i < n; i++){
    	int num;
    	scanf("%d", &num);
    	sTemp.push(num);
    }
    while(!sTemp.empty()){
    	sB.push(sTemp.pop());
    }
    for(int i = n; i > 0; i--){
    	sA.push(i);
    }
    // cout<<"========================="<<endl;
    // for(int i = 0; i < n; i++){
    // 	cout<<sA[i];
    // }
    // cout<<endl;
    // for(int i = 0; i < n; i++){
    // 	cout<<sB[i];
    // }
    // cout<<endl;
    bool can = true;
    while(!sB.empty()){
    	// cout<<"sb size:" << sB.size()<<endl;
    	if(sA.empty()){
    		// pStack(sS);
    		// pStack(sB);
    		// cout<<"sS top:"<<sS.top()<<" sB top:"<<sB.top()<<endl;
    		if(sS.top() == sB.top()){
    			sS.pop();
    			sB.pop();
    			action.push(0); // pop
    			continue;
    		}else{
    			// cout<<"=====01"<<endl;
    			can = false;
    			printf("%s", "No\n");
    		}
    	}
    	if(sB.top() == sA.top() && !sA.empty()){
    		// cout<<sB.top() << sA.top()<<endl;
    		// cout<<1<<endl;
    		sA.pop();
    		sB.pop();
    		action.push(1); // 1 是 push
    		action.push(0); // 0 是 pop
    	} else if(sA.top() < sB.top()){
    		if(sS.full()){
    			can = false;
    			// cout<<"=====02"<<endl;
    			printf("%s", "No");
    			break;
    		}
    		// cout<<2<<endl;
    		sS.push(sA.pop());
    		action.push(1); // push
    	} else {
    		if(sS.top() == sB.top()){
    		// cout<<3<<endl;
    			sS.pop();
    			sB.pop();
    			action.push(0); // pop
    		}else{
    			can = false;
    			// cout<<"=====03"<<endl;
    			printf("%s", "No\n");
    			break;
    		}
    	}
    }

    if(can){
    	for(int i = 0; i < action.size(); i++){
    		if(action[i] == 1){
    			printf("%s", "push\n");
    		}else{
    			printf("%s", "pop\n");

    		}
    		
    	}
    }
}