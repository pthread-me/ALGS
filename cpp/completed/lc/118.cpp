#include <algorithm>
#include <array>
#include <bits/stdc++.h>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <unistd.h>
#include <vector>

using namespace std;
namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;
using ll =  long long;

class Solution {
public:
  
  auto rec(int n, vector<vector<int>>& res) -> vector<vector<int>>{
    if(n==0) return res;
    if(res.empty()){
      res.push_back(vector<int>{1});
      return rec(n-1, res);
    }

    auto cur = vector<int>();
    cur.reserve(res.back().size()+1);
    cur.push_back(1);
    
    auto view = srv::pairwise_transform(res.back(), [](auto&... vals){
      auto pair = tie(vals...);  
      return get<0>(pair) + get<1>(pair);
      });

    sr::for_each(view, [&cur](auto e){cur.push_back(e);});
    cur.push_back(1);
    res.push_back(cur);

    return rec(n-1, res);
  }

  vector<vector<int>> generate(int numRows) {
    auto res = vector<vector<int>>();
    return rec(numRows, res);
  }
};


int main(){
  auto s = Solution();
  auto n = 5;
  auto res = s.generate(n);

  sr::for_each(res, [](auto e){
    println("{}", e);
  });
 }
