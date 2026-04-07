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



auto T(ull n) -> vl {
  ll i = 1;
  ll j = 3*n;

  vl res{};
  res.reserve(3*n);

  while(i < j){
    res.push_back(i);
    res.push_back(j-1);
    res.push_back(j);
    ++i;
    j-=2;
  }

  return res;
}

int main(){
  string line;
  getline(cin, line);
  ll n = stoll(line);

  for(auto _: srv::iota(0, n)){
    getline(cin, line);
    vl res = T(stoll(line));
    
    cout << res[0];
    for(auto it = next(res.begin()); it != res.end(); ++it){
      cout << " " << *it;
    }
    cout << "\n";
  }
}
