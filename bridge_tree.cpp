#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second
const int M=3e5+6;

int lv[M],prs[M],bridge[M],vist[M],vist2[M],cmpno;
vector<int> adj[M];
vector<int> tree[M];
vector<int> ind[M];
queue<int> q[M];

int bridge_marker(int u,int ed,int p,int lev)
{
	vist[u]=1;
	lv[u]=lev;
	int v,j,min_levl=lev;
	for(int i=0;i<adj[u].size();i++)
	{
		v=adj[u][i];
		j=ind[u][i];
		if(!vist[v])
			min_levl=min(min_levl,bridge_marker(v,j,u,lev+1));
		else if(v!=p)
			min_levl=min(min_levl,lv[v]);
	}
	if(min_levl==lev)
		bridge[ed]=1;
	return min_levl;
}

void bridging(int u,int curr_comp)
{
	prs[u]=curr_comp;
	q[curr_comp].push(u);
	int i,v,j;
	while(!q[curr_comp].empty())
	{
		u=q[curr_comp].front();
		q[curr_comp].pop();
		for(i=0;i<adj[u].size();i++)
		{
			v=adj[u][i];
			j=ind[u][i];
			if(vist2[v]) continue;
			if(bridge[j])
			{
				cmpno++;
				tree[curr_comp].pb(cmpno);
				tree[cmpno].pb(curr_comp);
				bridging(v,cmpno);
			}
			else
			{
				prs[v]=curr_comp;
				q[curr_comp].push(v);
				vist2[v]=1;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	return 0;
}
