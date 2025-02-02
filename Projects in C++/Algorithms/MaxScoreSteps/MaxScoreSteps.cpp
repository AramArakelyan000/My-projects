#include <iostream>
#include <vector>
#include <algorithm>

int maxPoints(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    
    std::vector<int> dp(n);
    dp[0] = arr[0];
    dp[1] = std::max(arr[0], arr[1]);
    
    for (int i = 2; i < n; ++i) {
        dp[i] = std::max(dp[i - 1], dp[i - 2] + arr[i]);
    }
    
    return dp[n - 1];
}

int maxPointsMatrix(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return 0;
    int cols = matrix[0].size();
    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols));
    
    dp[0][0] = matrix[0][0];
    
    for (int i = 1; i < rows; ++i) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }
    for (int j = 1; j < cols; ++j) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }
    
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            dp[i][j] = std::max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + matrix[i][j];
        }
    }
    
    return dp[rows - 1][cols - 1];
}

int main() {
    std::vector<int> arr = {1, -1, 3, 5, -2, 4, -3};
    std::cout << "Maximum points (array): " << maxPoints(arr) << std::endl;
    
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {-1, -2, -3},
        {4, 5, 6}
    };
    std::cout << "Maximum points (matrix): " << maxPointsMatrix(matrix) << std::endl;
    
    return 0;
}
