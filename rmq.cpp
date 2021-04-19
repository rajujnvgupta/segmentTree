//cradit goes to Errichto
#include<bits/stdc++.h>
using namespace std;
const int N = 1'000'005;
const int LOGN = 17;
int m[N][LOGN];
int qry(int l, int r){
	int len = r-l+1;
	int k = 0;
	while((1<<(k+1)) <= len){
		++k;
	}

	return min(m[l][k], m[r-(1<<k)+1][k]);
}

int main(){

	int n;
	cin>>n;
	vector<int>a(n);
	for(int i = 0; i < n; ++i){
		cin>>a[i];
		m[i][0] = a[i];
	}

	for(int k = 1; k < LOGN; ++k){
		for(int i = 0;  i+(1<<k)-1 < n; ++i){
			m[i][k] = min(m[i][k-1], m[i+(1<<(k-1))][k-1]);
		}
	}
	int q;
	cin>>q;
	for(int i = 0; i < q; ++i){
		int l, r;
		cin>>l>>r;
		cout<<qry(l, r)<<endl;
	}
}