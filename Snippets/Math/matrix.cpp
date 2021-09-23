#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/rocka0/CC

    Usage:  Matrix<int> M(2,2)
*/

template <typename T>
class Matrix {
    vector<vector<T>> mat;

public:
    int rows;
    int cols;

    Matrix(int N, int M) {
        assert(N > 0);
        assert(M > 0);
        rows = N;
        cols = M;
        mat.resize(N);
        for (int i = 0; i < rows; ++i) {
            mat[i].resize(M);
        }
    }

    vector<T>& operator[](int x) {
        assert(x < rows);
        return mat[x];
    }

    const vector<T>& operator[](int x) const {
        assert(x < rows);
        return mat[x];
    }

    bool operator==(const Matrix& B) { return mat == B.mat; }

    bool operator!=(const Matrix& B) { return mat != B.mat; }

    Matrix identity(int n) {
        assert(n > 0);
        Matrix I = Matrix<T>(n, n);
        for (int i = 0; i < n; ++i) {
            I[i][i] = T(1);
        }
        return I;
    }

    Matrix add(const Matrix& A, const Matrix& B) {
        assert(A.rows == B.rows);
        assert(A.cols == B.cols);
        Matrix ans(A.rows, B.cols);
        for (int i = 0; i < A.rows; ++i) {
            for (int j = 0; j < B.cols; ++j) {
                ans[i][j] = A[i][j] + B[i][j];
            }
        }
        return ans;
    }

    Matrix subtract(const Matrix& A, const Matrix& B) {
        assert(A.rows == B.rows);
        assert(A.cols == B.cols);
        Matrix ans(A.rows, B.cols);
        for (int i = 0; i < A.rows; ++i) {
            for (int j = 0; j < B.cols; ++j) {
                ans[i][j] = A[i][j] - B[i][j];
            }
        }
        return ans;
    }

    Matrix multiply(const Matrix& A, const Matrix& B) {
        assert(A.cols == B.rows);
        Matrix ans(A.rows, B.cols);
        for (int i = 0; i < A.rows; ++i) {
            for (int j = 0; j < B.cols; ++j) {
                for (int k = 0; k < A.cols; ++k) {
                    ans[i][j] += (A[i][k] * B[k][j]);
                }
            }
        }
        return ans;
    }

    Matrix power(const Matrix& M, int64_t p) {
        assert(M.rows == M.cols);
        assert(p >= 0);
        if (p == 0) {
            return M.identity(M.rows);
        } else if (p == 1) {
            return M;
        } else {
            Matrix H = power(M, p >> 1);
            H = multiply(H, H);
            if (p & 1) {
                H = multiply(H, M);
            }
            return H;
        }
    }
};
