#include <iostream>
#include "mMath.h"

using namespace std;

#pragma region Compulsory 2 - Tasks

void Task464()
{
    //  Find a polynomial of degree ≤ 3 which interpolates the points
    //  (0, 1), (1/2, 9/16), (3/2, -5/16), (3, 4)
    
    // A-Matrix
    std::vector<float> inputMatrixA = {
        0,        0,       0,       1,
        0.125,    0.25,    0.5,     1,
        3.375f,   2.25,    1.5,     1,
        27,       9,       3,       1,
    };
    
    const Matrix A(4, 4, inputMatrixA);
    
    // y-Matrix
    std::vector<float> inputMatrixB = {
        1, 
        9.0/16,
        -5.0/16, 
        4
    };
    
    const Matrix B(4, 1, inputMatrixB);

    
    const Matrix x = mMath::MultiplyMatrices(mMath::Inverse(A), B);
    cout << "Solution matrix for task 4.6.4:\n"; x.PrintMatrix(1);
}


void Task467()
{
    //  Construct a polynomial of degree ≤ 3 which interpolates the points p0(1, 0) and
    //  p1(π, 0) and where the derivatives are respectively 1 and -1 (we write p′(x0) = 1 and p′(x1) = −1).
    
    // A-Matrix
    std::vector<float> inputMatrixA = {
        1,        1,       1,       1,
        PI*PI*PI, PI*PI,   PI,      1,
        3,        2,       1,       0,
        3*PI*PI,  2*PI,    1,       0,
    };
    
    const Matrix A(4, 4, inputMatrixA);
    
    // y-Matrix
    std::vector<float> inputMatrixB = {
        0, 
        0,
        1, 
        -1
    };
    
    const Matrix B(4, 1, inputMatrixB);

    
    const Matrix x = mMath::MultiplyMatrices(mMath::Inverse(A), B);
    cout << "Solution matrix for task 4.6.7:\n"; x.PrintMatrix(5);
}


void Task4614()
{
    // Use the method of least squares to find the equation of the straight line which
    // fits the points best possible: (4, 3),(0, 1),(2, 0) og (3, 4).

    // A-Matrix
    std::vector<float> inputMatrixA = {
        4,  1,
        0,  1,
        2,  1,
        3,  1
    };
    
    const Matrix A(4, 2, inputMatrixA);
    
    
    // y-Matrix
    std::vector<float> inputMatrixB = {
        3, 
        1,
        0, 
        4
    };
    
    const Matrix b(4, 1, inputMatrixB);
    
    
    const Matrix invA = mMath::Inverse(mMath::MultiplyMatrices(mMath::TransposeMatrix(A), A));
    
    const Matrix y = mMath::MultiplyMatrices(mMath::TransposeMatrix(A), b);
    
    const Matrix x = mMath::MultiplyMatrices(invA, y);
    cout << "Solution matrix for task 4.6.14:\n"; x.PrintMatrix(5);
}


void Task4615()
{
    /*
    In a game scene the player is moving along a parabola (the graph of a second
    degree polynomial) and collect trophys along the path. The trophys have coordinates:

    (1/2, 1/2), (1/2, 3/2), (5/2, −1), (3, 1/2), (4, 3)
    
    The parabolic path should be constructed using the method of least squares.
    1. Write down the matrices A, AT and the vector y = ATb
    2. Find the equation for the second degree polynomial.
    */

    // A-Matrix
    std::vector<float> inputMatrixA = {
        1.f/4,      .5,     1,
        1.f/4,      .5,     1,
        25.f/4,     2.5,    1,
        3*3,        3,      1,
        4*4,        4,      1
    };    
    
    Matrix A(5, 3, inputMatrixA);
    cout << "A Matrix:\n"; A.PrintMatrix(2); cout << endl;
    cout << "AT Matrix:\n"; mMath::TransposeMatrix(A).PrintMatrix(2); cout << endl;
    
    // y-Matrix
    std::vector<float> inputMatrixB = {
        .5, 
        1.5,
        -1, 
        .5,
        3
    };
    
    const Matrix b(5, 1, inputMatrixB);

    
    const Matrix invA = mMath::Inverse(mMath::MultiplyMatrices(mMath::TransposeMatrix(A), A));
    
    const Matrix y = mMath::MultiplyMatrices(mMath::TransposeMatrix(A), b);
    cout << "y vector:\n";  y.PrintMatrix(); cout << endl;
    
    const Matrix x = mMath::MultiplyMatrices(invA, y);
    cout << "Solution matrix for task 4.6.15:\n"; x.PrintMatrix(5);
}


void Compulsory2()
{
    
    cout << "\n-------------\n";
    
    Task464();
    cout << "\n-------------\n";

    Task467();
    cout << "\n-------------\n";
    
    Task4614();
    cout << "\n-------------\n";

    Task4615();
}

#pragma endregion 


void ShowcaseLU()
{
    std::vector<float> inputMatrixA = {
        1,      2,      3,      1,
        2,      3,      4,      1,
        3,      4,      2,      1,
    };
    
    Matrix A(3, 4, inputMatrixA);

    cout << "\n-------------\n";

    cout << "Before LU factorization:\n";
    A.PrintMatrix(0);
    
    A.LU();
    cout << "\nAfter LU factorization:\n";
    A.PrintMatrix(0);

    cout << "-------------\n";
}

void Mathing()
{
    std::vector<float> inputMatrixB = {
        626,     172,     50,
        172,     50,      16,
        50,      16,      6
    };

    Matrix B(3, 3, inputMatrixB);
    //mMath::Inverse(B).PrintMatrix();

    std::vector<float> inputMatrixA = {
        143, 41, 13
    };

    Matrix c(3, 1, inputMatrixA);

    mMath::MultiplyMatrices(mMath::Inverse(B), c).PrintMatrix();
}

int main(int argc, char* argv[])
{
    //ShowcaseLU();
    
    //Compulsory2();

    Mathing();
    
    return 0;
}