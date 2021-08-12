#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node* left;
    node* right;
    int height;
};
int max(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    return b;
}
int h(node* x)
{
    if(x == NULL)
        return 0;
    
    return x->height;
}
int getBalance(node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return h(root->left) - h(root->right);
}
node* rightRotate(node* y)
{
    node* x = y->left;
    node* t = x->right;

    // Rotate
    x->right = y;
    y->left = t;

    y->height = 1 + max(h(y->left), h(y->right));
    x->height = 1 + max(h(x->left), h(x->right));

    return x;
}
node* leftRotate(node* x)
{
    node* y = x->right;
    node* t = y->left;

    // Rotate
    y->left = x;
    x->right = t;

    x->height = 1 + max(h(x->left), h(x->right));
    y->height = 1 + max(h(y->left), h(y->right));

    return y;
}
int countNode(node* root)
{
    int res = 1;
    if(root == NULL)
        return 0;
    else 
    {
        res = res + countNode(root->left);
        res = res + countNode(root->right);
        return res;
    }
}
int countLeaves(node* root)
{
    if(root == NULL)
        return 0;
    
    else if (root->height == 1)
    {
        return 1;
    }
    else
    {
        return countLeaves(root->left) + countLeaves(root->right);
    }
}
node* find(node* root,int key,int reach_flag,int print_flag)
{
    if(root == NULL)
    {
        cout<<"Not found: "<< key<< endl;
        return root;
    }
    if(root->data == key)
    {
        if(reach_flag)
            cout<<" Reached "<<root->data<<endl;
        else if(print_flag)
            cout<<"Found "<<key << endl;
        
        return root;
    }
    else if (root->data < key) 
    {
        if(reach_flag)
            cout<< root->data << " Right " << root->right->data;
        
        return find(root->right,key,reach_flag,print_flag);
    }
    else if (root->data > key)
    {
        if(reach_flag)
            cout<<root->data <<" Left " << root->left->data;
        
        return find(root->left,key,reach_flag,print_flag);
    }
}
node* insert(node* root, int key,int avl_flag)
{
    node* new_node = new node;
    new_node->data = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    if(root == NULL)
    {
        root = new_node;
        return root;
    }

    if(key > root->data ) // right subtree
    {
        root->right = insert(root->right,key,avl_flag);
    }
    else if (key < root->data )
    {
        root->left = insert(root->left,key,avl_flag); 
    }
    root->height = 1 + max(h(root->left), h(root->right));

    int balance = getBalance(root);

    if(avl_flag) // Do balacing
    {
            if(root->left != NULL)
        {
            // Left Left
            if(balance > 1 && key < root->left->data)
            {
                //cout<< "Going in LL" << endl;
                return rightRotate(root);
            }
            // Left Right 
            if(balance > 1 & key > root->left->data)
            {
                //cout<< "Going in LR" << endl;
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }   
        }
        if(root->right != NULL)
        {
            //Right Right
            if(balance < -1 &&  key > root->right->data)
            {
                //cout<< "Going in RR" << endl;
                return leftRotate(root);
            }
            // Right Left
            if(balance < -1 && key < root->right->data)
            {
                //cout<< "Going in RL" << endl;
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
    }
    
    return root;
}
node* minValue(node* n)
{
    node *curr = n;
    while (curr->left != NULL && curr)
    {
        curr = curr->left;
    }
    return curr;
}
node* deleteNode(node* root, int key, int avl_flag)
{
    if(root == NULL)
    {
        cout << key << " does not exist in tree."<<endl;
        return root;
    }
    if(key < root->data)
    {
        root->left = deleteNode(root->left,key,avl_flag);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right,key,avl_flag);
    }
    else
    {
        if(root->left == NULL || root->right == NULL)
        {
            node* temp;
            if(root->right == NULL)
            {
                temp = root->left;
            }
            else
            {
                temp = root->right;
            }
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
                delete temp;
            }
        }
        else
        {
            node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right,temp->data,avl_flag);
        }
    }
    if (root == NULL)
    {
        return root;
    }

    // Balancing
    root->height = 1 + max(h(root->left), h(root->right));
    int balance = getBalance(root);
    
    if(avl_flag)
    {
        if(root->left != NULL)
        {
            // Left Left
            if(balance > 1 && getBalance(root->left) >= 0)
            {
                //cout<< "Going in LL" << endl;
                return rightRotate(root);
            }
            // Left Right 
            if(balance > 1 & getBalance(root->left) < 0)
            {
                //cout<< "Going in LR" << endl;
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }   
        }
        if(root->right != NULL)
        {
            //Right Right
            if(balance < -1 &&  getBalance(root->right) <= 0)
            {
                //cout<< "Going in RR" << endl;
                return leftRotate(root);
            }
            // Right Left
            if(balance < -1 && getBalance(root->right) > 0)
            {
                //cout<< "Going in RL" << endl;
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
    }
    
    return root;    
}
void common_anc(int a,int b, node* root)
{
    if(root == NULL)
    {
        return;
    }
    if( (find(root,a,0,0) == NULL) || (find(root,b,0,0) == NULL)  )
    {
        cout<<"-1"<<endl;
        return;
    }
    if (root->data < a && root->data < b)
    {
        common_anc(a,b,root->right);
    }
    else if (root->data > a && root->data > b)
    {
        common_anc(a,b,root->left);
    }
    else 
    {
        cout<<root->data<<endl;
    }
}
void insert_LL(node** head_ref,int key)
{
    // right == next
    node* p = *head_ref;
    node* new_node = new node;
    new_node->data = key;
    new_node->right = NULL;
    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while(p->right != NULL)
    {
        p = p->right;
    }
    p->right = new_node;
    return;
}
void delete_LL(node **head_ref, int data)
{
    //printf("Deleting: %d\n",data);
    node *prev, *curr;
    prev = *head_ref;
    curr = prev->right;
    // deleting head
    if(prev->data == data)
    {
        *head_ref = curr;//update head pointer
        free(prev);
        return;
    }
    while (curr != NULL)
    {
        if(curr->data == data)// node to be deleted
        {
            prev->right = curr->right;
            free(curr);
            return;
        }
        prev = prev->right;
        curr = curr-> right;
    }
    printf("Wrong element\n");
    return;
}
int top_LL(node* head)
{
    node* p = head;
    while(p->right != NULL)
    {
        p = p->right;
    }
    return p->data;
}
void printLL(node* head)
{
    node* p = head;
    cout<<"Stack:";
    while (p!= NULL)
    {
        cout<< p->data<<" ";
        p = p->right;
    }
    cout<<endl;
}
void printPreorder(node* root)
{
    node* head = NULL;
    insert_LL(&head,root->data);
    while(head != NULL)
    {
        //root = s.pop()
        node* proot = find(root, top_LL(head) ,0,0);
        delete_LL(&head, proot->data);
        cout<< proot->data <<" ";
        if(proot->right != NULL)
        {
            //push root->right
            insert_LL(&head,proot->right->data);
        }
        if(proot->left != NULL)
        {
            // push root->left
            insert_LL(&head,proot->left->data);
        }
    }
}
void printInorder(node* root)
{
    if(root != NULL)
    {
        cout << "( ";
        printInorder(root->left);
        cout<< root->data ;
        printInorder(root->right);
        cout <<" )";
    }
}
void printPostorder(node* root)
{
    if(root != NULL)
    {
        printPostorder(root->left);
        printPostorder(root->right);
        cout << root->data <<" " ;
    }
}
void printLevelorder(node* root)
{
    node* head = NULL;
    insert_LL(&head,root->data);
    printLL(head);
    while (head != NULL)
    {
        //dequeue
        // root = head of LL
        // delete head
        node* qroot = find(root,head->data,0,0);
        
        cout<< qroot->data << " " ;
        
        delete_LL(&head,head->data);
        
        //if(root has children ) enqueue them in queue
        if(qroot->left)
        {
            //enqueue
            insert_LL(&head,qroot->left->data);
        }
        if(qroot->right)
        {
            //enqueue
            insert_LL(&head,qroot->right->data);
        }
        //printLL(head);
    }
}
int front(node* q[],int n)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        if(q[i]->data != INT16_MAX)
            return i;
    }
    return -1;
}
int rear(node* q[],int n)
{
    int x = front(q,n);
    if(x == n-1)
        return x;
    int i;
    for(i = n-1; i > x;i--)
    {
        if(q[i]->data != INT16_MAX)
            return i+1 ;
    }
    return x + 1;
}
void width(node* root)
{
    int n = countNode(root);
    node* queue[n*2];
    for (size_t i = 0; i < 2*n; i++)
    {
        queue[i] = new node;
        queue[i]->left = NULL;
        queue[i]->right = NULL;
        queue[i]->data = INT16_MAX;//means infinity
    }
    queue[0]->data = root->data;
    int result = 1;
    while (front(queue,n) != -1)
    {
        int start = front(queue,n);
        int end = rear(queue,n);
        int size = end - start  ;
        result = max(result,size);
        //cout << start << " " << end << " " << size << endl;
        if(size == 0 || end == n)
        {
            //cout<<"End == n"<<endl;
            goto a;
        }
        for(int i = 0;i < size ;i++)
        {
            int idx = front(queue,n);
            //cout << "Old front:"<< idx << "\tOld rear:" << rear(queue,n)<<endl;
            int l = 2*idx + 1; int r = 2*idx + 2;
            if(l > 2*n || r > 2*n)
            {
                //cout<< "out of bounds"<< endl;
                goto a;
            }
            node* p = find(root,queue[idx]->data,0,0);
            if(p==NULL)
                return;
            if(p->left)
            {
                queue[l]->data = p->left->data;
                //cout<<"Pushed:" << queue[l]->data << endl;
            }
            if(p->right)
            {
                queue[r]->data = p->right->data;
                //cout<<"Pushed:" << queue[r]->data << endl;
            }
            // Pop
            //cout<<"Popped:" << queue[idx]->data << endl;
            queue[idx]->data = INT16_MAX;
            if(front(queue,n) == -1)
            {
                goto a;
            }
            //cout << "New front:" << front(queue,n) << "\tNew rear:" << rear(queue,n) << endl;
        }
    }
    a:
    cout<<result << endl;
}
int diameter(node* root)
{
    if(root == NULL)
        return 0;
    
    int lh = h(root->left);
    int rh = h(root->right);

    int ldia = diameter(root->left);
    int rdia = diameter(root->right);

    return  max( lh + rh + 1, max(ldia, rdia) );

}
void printLeaves(node* root)
{
    if(root != NULL)
    {
        printLeaves(root->left);
        if(root->height == 1)
            cout << root->data << " ";
        printLeaves(root->right);
    }
}
void perimeter(node* root)
{
    if(root== NULL)
        return ;
    
    // Left side
    node* curr = root->left;
    cout << root->data << " ";
    while (curr!= NULL)
    {
        if(curr->left != NULL)
        {
            cout << curr->data << " ";
            curr = curr->left;
        }
        else if (curr->right != NULL)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else // means we are at leaf node
        {
            break;
        }
    }
    // Right side
    curr = root->right;
    while (curr!= NULL)
    {
        if(curr->right != NULL)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else if (curr->left != NULL)
        {
            cout << curr->data << " ";
            curr = curr->left;
        }
        else // means we are at leaf node
        {
            break;
        }
    }
    // Leaves
    printLeaves(root);
    
}
int eff_len(char s[])
{
    int i=0;
    while(1)
    {
        if(s[i] >= '0' && s[i] <= '9' && !(s[i+1] >= '0' && s[i+1] <= '9')
         && !(s[i+2] >= '0' && s[i+2] <= '9') && !(s[i+3] >= '0' && s[i+3] <= '9') )
         {
             //cout<< "Break:"<<s[i] << s[i+1] << s[i+2] << s[i+3] << endl;
             i++;break;
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
    cin >> t;
    node* root = NULL;
    while(t>0)
    {
        char s[100] = {};
        int i=0;
        int avl_flag = 0;
        int reach_flag=0;
        cout<<"\nEnter string:";
        scanf("%[^\n]%*c", s);
        int l = eff_len(s);
        cout << s << "  Len:" << l << endl;
        if(s[0] == 'T')
        {
            //BST
            if(root != NULL)
                root = NULL;
            i++;avl_flag = 0;
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
                    root = deleteNode(root,num,avl_flag);
                }
                else
                {
                    //insert num
                    cout<<"Insert Number:"<<num<<" i:"<< i << endl;
                    root = insert(root,num,avl_flag);
                }
                num = 0,del_flag=0;
                i=i+1;
            }
        }
        else if (s[0] =='H')
        {
            //AVL
            if(root != NULL)
                root = NULL;
            i++; avl_flag  = 1;
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
                    root = deleteNode(root,num,avl_flag);
                }
                else
                {
                    //insert num
                    cout<<"Insert Number:"<<num<<" i:"<< i << endl;
                    root = insert(root,num,avl_flag);
                }
                num = 0,del_flag=0;
                i=i+1;
            }
        }
        else if (s[0] =='A')
        {
            //Add to last tree
            i++;
            while(i < l)
            {
                int num=0;
                if(s[i] == ' ')
                    i++;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                //insert num
                cout<<"Insert Number:"<<num<<" i:"<< i << endl;
                root = insert(root,num,avl_flag);
                num = 0;
                i=i+1;
            }
        }
        else if (s[0] =='U')
        {
            //Uproot last tree
            i++;
            while(i < l)
            {
                int num=0;
                if(s[i] == ' ')
                    i++;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                //insert num
                cout<<"Delete Number:"<<num<<" i:"<< i << endl;
                root = deleteNode(root,num,avl_flag);
                num = 0;
                i=i+1;
            }
        }
        else if (s[0] =='F')
        {
            //Find
            i++;reach_flag=0;
            while(i < l)
            {
                int num=0;
                if(s[i] == ' ')
                    i++;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                //insert num
                //cout<<"Insert Number:"<<num<<" i:"<< i << endl;
                node* n = find(root,num,reach_flag,1);
                num = 0;
                i=i+1;
            }
        }
        else if (s[0] =='Q')
        {
            //ouput no. of leaves
            cout << "Leaves#:"<< countLeaves(root) << endl;
        }
        else if (s[0] =='N')
        {
            //ouput no. of nodes
            cout << "Nodes#:"<< countNode(root) << endl;
        }
        else if (s[0] =='P')
        {
            //print preorder traversal non recursive
            printPreorder(root);
            cout<<endl;
        }
        else if (s[0] =='I')
        {
            //Print Inorder traversal
            printInorder(root);
            cout<<endl;
        }
        else if (s[0] =='S')
        {
            //Postorder traversal
            printPostorder(root);
            cout<<endl;
        }
        else if (s[0] =='L')
        {
            //print tree level order traversal
            printLevelorder(root);
            cout << endl;
        }
        else if (s[0] =='D')
        {
            //depth/height of tree
            cout << root->height << endl;
        }
        else if (s[0] =='W')
        {
            //width of tree
            width(root);
            cout<<endl;
        }
        else if (s[0] =='C')
        {
            //lowest common ancestor
            i++; int a[2],j=0;
            while(i < l)
            {
                int num=0;
                if(s[i] == ' ')
                    i++;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                //insert num
                a[j] = num;
                //cout<<"Insert Number:"<<a[j]<<" and j:" << j << endl;
                num = 0;j++;
                i=i+1;
            }
            common_anc(a[0],a[1],root);
        }
        else if (s[0] =='R')
        {
            //route/path of 2 nodes
            i++; int a[2],j=0;
            while(i < l)
            {
                int num=0;
                if(s[i] == ' ')
                    i++;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    num = num*10 + s[i] - '0';i++;
                }
                //insert num
                a[j] = num;
                cout<<"Insert Number:"<<a[j]<<" and j:" << j << endl;
                num = 0;j++;
                i=i+1;
            }
            node* start = find(root,a[0],reach_flag,0);
            reach_flag = 1;
            if(a[0] < a[1])
            {
                cout<<"Unreachable" <<endl;
            }
            else
                node* p = find(start,a[1],reach_flag,0);
        }
        else if (s[0] =='X')
        {
            //length of diameter of tree
            cout<< diameter(root) << endl;
        }
        else if (s[0] =='Y')
        {
            //print perimeter of tree
            perimeter(root);
            cout << endl;
        }

        printInorder(root);
        t=t-1;
    }
    cout <<endl;
    return 0;
}