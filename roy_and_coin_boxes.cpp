#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define MAXNODE 3000010

int m[MAXNODE];
int a[MAXN];

void construct(int node, int i, int j, int sum)
{
    int mid;
    if (i == j)
    {
        a[i] = sum + m[node];
        return;
    }
    mid = (i + j) / 2;
    construct(node * 2, i, mid, sum + m[node]);
    construct(node * 2 + 1, mid + 1, j, sum + m[node]);
}

void update(int node, int i, int j, int x, int y)
{
    int mid;
    if (x == i && y == j)
    {
        m[node]++;
        return;
    }
    mid = (i + j ) / 2;
    if (y <= mid)
        update(node * 2, i, mid, x, y);
    else if (x > mid)
        update(node * 2 + 1, mid + 1, j, x, y);
    else
    {
        update(node * 2, i, mid, x, mid);
        update(node * 2 + 1, mid + 1, j, mid + 1, y);
    }
}

int findfirstindex(int start, int end, int key)
{
    int mid = (start + end) / 2;
    if (start > end)
        return -1;
    if (a[mid] >= key && (mid == 1 || a[mid - 1] < key))
        return mid;
    else if (a[mid] >= key)
        return findfirstindex(start, mid - 1, key);
    else
        return findfirstindex(mid + 1, end, key);
}

void print(int n)
{
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() 
{
    int i, n, m, l, r, q, x;
    scanf("%d%d",&n,&m);
    for (i=0; i < m; i++)
    {
        scanf("%d%d",&l,&r);
        update(1, 1, n, l, r);
    }
    construct(1, 1, n, 0);
    sort(a + 1, a + n + 1);
    scanf("%d",&q);
    for (i=0; i < q; i++)
    {
        scanf("%d",&x);
        int ans = findfirstindex(1, n, x);
        if (ans == -1)
            printf("0\n");
        else
            printf("%d\n", n - ans + 1);
    }
    return 0;
}