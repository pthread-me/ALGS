#include <algorithm>
#include <bits/stdc++.h>
#include <limits>
#include <ranges>
#include <utility>

using namespace std;
namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;
using ll =  long long;

/**
 *  Since we fill values by 1, 10 11 : take for example 152 we will always at
 *  least need 5 1's in the 10s position so the min is the max character in [0-9]
 *
 */
class Solution {
public:
  int minPartitions(string n) {
    vector<ll> nums = n | srv::transform([](char c){return (ll)c-'0';}) | sr::to<vector<ll>>();
    return *sr::max_element(nums.begin(), nums.end());
  }
};

int main(){
  auto S = Solution();
  auto n = "32";
  println("{}", S.minPartitions(n));
}
