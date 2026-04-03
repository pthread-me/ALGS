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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

  TreeNode* rec(vector<int>& nums, ll l, ll r){
    if(r == l) return nullptr;
    if(r-l == 1) return new TreeNode(nums[l]); 
    if(r-l == 2) return new TreeNode(nums[l+1], new TreeNode(nums[l]), nullptr); 


    ll m = l + (r-l)/2;
    auto node = new TreeNode(nums[m]);
    node->left = rec(nums, l, m);
    node->right = rec(nums, m+1, r);
    
    return node;
  }
    
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    return rec(nums, 0, nums.size());
  }
};

int main(){
  
}
