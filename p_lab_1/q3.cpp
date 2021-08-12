#include <iostream>
using namespace std;
/*
Print balanced parenthesis.
*/
char bracket[100];
void func(int id,int n,int l, int r)
{
    if(r==n)
    {
        for(int i=0;i<2*n;i++)
            cout<<bracket[i];
        
        cout << endl;
        return;
    }
    else
    {
        if(l < n)
        {
            bracket[id] = '(';
            func(id+1,n,l+1,r);
        }
        if(l > r)
        {
            bracket[id] = ')';
            func(id+1,n,l,r+1);
        }
    }
}
void printBracket(int n)
{
    if(n>0)
        func(0,n,0,0);
    
    return;
}
int main()
{
    int n;
    cout<<"Enter n:";
    cin>> n;
    printBracket(n);
    return 0;
}