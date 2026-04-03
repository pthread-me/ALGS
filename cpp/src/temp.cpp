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

auto solve(ll n, vector<ll>& perm, vector<ll>& nums, ll i) -> bool{
  //println("i: {}", i);
  if(i>=n) return true;   

  ll j = i;
  bool found_in = nums[i] == perm[i];
  while((j+1)<n && nums[j+1] == nums[j]){
    if(nums[j] == perm[j]) found_in = true;
    j++;
  }
  //println("j: {}", j);

  if (!found_in){
    if(i>0 && (i>0 && !(nums[i]==perm[i-1] && nums[i-1] == perm[i]))){
      found_in = nums[i] == perm[i-1];
    }else{
      found_in = false;
    }

    if(j<n-1 && !(nums[j]==perm[j+1] && nums[j+1]==perm[j])){
      found_in = nums[j] = perm[j+1];
    }else{
      found_in = false;
    }
  }

  if(!found_in) return false;

  //for(; i<=j; i++){
  //  perm[i] = nums[i];
  //}
  i = j+1;
  //println("perm: {}\nnums: {}", perm, nums);
  return solve(n, perm, nums, i);
}


int main(){
  string line;
  getline(cin, line);
  ll t = stoll(line);

  for(auto _ : srv::iota(0, t)){
    getline(cin, line);
    ll n = stoll(line);

    getline(cin, line);
    auto perm = line 
      | srv::split(' ')
      | srv::transform([](auto e){return stoll(string(string_view(e)));})
      | sr::to<vector<ll>>(); 
    

    getline(cin, line);
    auto nums = line 
      | srv::split(' ')
      | srv::transform([](auto e){return stoll(string(string_view(e)));})
      | sr::to<vector<ll>>(); 
    
    println("{}", solve(n, perm, nums, 0) ? "YES" : "NO");
  }
}
