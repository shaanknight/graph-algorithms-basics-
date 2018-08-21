#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define pi pair<int,int>
#define ff first
#define ss second

vector<int> adj[100003];
vector<pi> que[100003];
set<int> st[200003];
map<string,int> mp;
string str;
int sz[100003],lv[100003],rt[100003],ans[100003],big[100003],col[100003];

void dfs(int u,int p,int l)
{
	sz[u]=1;
	lv[u]=l;
	for(int i=0;i<adj[u].size();i++)
	{
		if(adj[u][i]!=p)
		{ 
			dfs(adj[u][i],u,l+1);
			sz[u]+=sz[adj[u][i]];
		}
	}
}

void add(int u,int p,int r)
{
	if(r>0) st[lv[u]].insert(col[u]);
	else st[lv[u]].erase(col[u]);
	for(int i=0;i<adj[u].size();i++)
		if(adj[u][i]!=p && !big[adj[u][i]]) add(adj[u][i],u,r);
}

int dsu(int u,int p,int r)
{
	int bg=0,i;
	for(i=0;i<adj[u].size();i++)
		if(adj[u][i]!=p && sz[adj[u][i]]>sz[bg]) bg=adj[u][i];
	big[bg]=1;
	for(i=0;i<adj[u].size();i++)
		if(adj[u][i]!=p && adj[u][i]!=bg) dsu(adj[u][i],u,-1);
	if(bg) dsu(bg,u,1);
	add(u,p,1);
	for(i=0;i<que[u].size();i++)
		ans[que[u][i].ff]=st[lv[u]+que[u][i].ss].size();
	big[bg]=0;
	if(r==-1) add(u,p,-1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n,i,p,j,fl=1,q,u,v;
	cin >> n;
	for(i=1;i<=n;i++)
	{
		cin >> str;
		cin >> p;
		if(!p) rt[i]=1;
		else
		{
			adj[i].pb(p);
			adj[p].pb(i);
		}
		j=mp[str];
		if(j) col[i]=j;
		else
		{
			mp[str]=fl++;
			col[i]=fl-1;
		}
	}
	for(i=1;i<=n;i++)
		if(rt[i]) dfs(i,0,1);
	cin >> q;
	for(i=1;i<=q;i++)
	{
		cin >> u >> v;
		que[u].pb(pi(i,v));
	}
	for(i=1;i<=n;i++)
		if(rt[i]) dsu(i,0,-1);

	for(i=1;i<=q;i++)
		cout << ans[i] << endl;
	return 0;
}
			
