#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int>>& array) {
        int row = array.size() - 1;
        int col = 0;
        if(array.empty())
            return false;

        while(col <= array[0].size() && row >= 0)
        {
            if(array[row][col]  == target)
                return true;
            else if(array[row][col]  > target)
                row--;
            else 
                col++;
        }
        return false;
    }
};


int main()
{
    Solution sol;

    // Test case 1
    vector<vector<int>> array1 = {{1, 4, 7, 11},
                                  {2, 5, 8, 12},
                                  {3, 6, 9, 16},
                                  {10, 13, 14, 17},
                                  {18, 21, 23, 26}};
    int target1 = 5;
    bool result1 = sol.Find(target1, array1);
    cout << "Test case 1: " << (result1 ? "true" : "false") << endl;

    // Test case 2
    vector<vector<int>> array2 = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9}};
    int target2 = 10;
    bool result2 = sol.Find(target2, array2);
    cout << "Test case 2: " << (result2 ? "true" : "false") << endl;

    // Test case 3
    vector<vector<int>> array3 = {{}};
    int target3 = -1;
    bool result3 = sol.Find(target3, array3);
    cout << "Test case 3: " << (result3 ? "true" : "false") << endl;

    return 0;
}