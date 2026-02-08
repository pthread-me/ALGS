#include <array>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <vector>


class Solution {
public:
  auto fac(ll n) -> ll{
    auto holder =  rsv::iota(1, n+1) | rs::to<vector<ll>>();
    return accumulate(holder.begin(), holder.end(), 1,  multiplies<ll>{});
  }

  auto rec(vector<ll>& C, ll k, string& sol) -> void{
    println("C: {}\nk: {}, sol: {}", C, k, sol);
    if (C.size() == 1){
      sol = sol + to_string(C[0]);
      return;
    }

    ll r = fac(C.size())/C.size();
    ll i = k/r;
    sol = sol + to_string(C[i]);
    C.erase(C.begin() + i);
    rec(C, k - (r*i), sol);
  }

  string getPermutation(int n, int k) {
    auto C = rsv::iota(1, n+1) | rs::to<vector<ll>>();      
    string sol = ""; 
    
    rec(C, k-1, sol);
    return sol;
  }
};

int main(){
  auto s = Solution();
  auto result = s.getPermutation(4, 9);
  println("{}", result);
}
