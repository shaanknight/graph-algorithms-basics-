#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define x first
#define y second
#define inf (ll)(2e18)

const int M=4e5+6;
pi ar[M];
vector<pi> vec[M];

ll dist(pi a,pi b)
{
	return ((b.y-a.y)*(b.y-a.y))+((b.x-a.x)*(b.x-a.x));
}

ll closepair(int l,int h,int p)
{
	if(l==h)
	{
		vec[p].pb(ar[l]);
		return inf;
	}
	if(l==h-1)
	{
		if(ar[l].y>=ar[h].y)
		{
			vec[p].pb(ar[l]);
			vec[p].pb(ar[h]);
		}
		else
		{
			vec[p].pb(ar[h]);
			vec[p].pb(ar[l]);
		}
		return dist(ar[l],ar[h]);
	}
	
	int i,j,c=0;
	int mid = l+(h-l)/2;
	ll d1=closepair(l,mid,2*p+1);
	ll d2=closepair(mid+1,h,2*p+2);
	
	ll d=min(d1,d2);

	for(i=0,j=0;i<vec[2*p+1].size() && j<vec[2*p+2].size();)
	{
		if(vec[2*p+1][i].y>=vec[2*p+2][j].y)
		{
			if(abs(vec[2*p+1][i].x-ar[mid].x)<=d)
				vec[p].pb(vec[2*p+1][i]);
			i++;
		}
		else
		{
			if(abs(vec[2*p+2][j].x-ar[mid].x)<=d)
				vec[p].pb(vec[2*p+2][j]);
			j++;
		}
	}

	while(i<vec[2*p+1].size())
	{
		if(abs(vec[2*p+1][i].x-ar[mid].x)<=d)
			vec[p].pb(vec[2*p+1][i]);
		i++;
	}	

	while(j<vec[2*p+2].size())
	{
		if(abs(vec[2*p+2][j].x-ar[mid].x)<=d)
			vec[p].pb(vec[2*p+2][j]);
		j++;
	}

	for(i=0;i<vec[p].size();++i)
	{
		c=0;
		for(j=i+1;j<vec[p].size() && c<=16;++j,c++)
			d=min(d,dist(vec[p][i],vec[p][j]));
	}

	return d;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	ll i,s=0,n,t;
	cin >> n;

	for(i=1;i<=n;++i)
	{
		cin >> t;
		s=s+t;
		ar[i]=pi(i,s);
	}

	sort(ar+1,ar+1+n);

	cout << closepair(1,n,0) << "\n";
	return 0;
}	
