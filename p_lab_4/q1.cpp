#include <iostream>
#include <vector>
using namespace std;
#define INF 999999
#define MAX 20

class node
{
public:
    int edge;
    int w;
};
class supernode
{
public:
    vector <int> super;
};

//Global variables
int flag = 0;
vector <supernode> sp = {};
int last_vist;
vector <node> g_stack[MAX][MAX] = {};
vector <int> v_stack= {};
vector <node> mincostArbor[MAX] = {};
bool incomingEdge[MAX] = {false};
int top = -1;

//Functions
void printVector(vector <int> v)
{
    for(auto it = v.begin();it != v.end();it++)
    {
        cout << *it <<" ";
    }
    cout << endl;
}
void addEdge(vector <node> adj[],int u, int v, int wt)
{
    node gnode;
    gnode.edge = v;
    gnode.w = wt;
    adj[u].push_back(gnode);
}
void removeEdge(vector <node> adj[], int u, int v)
{
    for(auto it = adj[u].begin(); it != adj[u].end(); it++)
    {
        if(it->edge == v)
        {
            adj[u].erase(it);
            return;
        }
    }
}
void printGraph(vector <node> adj[],int V)
{
    int i=0;
    for(i=0;i<V;i++)
    {
        cout <<"Printing for node:" << i+1 <<  endl;
        for(auto it = adj[i].begin();it !=  adj[i].end();it++)
        {
            cout << it->edge+1 <<" " << it->w << endl;
        }
    }
}
void cheap_edge(vector <node> adj[],int s,int V, int E,int v_end,vector <int> &cheap_edge_wt, vector <int> &parent)
{
    int u;
    for(u=0;u<V;u++)
    {
        for(auto it = adj[u].begin();it != adj[u].end(); it++)
        {
            if(it->edge == v_end)
            {
                if(it->w < cheap_edge_wt[v_end])
                {
                    cheap_edge_wt[v_end] = it->w;
                    parent[v_end] = u;
                }
            }
        }
    }
}
void modify_edge_wt(vector <node> adj[],int V, int E,vector <int> &cheap_edge_wt)
{
    int u;
    for(u=0;u<V;u++)
    {
        for(auto it = adj[u].begin();it != adj[u].end(); it++)
        {
            it->w = it->w - cheap_edge_wt[it->edge];
        }
    }
}
void dfs(vector <node> adj[],int u,vector <int> &parent,vector <string> &color)
{
    color[u] = "gray";
    //cout << "Searching for " << u+1 <<":";
    for(auto it = adj[u].begin(); it != adj[u].end(); it++)
    {
        if(color[it->edge] == "white" && it->w == 0)
        {
            //cout << it->edge + 1 <<" " << endl;
            color[it->edge] = "gray";
            parent[it->edge] = u;

            dfs(adj,it->edge,parent,color);
        }
        else if (color[it->edge] == "gray" && it->w == 0)//cycle
        {
            cout <<"Cycle found" << endl; flag = 1;
            last_vist = u;
            return;
        }   
    }
    color[u] = "black";
}
int inCycle(vector <int> cycle, int key)
{
    for(auto it = cycle.begin();it != cycle.end(); it++)
    {
        if(*it == key)
        {
            return 1;
        }
    }
    return 0;
}
/*
    Get last element from supernode and reconsrtuct the graph
    recursively maybe
*/
void edge_find(int u,int min_wt,int *v,int *wt)
{
    auto graph1 = g_stack[top-1];
    auto actualGraph = g_stack[top-2];
    int shift = 0;
    for(auto it = graph1[u].begin(); it !=graph1[u].end(); it++)
    {
        shift++;
        if(it->w == min_wt)
        {
            break;
        }
    }
    auto it = actualGraph[u].begin() + shift - 1;
    *v = it->edge;
    *wt = it->w;
}
void non_cyle_edge_find(int u,int v, int min_wt,int *wt)
{
    auto graph0 = g_stack[top-1];
    auto graph1 = g_stack[top-2];
    int shift = 0;
    for(auto it = graph0[u].begin(); it != graph0[u].end(); it++)
    {
        shift++;
        //cout<<"non_cyle_edge_find:" << u+1 <<" " << it->edge+1 << " " << min_wt << endl;
        if(it->w == min_wt && it->edge == v)
        {
            auto it = graph1[u].begin() + shift - 1;
            *wt = it->w;
            return;
        }
    }
    *wt = INF;
}
int cycle_weight(int u,int v)
{
    int x = top-1;
    //cout <<"\nTop accessed:" << x << endl;
    auto graph = g_stack[x];
    auto actualGraph = g_stack[x-1];int shift = 0;
    for(auto it = graph[u].begin(); it !=graph[u].end(); it++)
    {
        shift++;
        if(it->w == 0 && it->edge == v)
        {
            break;
        }
    }
    int wt = -1;
    auto it = actualGraph[u].begin() + shift -1;
    wt = it->w;
    //cout <<"For " << u+1 <<" and " << v+1;
    //cout << " weight in original graph:" << wt << endl;
    return wt;
}
int edge_match(int u, int v)
{
    for(auto it = g_stack[top][u].begin(); it != g_stack[top][u].end(); it++)
    {
        if(it->edge == v)
        {
            return it->w;
        }
    }
    return INF;
}
void dfs_visit(int u, vector<int> &parent,vector<int> &dist, vector<string> &color)
{
    color[u] = "gray";
    for(auto it = mincostArbor[u].begin(); it != mincostArbor[u].end(); it++)
    {
        if(color[it->edge] == "white")
        {
            parent[it->edge] = u;
            dist[it->edge] = dist[u] + it->w;
            dfs_visit(it->edge,parent,dist,color);
        }
    }
    color[u] = "black";
}
void finishing_touch(int s)
{
    int V = v_stack[top];
    int i,wt = INF;
    auto actualGraph = g_stack[top];
    for(i=0;i<V;i++)
    {
        auto it = mincostArbor[i].begin();
        while(it != mincostArbor[i].end())
        {
            a:
            wt = edge_match(i,it->edge);
            if(wt == INF)//means there is no actual such edge in the original graph
            {
                //cout << "Removing edge from " << i+1 << " to " << it->edge+1 << endl;
                removeEdge(mincostArbor,i,it->edge);
                it = mincostArbor[i].begin();
                goto a;
            }
            else if (it->w != wt)
            {
                it->w = wt;
            }
            it++;
        }
    }
    vector <int> parent;
    vector <int> dist;
    vector <string> color;
    parent.assign(V,-1);
    dist.assign(V,INF);
    color.assign(V,"white");
    dist[s] = 0;
    parent[s] = 0;
    dfs_visit(s,parent,dist,color);
    printVector(parent);
    printVector(dist);
}
void unfold(vector <node> adj[],int adjV,int s)
{
    vector <int> cycle = sp.back().super;
    auto backupCycle = cycle;
    sp.pop_back();
    int i,V;
    V = v_stack[top-1];
    
    vector <int> parent;
    parent.assign(V, -1);
    cout << "Cycle:"; 
    printVector(cycle);

    // Zero edge weight cycle construction................................
    
    int f = cycle.front();
    int b = cycle.back();
    while (cycle.size()> 1)
    {
        int v = cycle[0];
        int u = cycle[1];
        int wt = cycle_weight(u,v);
        addEdge(mincostArbor,u,v,wt);
        cycle.erase(cycle.begin());
        incomingEdge[v] = true;
        parent[v] = u;
    }
    int wt = cycle_weight(f,b);
    addEdge(mincostArbor,f,b,wt);
    incomingEdge[b] = true;
    parent[b] = f;
    
    //non cycle to cycle edges......................
    // Find minweight edge in contracted graph, then same edge weight in top-1 graph then actual graph
    
    auto inter = g_stack[top];
    int min_wt = INF;
    //cout << v_stack[top] << "\t";
    for(i=0;i<b;i++)
    {
        min_wt = INF;
        //cout << "Accessing for "<< i+1 << endl;
        for(auto it = inter[i].begin(); it != inter[i].end(); it++)
        {
            if(it->w < min_wt && inCycle(backupCycle,it->edge))
            {
                min_wt = it->w;
            }
        }
        if(min_wt == INF)
        {
            i++;
        }
        //cout << i+1 <<" " << min_wt <<" ";
        int v,wt;
        edge_find(i,min_wt,&v,&wt);
        //cout << v+1 <<" " << wt <<" "<<incomingEdge[v]<<" " <<parent[v]+1 << endl;
        if(incomingEdge[v] == true)
        {
            //cout << "Removing edge from " << parent[v]+1 << " to " << v+1 << endl;
            removeEdge(mincostArbor,parent[v],v);
        }
        addEdge(mincostArbor,i,v,wt);
    }
    
    //cycle to non cycle edges..........................
    
    min_wt = INF;
    vector <int> minWtedges;
    for(auto it = inter[b].begin();it != inter[b].end(); it++)
    {
        if(it->w < min_wt)
        {
            min_wt = it->w;
        }
    }
    for(auto it = inter[b].begin();it != inter[b].end(); it++)
    {
        if(it->w == min_wt)
        {
            minWtedges.push_back(it->edge);
        }
    }
    //cout << "Min weight found:";
    //cout << b+1 << " " << v+1 << " " << min_wt << endl;
    //printVector(backupCycle);
    //cout <<"Min wt edges:"; printVector(minWtedges);
    while (minWtedges.empty() == false)
    {
        int v = minWtedges.back();
        for(auto it = backupCycle.begin(); it != backupCycle.end(); it++)
        {
            //check if g_stack[top-1] has that min_wt edge
            int wt = INF;
            non_cyle_edge_find(*it,v,min_wt,&wt);
            if(wt != INF)
            {
                //cout<<"UNfold:" << *it+1 <<" " << v+1 << " " << wt << endl;
                addEdge(mincostArbor,*it,v,wt);
                incomingEdge[v] = true;
                break;
            }
        }
        minWtedges.pop_back();
    }
    
    // Removing top 2 graphs........................

    top = top-2;
    if(top == 0 )
    {
        finishing_touch(s);
        cout <<"\nMin cost Arbor graph......................\n";
        printGraph(mincostArbor,V);
    }
    else
    {
        //cout <<"Recreated uptill now ........................\n";
        //printGraph(mincostArbor,V);
        unfold(g_stack[top+1],v_stack[top+1],s);
    }
    
}
void arbor(vector <node> adj[],int s,int V, int E)
{
    vector <int> cheap_edge_wt;
    vector <int> parent;
    parent.assign(V,-1);
    parent[s] = 0;
    cheap_edge_wt.assign(V,INF);
    cheap_edge_wt[s] = 0;
    int i;
    
    // Storing graph before modification to get actual edge weights.......................
    
    cout << "Printing for g_stack...................\n";
    top++;v_stack.push_back(V);cout << "Incrementing TOP:"<<top << endl;
    for(i=0;i<V;i++)
    {
       for(auto it = adj[i].begin();it != adj[i].end();it++)
       {
           addEdge(g_stack[top],i,it->edge,it->w);
       }
    }
    //printGraph(g_stack[top],v_stack.front());

    // Modification...............................
    
    for(i=0;i<V;i++)
    {
        cheap_edge(adj,s,V,E,i,cheap_edge_wt,parent);
    }
    //printVector(cheap_edge_wt);
    //printVector(parent);
    modify_edge_wt(adj,V,E,cheap_edge_wt);
    //printGraph(adj,V);
    vector <int> dfs_parent;
    vector <string> color;
    dfs_parent.assign(V,-1);
    color.assign(V,"white");
    flag = 0;
    last_vist = INF;
    for(i=0;i<V;i++)
    {
        //cout <<"Dfs for "<< i+1 << endl;
        dfs(adj,i,dfs_parent,color);
        if(flag)
        {
            cout <<"Breaking at " <<i+1 << endl;
            break;
        }
    }
    if(flag == 0 )
    {
        cout <<"Done contraction" << endl;
        cout << "TOP:"<<top << endl;
        unfold(adj,V,s);
        return;
    }
    else if (E == 0)
    {
        cout << "no edges left" << endl;
        return;
    }
    /*
    Store the graph just before supernode creation. This will help in remembering 
    the edges while unfolding..................................
    */
    cout << "Printing for g_stack...................\n";
    top++;v_stack.push_back(V);
    cout << "Incrementing TOP:"<<top << endl;
    for(i=0;i<V;i++)
    {
       for(auto it = adj[i].begin();it != adj[i].end();it++)
       {
           addEdge(g_stack[top],i,it->edge,it->w);
       }
    }
    printGraph(g_stack[top],v_stack.front());
    /* 
    Now all the elements of cycle need to be put in the supernode vector
    Then a new graph needs to be constructed with that supernode and recalibrated edges.
    This graph will then be sent for arbor() recursively.
    */
    vector <int> cycle;
    i = last_vist;
    while (dfs_parent[i] != -1)
    {
        cycle.push_back(i);
        i = dfs_parent[i];
    }
    cycle.push_back(i);
    cout << "Cycle:";
    printVector(cycle);
    supernode sup;
    sup.super = cycle;
    sp.push_back(sup);

    //new graph generation....................................
    
    vector <node> new_adj[V];
    int new_edge = 0;
    int superNode = cycle.back();
    for(i=0;i<V;i++)
    {
        if(!inCycle(cycle,i))
        {
            for(auto it = adj[i].begin(); it != adj[i].end(); it++)
            {
                if(!inCycle(cycle,it->edge))
                {
                    addEdge(new_adj,i,it->edge,it->w);new_edge++;
                }
                else
                {
                    addEdge(new_adj,i,superNode,it->w);new_edge++;
                }
            }
        }
        else
        {
            for(auto it = adj[i].begin(); it != adj[i].end(); it++)
            {
                if(!inCycle(cycle,it->edge))
                {
                    addEdge(new_adj,superNode,it->edge,it->w);new_edge++;
                }
            }
        } 
    }
    //cout << "Printing new graph...........................\n";
    //printGraph(new_adj,V);

    //recursive call to Arbor() for new graph........................
    arbor(new_adj,s,V,new_edge);
}
int main()
{
    int t;
    cout <<"#Test:";
    cin>>t;
    while (t--)
    {
        //Intitialize()....................
        flag = 0;
        top = -1;
        last_vist = -1;
        sp.clear();
        v_stack.clear();
        incomingEdge[MAX] = {false};
        int i,j;
        for(i=0;i < MAX;i++)
        {
            mincostArbor[i].clear();
            for(j=0; j < MAX; j++)
            {
                g_stack[i][j].clear();
            }
        }
        // Input
        int n,s;
        cout <<"N s:";
        cin >> n >> s;s--;
        int e;
        cout <<"#Edges:";
        cin >> e;
        vector <node> graph[n];
        while (e--)
        {
            int u,v,wt;
            cin >> u >> v >> wt;
            u--;v--;
            addEdge(graph,u,v,wt);
        }
        //printGraph(graph,n);
        arbor(graph,s,n,e);
    }
    return 0;
}