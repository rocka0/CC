/*
Usage: Matrix <int> M(4, 5) creates a 4X5 matrix of <int>
Type T must have +, -, *, += operators defined/overloaded
*/
template <typename T>
struct Matrix
{
    vector<vector<T>> mat;
    int row;
    int col;

    Matrix(int rowsize, int colsize)
    {
        assert(rowsize > 0);
        assert(colsize > 0);
        row = rowsize;
        col = colsize;
        mat.resize(rowsize);
        for (int i = 0; i < rowsize; ++i)
        {
            mat[i].resize(colsize);
        }
    }

    Matrix add(const Matrix &A, const Matrix &B)
    {
        assert(A.row == B.row);
        assert(A.col == B.col);
        Matrix ans(A.row, B.col);
        for (int i = 0; i < A.row; ++i)
        {
            for (int j = 0; j < B.col; ++j)
            {
                ans.mat[i][j] = A.mat[i][j] + B.mat[i][j];
            }
        }
        return ans;
    }

    Matrix subtract(const Matrix &A, const Matrix &B)
    {
        assert(A.row == B.row);
        assert(A.col == B.col);
        Matrix ans(A.row, B.col);
        for (int i = 0; i < A.row; ++i)
        {
            for (int j = 0; j < B.col; ++j)
            {
                ans.mat[i][j] = A.mat[i][j] - B.mat[i][j];
            }
        }
        return ans;
    }

    Matrix multiply(const Matrix &A, const Matrix &B)
    {
        assert(A.col == B.row);
        Matrix ans(A.row, B.col);
        for (int i = 0; i < A.row; ++i)
        {
            for (int j = 0; j < B.col; ++j)
            {
                ans.mat[i][j] = T(0);
                for (int k = 0; k < A.col; ++k)
                {
                    ans.mat[i][j] += (A.mat[i][k] * B.mat[k][j]);
                }
            }
        }
        return ans;
    }

    Matrix power(const Matrix &M, int p)
    {
        assert(p >= 1);
        if (p == 1)
        {
            return M;
        }
        else
        {
            Matrix H = power(M, p >> 1);
            H = multiply(H, H);
            if (p & 1)
            {
                H = multiply(H, M);
            }
            return H;
        }
    }
};