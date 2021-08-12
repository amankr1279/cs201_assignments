#include <iostream>
#include <vector>
using namespace std;
#define INF 999999 
class node
{
public:
    int edge;
    int w;
};
vector <int> pre;
vector <int> post;
vector <int> toposort;
int Time;
void printVector(vector <int> v)
{
    for(auto it = v.begin();it != v.end();it++)
    {
        cout << *it <<" ";
    }
    cout << endl;
}
void addEdge(vector <node> adj[],int u, int v,int wt)
{
    node gnode;
    gnode.edge = v;
    gnode.w = wt;
    adj[u].push_back(gnode);
}
void printGraph(vector <node> adj[],int V)
{
    int i=0;
    for(i=0;i<V;i++)
    {
        cout <<"Printing for node:" << i <<  endl;
        for(auto it = adj[i].begin();it !=  adj[i].end();it++)
        {
            cout << it->edge <<" " << it->w << endl;
        }
    }
}
void bfsedgeCount(vector <node> adj[],vector <int> &parent,vector <int> &dist,int V,int E,int d)
{
    int tree_edge = 0,back_edge,forward_edge,cross_edge;
    back_edge = forward_edge = cross_edge = 0;
    int i;
    for(i=0;i<V;i++)
    {
        if(parent[i] != INF)
            tree_edge++;
    }
    
    if(d==0)//Undirected
    {
        cross_edge = E - tree_edge;
        cout << tree_edge << " " << cross_edge << endl;
    }
    else
    {
        for(i=0;i<V;i++)
        {
            for(auto it = adj[i].begin(); it != adj[i].end(); it++)
            {
                if(dist[it->edge] <= dist[i])
                {
                    back_edge++;
                }
            }
        }
        cross_edge = E - back_edge - tree_edge;
        cout << tree_edge <<" " << back_edge <<" "<< forward_edge <<" " << cross_edge << endl;
    }
}
void bfs(vector <node>adj[],int V,int source,int E,int d)
{
    vector <int> parent;
    vector <int> dist;
    vector <string> color;

    parent.assign(V,INF);
    dist.assign(V,INF);
    color.assign(V,"white");
    vector <int> level;
    level.assign(V,0);
    level[0] = 1;

    vector <int > q;
    q.push_back(source);
    color[source] = "gray";
    dist[source] = 0;
    while (!q.empty())
    {
        int u = q.front();//cout << u << " ";
        q.erase(q.begin());
        for(auto it = adj[u].begin(); it != adj[u].end(); it++)
        {
            if(color[it->edge] == "white")
            {
                //cout <<it->edge <<" "<< color[it->edge];
                color[it->edge] = "gray";
                parent[it->edge] = u;
                dist[it->edge] = dist[u] + 1;
                q.push_back(it->edge);
                level[dist[it->edge]]++;
            }
        }
        color[u] = "black";
    }
    vector <int> ::iterator it;
    it = level.begin();it++;
    for(;it != level.end();it++)
    {
        cout << *it <<" ";
        if(*it == 0)
            break;
    }
    bfsedgeCount(adj,parent,dist,V,E,d);
}

void dfs_visit(vector <node> adj[],vector<int> &parent,vector<string> &color, int u,int topo_flag)
{
    color[u] = "gray";
    Time++;
    pre[u] = Time;
    for(auto it = adj[u].begin(); it != adj[u].end();it++)
    {
        if(color[it->edge] == "white")
        {
            parent[it->edge] = u;
            dfs_visit(adj,parent,color,it->edge,topo_flag);
        }
    }
    color[u] = "black";
    Time++;
    post[u] = Time;
    if(topo_flag)
    {
        toposort.insert(toposort.begin(), u);
    }
}
void dfs(vector <node> adj[],int V, int source,int E, int d)
{
    vector <int> parent;
    vector <string> color;
    Time = 0;
    parent.assign(V,INF);
    color.assign(V,"white");
    pre.assign(V,0);
    post.assign(V,INF);

    dfs_visit(adj,parent,color,source,0);

    int tree_edge = 0,back_edge,forward_edge,cross_edge;
    back_edge = forward_edge = cross_edge = 0;
    int i;
    cout << post[source] <<" ";
    for(i=0;i<V;i++)
    {
        if(parent[i] != INF)
        {
            tree_edge++;
        }
    }
    if(d==0)
    {
        back_edge = E - tree_edge;
        cout << tree_edge <<" " << back_edge<< endl;
    }
    else
    {
        for(i=0;i<V;i++)
        {
            for(auto it  = adj[i].begin(); it != adj[i].end();it++)
            {
                if(parent[it->edge] !=i)
                {
                    if((post[i] > post [it->edge]) && pre[i] < pre[it->edge] )
                        forward_edge++;

                    if((post[i] < post[it->edge]) && pre[i] > pre[it->edge] )
                        back_edge++;
                }
            }
        }
        cross_edge = E - tree_edge - back_edge - forward_edge;
        cout << tree_edge <<" " << back_edge <<" " << forward_edge <<" " << cross_edge;
    }
    cout << endl;
    printVector(post);
}
void func_topo_sort(vector <node> adj[],int V,int E)
{
    int i;
    vector <int> parent;
    vector <string> color;
    parent.assign(V,INF);
    color.assign(V,"white");

    Time = 0;
    pre.assign(V,0);
    post.assign(V,INF);

    for(i=0;i<V;i++)
    {
        if(color[i] == "white")
        {
            //cout << "DFS for " << i << endl;
            dfs_visit(adj,parent,color,i,1);
            //cout << endl;
        }
    }
    
    for(i=0;i<V;i++)
    {
        for(auto it = adj[i].begin(); it != adj[i].end();it++)
        {
            if(parent[it->edge] != i)
            {
                if(post[it->edge] > post[i]) // Backedge exists => cycle
                {
                    cout <<"-1" << endl;
                    return;
                }
            }
        }
    }
    for(auto it = toposort.begin(); it != toposort.end();it++)
    {
        cout << *it <<" ";
    }
    cout << endl;
    toposort.clear();
}
int extract_min(vector <int>&q, vector <int>&dist)
{
    int i=0,index;
    int min = INF;
    for(auto it = q.begin();it!= q.end();it++)
    {
        if(dist[*it] < min)
        {
            min = dist[*it];index = i;
        }
        i++;
    }
    int x = q[index];
    q.erase(q.begin() + index);
    return x;
}
void dijkstra(vector <node> adj[],int source,int V,int E)
{
    vector <int> parent;
    vector <int> dist;
    parent.assign(V,INF);
    dist.assign(V,INF);
    dist[source] = 0;

    vector <int> q;
    int i;
    for(i=0;i<V;i++)
    {
        for(auto it = adj[i].begin(); it != adj[i].end();it++)
        {
            if(it->edge < 0)
            {
                cout <<"-1" << endl;
                return;
            }
        }
    }
    for(i=0;i<V;i++)
    {
        q.push_back(i);
    }
    while (!q.empty())
    {
        int u = extract_min(q,dist);
        for(auto it = adj[u].begin();it != adj[u].end();it++)
        {
            if(dist[it->edge] > dist[u] + it->w)
            {
                dist[it->edge] = dist[u] + it->w;
                parent[it->edge] = u;
            }
        }
    }
    printVector(dist);
}
void bellman_ford(vector <node> adj[], int source, int V, int E)
{
    vector <int> dist;
    vector <int> parent;

    dist.assign(V,INF);
    parent.assign(V,INF);
    dist[source] = 0;

    int i,u;
    int relax_edge=0,mod_relax_edge = 0;
    for (i=1; i<= (V-1);i++)
    {
        for(u=0;u<V;u++)
        {
            for(auto it = adj[u].begin(); it != adj[u].end();it++ )
            {
                relax_edge++;
                if(dist[it->edge] > dist[u] + it->w)
                {
                    mod_relax_edge++;
                    dist[it->edge] = dist[u] + it->w;
                    parent[it->edge] = u;
                }
            }
        }
    }
    for(u=0;u<V;u++)
    {
        for(auto it = adj[u].begin();it != adj[u].end(); it++)
        {
            if(dist[it->edge] > dist[u] + it->w)
            {
                cout << "-1" << endl;
                return;
            }
        }
    }
    for(auto it = dist.begin();it != dist.end();it++)
    {
        cout << *it <<" ";
    }
    cout << relax_edge <<" " << mod_relax_edge<<" " << endl;
}
void fast_bellman_ford(vector <node> adj[], int source, int V, int E)
{
    vector <int> dist;
    vector <int> parent;
    vector <int> count;

    dist.assign(V,INF);
    count.assign(V,0);
    parent.assign(V,INF);
    dist[source] = 0;

    vector <int> q;
    vector <bool> visited;
    visited.assign(V,false);

    q.push_back(source);
    visited[source] = true;

    int relax_edge=0,mod_relax_edge = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.erase(q.begin());
        visited[u] = false;
        for(auto it = adj[u].begin(); it != adj[u].end(); it++)
        {
            relax_edge++;
            if(dist[it->edge] > dist[u] + it->w)
            {
                mod_relax_edge++;
                dist[it->edge] = dist[u] + it->w;
                parent[it->edge] = u;
                if(visited[it->edge] == false)
                {
                    q.push_back(it->edge);
                    visited[it->edge] = true;
                    count[it->edge]++;
                    if(count[it->edge] > V)
                    {
                        cout <<"-1" << endl;
                        return;
                    }
                }
            }
        }
    }
    for(auto it = dist.begin();it != dist.end();it++)
    {
        cout << *it <<" ";
    }
    cout << relax_edge <<" " << mod_relax_edge<<" " << endl;
}
int main()
{
    int t,q,n,d,s;
    cout <<"#Test:";
    cin >> t;
    while (t--)
    {
        cout <<"#Query:";
        cin >> q;
        if(q==1)
        {
            //BFS
            int edge_num = 0;
            cout <<"N d s:";
            cin >> n >> d >> s;s--;
            int adj[n][n];
            vector <node> graph[n];
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    cin >> adj[i][j];
                    if(adj[i][j] != 0)
                    {
                        addEdge(graph,i,j,adj[i][j]);
                        edge_num++;
                    }
                }
            }
            if(d==0)
            {
                edge_num = edge_num/2;
            }
            //printGraph(graph,n);
            bfs(graph,n,s,edge_num,d);
        }
        else if (q==2)
        {
            //DFS
            cout <<"N d s:";
            cin >> n >> d >> s;s--;
            int adj[n][n];
            int edge_num = 0;
            vector <node> graph[n];
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    cin >> adj[i][j];
                    if(adj[i][j] != 0)
                    {
                        addEdge(graph,i,j,adj[i][j]);
                        edge_num++;
                    }
                }
            }
            if(d==0)
            {
                edge_num = edge_num/2;
            }
            dfs(graph,n,s,edge_num,d);
        }
        else if (q==3)
        {
            //Topological Sort
            cout <<"N:";
            cin >> n;
            int adj[n][n];
            int edge_num = 0;
            vector <node> graph[n];
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    cin >> adj[i][j];
                    if(adj[i][j] != 0)
                    {
                        addEdge(graph,i,j,adj[i][j]);
                        edge_num++;
                    }
                }
            }
            func_topo_sort(graph,n,edge_num);
        }
        else if (q==4)
        {
            //Dijkstra
            cout <<"N d s:";
            cin >> n >> d >> s;s--;
            int edge_num = 0;
            int adj[n][n];
            vector <node> graph[n];
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    cin >> adj[i][j];
                    if(adj[i][j] != 0)
                    {
                        addEdge(graph,i,j,adj[i][j]);
                        edge_num++;
                    }
                }
            }
            if(d==0)
            {
                edge_num = edge_num/2;
            }
            dijkstra(graph,s,n,edge_num);
        }
        else if (q==5)
        {
            //Belmman Ford
            cout <<"N d s:";
            cin >> n >> d >> s;s--;
            int adj[n][n];
            int edge_num = 0;
            vector <node> graph[n];
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    cin >> adj[i][j];
                    if(adj[i][j] != 0)
                    {
                        addEdge(graph,i,j,adj[i][j]);
                        edge_num++;
                    }
                }
            }
            if(d==0)
            {
                edge_num = edge_num/2;
            }
            fast_bellman_ford(graph,s,n,edge_num);
            //bellman_ford(graph,s,n,edge_num);
        }
        else
        {
            //Wrong case
            cout <<"Wrong query entered." << endl;
        } 
    }
    
    return 0;
}