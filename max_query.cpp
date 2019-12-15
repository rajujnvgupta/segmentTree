/*
	@rajujnvgupta
	15/dec/2019   
*/

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector<vector<int>>tree(4*N+1);
vector<int>arr(N);
int k;
void buildTree(int ss, int se, int index){
	if(ss == se){
		tree[index].push_back(arr[ss]);
		return;
	}
	int mid = ss + (se-ss)/2;
	buildTree(ss, mid, 2*index);
	buildTree(mid+1, se, 2*index+1);
	merge(tree[2*index].begin(), tree[2*index].end(), tree[2*index+1].begin(), tree[2*index+1].end(), back_inserter(tree[index]));
	return;
}

int bs(int index){
	
	///int ans = 0;
	int left = 0;
	int right = (int)tree[index].size()-1;
	int ans_index = -1;
	while(left<=right){
		int mid = left + (right-left)/2;
		if(tree[index][mid] >= k){
			right = mid-1;
			ans_index = mid;
		}else{
			left = mid+1;
		}
	}
	if(ans_index < 0){
		return 0;
	}	
	int n = (int)tree[index].size();
	return n-ans_index;
}

int query(int ss, int se, int l, int r, int index){
	if(r < ss || l > se){
		return 0;
	}
	if(ss>=l && se<=r){
		return bs(index);
		///perform binary search
	}
	int mid = ss + (se-ss)/2;
	int left = query(ss, mid, l, r, 2*index);
	int right = query(mid+1, se, l, r, 2*index+1);
	return left + right;
}
	

int main(){
	int n;
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>arr[i];
	}
	buildTree(0, n-1, 1);
	int q;
	cin>>q;
	while(q--){
		int l, r;
		cin>>l>>r>>k;
		int ans = query(0, n-1, l-1, r-1, 1);
		cout<<ans<<'\n';
	}
	return 0;
}
