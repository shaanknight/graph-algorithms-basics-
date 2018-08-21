#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define inf (ll)(1e18)
#define md (ll)(1e9+7)
#define pi pair<ll,ll>
#define ff first
#define ss second

ll kv[100005],mrk[100005],pr[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n,m,i,u,v,w,c,j,ans=0;
	vector<pi> adj[100005];
	cin >> n >> m;
	for(i=1;i<=m;i++)
	{
		cin >> u >> v >> w;
		adj[u].pb(pi(w,v));
		adj[v].pb(pi(w,u));
	}
	priority_queue< pi,vector<pi>,greater<pi> > pq;
	for(i=1;i<=n;i++)
		kv[i]=inf;
	kv[1]=0;
	pq.push(pi(kv[1],1));
	while(!pq.empty())
	{
		//cout << pq.top().ss << endl;
		c=pq.top().ff;
		u=pq.top().ss;
		pq.pop();
		if(!mrk[u])
		{
			if(u!=1)
			cout << pr[u] << " " << u << endl;
			ans+=c;
			mrk[u]=1;
			for(i=0;i<adj[u].size();i++)
			{
				j=adj[u][i].ss;
				//cout << "in " << j << endl;
				if(!mrk[j])
				{
					c=adj[u][i].ff;
					if(kv[j]>c)
					{
						kv[j]=c;
						pr[j]=u;
						pq.push(pi(kv[j],j));
						//cout << "added : " << j << " " << kv[j] << endl;
					}
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}


