#include<iostream>
#include<vector>
#include<queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

int N;

int findway(vector<vector<int> >&matrix,vector<int>&path,int N) {

    path.clear();
    vector<int>used(N,-1);
    queue<int>q;
    used[0] = 0;
    q.push(0);
    int now;
    while(!q.empty() && q.front()!=1 && q.back()!=1) {
        now = q.front();
        q.pop();
        for(int i = 0; i<N;i++) {
            if(matrix[now][i]>0&&used[i]==-1){
                used[i]=now;       
                q.push(i);
                if (i==1) break;
            }
        }
    }
    int weight=0;
    if (used[1]==-1) return 0;
    weight=matrix[used[1]][1];
    for(int i = 1;i!=0; i=used[i]) {
        path.push_back(i);
        if(weight >= matrix[used[i]][i]) 
        {weight = matrix[used[i]][i];}
    }
    path.push_back(0);
    return weight;
}
int main(){ 
    cin>>N;
    vector<int> way;
    vector <vector<int> >matrix(N,vector<int>(N));
    for(int i = 0 ;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>matrix[i][j];
        }
    }
    int weight;
    vector<vector<int> >flow(N,vector<int>(N,0));    //алгоритм нахождуния потока
    for(weight = findway(matrix,way,N); weight !=0;weight = findway(matrix,way,N))
    {
        for(size_t i =0; i < way.size()-1;i++){
            int a = way[i+1] , b=way[i];
            flow[a][b]+=weight;
            flow[b][a]-=weight;
            matrix[a][b]-=weight;
            matrix[b][a]+=weight;
        //    cout<<a<<"_"<<b<<"|";
        }
        //cout<<"way"<<weight<<endl;;
    }

    int f = 0;
    for(int i =0; i<N;i++) {
        f+=flow[0][i];
       // cout<<flow[0][i]<<" "<<matrix[0][i]<<" ";
    }
    cout<<f<<endl;
    return 0;
}


