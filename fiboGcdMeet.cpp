/*  
  @rajujnvgupta
  13/dec/2019
*/

#include<bits/stdc++.h>
#define int long long int
using namespace std;
const int N = 1e5+5;
const  int inf = 1e9 + 7;
int arr[N];
int tree[4*N+1];
const int mod = 1e9+7;

class Mat{
	public:
	int **mat = new int*[2];
	Mat(){
		for(int i = 0; i < 2; ++i){
			mat[i] = new int[2];
			for(int j = 0; j < 2; ++j){
				mat[i][j] = 0;
			}
		}
	}
	
	Mat operator*(const Mat &a){
		Mat r;
		for(int i = 0; i < 2; ++i){
			for(int j = 0; j < 2; ++j){
				for(int k = 0; k < 2; ++k){
					r.mat[i][j] += (mat[i][k]*a.mat[k][j])%mod;
					r.mat[i][j] %= mod;
				}
			}
		}
		return r;
	}
};

int fibo(int n){
	Mat r;
	r.mat[0][0] = 1;
	r.mat[1][1] = 1;
	Mat a;
	a.mat[0][0] = 0;
	a.mat[1][1] = 1;
	a.mat[1][0] = 1;
	a.mat[0][1] = 1;
	
	while(n > 0){
		if(n&1){
			r = r*a;
		}
		a = a * a;
		n /= 2;
	}
	return r.mat[1][1]%mod;
}


void buildTree(int ss, int se, int index){
	if(ss == se){
		tree[index] = arr[ss];
		return;
	}
	
	int mid = ss + (se-ss)/2;
	buildTree(ss, mid, 2*index);
	buildTree(mid+1, se, 2*index+1);
	tree[index] = __gcd(tree[2*index], tree[2*index+1]);
	return;
}

int query(int ss, int se, int l, int r, int index){
	//no overlapping 
	if(ss > r || se < l){
		return inf; ///what should i have to return
	}

	if(ss >= l && se<=r){
		return tree[index];
	}
	int mid = ss + (se-ss)/2;
	int left = query(ss, mid, l, r, 2*index);
	int right = query(mid+1, se, l, r, 2*index+1);
	if(left == inf){
		return right;
	}else if(right == inf){
		return left;
	}else{
		return __gcd(left , right);
	}
}
	
int32_t main(){
	
	int n, q;
	cin>>n>>q;
	for(int i = 0; i < n; i++){
		cin>>arr[i];
	}
	buildTree(0, n-1, 1);
	
	while(q--){
		int l, r;
		cin>>l>>r;
		if(l > r){
			swap(l, r);
		}
		int ans = query(0, n-1, l-1, r-1, 1);
		ans = fibo(ans-1);
		cout<<ans<<'\n';
	}
	return 0;
}


