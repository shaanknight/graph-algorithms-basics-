#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second



void dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	t[h][0]=l;
	s[h++][0]=u;
	if(p!=0)
		mat[u][0]=val[p];
	else
		mat[u][0]=val[u];
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

	cin >> n >> q;
	for(i=1;i<=n;i++)
		cin >> val[i];
	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
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

	for(j=1;(1<<j)<n;j++)
	{
		for(i=1;i<=n;i++)
			mat[i][j]=min(mat[i][j-1],mat[mat[i][j-1]][j-1]);
	}

	while(q--)
	{
		cin >> u >> v;
		lca=querry(min(srt[u],srt[v]),max(srt[u],srt[v]));
		



