#include<iostream>
#include<list>
using namespace std;

class Graph{
    list<pair<int,int>> *l;
    int V;
public:
    Graph(int v){
        V = v;
        l = new list<pair<int,int>>[v];
    }

    void addEdge(int x, int y, int cost){
        l[x].push_back(make_pair(y,cost));
        l[y].push_back(make_pair(x,cost));
    }

    int dfs_helper(int node, bool *visited, int *count, int &ans){
        //mark the node as visited and increase its count by 1
        visited[node] = true;
        count[node] = 1;

        for(auto nbr_pair: l[node]){
            int nbr = nbr_pair.first;
            int weight = nbr_pair.second;

            if(!visited[nbr]){
                count[node] += dfs_helper(nbr,visited,count,ans);
                int nx = count[nbr];
                int ny = V - nx;

                ans += 2*min(nx,ny)*weight;
            }
        }
        return count[node];
    }

    int HoliAcc(){
        bool *visited = new bool[V]{0};
        int *count = new int[V]{0};

        int ans = 0;
        dfs_helper(0,visited,count,ans); //source node as 0
        return ans;
    }
};

int main(){

    Graph g(4);
    g.addEdge(0,1,3);
    g.addEdge(1,2,2);
    g.addEdge(2,3,2);

    cout<<g.HoliAcc()<<endl;

    return 0;
}