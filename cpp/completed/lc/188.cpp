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

class Solution {
public:
  vector<int> prices;
  vector<vector<int>> dp;
  
  
  // 2d dp, There is a better 3d version which u should look into
  // This sol is easy, we keep a row for everynumber of k 
  // and solve the old 309.cpp for each row
  auto T(int k) -> int {
    for(int r=1; r<dp.size(); ++r){
      for(int i=dp[r].size()-2; i>=0; --i){
        for(int j = i+1; j<dp[r].size(); ++j){
          int j_jump = min((size_t)(j+1), dp[r].size()-1);
          dp[r][i] = max(dp[r][i], prices[j]-prices[i]+dp[r-1][j_jump]);
        }
        dp[r][i] = max(dp[r][i], dp[r][i+1]);
      }
    }
    return dp.back()[0];
  }


  int maxProfit(int k, vector<int>& prices) {
    if(k == 0) return 0 ;
    ++k;
    this->prices = prices;
    dp = vector<vector<int>>(k, vector<int>(prices.size(), 0));
    return T(k);
  }
};


int main(){
  Solution s{};
  vector<int> p{2,4,1};

  cout << s.maxProfit(2, p);
}
