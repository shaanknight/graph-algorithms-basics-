#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second

vector<pi > euler;
pi tree[1000009];
vector<ll> adj[100009];
ll frs[1000006],pr[1000006],ql,qh;

void dfs(ll u,ll p,ll l)
{
	euler.pb(pi(l,u));
	frs[u]=euler.size()-1;
	for(ll i=0;i<adj[u].size();i++)
	{
		ll j=adj[u][i];
		if(j!=p)
		{
			dfs(j,u,l+1);
			euler.pb(pi(l,u));
		}
	}
}

void build(ll l,ll h,ll p)
{
	if(l==h)
	{
		tree[p]=euler[l];
		return;
	}
	ll m=l+(h-l)/2;
	build(l,m,2*p+1);
	build(m+1,h,2*p+2);
	if(tree[2*p+1].ff < tree[2*p+2].ff)
		tree[p]=tree[2*p+1];
	else
		tree[p]=tree[2*p+2];
	return;
}

pi querry(ll l,ll h,ll p)
{
	if(l>=ql && h<=qh)
		return tree[p];
	else if(h<ql || l>qh)
		return {1e9,1e9};
	ll m=l+(h-l)/2;
	pi a=querry(l,m,2*p+1);
	pi b=querry(m+1,h,2*p+2);
	if(a.ff<b.ff)
		return a;
	else
		return b;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll t,n,m,i,j,u,v,q;
	cin >> t;
	for(ll k=1;k<=t;k++)
	{
		cin >> n;
		for(i=1;i<=n;i++)
		{
			cin >> m;
			for(j=1;j<=m;j++)
			{
				cin >> v;
				adj[i].pb(v);
				adj[v].pb(i);
				pr[v]++;
			}
		}
		for(u=1;u<=100009 && pr[u]!=0;u++);
		dfs(u,0,0);
		build(0,(ll)(euler.size())-1,0);
		cin >> q;
		cout << "Case " << k << ":" << endl;
		while(q--)
		{
			cin >> u >> v;
			ql=min(frs[u],frs[v]);
			qh=max(frs[u],frs[v]);
			cout << (querry(0,euler.size()-1,0)).ss << endl;
		}
		for(i=1;i<=n;i++)
			adj[i].clear();
		euler.clear();
		for(i=0;i<=1000000;i++)
		{
			frs[i]=0;
			tree[i]={0,0};
		}
	}
	return 0;
}
	

