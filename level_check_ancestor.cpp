#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back

vector<ll> adj[100009];
vector<ll> lev[100009];
ll pr[100009],strt[100009],fin[100009],lv[100009],t=0,id1[500009],id2[500009];

void dfs(ll u,ll l)
{
	strt[u]=t++;
	id1[t-1]=u;
	lv[u]=l;
	lev[l].pb(strt[u]);
	for(ll i=0;i<adj[u].size();i++)
		dfs(adj[u][i],l+1);
	fin[u]=t++;
	id2[t-1]=u;
}

int main()
{
	ll n,i,u,v,q,p;
	cin >> n;
	for(i=1;i<=n;i++)
	{
		cin >> pr[i];
		if(pr[i])
			adj[pr[i]].pb(i);
	}
	for(i=1;i<=n;i++)
	{
		if(!pr[i])
			dfs(i,0);
	}

	cin >> q;
	while(q--)
	{
		cin >> u >> p;
		if(lv[u]-p<0)
			cout << 0 << endl;
		else
		{
			auto it = upper_bound(lev[lv[u]-p].begin(),lev[lv[u]-p].end(),strt[u]);
			it--;
			cout << upper_bound(lev[lv[u]].begin(),lev[lv[u]].end(),fin[id1[*it]])-lower_bound(lev[lv[u]].begin(),lev[lv[u]].end(),strt[id1[*it]])-1 << endl;
		}
	}
	return 0;
}
