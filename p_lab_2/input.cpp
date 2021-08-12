#include <iostream>
using namespace std;
int eff_len(char s[])
{
    int i=0;
    while(1)
    {
        if(s[i] >= '0' && s[i] <= '9' && !(s[i+1] >= '0' && s[i+1] <= '9')
         && !(s[i+2] >= '0' && s[i+2] <= '9') && !(s[i+3] >= '0' && s[i+3] <= '9') )
         {
             //cout<<s[i] << s[i+1] << s[i+2] << s[i+3] << endl;
             i++;
             break;
         }
         else
         {
             i++;
         }
    }
    return i;
}
int main()
{
    int t;
    cout<<"Enter t:";
    cin>>t;
    while(t--)
    {
        char s[100] = {};
        cout<<"Enter string:";
        scanf("%[^\n]%*c", s);
        int l=0;
        l = eff_len(s);
        int i=1;
        cout << s << " Len:" << l<< endl;
        while(i < l)
            {
                int num=0,del_flag=0;
                if(s[i] == ' ')
                    i++;
                if(s[i] =='-')
                {
                    i++;del_flag = 1;
                }
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                if(del_flag)
                {
                    // delete num
                    cout<<"Delete Number:"<<num<<" i:"<< i << endl;
                }
                else
                {
                    //insert num
                    cout<<"Insert Number:"<<num<<" i:"<< i << endl;
                }
                num = 0,del_flag=0;
                i=i+1;
            }
    }
    cout << endl;
    return 0;
}