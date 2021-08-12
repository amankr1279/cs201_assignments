#include <iostream>
using namespace std;
/*
n# = (1^1) * (2^2) * (3^3) * … (n^n). Create a linked list to store it.
*/

/*void n_hash(int n)
{
    int i,prod =1;
    for(i=0;i<n;i++)
    {
        prod = prod * pow(i,i);
    }
    cout << "n# = " << prod << endl;
}*/
class node
{
public:
    int data;
    node* next;
    node* prev;
};
void insert( node **head_ref, int key)// inserts at the end
{
    node *new_node;
    new_node = new node;
    new_node->data = key;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        new_node->prev = NULL;
        return;
    }
    else
    {
        node *p = *head_ref;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_node;
        new_node->prev = p;
        return;
    }
}
void printList(node* head)
{
    node* p = head;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
void new_factorial(int n, node *head)
{
    //printList(head);
    int carry =0,prod_digit, prod;
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= i; j++)
        {
            node *p = head;
            carry = 0;
            while (p != NULL)
            {
                prod = p->data * i + carry;
                carry = prod / 10;
                prod_digit = prod % 10;
                p->data = prod_digit;
                p = p->next;
            }
            if(carry != 0)
            {
                int x = carry;
                while (x > 0)
                {
                    insert(&head,x%10);
                    x = x/10;
                }
            }
        }
        //printList(head);
    }
}
void printHash(node* head)
{
    node* p = head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    while (p != NULL)
    {
        cout << p->data;
        p = p->prev;
    }
    cout <<endl;
}
int main()
{
    int n;
    cout << "Enter n:";
    cin >> n;
    /*n_hash(n);*/
    node *head = NULL;
    insert(&head,1); // Base case
    new_factorial(n,head);
    printHash(head);
    return 0;
}