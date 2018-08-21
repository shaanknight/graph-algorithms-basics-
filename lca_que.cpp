#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back

ll srt[100009],n,t[200009][18],s[200009][18],lv[100009],lg[1000009],tc,h;
vector<ll> adj[100009];

ll dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	t[h][0]=l;
	s[h++][0]=u;
	lv[u]=l;
	ll c=1;
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
	return c; 
}

ll lca(ll u,ll v)
{
	ll l=min(srt[u],srt[v]);
	ll r=max(srt[u],srt[v]);
	ll j=lg[r-l+1];
	if(t[l][j] <= t[r-(1<<j)+1][j])
		return s[l][j];
	else
		return s[r-(1<<j)+1][j];
}

ll dist(ll u,ll v)
{
	return lv[u]+lv[v]-2*lv[lca(u,v)];
}

ll querry(ll u,ll v,ll x)
{
	return 1+(dist(u,x)+dist(v,x)-dist(u,lca(u,v))-dist(v,lca(u,v)))/2;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll m,i,u,v,j,tg,q,x,y,z;
	cin >> n >> q;
	for(i=2;i<=n;i++)
	{
		cin >> u;
		adj[u].pb(i);
		adj[i].pb(u);
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

	while(q--)
	{
		cin >> x >> y >> z;
		cout << max({querry(x,y,z),querry(x,z,y),querry(z,y,x)}) << endl;
	}

	return 0;
}
