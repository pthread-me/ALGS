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


/*
 *  This took me an embarassingly long time:
 *  
 *  We want to construct pairs that fit into h and l, the correct approach
 *  is to find the min, wlog let h<=l then we can have 2 lists for 
 *  elements that are <=h and <=l.
 *
 *  If the |h| <= |l|/2 the every element in h can be paired with an element in 
 *  l and since l>h no two elements in l will satisfy the pairing condition together
 *  (that is we need one e from h)
 *
 *  the second case is when |h| > |l|/2. here observe that
 *  any element in h is also in l, so the number of elements in l that are >h
 *  will always be less than |h| (if this wasnt the case then we would be in
 *  case 1) 
 *  now pairing every element in e in l where e>h with an element in h, leaves 
 *  us with some e in h that we can pair together. thus the solution is 
 *  # of e in l>h + (|h| - the paired values)/2
 *
 * Bellow:
 * hf = h filter, lf = l filter, ch = h count etc,
 * gth = greater than h, cgth the count of gth
 *
 */

auto solve(vector<ll>& param, vector<ll>& vals) -> ll{
  auto n = param[0];
  ll h = min(param[1], param[2]);
  ll l = max(param[1], param[2]);
  
  auto hf = vals | srv::transform([&h](auto e){return e<=h ? 1 : 0;});
  ll ch = accumulate(hf.begin(), hf.end(), 0);
  auto lf = vals | srv::transform([&l](auto e){return e<=l ? 1 : 0;});
  ll cl = accumulate(lf.begin(), lf.end(), 0);

  println("<= h: {}", hf);
  println("<= l: {}", lf);

  if (ch <= cl/2){
    return ch;
  }else{
    auto gth = vals | srv::transform([&h, &l](auto e){return h<e && e<=l ? 1 : 0;});
    println("h < [] <= l: {}", lf);
    ll cgth = accumulate(gth.begin(), gth.end(), 0);
    ll res = cgth;
    ch -= cgth;
    res += ch/2;
    return res;
  }
}


int main(){
  string line;
  getline(cin, line);
  ll t = stoll(line);
  
  for(auto _ : srv::iota(0, t)){
    getline(cin, line);
    auto params = line 
      | srv::split(' ') 
      | srv::transform([](auto rng){return string(string_view(rng));})
      | srv::transform([](string a){return stoll(a);})
      | sr::to<vector<ll>>();

    getline(cin, line);
    auto nums = line 
      | srv::split(' ') 
      | srv::transform([](auto rng){return string(string_view(rng));})
      | srv::transform([](string a){return stoll(a);})
      | sr::to<vector<ll>>();
  
    println("{}", solve(params, nums));
  }
}
