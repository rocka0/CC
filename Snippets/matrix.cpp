template <typename T>
struct Matrix {
    vector<vector<T>> mat;
    int row_size;
    int col_size;

    Matrix(int R, int C)
    {
        assert(R > 0);
        assert(C > 0);
        row_size = R;
        col_size = C;
        mat.resize(R);
        for (int i = 0; i < row_size; ++i)
            mat[i].resize(C);
    }

    vector<T>& operator[](int x)
    {
        assert(x < row_size);
        return mat[x];
    }

    const vector<T>& operator[](int x) const
    {
        assert(x < row_size);
        return mat[x];
    }

    Matrix add(const Matrix& A, const Matrix& B)
    {
        assert(A.row_size == B.row_size);
        assert(A.col_size == B.col_size);
        Matrix ans(A.row_size, B.col_size);
        for (int i = 0; i < A.row_size; ++i) {
            for (int j = 0; j < B.col_size; ++j) {
                ans[i][j] = A[i][j] + B[i][j];
            }
        }
        return ans;
    }

    Matrix subtract(const Matrix& A, const Matrix& B)
    {
        assert(A.row_size == B.row_size);
        assert(A.col_size == B.col_size);
        Matrix ans(A.row_size, B.col_size);
        for (int i = 0; i < A.row_size; ++i) {
            for (int j = 0; j < B.col_size; ++j) {
                ans[i][j] = A[i][j] - B[i][j];
            }
        }
        return ans;
    }

    Matrix multiply(const Matrix& A, const Matrix& B)
    {
        assert(A.col_size == B.row_size);
        Matrix ans(A.row_size, B.col_size);
        for (int i = 0; i < A.row_size; ++i) {
            for (int j = 0; j < B.col_size; ++j) {
                for (int k = 0; k < A.col_size; ++k) {
                    ans[i][j] += (A[i][k] * B[k][j]);
                }
            }
        }
        return ans;
    }

    Matrix power(const Matrix& M, ll p)
    {
        assert(p >= 1);
        if (p == 1) {
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