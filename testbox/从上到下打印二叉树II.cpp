#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <unordered_map>
#include <regex>
#include <climits>
#include <math.h>
#include <stack>
#include <queue>
struct TreeNode 
{
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
using namespace std;
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> Que;
        if(root != NULL)
             Que.push(root);
        else
            return res;
        int depth = 0;
        while(!Que.empty())
        {   
            int size = Que.size();
            vector<int> V;

            for(int i = 0; i < size; i++)
            {
                TreeNode *node = Que.front();
                V.push_back(node->val);
                if(node->left)
                    Que.push(node->left);
                if(node->right)
                    Que.push(node->right);
                Que.pop();
            }
            res.push_back(V);
        }
        return res;
    }
};

int main() {

    Solution s;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> res = s.levelOrder(root);

    for (auto v : res) {
        for (auto i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}