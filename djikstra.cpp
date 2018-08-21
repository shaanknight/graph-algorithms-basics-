#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pi pair<ll,ll>

vector<pi> adj[300009];
vector<ll> ind[300009];
ll wgt[300009],far[300009],sto[300009],pr[300009],mrk[300009],ans;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n,m,i,j,u,v,w,s,k;
	vector<pi> adj[300009];
	cin >> n >> m;
	for(i=1;i<=m;i++)
	{
		cin >> u >> v >> w;
		adj[u].pb(pi(w,v));
		adj[v].pb(pi(w,u));
		ind[u].pb(i);
		ind[v].pb(i);
		wgt[i]=w;
	}
	for(i=1;i<=n;i++)
	{
		far[i]=1e18;
		sto[i]=1e18;
	}
	cin >> s;
	far[s]=0;
	priority_queue< pi,vector<pi>,greater<pi> > pq;
	pq.push(pi(0,s));
	while(!pq.empty())
	{
		u=pq.top().second;
		pq.pop();
		if(!mrk[u])
		{
			mrk[u]=1;
			for(i=0;i<adj[u].size();i++)
			{
				j=adj[u][i].second;
				k=adj[u][i].first;
				if(!mrk[j])
				{
					if(far[j]>far[u]+k || (far[j]==far[u]+k && sto[j]>k))
			 		{
						far[j]=far[u]+k;
						sto[j]=k;
						pr[j]=ind[u][i];
						pq.push(pi(far[j],j));
					}
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(i!=s)
			ans+=wgt[pr[i]];
	}
	cout << ans << endl;
	for(i=1;i<=n;i++)
	{
		if(i!=s)
			cout << pr[i] << " ";
	}
	cout << endl;
	return 0;
}
