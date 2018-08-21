#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second


ll ind[200005],mrk[200005],lv[200005];
vector<ll> adj[200005];

void dfs(ll u,ll p,ll l)
{
	lv[u]=l;
	for(ll i=0;i<adj[u].size();i++)
	{
		if(adj[u][i]!=p)
			dfs(adj[u][i],u,l+1);
	}
}

class cmp
{
	public:
		bool operator()(pi& n1,pi& n2)
		{
			if(n1.ss%2==1 && n2.ss%2==0)
				return true;
			else if(n1.ss%2==0 && n2.ss%2==1)
				return false;
			else if(lv[n1.ff]<lv[n2.ff])
				return true;
			else
				return false;
		}
};


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n,i,u,p,j;

	cin >> n;
	for(i=1;i<=n;i++)
	{
		cin >> u;
		if(u!=0)
		{
			adj[u].pb(i);
			adj[i].pb(u);
			ind[u]++;
			ind[i]++;
		}
		else
			p=i;
	}

	if(n%2==0)
	{
		cout << "NO" << endl;
		return 0;
	}
	
	cout << "YES" << endl;

	dfs(p,0,0);
	
	priority_queue<pi,vector<pi>,cmp> pq;

	for(i=1;i<=n;i++)
		pq.push({i,ind[i]});

	while(!pq.empty())
	{
		u=pq.top().ff;
		pq.pop();
		//cout << u << endl;
		if(!mrk[u] && ind[u]%2==0)
		{
			cout << u << endl;
			mrk[u]=1;
			for(i=0;i<adj[u].size();i++)
			{
				j=adj[u][i];
				if(!mrk[j])
				{
					ind[j]--;
					pq.push({j,ind[j]});
				}
			}
		}
	}

	return 0;
}
						


