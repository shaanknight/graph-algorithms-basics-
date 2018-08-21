#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define inf (ll)(1e18)
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ppi pair<ll,pi>
#define ff first
#define ss second

ll pr[100005],rnk[100005];

ll find(ll u)
{
	if(pr[u]==u)
		return u;
	return find(pr[u]);
}

ll connect(ll x,ll y)
{
	if(rnk[x]<rnk[y])
		pr[x]=y;
	else if(rnk[x]>rnk[y])
		pr[y]=x;
	else
	{
		pr[x]=y;
		rnk[y]++;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n,m,u,v,i,w,l,c=0,ans=0,set_u,set_v,cost;
	vector<ppi> adj;
	cin >> n >> m;
	for(i=1;i<=n;i++)
	{
		pr[i]=i;
		rnk[i]=1;
	}
	for(i=1;i<=m;i++)
	{
		cin >> u >> v >> w;
		adj.pb(ppi(w,pi(u,v)));
	}
	sort(adj.begin(),adj.end());
	reverse(adj.begin(),adj.end());
	l=adj.size()-1;
	while(c!=n-1)
	{
		cost=adj[l].ff;
		u=(adj[l].ss).ff;
		v=(adj[l].ss).ss;
		set_u=find(u);
		set_v=find(v);
		if(set_u != set_v)
		{
			c++;
			cout << u << " " << v << endl;
			ans+=cost;
			connect(set_u,set_v);
		}
		l--;
	}
	cout << ans << endl;
	return 0;
}


