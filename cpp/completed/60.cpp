#include <array>
#include <functional>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <vector>


/**
 *  I am replicating BWT traversals here.
 *  Maintain a vector C of all the elements, r is the length of a 
 *  permutation run ex for n = 3:
 *    123
 *    132
 *    213
 *    231
 *    312
 *    312
 *  Here r is 2 since for n = 2 the number of permutations that start with the
 *  same number is 2. r is that number.
 *
 *  r = n!/n
 *
 *  we then need to find which run the kth permutation occurs in, let that index
 *  be i, i = k/r.
 *  Once we find i we just need to get its value by indexing into C. its important
 *  that C shrinks to maintain the inequality for future recursions.
 *  Finally we update k by setting it to the number of remaining positions we need 
 *  to skip over (aka k - the number of pos we skipped = r*i) so k = k-(r*i)
 *
 *  repeat this until len(C) == 1
 *
 *  We can speed up the impl by pre calculating factorials but ill leave that
 *  as an excercise to the reader lmao.
 *
 *
 *  PS: This is exactly how forward backwards works in bioinformatics, if interested
 *  check Ben Langmeads vids on YT
 *
 */

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
