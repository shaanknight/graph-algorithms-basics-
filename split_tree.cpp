#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second

vector<ll> adj[100005];
vector<ll> ind[100005];
vector<ll> ans;
ll d,mrk[100005],pr[100005],ed[100005],gur[100005],dist[100005]; 

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n,k,i,t,u,v,p,c=0;

	cin >> n >> k >> d;
	for(i=1;i<=k;i++)
	{
		cin >> t;
		mrk[t]++;
		gur[t]=1;
		p=t;
	}

	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		ind[u].pb(i);
		ind[v].pb(i);
	}
	
	if(k==1)
	{
		cout << 0 << endl;
		return 0;
	}
	if(d==0)
	{
		cout << n-1 << endl;
		for(i=1;i<n;i++)
			cout << i << " ";
		cout << endl;
		return 0;
	}

	queue<ll> q;
	q.push(p);
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		if(mrk[u])
		{
			dist[u]=0;
			if(c!=0)
				trv(u);
			c++;
		}
		for(i=0;i<adj[u].size();i++)
			if(pr[u]!=adj[u][i])
			{
				q.push(adj[u][i]);
				pr[adj[u][i]]=u;
				dist[adj[u][i]]=dist[u]+1;
				ed[adj[u][i]]=ind[u][i];
			}
	}
		
	cout << c-1 << endl;
	for(auto it:ans)
		cout << it << " ";
	cout << endl;
	return 0;
}	


