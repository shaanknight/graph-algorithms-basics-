#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pi pair<ll,ll>

ll srt[100009],t[200009][18],s[200009][18],lg[1000009],cost[100009],ls[100009],tc,h;
vector<ll> adj[100009];
vector<ll> ind[100009];

void dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	t[h][0]=l;
	s[h++][0]=u;
	for(ll i=0;i<adj[u].size();i++)
	{
		ll j=adj[u][i];
		if(j!=p)
		{
			dfs(j,u,l+1);
			t[h][0]=l;
			s[h++][0]=u;
		}
	}
	tc++;
}

ll trv(ll u,ll p)
{
	for(ll i=0;i<adj[u].size();i++)
	{
		ll j=adj[u][i];
		if(j!=p)
		{
			ll r=trv(j,u);
			cost[ind[u][i]]=r;
			ls[u]+=r;
		}
	}
	return ls[u];
}

ll querry(ll l,ll r)
{
	ll j=lg[r-l+1];
	if(t[l][j] <= t[r-(1<<j)+1][j])
		return s[l][j];
	else
		return s[r-(1<<j)+1][j];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n,q,u,v,i,tg,j;
	cin >> n;
	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		ind[u].pb(i);
		ind[v].pb(i);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	tg=1;
	j=0;
	for(i=1;i<=1000000;i++)
	{
		if(tg==i)
		{
			lg[i]=j;
			tg*=2;
			j++;
		}
		else
			lg[i]=lg[i-1];
	}	
	dfs(1,0,0);
	for(j=1;(1<<j)<=h;j++)
	{
		for(i=0;(i+(1<<j)-1)<h;i++)
		{
			if(t[i][j-1] < t[i+(1<<(j-1))][j-1])
			{
				t[i][j]=t[i][j-1];
				s[i][j]=s[i][j-1];
			}
			else
			{
				t[i][j]=t[i+(1<<(j-1))][j-1];
				s[i][j]=s[i+(1<<(j-1))][j-1];
			}
		}
	}
	ll lca;
	cin >> q;
	while(q--)
	{
		cin >> u >> v;
		lca=querry(min(srt[u],srt[v]),max(srt[u],srt[v]));
		ls[u]+=1;
		ls[v]+=1;
		ls[lca]-=2;
	}
	trv(1,0);
	for(i=1;i<n;i++)
		cout << cost[i] << " ";
	cout << endl;
	return 0;
}

