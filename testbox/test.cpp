#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:

    vector<vector<int> > permute(vector<int> &num, int start, int end)
    {
        if(start == end)
        
    }
    
    vector<vector<int> > permute(vector<int> &num) {
        int size = num.size();

        return permute_all(num, 0, size - 1);
        
    }
};