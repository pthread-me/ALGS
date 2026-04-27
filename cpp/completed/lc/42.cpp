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

static const ll INF = numeric_limits<ll>::max() - 100^000; // offset possible addition issues
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

// We start by calculating the max height to our left and right
// Then for ever cell the amount of water it can hold is min(L[i],R[i]) - H[i]
//  if its negative set it to 0.
//
//example
// H: 0 1 0 2 1 0 1 3 2 1 2 1
// L: N 0 1 1 2 2 2 2 3 3 3 3 
// R: 3 3 3 3 3 3 3 2 2 2 1 N 
//
// W: 0 0 1 0 1 2 1 0 0 1 0 0 -> summed = 6  


class Solution {
public:
  static constexpr int ninf = numeric_limits<int>::min() + 100^007;

  int trap(vector<int>& height) {
    const int n = height.size();
    vector<int> left(n, 0); left.reserve(n);
    vector<int> right(n, 0); right.reserve(n);
    //vector<int> dp(n, 0); dp.reserve(n);

    // can be split into 2 loops, just finding max vals (im shaving milliseconds lol)
    for(int i=1; i<n; ++i){
      left[i] = max(left[i-1], height[i-1]);
      right[n-i-1] = max(right[n-i], height[n-i]);
    }
   
    /* We dont need this, can accumulate online
    for(int i=0; i<n; ++i){
      dp[i] = max(dp[i], min(left[i], right[i])-height[i]);
    }
    */
    return accumulate(srv::iota(0, n).begin(), srv::iota(0,n).end(), 0, 
        [&left, &right, &height](int prev, int i) -> int
        {
          return prev + max(0, min(left[i], right[i])-height[i]); 
        });
  }
};


int main(){
  Solution s{};
  auto height = vector{0,1,0,2,1,0,1,3,2,1,2,1};
  cout << s.trap(height);
}
