#pragma once
#include <vector>
#include "Matrix.h"

using namespace std;


class mMath
{
public:
    static Matrix TransposeMatrix(const Matrix& A);
    
    static Matrix MultiplyMatrices(const Matrix& A, const Matrix& B);
    
    static float Determinant(const Matrix& A);
    
    static Matrix Adjoint(const Matrix& A);

    static Matrix Inverse(const Matrix& A);

private:
    
    static float Determinant2x2(const Matrix& A);
    static float Determinant3x3(const Matrix& A); // Non-recursive
    static float DeterminantOver2(const Matrix& A); // Recursive
    
    static Matrix Cofactor2x2(const Matrix& A);
    static Matrix Cofactor3x3(const Matrix& A); // This is non-recursive and more performative
    static Matrix CofactorOver2(const Matrix& A); // Generates and calculates submatrices using recursion
};
