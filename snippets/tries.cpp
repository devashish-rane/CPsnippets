#include <bits/stdc++.h>
using namespace std;
struct node
{
    int count;
    struct node *index[26];
    int end;
};
struct node *create()
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    for(int i=0;i<26;i++)
    {
        temp->index[i]=NULL;
    }
    temp->count=0;
    temp->end=0;
    return temp;
}
void insert(struct node *root, string s)
{
    struct node *temp=root;
    for(int i=0;i<s.length();i++)
    {
        if(temp->index[s[i]-'a']==NULL)
            temp->index[s[i]-'a']=create();
        
        temp=temp->index[s[i]-'a'];
        (temp->count)+=1;
    }
    temp->end=1;
}
int countIt(struct node *root,string s)
{
    int i=0;
    struct node *temp=root;
    while(i<s.length())
    {
        if(temp->index[s[i]-'a']==NULL)
            return 0;
        temp=temp->index[s[i]-'a'];
        i++;
    }
    return(temp->count);
}
int main()
{
    struct node *root=create();
    int i,n;
    cin>>n;
    string op,str;
    while(n--)
    {
        cin>>op>>str;
        if(op=="add")
        {
            insert(root,str);
        }
        else
        {
            cout<<(countIt(root,str))<<endl;
        }
    }
    
    return 0;
}