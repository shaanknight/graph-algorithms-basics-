#include<bits/stdc++.h>
using namespace std;
#define pb push_back

int mat[1000005][21],mrk[1000005],lv[1000005],lg[1000005];
vector<int> adj[1000005];

void dfs(int u,int p,int l)
{
	mat[u][0]=p;
	mrk[u]=2;
	lv[u]=l;
	for(int i=0;i<adj[u].size();i++)
	{
		if(adj[u][i]!=p)
			dfs(adj[u][i],u,l+1);
	}
}

int getpr(int u,int n)
{
	if(mrk[mat[u][0]]!=2)
		return u;
	int l=0,m,r=lg[lv[u]-lv[n]];
	int ans;
	while(l<=r)
	{
		m=l+(r-l)/2;
		if(mrk[mat[u][m]]==2 && mrk[mat[u][m+1]]!=2)
		{
			ans=mat[u][m];
			break;
		}
		else if(mrk[mat[u][m+1]]==2)
			l=m+1;
		else if(mrk[mat[u][m]]!=2)
			r=m-1;
	}
	return getpr(ans,n);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n,k,u,v,i,j,tg,p,s,d;

	cin >> n >> k;

	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(n,0,0);

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

	for(j=1;(1<<j)<n;j++)
	{
		for(i=1;i<=n;i++)
			mat[i][j]=mat[mat[i][j-1]][j-1];
	}

	d=n-k-1;
	mrk[n]=1;

	for(i=n-1;i>=1 && d>=0;i--)
	{
		if(mrk[i]==2)
		{
			p=getpr(i,n);
			if(lv[i]-lv[p]+1<=d)
			{
				s=i;
				while(s!=p)
				{
					mrk[s]=1;
					s=mat[s][0];
				}
				mrk[p]=1;
				d-=(lv[i]-lv[p]+1);
			}
		}
	}

	for(i=1;i<=n;i++)
	{
		if(mrk[i]==2)
			cout << i << " ";
	}
	cout << "\n";
	return 0;
}

