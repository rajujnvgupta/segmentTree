#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll N = 1e5+5;

vector<vector<int>>table;
vector<vector<int>>adj;
ll par[N];
ll depth[N];
ll visited[N];
ll logN;

void bfs(ll src){
	queue<ll>q;
	q.push(src);
	while(!q.empty()){
		ll v = q.front();
		q.pop();
		visited[v] = 1LL;
		for(auto &u : adj[v]){
			if(!visited[u]){
				visited[u] = 1LL;
				q.push(u);
				par[u] = v;
				depth[u] = depth[v]+1LL;
			}
		}
	}
}

//table[0][i] = par[i]
//2^k <= n
//k 	<= log2(N)
//size Nlog2(N)
//use table[k] to build table[k+1]
//walk(i, k);
//i = table[k][i] (2^k) lifting
//j = table[k][i] (2^k) lifting

ll walk(int u, int dep){
	for(ll k = 0LL; k <= logN && u != -1LL; k++){
		if(dep & (1LL << k)){
			u = table[k][u];
		}
	}
	return u;
}

ll LCA(ll u, ll v){
	if(depth[u] > depth[v]){
		u = walk(u, depth[u] - depth[v]);
	}else if(depth[v] > depth[u]){
		v = walk(v, depth[v] - depth[u]);
	}
	if(u == v){
		return u;
	}
	///walk step by step
	for(ll k = logN; k>=0LL; k--){
		if(table[k][u] != table[k][v]){
			u = table[k][u];
			v = table[k][v];
		}
	}
	return table[0LL][u];
}
//kattis tourists problems
//ll dist(ll u, ll v){
	//return depth[u]+depth[v]- 2*depth[LCA(u, v)];
//}

int	main(){
	ll n;
	cin>>n;
	#warning make appropriate change for long long
	//calculating highest set bit in n
	logN = 32 - __builtin_clz(n) - 1;
	table.resize(logN+1);
	for(int i = 0; i<=logN; i++){
		table[i].resize(n, -1);
	}

	adj.resize(n);
	for(ll i = 0LL; i < n-1LL; i++){
		ll u, v;
		cin>>u>>v;
		--u;
		--v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	memset(par, -1LL, sizeof(par));
	//memset(table, -1LL, sizeof(table));
	memset(visited, 0LL, sizeof(visited));
	memset(depth, 0LL, sizeof(depth));
	bfs(0);
	//for(ll i = 0LL; i < n; i++){
		//cout<<i <<' '<<par[i]<<endl;
	//}
	//cout<<endl;
	//for(ll i = 0LL; i < n; i++){
		//cout<<i <<' '<<depth[i]<<endl;
	//}
	//cout<<endl;
	for(ll i = 0LL; i < n; i++){
		table[0LL][i] = par[i];
	}
	for(ll k = 1LL; k <= logN; k++){
		for(ll i = 0LL; i < n; i++){
			int isParent = table[k-1LL][i];
			if(isParent != -1){
				table[k][i] = table[k-1LL][i];
			}
		}
	}
	//ll q;
	//cin>>q;
	//while(q--){
		//ll u, v;
		//cin>>u>>v;
		//ll ans = LCA(u-1, v-1);
		//cout<<ans<<'\n';
	//}
	
	//kattis tourists problem solutions
	//ll ans = 0;
	//for(ll i = 1; i<=logN; i++){
		//for(int j = i+i; j<= n; j+=i){
			//ans += dist(i-1, j-1)+1;
		//}
	//}
	//cout<<ans<<'\n';
	
	int q;
	cin>>q;
	while(q--){
		int u, v;
		cin>>u>>v;
		int ans = LCA(u-1, v-1);
		cout<<ans<<endl;
	}
	return 0;
}
