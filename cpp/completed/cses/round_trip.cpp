#include <bits/stdc++.h>

using namespace std;



using ll =  long long;
using ull =  unsigned long long;
using vs = vector<string>;
using vl = vector<ll>;
using vul = vector<ull>;
using vvl = vector<vl>;
using vvs = vector<vs>;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;

static const ll INF = numeric_limits<ll>::max() - 10000; // offset possible addition issues
static const ll NINF = numeric_limits<ll>::min();

inline auto ltrim(string_view s) -> string_view {
  if(s.size() == 0) return string_view{s};
  auto it=s.find_last_not_of(" \n\t\f\r\v");
  return s.substr(0, it+1);
}
inline auto rtrim(string_view s) -> string_view {
  if(s.size()==0) return s;
  auto it=s.find_first_not_of(" \n\t\f\r\v");
  return s.substr(it);
}
inline auto trim(string_view s) -> string_view{
  return ltrim(rtrim(s));
}


template<typename T>
concept number = is_integral_v<T>;
template<typename T>
concept printable =  requires (ostream& os, T const& t) {
  {os << t} -> same_as<ostream&>;
};

template<typename T>
auto read_line() -> vs {
  string line;
  getline(cin, line);
  
  vs res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> string{
      return std::string(sub.begin(), sub.end());
      });
  
  sr::for_each(x.begin(), x.end(), [&res](string s){res.push_back(s);}); 

  return res;
}

template<number T>
auto read_line() -> vector<T> {
  string line;
  getline(cin, line);

  vector<T> res{};
  auto x = trim(line) | srv::split(' ') 
    | srv::transform([](auto&& sub) -> T{
        auto b = &*sub.begin();
        auto e = &*sub.end();
        T i{};

        auto [ptr, err] = from_chars(b, e, i);
        if(err == errc::result_out_of_range || err == errc::invalid_argument){
          cerr << "Error in line to vector<{}> read " <<  typeid(T).name() << "\n";
          exit(1);
        }
        return i;
      });

  sr::for_each(x.begin(), x.end(), [&res](auto&& a){res.push_back(a);}); 
  return res;
}

template<printable T>
auto print_vec(vector<T>& v) -> void{
  cout << *v.begin();
  for(auto it = next(v.begin()); it!=v.end(); ++it){
    cout << " " << *it;
  }
  cout << "\n";
}

template<number T>
constexpr auto mypow(T a, T b) -> T {
  T res = 1;
  for(;b>0;--b){
    res *= a; 
  }
  return res;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// SOLUTIONS BELLOW
////-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


const pair<ll, ll> false_pair = make_pair(-1ll, -1ll);

// Passes on correctness but fails on some TLE and idk whats the diff
// cause it reads similar to other sol i saw
auto T(vvl& adj, vl& visited, vl& parent, ll i) -> pair<ll, ll> {
  assert(visited[i] == 0);        
  visited[i] = 1;                
  for(ll c: adj[i]){            
    if(c == parent[i]) continue; 
    if(visited[c]){ 
      return make_pair(c, i); 
    }
    parent[c] = i; 
    auto rec_res = T(adj, visited, parent, c); 
    if(rec_res != false_pair){
      return rec_res;
    }
  }
  return false_pair;
}

int main(){
  ll n, m;
  cin >> n >> m;

  vvl adj(n, vl{});

  for(auto _: srv::iota(0, m)){
    ll a, b;
    cin >> a >> b;
    adj[a-1].push_back(b-1);
    adj[b-1].push_back(a-1);
  }
  
  pair<ll, ll> p = make_pair(-1ll, -1ll);
  vl visited(n, 0);
  vl parent(n, INF);

  for(auto i: srv::iota(0, n)){
    auto res = T(adj, visited, parent, i);
    if(res != false_pair){
      p = res; 
      break;
    }
    transform(visited.begin(), visited.end(), visited.begin(), [](auto _){return 0;});
    transform(parent.begin(), parent.end(), parent.begin(), [](auto _){return INF;});
  }


  if(p == false_pair){
    cout << "IMPOSSIBLE";
  }else{
    vl ans{};
    ans.reserve(n);
    ans.push_back(p.first); 
    ans.push_back(p.second); 

    ll cur = parent[ans.back()];
    while(cur != ans.front()){
      ans.push_back(cur);
      cur = parent[cur];
    }
    ans.push_back(cur);
    
    transform(ans.begin(), ans.end(), ans.begin(), [](ll e){return e+1;});
    cout << ans.size() << "\n";
    print_vec(ans);
  }
}
