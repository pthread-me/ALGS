#include <print>
#include <string>
#include <utility>
#include <utils.hpp>
#include <bits/stdc++.h>
#include <vector>


/*
 *  Classic backtracking, maintain a temp list of current solution then for every
 *  cell check if we can insert a queen, if so we recurse into 2 paths of either 
 *  adding or not. once we reach the last cell or len of temp == n we evaluate 
 *  if its a solution or not.
 *
 */
class Solution {
public:
  auto backtrack(vector<vector<pair<ll,ll>>>& res, ll n, vector<pair<ll,ll>>& temp, ll i, ll j) -> void {
    // Check
    auto check = [&n](vector<pair<ll,ll>>const& temp, ll i, ll j) -> bool {
      ll ri{i}, rj{j}, li{i}, lj{j};  
      for(;ri<n && rj<n; ri++, rj++);
      for(;li<n && lj>-1; li++, lj--);

      for (auto [Qi, Qj]: temp){
        ll Ri{Qi}, Rj{Qj}, Li{Qi}, Lj{Qj};  
        if (Qi==i || Qj==j){
          return false;
        }

        for(;Ri<n && Rj<n; Ri++, Rj++);
        if (ri == Ri && rj == Rj){
          return false;
        } 
        for(;Li<n && Lj>-1; Li++, Lj--);

        if (li == Li && lj == Lj) return false;
      }
      return true;
    }; 

    auto next = [&n](ll i, ll j)-> pair<ll, ll> {
      if (j<n-1){
        return make_pair(i, j+1);
      }else{
        return make_pair(i+1, 0);
      }
    };
    
    if (temp.size() == n){
      auto copy = vector<pair<ll,ll>>(temp);
      res.push_back(copy);
      return;
    }else if(i==n) return;

    while (i<n){
      auto next_move = next(i,j);
      if (check(temp, i, j)){
        temp.push_back(make_pair(i, j));
        backtrack(res, n, temp, next_move.first, next_move.second);
        temp.pop_back();
      }   
      i = next_move.first;
      j = next_move.second;
    } 
  };



  vector<vector<string>> solveNQueens(int n) {
    if (n == 1) return {{"Q"}};
    auto res = vector<vector<pair<ll,ll>>>();      
    auto temp = vector<pair<ll,ll>>();
    auto result = vector<vector<string>>();
    
    string s = ""; for (ll i=0; i<n;i++) s = s+".";
    backtrack(res, n, temp, 0, 0);  
    
    println("{}", res);
    for (auto e: res){
      vector<string> vec = vector(n, s); 
      for(auto [vec_pos, s_pos]: e){
        vec[vec_pos][s_pos] = 'Q';
      } 
      result.push_back(vec);
    }
    
    return result;
  }
};

int main(){
  auto s = Solution();
  auto result = s.solveNQueens(5);

  for (auto v: result){
    println("{}", v);
  }
}
