#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <climits>
class Solution
{
public:
    int jumpFloor(int number)
    {
        if (number == 1)
            return 1;
        if (number == 2)
            return 2;
        return jumpFloor(number - 1) + jumpFloor(number - 2);
    }
};