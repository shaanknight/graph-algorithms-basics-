#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<int,int>
#define ff first
#define ss second

vector<int> adj[100005];
int vis[100005],tr,mrk[100005],deg[100005];
pi lis[400005];
priority_queue<pi,vector<pi>,greater<pi> > pq;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t,h,i,n,m,u,v,mx;
	pi ed;

	cin >> t;
	while(t--)
	{
		tr=1;
		h=0;
		mx=0;
		cin >> n >> m;
		for(i=1;i<=m;++i)
		{
			cin >> u >> v;
			adj[u].pb(v);
			adj[v].pb(u);
			deg[u]++;
			deg[v]++;
		}
		for(i=1;i<=n;++i)
			pq.push(pi(adj[i].size(),i));
		h=0;
		while(!pq.empty())
		{
			ed=pq.top();
			pq.pop();
			u=ed.ss;
			if(mrk[u])
				continue;
			mx=max(mx,ed.ff);
			lis[h++]=pi(ed.ff,ed.ss);
			mrk[u]=1;
			for(auto v:adj[u])
			{
				deg[v]--;
				pq.push(pi(deg[v],v));
			}
		}
		cout << mx+1 << "\n";
		for(i=1;i<=n;++i)
		{
			adj[i].clear();
			deg[i]=mrk[i]=vis[i]=0;
		}
	}

	return 0;
}


