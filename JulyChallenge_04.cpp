#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <stdio.h>
using namespace std;
 
long long int A[100005];
long long int wt[100005];
long long int val[100005];
long long int w[100005];
long long int K[100005][501];
long long int tree[400020];
long long int lazy[400020];
 
void build_tree(int node, int a, int b) {
  	if(a > b) return;
  	if(a == b) {
    	tree[node] = w[a];
		return;
	}
	build_tree(node*2, a, (a+b)/2);
	build_tree(node*2+1, 1+(a+b)/2, b);
	tree[node] = min(tree[node*2], tree[node*2+1]);
}
 
void update(int node, int a, int b, int i, int j, long long int value) {
  	if(lazy[node] != 10000) {
   		tree[node] = min(lazy[node], tree[node]);
		if(a != b) {
			lazy[node*2] = min(lazy[node], lazy[node*2]);
    		lazy[node*2+1] = min(lazy[node], lazy[node*2+1]);
		}
   		lazy[node] = 10000;
  	}
	if(a > b || a > j || b < i)
		return;
  	if(a >= i && b <= j) {
    	tree[node] =  min(tree[node], value);
		if(a != b) {
			lazy[node*2] = min(value, lazy[node*2]);
    		lazy[node*2+1] = min(value, lazy[node*2+1]);
		}
    	return;
	}
	update(node*2, a, (a+b)/2, i, j, value);
	update(1+node*2, 1+(a+b)/2, b, i, j, value);
	tree[node] = min(tree[node*2], tree[node*2+1]);
}
 
long long int query(int node, int a, int b, int i, int j) {
	if(a > b || a > j || b < i) return 100000;
	if(lazy[node] != 10000) {
		tree[node] = min(tree[node], lazy[node]);
		if(a != b) {
			lazy[node*2] = min(lazy[node], lazy[node*2]);
			lazy[node*2+1] = min(lazy[node], lazy[node*2+1]);
		}
		lazy[node] = 10000;
	}
	if(a >= i && b <= j){
		return tree[node];
	}
	long long int q1 = query(node*2, a, (a+b)/2, i, j);
	long long int q2 = query(1+node*2, 1+(a+b)/2, b, i, j);
	long long int res = min(q1, q2);
	return res;
}
 
long long int knapSack(int W, int n) {
   int i, w;
   for (i = 0; i <= n; i++) {
       for (w = 0; w <= W; w++) {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
   return K[n][W];
}

struct oper{
    int l, r;
    long long int k;
};
oper operarray[100005];
int MIN[100005];
vector<int> L[100005], R[100005];
set< pair<int,int> > iset;

int main() {
	int t;
	int N, M;
	int K;
	int l, r;
	long long int cost;
	cin >> t;
	while (t--){
		scanf("%d %d %d", &N, &K, &M);
		long long int sum = 0;
		for (int i=1; i<=N; i++){
			scanf("%lld", &A[i]);
			sum += A[i];
			w[i] = 10000;
		}
		//for (int i=1; i<=4*N+1; i++){
		//	lazy[i] = 10000;
		//}
		//build_tree(1, 1, N);
		for (int i=1; i<=M; i++){
			scanf("%d %d %lld", &l, &r, &cost);
			operarray[i].l = l;
			operarray[i].r = r;
			operarray[i].k = cost;
			L[l].push_back(i);
			R[r].push_back(i);
		//	update(1,1,N,l,r,cost);
		}
		int cnt = 0;
		for (int i=1; i<=N; i++){
			for (int j=0; j<L[i].size(); j++){
			    int operindex = L[i][j];
			    int cost = operarray[operindex].k;
			    iset.insert(make_pair(cost,operindex));
			}
			MIN[i] = iset.begin()->first;
			for (int j=0; j<R[i].size(); j++){
			    int operindex = R[i][j];
			    int cost = operarray[operindex].k;
			    iset.erase(make_pair(cost,operindex));
			}			
		}
		for (int i=1; i<=N; i++){
			if (A[i] < 0){
				val[cnt] = -1 * A[i];
				wt[cnt] = MIN[i];
				cnt++;
			}
		}		
		printf("%lld\n", sum + knapSack(K, cnt));
	}
	return 0;
} 