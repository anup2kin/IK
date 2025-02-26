#include <stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        int max_len = 0;
        stk.push(-1);

        for(int i = 0; i < size(s); i++)
        {
            if(s[i] == '(') stk.push(i);
            else
            {
                stk.pop();
                if(empty(stk)) stk.push(i);
                else max_len = max(max_len, i - stk.top());
            }
        }

        return max_len;
    }
};