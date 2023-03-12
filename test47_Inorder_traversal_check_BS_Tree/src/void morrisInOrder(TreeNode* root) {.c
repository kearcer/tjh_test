void morrisInOrder(TreeNode *root)
{
    TreeNode *cur = root;
    TreeNode *pre = NULL;
    while (cur != NULL)
    {
        if (cur->left == NULL)
        {
            cout << cur->value << " ";
            cur = cur->right;
        }
        else
        {
            pre = cur->left;
            while (pre->right != NULL && pre->right != cur)
            {
                pre = pre->right;
            }
            if (pre->right == NULL)
            {
                pre->right = cur;
                cur = cur->left;
            }
            else
            {
                pre->right = NULL;
                cout << cur->value << " ";
                cur = cur->right;
            }
        }
    }
}

void morrisInOrder(TreeNode *root)
{
    TreeNode *cur = root;
    TreeNode *pre = NULL;
    int last = INT_MIN; //记录上一个访问的节点的值
    bool flag = true;   //记录是否是二叉搜索树
    while (cur != NULL)
    {
        if (cur->left == NULL)
        {
            if (cur->value < last)
            { //如果当前节点的值小于上一个节点的值，就不是二叉搜索树
                flag = false;
                break;
            }
            last = cur->value; //更新上一个节点的值
            cur = cur->right;
        }
        else
        {
            pre = cur->left;
            while (pre->right != NULL && pre->right != cur)
            {
                pre = pre->right;
            }
            if (pre->right == NULL)
            {
                pre->right = cur;
                cur = cur->left;
            }
            else
            {
                pre->right = NULL;
                if (cur->value < last)
                { //如果当前节点的值小于上一个节点的值，就不是二叉搜索树
                    flag = false;
                    break;
                }
                last = cur->value; //更新上一个节点的值
                cur = cur->right;
            }
        }
    }
    cout << "The tree is " << (flag ? "a BST" : "not a BST") << endl; //输出结果
}