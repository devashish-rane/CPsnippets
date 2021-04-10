#include<bits/stdc++.h>
using namespace std;

int n=10000
vector<int > p(n);
vector<int > size(n);

void makeSet(int first){
    p[first]=first;
    size[first]=1;
}
int find(int v){
    if(v == p[v])
        return v;
    return p[v] =find(p[v]);    
}

int  makeUnion(int a,int b){
    int au = find(a);
    int bu = find(b);
    //bi
    if(au!=bu){
        if(size[au] < size[bu])   //bigger gets the append
           swap(au,bu);
        p[bu]=au;//parent of b is a 
        size[au]+=size[bu]; 
        return 1;   //union done
    }
    return -1;  //already in same set
    
}

int main(){
    
    return 0;
}