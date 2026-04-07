#include <algorithm>
#include <charconv>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;
using ll =  long long;
using ull =  unsigned long long;

using us = unordered_set<string>;
using um = unordered_map<char, ull>;
using vl = vector<ll>;
using vvl = vector<vl>;
using foid = void;

namespace srv = ranges::views;
namespace sr = ranges;
namespace sv = views;



auto T(vl& nums) -> ll {
  auto max_pos = sr::max_element(nums.begin(), nums.end());
  
  for(auto it=nums.begin(); it != nums.end(); ++it){
    if(it != max_pos){
      *it = *it * -1; 
    }
  }
  
  return accumulate(nums.begin(), nums.end(), 0);
}

int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);

  for(auto _: srv::iota(0, n)){
    getline(cin, line);

    vl nums{};
    nums.reserve(7);

    for(auto sub: line | srv::split(' ')){
      char* b = &*sub.begin();
      char* e = &*sub.end();

      ll i{};
      from_chars(b, e, i); // ignoring errs
      nums.push_back(i);      
    }

    cout << T(nums) << "\n";
  }
}
