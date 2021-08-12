#include<iostream>
using namespace std;
/*
Take an infix expression and evaluate it using stacks.
*/
class op
{
public:
    char s[5];
};
int power(int base, int exp)
{
    int res = 1;
    for(int i =0;i< exp;i++)
    {
        res = res * base;
    }
    return res;
}
int precedence(char a)
{
    if (a == '*' || a == '/' || a == '%')
    {
        return 8;
    }
    else if (a == '+'|| a == '-')
    {
        return 7;
    }/*
    else if (a == '<<'|| a == '>>')
    {
        return 6;
    }*/
    else if (a == '<'|| a == '>' /* s[i] == '<<' || s[i] == '>> */)
    {
        return 5;
    }/*
    else if (a == '=='|| a == '!=')
    {
        return 4;
    }*/
    else if (a == '&')
    {
        return 3;
    }
    else if (a == '^')
    {
        return 2;
    }
    else if (a == '|')
    {
        return 1;
    }
    else
        return 0;
}
int str_cmp(char s[], char t[])
{
    int i=0,flag=1;
    while(s[i] != '\0')
    {
        if(s[i] == t[i])
        {
            flag = 1;i++;
        }
        else
        {
            flag = 0;
            return flag;
        }
    }
    return flag;
}
int doube_operation(int x, int y, char op[])
{
    if (str_cmp("<<",op ))
    {
        return x<<y;
    }
    else if (str_cmp(">>",op))
    {
        return x>>y;
    }
    else if (str_cmp( "<=" ,op))
    {
        return x<=y;
    }
    else if (str_cmp(">=",op))
    {
        return x>=y;
    }
    else if (str_cmp("==",op))
    {
        return x==y;
    }
    else if (str_cmp("!=",op))
    {
        return x!=y;
    }
}
int operation(int x, int y, char op)
{
    if(op == '+')
        return x+y;
    else if (op == '-')
    {
        return x-y;
    }
    else if (op == '*')
    {
        return x*y;
    }
    else if (op == '/')
    {
        return x/y;
    }
    else if (op == '%')
    {
        return x%y;
    }
    else if (op == '>')
    {
        return x>y;
    }
    else if (op == '<')
    {
        return x<y;
    }
    else if (op == '&')
    {
        return x&y;
    }
    else if (op == '^')
    {
        return x^y;
    }
    else if (op == '|')
    {
        return x|y;
    }
}
void infix_eval(char *s)
{
    int st_operands[10];
    char st_operators[10];
    int top1,top2;
    top1 = top2 = -1;
    int i=0;
    while (s[i] != '\0')
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            int num = 0;int j=i;
            while (s[j] >= '0' && s[j] <= '9')
            {
                num = num * 10 + s[j] - '0';
                j++;
            }
            i=j;
            // push it on stack
            top1++;
            st_operands[top1] = num;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' 
        || s[i] == '<' || s[i] == '>' || s[i] == '&' || s[i] == '^' || s[i] == '|' )
        {
            //cout << s[i] <<" " <<st_operators[top2] << " " << top2<< endl;
            //cout << precedence(s[i]) <<" " << precedence(st_operators[top2]) << " " << top2<< endl;
            while( ( precedence(s[i]) <= precedence(st_operators[top2]) ) && top2 != -1)
            {
                int val2 = st_operands[top1]; top1--;
                int val1 = st_operands[top1];top1--;

                char op = st_operators[top2];top2--;
                int res = operation(val1,val2,op);
                cout << "Res:" << res << endl;
                top1++;
                st_operands[top1] = res;
            }
            //cout <<"Pushed in operaors stack:" << s[i] << endl;
            top2++;
            st_operators[top2] = s[i];
            i++;
        }
    }
    while( top2 != -1)
    {
        int val2 = st_operands[top1]; top1--;
        int val1 = st_operands[top1];top1--;

        char op = st_operators[top2];top2--;
        int res = operation(val1,val2,op);
        top1++;
        st_operands[top1] = res;
    }
    cout << "Result:" << st_operands[top1];
    cout << endl;
}
int main()
{
    char *s;
    int i=0;
    char c;
    cout << "Enter expression:";
    while (1)
    {
        cin >> c;
        if(c == '#')
        {
            s[i] = '\0';
            break;
        }
        else
        {
            s[i] = c;
            i++;
        }
    }
    i=0;
    while (s[i] != '\0')
    {
        cout << s[i];
        i++;
    }
    cout <<endl;
    infix_eval(s);
    return 0;
}