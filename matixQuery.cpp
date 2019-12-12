/*
  12/dec/2019 @rajujnvgupta
  problem:
  Mike has N 2*2 matrices, M1, M2, …, Mn. Elements of matrices are in range [0,r-1], where r is an integer. Mike considers an operation, o, such that A2x2 o B2x2 = (A2x2 * B2x2)%r (each value in the product of 2 matrices is stored modulo r). Mike gives you q queries, each of the form L,R. For each query, you have to find ML o ML+1 o … o MR.
  Note that it is not necessary, that all the input matrices are invertible. For eg. a matrix, A2x2=[[0,0],[0,0]] can be present in input.
  
  input :
  3 4 4
0 1
0 0

2 1
1 2

0 0
0 2

1 0
0 2

1 4
2 3
1 3
2 2
output:
0 2
0 0

0 2
0 1

0 1
0 0

2 1
1 2

*/


#include <iostream>
using namespace std;

int mod;
class Mat{
    public:
    int **mat = new int*[2];
    Mat(){
        //~ mat[0] = new int[2];
        //~ mat[1] = new int[2];
        for(int i = 0; i < 2; i++){
			mat[i] = new int[2];
			for(int j = 0; j < 2; ++j){
				mat[i][j] = 0;
			}
		}
    }
    
    Mat operator*(Mat const &a){
		Mat r;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				for(int k = 0; k < 2; k++){
					r.mat[i][j] += (mat[i][k]*a.mat[k][j]) % mod;
					r.mat[i][j] %= mod;
				}
			}
		}
		return r;
	}
};

const int N = 100005;
Mat tree[4*N+1];
Mat arr[N];

void buildTree(int ss, int se, int index){
	
	if(ss == se){
		tree[index] = arr[ss];
		return;
	}
	int mid = ss + (se - ss)/2;
	buildTree(ss, mid, 2*index);
	buildTree(mid+1, se, 2*index+1);
	///operator overloading 
	tree[index] = tree[2*index]*tree[2*index+1];
}

Mat query(int ss, int se, int l, int r, int index){
	
	///no overlapping 
	if(ss > r || se < l){
		Mat idtt;
		idtt.mat[0][0] = 1;
		idtt.mat[1][1] = 1;
		///i think here it should be identity matrix
		return idtt;
	}
	///complete overlapping 
	if(ss >= l && se <= r && ss <= se){
		return tree[index];
	}
	
	int mid = ss + (se - ss)/2;
	Mat left = query(ss, mid, l, r, 2*index);
	Mat right = query(mid+1, se, l, r, 2*index+1);
	return left*right;
}

void solve(int mod, int n, int q){
	buildTree(0, n-1 , 1);
	while(q--){
		int l, r;
		cin>>l>>r;
		if(l > r){
			swap(l, r);
		}
		Mat result = query(0, n-1, l-1, r-1, 1);
		for(int i = 0; i < 2; ++i){
			for(int j = 0; j < 2; ++j){
				cout<<(result.mat[i][j] % mod)<<' ';
			}
			cout<<'\n';
		}
		cout<<'\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    int n;
    int q;
    cin>>mod>>n>>q;
    for(int n_size = 0; n_size < n; n_size++){
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				int num;
				cin>>num;
				arr[n_size].mat[i][j] = num;
			}
		}
	}
	solve(mod, n, q);
	//~ for(int n_size = 0; n_size < n; n_size++){
		//~ for(int i = 0; i < 2; i++){
			//~ for(int j = 0; j < 2; j++){
				//~ cout<<result.mat[i][j]<<' ';
			//~ }
			//~ cout<<'\n';
		//~ }
		//~ cout<<'\n';
		//~ cout<<'\n';
	//~ }
	
	return 0;
}
