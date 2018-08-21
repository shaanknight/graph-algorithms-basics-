#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define inf (ll)(1e18)
#define md (ll)(1e9+7)
#define pi pair<ll,ll>
#define pii pair<ll,pi>
#define ff first
#define ss second

ll n,m,i,u,v,w,p,g,j,val[100005];
vector< pair<ll,pi> > edges;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for(i=0;i<m;i++)
	{
		cin >> u >> v >> w;
		edges.pb(pii(w,pi(u,v)));
	}
	cin >> p;
	for(i=1;i<=n;i++)
		val[i]=1e18;
	g = 1;
	val[p]=0;
	for(i=1;i<=n && g;i++)
	{
		g = 0;
		for(j=0;j<m;j++)
		{
			w = edges[j].ff;
			u = edges[j].ss.ff;
			v = edges[j].ss.ss;
			if(val[v]>val[u]+w)
			{
				g++;
				val[v]=val[u]+w;
			}
		}
		if(i == n && g)
		{
			cout << "negative cycle exists" << endl;
			return 0;
		}
	}
	for(i=1;i<=n;i++)
		cout << val[i] << " ";
	cout << endl;
	return 0;
}
