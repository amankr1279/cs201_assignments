#include<iostream>
using namespace std;
/*
Take an infix expression and evaluate it using stacks.
*/
class op
{
public:
    char s[3];
};
int str_cmp(char s[], char t[])
{
    int i=0,flag=1;
    /*cout <<"S:" << s;
    cout <<"\tT:" << t << endl;*/
    while(s[i] != '\0' && t[i] != '\0')
    {
        if(s[i] == t[i])
        {
            i++;
        }
        else
        {
            flag = 0;
            return flag;
        }
    }
    return flag;
}
int precedence(char a[])
{
    if (a[0] == '*' || a[0] == '/' || a[0] == '%')
    {
        return 8;
    }
    else if (a[0] == '+'|| a[0] == '-')
    {
        return 7;
    }
    else if (str_cmp(a,"<<") || str_cmp(a,">>"))
    {
        return 6;
    }
    else if ( str_cmp(a,"<") || str_cmp(a,">") || str_cmp(a,"<=") || str_cmp(a,">="))
    {
        return 5;
    }
    else if (str_cmp(a,"==")|| str_cmp(a,"!="))
    {
        return 4;
    }
    else if (a[0] == '&')
    {
        return 3;
    }
    else if (a[0] == '^')
    {
        return 2;
    }
    else if (a[0] == '|')
    {
        return 1;
    }
    else
        return 0;
}
int double_operation(int x, int y, char opt[])
{
    if (str_cmp("<<",opt))
    {
        return x<<y;
    }
    else if (str_cmp(">>",opt))
    {
        return x>>y;
    }
    else if (str_cmp( "<=" ,opt))
    {
        return x<=y;
    }
    else if (str_cmp(">=",opt))
    {
        return x>=y;
    }
    else if (str_cmp("==", opt))
    {
        return x==y;
    }
    else if (str_cmp("!=", opt))
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
    op st_op[10];/*
    st_op[0].s[0] = '<';
    st_op[0].s[1] = '<';
    cout << "Checking:"<<st_op[0].s<<endl;*/
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
        || s[i] == '<' || s[i] == '>' || s[i] == '&' || s[i] == '^' || s[i] == '|' || s[i] =='=' || 
        s[i] =='!')
        {
            char op[2];
            int inc = 1;
            // Single Operators
            op[0] = s[i];
            op[1] = '\0';
            // Double operators
            if(s[i] == '<' && s[i+1] == '<') // << operator
            {
                op[1] = '<'; inc = 2;
            }
            else if (s[i] == '<' && s[i+1] == '=') // <= operator
            {
                op[1] = '=';inc = 2;
            }
            else if (s[i] == '>' && s[i+1] == '=') // >= operator
            {
                op[1] = '=';inc = 2;
            }
            else if (s[i] == '>' && s[i+1] == '>') // >> operator
            {
                op[1] = '>';inc = 2;
            }
            else if (s[i] == '=' && s[i+1] == '=') // == operator
            {
                op[1] = '=';inc = 2;
            }
            else if (s[i] == '!' && s[i+1] == '=') // != operator
            {
                op[1] = '=';inc = 2;
            }
            //cout << s[i] <<" " <<st_operators[top2] << " " << top2<< endl;
            //cout << precedence(s[i]) <<" " << precedence(st_operators[top2]) << " " << top2<< endl;
            while( ( precedence(op) <= precedence(st_op[top2].s) ) && top2 != -1)
            {
                int val2 = st_operands[top1]; top1--;
                int val1 = st_operands[top1];top1--;

                // Single operator
                if(st_op[top2].s[1] == '\0')
                {
                    char opt = st_op[top2].s[0];top2--;
                    int res = operation(val1,val2,opt);
                    //cout << "Res_single:" << res << endl;
                    top1++;
                    st_operands[top1] = res;
                }
                else // Double Operator
                {
                    char opt[2]; 
                    opt[0]= st_op[top2].s[0];
                    opt[1]= st_op[top2].s[1];top2--;
                    int res = double_operation(val1,val2,opt);
                    //cout << "Res_double:" << res << endl;
                    top1++;
                    st_operands[top1] = res;
                }
            }
            top2++;
            st_op[top2].s[0] = op[0];
            st_op[top2].s[1] = op[1];
            //cout <<"Pushed in operaors stack:" << st_op[top2].s[0] <<"" <<st_op[top2].s[1] << endl;
            //cout <<"Precedence check:"<<precedence(st_op[top2].s) <<endl;
            i = i + inc;
        }
    }
    while( top2 != -1)
    {
        int val2 = st_operands[top1]; top1--;
        int val1 = st_operands[top1];top1--;

        // Single operator
        if(st_op[top2].s[1] == '\0')
        {
            char opt = st_op[top2].s[0];top2--;
            int res = operation(val1,val2,opt);
            //cout << "Res_single:" << res << endl;
            top1++;
            st_operands[top1] = res;
        }
        else // Double Operator
        {
            char opt[2]; 
            opt[0]= st_op[top2].s[0];
            opt[1]= st_op[top2].s[1];top2--;
            int res = double_operation(val1,val2,opt);
            //cout << "Res_double:" << res << endl;
            top1++;
            st_operands[top1] = res;
        }
    }
    if(top1 != 0)
    {
        cout<<"Error"<<endl;
        return;
    }
    cout << "Result:" << st_operands[top1] << "Top:" <<top1;
    cout << endl;
}
int main()
{
    int t;
    cin >> t;
    while(t--)
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
    }
    return 0;
}