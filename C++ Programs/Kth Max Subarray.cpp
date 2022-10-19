#include <bits/stdc++.h>
using namespace std;


#ifdef Azizul
#include "debug.cpp"
#else
#define dbg(x...)
#endif

#define   int  long long
#define   ld   long double
#define   pb   push_back
#define   vi   vector<int>
#define   bitcount(x)  (int)__builtin_popcount(x)
#define   Lsb(x)  (int)__builtin_ctzll(x)
#define   fast  ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define   sz(x)  (int)x.size()
#define   all(a) (a).begin(),(a).end()
#define   Yes  cout << "YES\n"
#define   No  cout << "NO\n"
#define   ff   first
#define   ss   second
#define   endl  "\n"
#define   pi   acos(-1.0)
#define   pii  pair<int,int>
#define   lcm(a,b) (a/__gcd(a, b)*b)

const int  mod = 998244353 ;
const int M = 200005 ;
const int inf = 1LL<<40 ;
vector <int> ans, a(M) ;
int n, m;

inline void solve() {
    int n, m;
    cin >> n >> m ;
    vector <int> a(n+5) ;
    for (int i=1;i<=n;++i) cin >> a[i] ;
    vector <int> l(n+5), r(n+5) ;
    stack <int> s;
    s.push(0) ;
    a[0] = a[n+1] = inf ;
    for (int i=1;i<=n;++i) {
        while (a[s.top()] <= a[i]) s.pop() ;
        l[i] = i-s.top() ;
        s.push(i) ;
    }
    while (!s.empty()) s.pop() ;
    s.push(n+1) ;
    for (int i=n;i>=1;i--) {
        while (a[s.top()] < a[i]) s.pop() ;
        r[i] = s.top()-i ;
        s.push(i) ;
    }
    vector <pii> v;
    for (int i=1;i<=n;++i) {
        int ll = l[i], rr = r[i];
        v.push_back({a[i], ll*rr}) ;
    }
    sort(all(v), greater<pii>()) ;
    vector <int> pref(n) ;
    for (int i=0;i<n;++i) {
        pref[i] = v[i].ss ;
        if (i > 0) pref[i] += pref[i-1] ;
    }
    while (m--) {
        int x; cin >> x ;
        int l = 0, r = n-1, ans ;
        while (l <= r) {
            int m = (l+r)>>1;
            if (pref[m] >= x) {
                ans = v[m].ff ;
                r = m-1;
            }
            else l = m+1 ;
        }
        cout << ans << endl;
    }
}

signed main()
{
    fast ;
    int t = 1 ;  cin >> t ;
    while (t--) solve() ;
    return 0 ;
}
