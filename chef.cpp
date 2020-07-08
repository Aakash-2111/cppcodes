#include <bits/stdc++.h>
using namespace std;
typedef long long int ll; 
#define fi   first
#define sec  second
ll mod=1000000007;
ll powy(ll a,ll b)
{
    if(b==0) return 1;
    ll c=powy(a,b/2);
    if(b&1) return (c*((c*a)%mod)%mod);
    else return (c*c)%mod;
}
ll fact(ll n)
{
    if(n==1 || n==0) return 1;
    return (n*fact(n-1))%mod; 
}
ll nck(ll n,ll k)
{
    ll p=(fact(n-k)*fact(k))%mod; 
    ll in=powy(p,mod-2); 
    ll ans=(fact(n)*in)%mod;
    return ans;
}
ll i1=0,i2=0;
bool func(ll k,vector<vector<ll> > &vec,ll n,ll m)
{
    ll tm=1;
    for(ll i=0;i<m;i++) tm=tm*2;
    vector<ll> v(tm,-1);
    for(ll i=0;i<n;i++)
    {
        ll mk=1,val=0;
        for(ll j=0;j<m;j++)
        {
            if(vec[i][j]>=k) val=val+mk;
            mk=mk*2;
        }
        v[val]=i;
    }
    for(ll i=0;i<tm;i++)
    {
        for(ll j=0;j<tm;j++)
        {
            if((v[i]!=-1) && (v[j]!=-1) && ((i|j)==tm-1))
            {
                i1=v[i]; i2=v[j];
                return true;
            }
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,m; cin>>n>>m;
    vector<vector<ll> > vec(n,vector<ll> (m));
    for(ll i=0;i<n;i++)
    {
        for(ll j=0;j<m;j++)
            cin>>vec[i][j];
    }
    ll s=0,e=mod;
    while(s<e-1)
    {
        ll mid=(s+e)/2;
        if(func(mid,vec,n,m)) s=mid;
        else e=mid;
    }
    if(func(s,vec,n,m)) s+=1;
    cout<<i1+1<<" "<<i2+1<<endl;
    return 0;
}