#include <vector>

using namespace std;

class NumMatrix {
    vector<vector<int>> prefix_sums;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        // We have been given a 2D matrix and we need to return result for the queries later.
        // These queries needs to be answered in O(1) time complexity and hence we need to
        // do some preprocessing on the input matrix.
        // One way would be to store the sum of each region and then use that to return the 
        // result of the query.
        // This is possible if we can find a way to enhance the input matrix to prefix sum matrix.
        // To find the area of region starting from 0,0 to m, n. 
        // Area of i, j = area of (0, 0) to (i, j) = area of (0, 0) to (i, j - 1) + area of (0, 0)
        // to (i - 1, j) - ovelapping area in between area (i, j - 1) and area (i - 1, j) i.e. area
        // of (0, 0) to (r - 1, c - 1).
        // Above is the same approach as in case of filling matrix in case of DP problems.

        prefix_sums.resize(size(matrix), vector<int>(size(matrix[0])));

        // Base case for top left cell
        prefix_sums[0][0] = matrix[0][0];

        // Prefix sum of the first column
        for(int r = 1; r < size(matrix); r++) prefix_sums[r][0] = prefix_sums[r - 1][0] + matrix[r][0];
        // Prefix sum of the top row
        for(int c = 1; c < size(matrix[0]); c++) prefix_sums[0][c] = prefix_sums[0][c - 1] + matrix[0][c];

        for(int r = 1; r < size(matrix); r++)
        {
            for(int c = 1; c < size(matrix[0]); c++)
            {
                prefix_sums[r][c] = matrix[r][c] 
                    + prefix_sums[r][c - 1]
                    + prefix_sums[r - 1][c]
                    - prefix_sums[r - 1][c - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if(row1 == 0 && col1 == 0) return prefix_sums[row2][col2];
        else if(row1 == 0) return prefix_sums[row2][col2] - prefix_sums[row2][col1 - 1];
        else if(col1 == 0) return prefix_sums[row2][col2] - prefix_sums[row1 - 1][col2];
        else return prefix_sums[row2][col2] 
            - prefix_sums[row2][col1 - 1] 
            - prefix_sums[row1 - 1][col2]
            + prefix_sums[row1 - 1][col1 - 1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */