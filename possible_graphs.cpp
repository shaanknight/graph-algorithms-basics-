#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define md (ll)(1e9+7)
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second

ll ncr[1002][1002],mrk[1002],brk[1002],f[1002],n,dt,i,j,gh,ans,inv[100],mn,mx,mid,cal[1002][1002];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for(i=1;i<=1000;++i)
	{
		ncr[i][0]=ncr[i][i]=1;
		for(j=1;j<i;++j)
			ncr[i][j]=(ncr[i-1][j]+ncr[i-1][j-1])%md;
	}

	f[0]=1;
	for(i=1;i<=1000;++i)
		f[i]=(f[i-1]*i)%md;

	cin >> n;
	
	dt=(md-(md/2))%md;
	inv[1]=1;
	for(i=2;i<=10;++i)
	{
		inv[i]=(md-((md/i)*inv[md%i])%md)%md;
		//cout << inv[i] << endl;
	}

	for(i=1;i<=n-3 && brk[i]==0 && n-2-i>=1;++i)
	{
		brk[i]=brk[n-2-i]=1;
		gh=(ncr[n][2]*((ncr[n-2][i]*((f[i]*f[n-2-i])%md))%md))%md;	
		if(n-2-i==i)
			gh=(gh*inv[2])%md;
		//cout << "first : " << gh << endl;
		ans=(ans+gh)%md;
	}

	for(i=1;i<=n-4;++i)
	{
		for(j=1;j<=n-3-i;++j)
		{
			mn=min({i,j,n-2-i-j});
			mx=max({i,j,n-2-i-j});
			mid=i^j^mn^mx^(n-2-i-j);
			if(cal[mn][mx]==1)
				continue;
			cal[mn][mx]=1;
			gh=(ncr[n][2]*((ncr[n-2][i]*((ncr[n-2-i][j]*((f[i]*((f[j]*f[n-2-i-j])%md))%md))%md))%md))%md;
			if(mn==mx)
				gh=(gh*inv[6])%md;
			else if(mn==mid || mx==mid)
				gh=(gh*inv[2])%md;
			//cout << "middle : " << gh << endl;
			ans=(ans+gh)%md;
		}
	}


	for(i=2;i<=n-3 && mrk[i]==0 && n-1-i>=2;++i)
	{
		mrk[i]=mrk[n-i-1]=1;
		gh=(n*((ncr[n-1][i]*((f[i]*f[n-1-i])%md))%md))%md;
		if((n-1-i)==i)
			gh=(gh*inv[8])%md;
		else
			gh=(gh*inv[4])%md;
		//if(gh<0)
		//{
			//cout << i << " " << gh << endl;
			//return 0;
		//}
		//cout << "second : " << gh << endl;
		ans=(ans+gh)%md;
	}

	cout << ans << "\n";
	return 0;
}


