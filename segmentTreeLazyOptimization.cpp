#include <iostream>
#include<climits>
using namespace std;

int queryLazy(int *tree, int *lazy, int ss, int se, int qs, int qe, int index)
{
    ///first step - resolve the lazy value
    if(lazy[index] != 0)
    {
        tree[index] += lazy[index];
        if(ss != se)
        {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }

        lazy[index] = 0;
    }

    /// No overlap
    if(ss > qe || se < qs)
    {
        return INT_MAX;
    }
    ///Complete overlap
    if(ss>=qs && se <=qe)
    {
        return tree[index];
    }

    ///partial overlap
    int mid = (ss+se)/2;
    int left = queryLazy(tree, lazy, ss, mid, qs, qe, 2*index);
    int right = queryLazy(tree, lazy, mid+1, se, qs, qe, 2*index+1);
    return min(left, right);

}

void updateRangeLazy(int *tree, int *lazy, int ss, int se, int l, int r, int inc, int index)
{
    ///first step - Never we go down if you have lazy value at node you have to resolve
    if(lazy[index] != 0)
    {
        tree[index] += lazy[index];
        ///if not a leaf node
        if(ss != se)
        {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }

        lazy[index] = 0;
    }

    ///out of bounds case
    if(ss > r || l > se)
    {
        return;
    }

    ///complete overlap- return from that index no need to go to children node
    if(ss>=l && se<=r)
    {
        tree[index] += inc;
        ///pass the lazy value to children
        if(ss != se)
        {
            lazy[2*index] += inc;
            lazy[2*index+1] += inc;
        }
        return;
    }
    ///call on left and right
    int mid = (ss+se)/2;
    updateRangeLazy(tree, lazy, ss, mid, l, r, inc, 2*index);
    updateRangeLazy(tree, lazy, mid+1, se, l, r, inc, 2*index + 1);
    tree[index] = min(tree[2*index], tree[2*index + 1]);
    return;
}

void segmentTreeBuild(int a[], int s, int e,int *tree, int index)
{
    if(s == e)
    {
        tree[index] = a[s];
        return;
    }
    int mid = (s+e)/ 2;

    segmentTreeBuild(a, s, mid, tree, 2*index);
    segmentTreeBuild(a, mid+1, e, tree, 2*index+1);
    tree[index] = min(tree[2*index], tree[2*index + 1]);
    return;
}

int main()
{

    int a[] = {1, 3, 2, -5, 6, 4};  ///ans = {1, 3, 12, 5, 6, 4};

    int N = sizeof(a)/sizeof(int);

    int *tree = new int[4*N+1];

    segmentTreeBuild(a, 0, N-1, tree, 1);

    int *lazy = new int[N*4+1];
    lazy[N*4+1] = {0};

    int inc = 10;
    updateRangeLazy(tree, lazy, 0, N-1, 2, 3, inc, 1);

    int no_of_q = 6;
    while(no_of_q--)
    {
        int l, r;
        cin>>l>>r;
        cout<<queryLazy(tree, lazy, 0, N-1, l, r, 1)<<endl;
    }
    return 0;
}

