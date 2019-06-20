#include <iostream>
#include<assert.h>

using namespace std;


int queryBIT(int *BIT, int i)  ///sum till i th index
{
    int ans = 0;
    while(i > 0)
    {
        ans += BIT[i];
        i -= (i & (-i));
    }
    return ans;
}


void updateBIT(int *BIT, int i, int n, int inc)
{
    while(i <= n) ///BIT[i] += inc;
    {
        BIT[i] += inc;
        i += ( i & (-i));
    }
}

void buildBIT(int *a, int *BIT, int n)
{
    for(int i = 1; i <= n; i++)
    {
        updateBIT(BIT, i, n, a[i]);
    }
}

int main()
{
    int a[6] = {0,2,3,1,4,7};///put a[0] = 0
    int n = sizeof(a)/sizeof(int);

    assert(n > 0);

    int *BIT = new int[n];


    buildBIT(a, BIT, n);

    int q;

    cin>>q;

    while(q--)
    {
        int l, r;
        cin>>l>>r;
        cout<<queryBIT(BIT, r) - queryBIT(BIT, l-1)<<endl;
    }

    return 0;
}


