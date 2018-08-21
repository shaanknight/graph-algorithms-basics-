#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back

ll srt[100009],n,sz[100009],id1[200009],t[200009][18],s[200009][18],lv[100009],lg[1000009],tc,h;
vector<ll> adj[100009];
vector<ll> lev[100009];


ll dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	id1[srt[u]]=u;
	lev[l].pb(srt[u]);
	t[h][0]=l;
	s[h++][0]=u;
	lv[u]=l;
	ll c=1;
	for(ll i=0;i<adj[u].size();i++)
	{
		ll j=adj[u][i];
		if(j!=p)
		{
			c+=dfs(j,u,l+1);
			t[h][0]=l;
			s[h++][0]=u;
		}
	}
	tc++;
	sz[u]=c;
	return c; 
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

	ll m,i,u,v,j,tg,q;
	cin >> n;
	for(i=1;i<n;i++)
	{
		cin >> u >> v;
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
	cin >> q;
	while(q--)
	{
		cin >> u >> v;
		if(u==v)
			cout << n << endl;
		else
		{
			ll lca=querry(min(srt[u],srt[v]),max(srt[u],srt[v]));
			ll dist=lv[u]+lv[v]-2*lv[lca];
			if(dist%2==1)
				cout << 0 << endl;
			else
			{
				if(lv[u]!=lv[v])
				{
					ll sr=lv[lca]+(max(lv[u],lv[v])-min(lv[u],lv[v]))/2;
					if(lv[u]>lv[v])
						i=u;
					else
						i=v;
					auto it=upper_bound(lev[sr].begin(),lev[sr].end(),srt[i]);
					it--;
					ll ans=sz[id1[*it]];
					sr++;
					auto pt=upper_bound(lev[sr].begin(),lev[sr].end(),srt[i]);
					pt--;
					ans-=sz[id1[*pt]];
					cout << ans << endl;
				}
				else
				{
					ll sr=lv[lca]+1;
					auto it=upper_bound(lev[sr].begin(),lev[sr].end(),srt[u]);
					it--;
					ll ans=n-sz[id1[*it]];
					auto pt=upper_bound(lev[sr].begin(),lev[sr].end(),srt[v]);
					pt--;
					ans-=sz[id1[*pt]];
					cout << ans << endl;
				}
			}
		}

	}
	return 0;
}

