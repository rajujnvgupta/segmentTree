#include <iostream>
#include<algorithm>
#include<climits>
using namespace std;

void updateRange(int *tree, int ss, int se, int l, int r, int inc, int index)
{
    ///there is no case of complete overlaping in rangeupdate
    ///out of bounds case
    if(l > se || r < ss)
        return;

    ///leaf node
    if(ss = se)
    {
        tree[index] += inc;
        return;
    }

    int mid = (ss + se)/2;
    updateRange(tree, ss, mid, l, r, inc, 2*index);
    updateRange(tree, mid+1, se, l, r, inc, 2*index+1);
    tree[index] =   min(tree[2*index], tree[2*index+1]);
}


void updateNode(int *tree, int ss, int se, int i, int increament,int index)
{
    ///leaf update  outofbound update
    if(i > se || i < ss)
    {
        return;
    }

    ///leaf node
    if(ss = se)
    {
        tree[index] += increament;
        return;
    }


    ///left and right call
    int mid = (ss + se)/ 2;
    updateNode(tree, ss, mid, i, increament, 2*index);
    updateNode(tree, mid+1, se, i, increament, 2*index + 1);
    tree[index] = min(tree[2*index], tree[2*index + 1]);

}


int query(int *tree, int ss, int se, int qs, int qe, int index)
{   ///complete overlap
    if(ss>=qs && se<=qe)
        return tree[index];

    ///no overlap
    if(qe<ss || qs > se)
        return INT_MAX;

    ///partial overlap call both sides and update
    int mid = (ss+se)/2;
    int leftAns = query(tree, ss, mid, qs, qe, 2*index);
    int rightAns = query(tree, mid+1, se, qs, qe, 2*index+1);
    return min(leftAns, rightAns);
}

void segmentTreeBuild(int *a, int s, int e, int *tree, int index)
{
    if(s == e)
    {
        tree[index] = a[s];  ///a[s] ?
        return;
    }

    int mid = (s+e)/2;

    segmentTreeBuild(a, s, mid, tree, 2*index);

    segmentTreeBuild(a, mid+1, e, tree, 2*index + 1);

    tree[index] = min(tree[2*index], tree[2*index + 1]);
}

int main()
{
    int a[] = {1, 3, 12, 5, 6, 4};

    int N = sizeof(a)/sizeof(int);

    int *tree = new int[4*N+1];

    segmentTreeBuild(a, 0, N-1, tree, 1);

    for(int i = 1; i <= 25; i++)
    {
        cout<<tree[i]<<" ";
    }

    cout<<endl;
    ///check for query
  ///  int l, r;
   // cin>>l>>r;
   /// int leftAns = query(tree, 0, N-1, l, r, 1);
    ///cout<<leftAns;


    //updateNode(tree, 0, N-1, 2, 10, 1);
    ///updateNode(tree, 0, N-1, 3, 15, 1);
    updateRange(tree, 0, N-1, 2, 3, 10, 1);

    int no_of_q = 6;
    while(no_of_q--)
    {
        int l, r;
        cin>>l>>r;
        cout<<query(tree, 0, N-1, l, r, 1);
    }

    return 0;
}

