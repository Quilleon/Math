#include <iostream>
#include "mMath.h"

using namespace std;

void MatrixCalculation()
{
    float inputMatrixA[5][5] = {
        {1, 1, 1},
        {5, 3, 2},
        {1, 3, 2}
    };

    float inputMatrixB[5][5] = {
        {1},
        {2},
        {1}
    };
    
    const Matrix A(3, 3, inputMatrixA);
    cout << "Input matrix A:\n"; A.PrintMatrix();

    
    const Matrix B(3, 1, inputMatrixB);
    cout << "Input matrix B:\n"; B.PrintMatrix();
    
    
    Matrix AT = mMath::TransposeMatrix(A);
    cout << "Transposed A-matrix:\n"; AT.PrintMatrix();
    
    
    const Matrix adjA = mMath::Adjoint(A);
    cout << "Adjoint A-matrix:\n"; adjA.PrintMatrix();
    
    
    float detA = mMath::Determinant(A);
    cout << "Determinant A-matrix: " << detA << "\n"; 
    
    
    const Matrix invA = mMath::Inverse(A);
    cout << "Inverse A-matrix:\n"; invA.PrintMatrix();

    
    const Matrix solAB = mMath::MultiplyMatrices(invA, B);
    cout << "Solution invA*B matrix:\n"; solAB.PrintMatrix();
}

void NewMatrixCalculation()
{
    std::vector<float> a = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    NewMatrix A(3, 3, a);

    A.TransposeMatrix();

    A.ScaleMatrix(static_cast<float>(1)/2);
    
    A.PrintMatrix();
}

int main(int argc, char* argv[])
{
    MatrixCalculation();    

    //NewMatrixCalculation();
    
    return 0;
}


/*
    // Saved Inputs:

    float inputMatrixA[5][5] = {
        {1, 1, 1, 1},
        {27, 9, 3, 1},
        {3, 2, 1, 0},
        {27, 6, 1, 0}
    };

    float inputMatrixB[5][5] = {
        {1},
        {2},
        {.25f},
        {0}
    };
    
    float inputC[5][5] = {
        {2, 20},
        {4, 5}
    };

    const Matrix C(2, 2, inputC);
    float detC = mMath::Determinant(C);
    cout << "Determinant C: " << detC << "\n";
*/