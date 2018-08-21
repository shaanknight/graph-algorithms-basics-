#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define pi pair<ll,ll>
#define ff first
#define ss second

long double tim[200009];
ll mrk[200009],srt[200009],n,t[400009][21],s[400009][21],lv[200009],lg[800009],tc,h,w,cno,ptr,chead[200009],cind[200009],sup[800009],bup[800009],tree[800009],pr[200009],sz[200009],dsr[200009],ar[200009],pos[200009];
vector<ll> adj[200009];
vector<ll> ind[200009];

struct node
{
	ll up;
	ll vp;
	long double tp;
	long double sp;
};

struct cmp
{
	bool operator()(node& l,node& r)
	{
		return l.tp > r.tp;
	}
};

void dfs(ll u,ll p,ll l)
{
	srt[u]=tc++;
	t[h][0]=l;
	s[h++][0]=u;
	lv[u]=l;
	sz[u]=1;
	pr[u]=p;
	for(ll i=0;i<adj[u].size();i++)
	{
		ll j=adj[u][i];
		if(j!=p)
		{
			dsr[j]=dsr[u]+ind[u][i];
			dfs(j,u,l+1);
			sz[u]+=sz[j];
			t[h][0]=l;
			s[h++][0]=u;
		}
	}
	tc++;
}

ll findlca(ll u,ll v)
{
	ll l=min(srt[u],srt[v]);
	ll r=max(srt[u],srt[v]);
	ll j=lg[r-l+1];
	if(t[l][j] <= t[r-(1<<j)+1][j])
		return s[l][j];
	else
		return s[r-(1<<j)+1][j];
}

long double dist(ll u,ll v)
{
	return dsr[u]+dsr[v]-2*dsr[findlca(u,v)];
}

void hld(ll u,ll p)
{
	if(chead[cno]==0) chead[cno]=u;
	cind[u]=cno;
	ar[ptr++]=u;
	pos[u]=ptr-1;

	ll sc=-1,i;
	for(i=0;i<adj[u].size();i++)
		if(adj[u][i]!=p && (sc==-1 || sz[sc] < sz[adj[u][i]]))
			sc=adj[u][i];

	if (sc!=-1) hld(sc,u);

	for(i=0;i<adj[u].size();i++)
		if(adj[u][i]!=p && adj[u][i]!=sc)
		{
			cno++;
			hld(adj[u][i],u);
		}
}

ll minlev(ll u,ll v)
{
	if(tree[u]==tree[v])
	{
		if(lv[sup[u]]>lv[sup[v]]) return sup[u];
		else return sup[v];
	}
	else if(tree[u]<tree[v]) return sup[u];
	else return sup[v];
}

ll maxlev(ll u,ll v)
{
	if(tree[u]==tree[v])
	{
		if(lv[bup[u]]<lv[bup[v]]) return bup[u];
		else return bup[v];
	}
	else if(tree[u]<tree[v]) return bup[u];
	else return bup[v];
}

void build(ll l,ll h,ll p)
{
	if(l==h)
	{
		tree[p]=0;
		sup[p]=ar[l];
		bup[p]=ar[l];
		return;
	}
	ll m=l+(h-l)/2;
	build(l,m,2*p+1);
	build(m+1,h,2*p+2);
	tree[p]=min(tree[2*p+1],tree[2*p+2]);
	sup[p]=minlev(2*p+1,2*p+2);
	bup[p]=maxlev(2*p+1,2*p+2);
}

void update(ll l,ll h,ll tg,ll p)
{
	if(l==h)
	{
		tree[p]=1;
		sup[p]=ar[l];
		bup[p]=ar[l];
		return;
	}
	ll m=l+(h-l)/2;
	if(tg<=m)
		update(l,m,tg,2*p+1);
	else
		update(m+1,h,tg,2*p+2);
	tree[p]=min(tree[2*p+1],tree[2*p+2]);
	sup[p]=minlev(2*p+1,2*p+2);
	bup[p]=maxlev(2*p+1,2*p+2);
}

pi query(ll l,ll h,ll ql,ll qh,ll p)
{
	if(l>=ql && h<=qh)
	{
		if(w==1) return {tree[p],sup[p]};
		else return {tree[p],bup[p]};
	}
	else if(l>qh || h<ql)
		return {1e18,0};
	ll m=l+(h-l)/2;
	pi lq=query(l,m,ql,qh,2*p+1);
	pi rq=query(m+1,h,ql,qh,2*p+2);
	if(lq.ff<rq.ff) return lq;
	if(lq.ff>rq.ff) return rq;
	if(lq.ff==rq.ff)
	{
		if(w==1)
		{
			if(lv[lq.ss]>lv[rq.ss]) return lq;
			else return rq;
		}
		else
		{
			if(lv[lq.ss]>lv[rq.ss]) return rq;
			else return lq;
		}
	}
}

ll findunmarked(ll u,ll v)
{
	pi q;
	ll lca = findlca(u,v);
	ll uc,vc,ans=0,a=u,b=v;
	if(lca!=u)
	{
		w=1;
		lv[0]=0;
		vc=cind[lca];
		while(ans==0)
		{
			uc=cind[u];
			if(uc==vc)
			{
				q=query(0,ptr-1,pos[lca],pos[u],0);
				if(q.ff==0)
					ans=q.ss;
				break;
			}
			q=query(0,ptr-1,pos[chead[uc]],pos[u],0);
			if(q.ff==0)
				ans=q.ss;
			u=pr[chead[uc]];
		}
		if(ans!=0) return ans;
	}
	if(lca!=v)
	{
		w=2;
		lv[0]=19999999;
		vc=cind[lca];
		while(1)
		{
			uc=cind[v];
			if(uc==vc)
			{
				q=query(0,ptr-1,pos[lca],pos[v],0);
				if(q.ff==0)
					ans=q.ss;
				break;
			}
			q=query(0,ptr-1,pos[chead[uc]],pos[v],0);
			if(q.ff==0)
				ans=q.ss;
			//if(a==1 && b==5)
			//	cout << q.ff << " " << q.ss << endl;
			v=pr[chead[uc]];
		}
	}
	//if(ans==0 && mrk[lca]==0) return lca; 
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll tg=1,i,j=0,q,u,v,w,m,f,g;
	long double ti,si;
	for(i=1;i<=800000;i++)
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

	cin >> q;
	while(q--)
	{
		ptr=h=cno=tc=g=0;
		for(i=1;i<=n;i++)
		{
			tim[i]=-1;
			adj[i].clear();
			ind[i].clear();
			chead[i]=0;
			ar[i]=mrk[i]=0;
		}

		cin >> n;

		for(i=1;i<n;i++)
		{
			cin >> u >> v >> w;
			adj[u].pb(v);
			adj[v].pb(u);
			ind[u].pb(w);
			ind[v].pb(w);
		}
		dfs(1,0,0);

		//for(i=1;i<=n;i++)
		//	cout << "dsr " << i << " " << dsr[i] << endl;

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

		hld(1,0);
		build(0,ptr-1,0);

		priority_queue<node,vector<node>,cmp > pq;
		cin >> m;
		for(i=1;i<=m;i++)
		{
			cin >> u >> v >> ti >> si;
			pq.push({u,v,ti,si});
		}

		//cout << "debugging" << endl << endl;
		while(!pq.empty())
		{
			node nd=pq.top();
			pq.pop();
			u=nd.up;
			v=nd.vp;
			ti=nd.tp;
			si=nd.sp;

			if(mrk[u]==0)
			{
				g++;
				tim[u]=ti;
				mrk[u]=1;
				update(0,ptr-1,pos[u],0);
			}
			
			tim[u]=min(ti,tim[u]);

			f = findunmarked(u,v);
			//cout << u << " " << ti << " " << f << " " << dist(u,f) << " " << ti+dist(u,f)/si << endl;
			if(f)
				pq.push({f,v,ti+(dist(u,f)/si),si});
		}

		for(i=1;i<=n;i++)
			cout << setprecision(27) << ((tim[i]>=1)?tim[i]:-1) << endl;
	}
	return 0;
}


