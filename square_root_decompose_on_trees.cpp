#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back

ll srt[100009],ds[1000009],fin[100009],t[200009][18],s[200009][18],lv[100009],lg[1000009],tc,h;
vector<ll> adj[100009];
vector<ll> pob;
queue<ll> q;

void bfs(ll n)
{
	for(ll i=1;i<=n;i++)
	{
		if(ds[i]==0)
			q.push(i);
	}
	while(!q.empty())
	{
		ll u=q.front();
		q.pop();
		for(ll i=0;i<adj[u].size();i++)
		{
			ll v=adj[u][i];
			if(ds[v]>ds[u]+1)
			{
				ds[v]=ds[u]+1;
				q.push(v);
			}
		}
	}
}

void dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	t[h][0]=l;
	s[h++][0]=u;
	lv[u]=l;
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
	fin[u]=tc++;
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
	
	ll n,m,i,u,v,j,tg,q;
	cin >> n >> q;
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
		ds[i]=1e16;
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
	ll sq=sqrt(q)+1,ch,lca;
	ds[1]=0;
	bfs(n);
	i=0;
	while(q--)
	{
		i++;
		if(i%sq==0)
		{
			bfs(n);
			pob.clear();
		}
		cin >> ch >> v;
		if(ch==1)
		{
			ds[v]=0;
			pob.pb(v);
		}
		else
		{
			for(j=0;j<pob.size();j++)
			{
				u=pob[j];
				lca=querry(min(srt[u],srt[v]),max(srt[u],srt[v]));
				ds[v]=min(ds[v],lv[v]+lv[u]-2*lv[lca]);
			}
			cout << ds[v] << endl;
		}
	}
	return 0;
}
