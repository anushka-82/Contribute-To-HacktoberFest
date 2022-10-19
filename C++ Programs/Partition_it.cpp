#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
  #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif
  
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int t;
  cin >> t;

  while(t--) {
    int n, k;
    cin >> n >> k;
    vector<int> d(n+1);
    iota(d.begin(), d.end(), 0);
    function<int(int)> top = 
      [&] (int i) -> int {
        if(d[i] == i) return i;
        return d[i] = top(d[i]);
      };
    for(int i=2;i<=n/2;i++) {
      if(d[i] != i) continue;
      for(int j=1;i*j<=n;j++) {
        d[top(j*i)] = top(d[i]);
      }
    }
    for(int i=1;i<=n;i++) {
      d[i] = top(i);
    }
    vector<int> c, p;
    for(int i=1;i<=n;i++) {
      if(d[i] == d[2]) c.push_back(i);
      else p.push_back(i);
    }
    if(k >= c.size() || k <= p.size()) {
      cout << "Yes\n";
      if(k >= c.size()) {
        for(auto i:c) cout << i << " ";
        k -= c.size();
      }
      for(int i=0;i<k;i++) cout << p[i] << " ";
    } else cout << "No";
    cout << '\n';
  }
}
