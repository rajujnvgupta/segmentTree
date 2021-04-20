// binary lifting kth ancestor node leetcode problem 
//credit Errichto
#include<bits/stdc++.h>
using namespace std;
const int LOGN;
vector<vector<int>>up;
vector<int>depth;

void binary_lifting(int n, vector<int>&par){
	int n;
	cin>>n;
	LOGN = 0;

	while((1<<LOGN) <= n){
		++LOGN;
	}
	par[0] = 0;  // for root node
	up.resize(n, vector<int>(LOGN));
	for(int v = 0; v < n; ++i){
		up[v][0] = par[v];
		if(v != 0){
			depth[v] = depth[par[v]]+1;  // finding depth of each node 
		}
		for(int j = 1; j < LOGN; ++j){
			up[v][j] = up[up[v][j-1]][j-1];
		}
	}
}

int main(){
	
	int n;
	cin>>n;
	vector<int>par(n);
	for(int i = 0; i < n; ++i){
		// par[i] = parent of i'th node
	}
	binary_lifting(n, par); // preprocessing

	if(k > depth[node]){
       		return -1;
    	}
    for(int i = 0; i <= LOGN-1; ++i){
        if((1<<i) & k){ //masking only set bit to add up k 
            node = up[node][i];
        }
    } 
    cout<<node<<endl;
}
