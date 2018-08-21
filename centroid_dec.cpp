#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second
#define XV (ll)(1e5+9)

ll lv[XV],sz[XV],pr[XV];
vector<ll> adj[XV];
vector<ll> tmp[XV];

ll sizespecify(ll u,ll p)
{
	ll c=1;
	sz[u]=1;
	for(ll i=0;i<tmp[u].size();i++)
	{
		ll j=tmp[u][i];
		if(j!=p)
		{
			c+=sizespecify(j,u);
			sz[u]+=sz[j];
		}
	}
	return c;
}

ll getcentroid(ll u,ll p,ll s)
{
	for(ll i=0;i<tmp[u].size();i++)
	{
		ll j=tmp[u][i];	
		if(j!=p && sz[j]>s/2)
			return getcentroid(j,u,s);
	}
	return u;
}

void decompose(ll u, ll p)
{
	//cout << "checkseg" << endl;
	ll cs = sizespecify(u,p);
	ll cnt = getcentroid(u,p,cs);
	pr[cnt]=p;
	lv[cnt]=lv[p]+1;
	for(ll i=0;i<tmp[cnt].size();i++)
	{
		ll j=tmp[cnt][i];
		for(ll k=0;k<tmp[j].size();k++)
		{
			if(tmp[j][k]==cnt)
				tmp[j].erase(tmp[j].begin()+k);
		}
		decompose(j,cnt);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n,u,v,i;

	cin >> n;
	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
		tmp[u].pb(v);
		tmp[v].pb(u);
	}

	decompose(1,0);	
	for(i=1;i<=n;i++)
		cout << (char)(lv[i]+64) << " ";

	cout << endl;
	return 0;

}
