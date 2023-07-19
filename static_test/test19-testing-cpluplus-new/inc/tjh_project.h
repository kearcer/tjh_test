/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-25 22:24:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-12-08 13:53:59
 * @Description:
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <memory>
#include <list>
#include <stack> // std::stack
#include <queue>
#include <functional> // std::greater
#include <unordered_set>
#include <math.h>
#include <map>
#include <stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> result;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    return {i, j};
                }
            }
        }
        //        return result;
    }
};

class mycomparison
{
    bool reverse;

public:
    mycomparison(const bool &revparam = false)
    {
        reverse = revparam;
    }
    bool operator()(const int &lhs, const int &rhs) const
    {
        if (reverse)
            return (lhs > rhs);
        else
            return (lhs < rhs);
    }
};

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

template <class T>
T cmerge(T a, T b)
{
    T t(a);
    t.insert(b.begin(), b.end());
    return t;
}

class Jumpfloor
{
public:
    int jumpFloor(int number)
    {
        if (number <= 1)
            return 1;
        else if (number > 1)
            return jumpFloor(number - 2) + jumpFloor(number - 1);
    }
};

class Test_create
{
public:
    Test_create() { cout << "Test的构造函数..." << endl; }
    ~Test_create() { cout << "Test的析构函数..." << endl; }

    int getDebug() { return this->debug; }

private:
    int debug = 20;
};

class Test
{
public:
    Test() { cout << "Test的构造函数..." << endl; }
    ~Test() { cout << "Test的析构函数..." << endl; }

    void doSomething() { cout << "do something......" << endl; }
};

// 自定义一个内存释放其
class DestructTest
{
public:
    void operator()(Test *pt)
    {
        pt->doSomething();
        delete pt;
    }
};

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

// struct TreeNode
// {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

typedef unsigned int ULONG;
// typedef long BOOL;
typedef unsigned char BYTE;
typedef unsigned char *LPBYTE;
typedef long long LONGLONG;
typedef unsigned int UINT;
typedef double DOUBLE;
typedef long LONG;

typedef void *InputFrameHandle; // see INSAMPLEPARAM

typedef struct BASEPARAM
{
    ULONG ulParamFormat;
    ULONG ulSize;
} BaseParam;

typedef struct INSAMPLEPARAM : public BaseParam
{
    LONGLONG llStart; /* Start sample time */
    LONGLONG llEnd;   /* End sample time */
    void *pbBuffer;
    LONG lBufSize;
    ULONG ulBufMode;
    ULONG ulMask;
    LPBYTE pbYUV[3];      //[I]: original I420 data
    ULONG lFrameBuffered; //[O] to indicate the num of frames buffered in the encoder
    LPBYTE pTransData;
    ULONG lTransSize;
} InSampleParam;

typedef struct ComCodecContextEx
{
    int a;
    // suport : GET_ENC_INBUF_FUNC ,alloc memory in wrapper
    std::map<void *, InputFrameHandle> p_in_frame_list;      // used
    std::map<void *, InputFrameHandle> p_in_frame_list_idel; // idel

} ComCodecContextEx, *ComCodecHandleEx;

sem_t sem;

void *testfunc1(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
    }
}

void *testfunc2(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
    }
}
void *testfunc3(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
    }
}

void *testfunc4(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
    }
}

void *testfunc5(void *arg)
{
    while (1)
    {
        sem_wait(&sem);
    }
}