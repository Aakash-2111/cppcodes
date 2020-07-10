#include<bits/stdc++.h>
using namespace std;
typedef long long int ll; 
struct node{
  ll sum,psum,ssum,mxsum;
};
ll maxn=500000;
vector<node> segt(2*maxn);
node merge(node &a,node &b)
{
  node ret;
  ret.sum=a.sum+b.sum;
  ret.psum=max(a.psum,a.sum+b.psum);
  ret.ssum=max(a.ssum+b.sum,b.ssum);
  ret.mxsum=max(max(a.mxsum,b.mxsum),a.ssum+b.psum);
  return ret;
}
void build(vector<ll> &vec,ll s,ll e,ll i)
{
  if(s==e)
  {
    segt[i].sum=vec[s];  segt[i].psum=vec[s];
    segt[i].ssum=vec[s];  segt[i].mxsum=vec[s];
    return ;
  }
  ll mid=(s+e)/2,c=(2*i)+1;
  build(vec,s,mid,c);
  build(vec,mid+1,e,c+1);
  segt[i]=merge(segt[c],segt[c+1]);
  return ;
}
void update(vector<ll> &vec,ll s,ll e,ll i,ll id,ll v)
{
  if(s==e)
  {
    segt[i].sum=v;  segt[i].psum=v;
    segt[i].ssum=v;  segt[i].mxsum=v;
    return ;
  }
  ll mid=(s+e)/2,c=(2*i)+1;
  if(id<=mid) update(vec,s,mid,c,id,v);
  else update(vec,mid+1,e,c+1,id,v);
  segt[i]=merge(segt[c],segt[c+1]);
  return ;
}
node query(vector<ll> &vec,ll s,ll e,ll i,ll l,ll r)
{
  node ans;
  ans.sum=ans.psum=ans.ssum=ans.mxsum=LLONG_MIN;
  if(s>r || e<l) return ans;
  if(l<=s && r>=e) return segt[i];
  ll mid=(s+e)/2,c=(2*i)+1;
  if(l>mid) return query(vec,mid+1,e,c+1,l,r);
  if(r<=mid)  return query(vec,s,mid,c,l,r);
  node left=query(vec,s,mid,c,l,r);
  node right=query(vec,mid+1,e,c+1,l,r);
  ans=merge(left,right);
  return ans;
}
int main()
{   ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll t; cin>>t;
    while(t--)
    {
      ll n;
      cin>>n;
      vector<ll> vec(n);
      for(ll i=0;i<n;i++) cin>>vec[i];
      build(vec,0,n-1,0);
      node r=query(vec,0,n-1,0,0,n-1);
      cout<<r.mxsum<<" ";
      for(ll i=0;i<n-1;i++)
      {
        node left=query(vec,0,n-1,0,0,i);
        node right=query(vec,0,n-1,0,i+1,n-1);
        ll ans=max(max(left.mxsum,right.mxsum),left.psum+right.ssum);
        cout<<ans<<" ";
      }
      cout<<"\n";
    }
    return 0;
}