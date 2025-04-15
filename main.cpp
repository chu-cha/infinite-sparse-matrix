#include <iostream>
#include "sparse_matrix.h"


int main() {
    SparseMatrix<int, 0> matrix;
    
    for (int i = 0; i < 10; i++) {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }

    std::cout << "\nAll elements: \n";
    for (auto& c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "[" << x << "][" << y << "] = " << v << std::endl;
    }

    return 0;
}
