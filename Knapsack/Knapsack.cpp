#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int solve(int k, vector<int> worht, vector<int> weights, int W) 
{
    vector<int> memo_1(W + 1, 0);
    vector<int> memo_2(W + 1, 0);
    for (int p = 1; p <= k; p++) 
    {
        vector<int> temp = memo_1;
        memo_1 = memo_2;
        memo_2 = temp;
        for (int q = 0; q <= W; q++)
        {
            memo_2[q] = memo_1[q];
            if (q - weights[p - 1] >= 0) 
            {
                memo_2[q] = max(memo_2[q], memo_1[q - weights[p - 1]] + worht[p - 1]);
            }
        }
    }
    int result = 0;
    for (int p = W; p >= 0; p--) 
    {
        if (memo_2[p] != 0) 
        {
            result = memo_2[p];
            break;
        }
    }
    return result;
}

int main() 
{
    string path = "/Users/annalarina/knapsack";
    auto it = fs::directory_iterator(path);
    vector<fs::path> matrix_path;
    copy_if(fs::begin(it), fs::end(it), std::back_inserter(matrix_path),
        [](const auto& entry) 
        {
            return fs::is_regular_file(entry);
        });
    for (auto& p : matrix_path)
    {
        ifstream f;
        f.open(p.string());
        cout << p.string() << endl;
        int k, W;
        f >> k >> W;
        vector<int> worht;
        vector<int> weights;
        for (int p = 0; p < k; p++) 
        {
            int worht, weight;
            f >> worht >> weight;
            worht.push_back(worht);
            weights.push_back(weight);
        }
        int max_value = solve(k, worht, weights, W);
        cout << max_value << endl;
    }
    return 0;
}
