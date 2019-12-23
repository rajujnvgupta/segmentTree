
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int tree[4*N+1][4*N+1] = {0};
int arr[N][N];
int index_X, index_Y;
int new_val;
int row1, row2;
int col1, col2;
int n;
//building process
void buildTree_y(int vx, int lx, int rx, int vy, int ly, int ry){
	if(ly == ry){
		if(lx == rx){
			tree[vx][vy] = arr[lx][ly];
		}else{
			//merging row
			tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
		}
	}else{
		int mid = (ly+ry)/2;
		buildTree_y(vx, lx, rx, 2*vy, ly, mid);
		buildTree_y(vx, lx, rx, 2*vy+1, mid+1, ry);
		tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
	}
}

void buildTree_x(int vx, int lx, int rx){
	if(lx != rx){
		int mid = (lx+rx)/2;
		buildTree_x(2*vx, lx, mid);
		buildTree_x(2*vx+1, mid+1, rx);
	}
	buildTree_y(vx, lx, rx, 1, 0, n-1);
}
int sum_y(int ly, int ry, int lqy, int rqy, int vx, int vy){
	if(lqy > rqy){
		return 0;
	}
	if(lqy == ly && rqy == ry){
		return tree[vx][vy];
	}
	int mid = (ly+ry)/2;
	int left = sum_y(ly, mid, lqy, min(rqy, mid), vx, 2*vy);
	int right = sum_y(mid+1, ry, max(lqy, mid+1), rqy, vx, 2*vy+1);
	return left+right;
}

int sum_x(int lx, int rx, int lqx,	int rqx, int vx){
	if(lqx > rqx){
		return 0;
	}
	if(lqx == lx && rqx == rx){
		return sum_y(0, n-1, col1, col2, vx, 1);
	}
	int mid = (lx+rx)/2;
	int left = sum_x(lx, mid, lqx, min(rqx, mid), 2*vx);
	int right = sum_x(mid+1, rx, max(lqx, mid+1), rqx, 2*vx+1);
	return left+right;
}

void update_y(int ly, int ry, int lx, int rx, int vx, int vy, int index_y, int val){

	if(ly == ry){
		if(lx == rx){
			tree[vx][vy] = val;
		}else{
			tree[vx][vy] = tree[2*vx][vy] + tree[2*vx+1][vy];
		}
	}else{
		int mid = (ly+ry)/2;
		if(index_y <= mid){
			update_y(ly, mid, lx, rx, vx, 2*vy, index_y, val);
		}else{
			update_y(mid+1, ry, lx, rx, vx, 2*vy+1, index_y, val);
		}
		tree[vx][vy] = tree[vx][2*vy] + tree[vx][2*vy+1];
	}
}

void update_x(int lx, int rx, int vx, int index_x, int val){
	if(lx != rx){
		int mid = (lx+rx)/2;
		if(index_x <= mid){
			update_x(lx, mid, 2*vx, index_x, val);
		}else{
			update_x(mid+1, rx, 2*vx+1, index_x, val);
		}
	}
	update_y(0, n-1, lx, rx, vx, 1, index_Y, val);
}

int main(){
	
	cin>>n;
	//for(int i = 0; i<= 4*n; i++){
		//for(int j = 0; j <= 4*n; j++){
			//cout<<tree[i][j]<<' ';
		//}
		//cout<<endl;
	//}
	//int n;

	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin>>arr[i][j];
		}
	}

	buildTree_x(1, 0, n-1);
	int t;
	cin>>t;
	while(t--){
		string type;
		cin>>type;
		if(type == "QUERY"){
			cin>>row1>>row2>>col1>>col2;
			if(row1 > row2){
				swap(row1, row2);
			}
			if(col1 > col2){
				swap(col1, col2);
			}
			int ans = sum_x(0, n-1, row1, row2, 1);
			cout<<ans<<'\n';
		}else if(type == "UPDATE"){
			cin>>index_X>>index_Y>>new_val;
			update_x(0, n-1, 1, index_X, new_val);
		}
	}
	return 0;
}
