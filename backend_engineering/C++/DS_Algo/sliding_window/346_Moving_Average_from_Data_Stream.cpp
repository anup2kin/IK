#include<queue>

using namespace std;

class MovingAverage {
    queue<int> q;
    int size = 0;
    int total_sum_so_far = 0;
public:
    MovingAverage(int size) {
        this->size = size;
    }
    
    double next(int val) {
        q.push(val);
        total_sum_so_far += val;
        
        if(std::size(q) > size)
        {
            total_sum_so_far -= q.front();
            q.pop();
        }

        return static_cast<double>(total_sum_so_far) / std::size(q);
    }
};
