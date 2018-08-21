#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pp pop_back
#define pi pair<ll,ll>

ll t,z,strt[200005],fin[200005];
vector<ll> tope;
vector<ll> scc[200005];
vector<ll> adj[200005];
vector<ll> jda[200005];

void dfs(ll u,vector<ll> adj[],vector<bool> &vist,ll key)
{
	ll i;
	vist[u]=true;
	if(key==0)
		strt[u]=t++;
	else
		scc[z].pb(u);
	for(i=0;i<adj[u].size();i++)
	{
		if(!vist[adj[u][i]])
			dfs(adj[u][i],adj,vist,key);
	}
	if(key==0)
	{
		fin[u]=t++;
		tope.pb(u);
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll m,n,i,u,v,e=0;
	cin >> n >> m;
	for(i=1;i<=m;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		jda[v].pb(u);
	}
	vector<bool> vist1(n+9,false);
	vector<bool> vist2(n+9,false);
	for(i=1;i<=n;i++)
	{
		if(!vist1[i])
			dfs(i,adj,vist1,0);
	}
	for(i=0;i<tope.size();i++)
	{
		if(!vist2[tope[i]])
		{
			dfs(tope[i],jda,vist2,1);
			z++;
		}
	}
	return 0;
}



