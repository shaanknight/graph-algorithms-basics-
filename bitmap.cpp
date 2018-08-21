#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pp pop_back
#define md (ll)(1e9+7)
#define inf (ll)(1e18)

vector<ll> adj[1000000];
ll k,n,m,t,mrk[1000000],dist[1000000],col[1000000];
string str;

void connect(ll u)
{
	if(u-m>=1)
		adj[u].pb(u-m);
	if(u+m<k)
		adj[u].pb(u+m);
	if(u%m==1 && m>1)
		adj[u].pb(u+1);
	else if(u%m==0 && m>1)
		adj[u].pb(u-1);
	else if(m>1)
	{
		adj[u].pb(u-1);
		adj[u].pb(u+1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll u,v,c=0,i,j;
	queue<ll> q;
	cin >> t;
	while(t--)
	{
		cin >> n >> m;
		k=1;
		for(i=1;i<=n;i++)
		{
			cin >> str;
			for(j=0;j<m;j++)
				col[k++]=(ll)(str[j]-'0');
		}
		//cout << k << endl;
		for(i=1;i<k;i++)
		{
			connect(i);
			if(col[i]==1)
			{
				q.push(i);
				dist[i]=0;
			}
			else
				dist[i]=inf;
			//cout << col[i] << endl;
		}
		while(!q.empty())
		{
			u=q.front();
			q.pop();
			if(!mrk[u])
			{
				mrk[u]=1;
				for(i=0;i<adj[u].size();i++)
				{
					v=adj[u][i];
					if(!mrk[v] && v>=1 && v<k && dist[v]>dist[u]+1)
					{
						dist[v]=dist[u]+1;
						q.push(v);
					}
				}
			}
		}
		c=1;
		for(i=1;i<k;i++,c++)
		{
			cout << dist[i] << " ";
			if(c%m==0)
				cout << endl;
			dist[i]=0;
			mrk[i]=0;
			col[i]=0;
			while(adj[i].size()!=0)
				adj[i].pp();
		}
	}
	return 0;
}
		



		

