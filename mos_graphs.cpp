#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define pi pair<int,int>
#define pii pair<int,pi>
#define ff first
#define ss second

vector<int> adj[100005];
vector<pii> xdj;
int col[100005],ar[100005],n,h,tc,s,qnt[100005],cnt[100005],srt[100005],fin[100005],uv[100005],k[100005],otp[100005];

bool cmp(pii a,pii b)
{
	pi f=a.ss;
	pi s=b.ss;
	return (f.ff==s.ff) ? (f.ss<s.ss) : (f.ff<s.ff);
}

void add(int p)
{
	if(p>=1 && p<=n)
	{
		cnt[ar[p]]++;
		if(cnt[ar[p]]<=n) qnt[cnt[ar[p]]]++;
	}
}

void remove(int p)
{
	if(p>=1 && p<=n)
	{
		cnt[ar[p]]--;
		if(cnt[ar[p]]<n) qnt[cnt[ar[p]]+1]--;
	}
}

void dfs(int u,int p)
{
	srt[u]=tc++;
	ar[h++]=col[u];
	for(int i=0;i<adj[u].size();i++)
	{
		int j=adj[u][i];
		if(j!=p) dfs(j,u);
	}
	fin[u]=tc-1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int q,i,u,v,cl,cr,j,x,l,r;

	cin >> n >> q;
	for(i=1;i<=n;i++)
		cin >> col[i];

	for(i=1;i<n;i++)
	{
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	tc=h=1;
	dfs(1,0);
	s=ceil(sqrt(n));

	for(i=1;i<=q;i++)
	{
		cin >> uv[i] >> k[i];
		xdj.pb(pii(i,pi(srt[uv[i]]/s+1,fin[uv[i]]/s+1)));
	}

	sort(xdj.begin(),xdj.end(),cmp);
	
	cl=cr=0;
	for(i=0;i<xdj.size();i++)
	{
		j=xdj[i].ff;
		l=srt[uv[j]];
		r=fin[uv[j]];
		while(cl>l) add(--cl);
		while(cl<l) remove(cl++);
		while(cr>r) remove(cr--);
		while(cr<r) add(++cr);
		otp[j]=qnt[k[j]];
	}

	for(i=1;i<=q;i++)
		cout << otp[i] << "\n";

	return 0;
}
