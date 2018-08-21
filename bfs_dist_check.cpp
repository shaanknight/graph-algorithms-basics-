#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second

ll dist[3][10000],mrk[3][10000],adm[1009][1009],n;

void bfs(vector<ll> adj[],ll u,ll k)
{
	ll i,v;
	queue<ll> q;
	q.push(u);
	for(i=1;i<=n;i++)
		dist[k][i]=1e18;
	dist[k][u]=0;
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		if(!mrk[k][u])
		{
			mrk[k][u]=1;
			for(i=0;i<adj[u].size();i++)
			{
				v=adj[u][i];
				if(!mrk[k][v] && dist[k][v]>dist[k][u]+1)
				{
					dist[k][v]=dist[k][u]+1;
					q.push(v);
				}
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll m,s,t,u,v,i,j,c=0;
	cin >> n >> m >> s >> t;
	vector<ll> adj[n+9];
	for(i=1;i<=m;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		adm[u][v]=1;
		adm[v][u]=1;
	}
	bfs(adj,s,0);
	bfs(adj,t,1);
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(!adm[i][j])
			{
				//cout << i << " : " << dist[0][i] << " " << dist[1][i] << " and " << j << " : " << dist[0][j] << " " << dist[1][j] << endl;
				if(dist[0][i]+dist[1][j]+1 >= dist[0][t] && dist[1][i]+dist[0][j]+1 >= dist[0][t])
					c++;
			}
		}
	}
	cout << c << endl;
	return 0;
}
