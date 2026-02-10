#include "mMath.h"

// Transposing a matrix is built into the matrix struct
Matrix mMath::TransposeMatrix(const Matrix& A)
{
    float tempM[5][5];
        
    for (int r = 0; r < A.rows; ++r)
    {
        for (int c = 0; c < A.columns; ++c)
        {
            tempM[r][c] = A.M[c][r];
        }
    }
        
    const Matrix AT(A.rows, A.columns, tempM);
    return AT;
}

Matrix mMath::MultiplyMatrices(const Matrix& A, const Matrix& B)
{
    if(A.columns != B.rows)
    {
        cout << "CANNOT MULTIPLY MATRICES!\n";
        return B;
    }
        
        
    float tempM[5][5];
    Matrix newM(A.rows, B.columns, tempM);

    //cout << A.rows << ", " << B.columns << "\n";
        
    for (int C = 0; C < B.columns; ++C) //
        {
        for (int R = 0; R < A.rows; ++R) //
            {
            float tempElement = 0;

            for (int i = 0; i < B.rows; ++i) // indexing
                tempElement += A.M[R][i] * B.M[i][C]; // Adding all the terms together
                
            newM.M[R][C] = tempElement;
            }
        }

    return newM;
}


Matrix mMath::Cofactor2x2(const Matrix& A)
{
    if (A.columns == 2 && A.rows == 2)
    {
        cout << "CANNOT FIND 2x2 COFACTOR MATRIX FOR NON-SQUARE MATRIX!\n";
        return A;
    }
    
    float cofactorMatrix[5][5] = {
        {A.M[1][1], -A.M[1][0]},
        {-A.M[0][1], A.M[0][0]}
    };

    Matrix cofactorA = A;
    cofactorA.SetMatrix(cofactorMatrix);

    return cofactorA;
}

Matrix mMath::Cofactor3x3(const Matrix& A)
{
    if (A.columns != 3 && A.rows != 3)
    {
        cout << "CANNOT FIND 3x3 COFACTOR MATRIX FOR NON-SQUARE MATRIX!\n";
        return A;
    }

    
    Matrix cofactorA = A;
    
    for (int r = 0; r < A.rows; ++r)
    {
        for (int c = 0; c < A.columns; ++c)
        {
            // Find the correct coordinates for the numbers
            // Using the rest function (%) to clamp the numbers between 0-2
            int r1 = (r+1)%A.rows;
            int r2 = (r+2)%A.rows;
            int c1 = (c+1)%A.columns;
            int c2 = (c+2)%A.columns;            

            // Calculating the two terms separately
            float a = A.M[r1][c1]*A.M[r2][c2];
            float b = A.M[r1][c2]*A.M[r2][c1];

            // Calculating the minor matrix for this element
            cofactorA.M[r][c] =
                ((r+c)%2 == 0 ? 1 : -1)             // If i+j is odd then -1, if even then 1
                * ((r+c)%2 == 0 ? a-b : b-a);       // Change subtraction direction if odd
        }
    }

    // Transpose the Cofactor Matrix to get the Inverse Matrix
    

    return cofactorA;
}

Matrix mMath::CofactorOver2(const Matrix& A)
{
    Matrix cofactorA = A;

    const int submatrixSize = A.rows-1; // It is square so we only need one

    // Go through the whole matrix
    for (int R = 0; R < A.rows; ++R)
    {
        for (int C = 0; C < A.columns; ++C) 
        {
            float tempSubmatrix[5][5];

            
            int rSkip = 0;
            
            // Create the submatrix for A[R][C] element
            for (int r = 0; r < submatrixSize; ++r)
            {
                // Skip row of RC-Element
                rSkip += r == R ? 1 : 0;
                int cSkip = 0;
                
                for (int c = 0; c < submatrixSize; ++c)
                {
                    // Skip column of RC-Element
                    cSkip += c == C ? 1 : 0;

                    tempSubmatrix[r][c] = A.M[r + rSkip][c + cSkip];
                }
            }
                
            Matrix submatrix(submatrixSize, submatrixSize, tempSubmatrix); 
            float minor = Determinant(submatrix); 

            // RC-Element in cofactor matrix becomes the determinant of the cofactor of A[R][C]
            cofactorA.M[R][C] = ((R+C)%2 == 0 ? 1 : -1) * minor;
            
            // -- Debugging --
            //submatrix.PrintMatrix(); //cout << "\n";
            //cout << "Determinant: " << minor << "\n";
            //cout << detA << "\n";
        }
    }
    
    return cofactorA;
}

Matrix mMath::Adjoint(const Matrix& A)
{
    if (A.columns != A.rows)
    {
        cout << "CANNOT FIND COFACTOR MATRIX FOR NON-SQUARE MATRIX AND THEREFORE THERE IS NO ADJOINT MATRIX!\n";
        return A;
    }

    switch (A.rows)
    {
    case 1: return A;
    case 2: return TransposeMatrix(Cofactor2x2(A));
    //case 3: return TransposeMatrix(Cofactor3x3(A));
    default:
        if (A.rows < 1)
        {
            cout << "WHERE IS YOUR MATRIX??\n";
            return A;
        }

        return TransposeMatrix(CofactorOver2(A));
    }    
}



float mMath::Determinant2x2(const Matrix& A)
{
    if (A.columns != A.rows)
    {
        cout << "CANNOT FIND DETERMINANT FOR NON-SQUARE MATRIX!\n";
        return 0;
    }

    return A.M[0][0]*A.M[1][1] - A.M[0][1]*A.M[1][0];
}

// This function is more performative for 3x3 than DeterminantOver2()
float mMath::Determinant3x3(const Matrix& A)
{
    if (A.columns != A.rows)
    {
        cout << "CANNOT FIND DETERMINANT FOR NON-SQUARE MATRIX!\n";
        return 0;
    }
    
    
    // Initialise determinant variable
    float detA = 0;

    // For the determinant we will not be iterating over the rows
    for (int c = 0; c < A.columns; ++c)
    {
        // Find the correct coordinates for the submatrix
        int r1 = 1%A.columns;
        int r2 = 2%A.rows;
        int c1 = (c+1)%A.columns;
        int c2 = (c+2)%A.columns;

        // Calculating the two terms separately
        float a = A.M[r1][c1]*A.M[r2][c2];
        float b = A.M[r1][c2]*A.M[r2][c1];

        // Calculating the element multiplied by its minor, and adding it to the determinant
        detA += A.M[0][c]
            * (c%2 == 0 ? -1 : 1)           // If c is odd then -1, if even then 1
            * (c%2 == 1 ? a-b : b-a);       // Change subtraction direction if odd
    }

    return detA;
}

float mMath::DeterminantOver2(const Matrix& A)
{
    float detA = 0;

    const int submatrixSize = A.rows-1; // It is square so we only need one

    for (int i = 0; i < A.columns; ++i)
    {
        float tempM[5][5];
        
        // Create the submatrix
        for (int r = 0; r < submatrixSize; ++r)
        {
            int cSkip = 0;
            for (int c = 0; c < submatrixSize; ++c)
            {
                // Skip column
                cSkip += c == i ? 1 : 0;
                
                tempM[r][c] = A.M[r + 1][c + cSkip];
            }
        }
            
        Matrix submatrix(submatrixSize, submatrixSize, tempM); 
        float minor = Determinant(submatrix); 

        detA += A.M[0][i] * minor
                * (i%2 == 0 ? 1 : -1);
        
        // -- Debugging --
        //submatrix.PrintMatrix(); //cout << "\n";
        //cout << "Determinant: " << minor << "\n";
        //cout << detA << "\n";
    }
    
    return detA;
}

float mMath::Determinant(const Matrix& A)
{
    if (A.columns != A.rows)
    {
        cout << "CANNOT FIND DETERMINANT FOR NON-SQUARE MATRIX!\n";
        return 0;
    }

    switch (A.rows)
    {
    case 1: return A.M[0][0];
    case 2: return Determinant2x2(A);
    //case 3: return Determinant3x3(A);
    default:
        if (A.rows < 1)
        {
            cout << "WHERE IS YOUR MATRIX??\n";
            return 0;
        }

        return DeterminantOver2(A);
        
        cout << "NO IMPLEMENTATION FOR DETERMINANT OF THE SQUARE MATRIX!\n";
    }    
}



Matrix mMath::Inverse(const Matrix& A)
{
    if (A.columns != A.rows)
    {
        cout << "CANNOT FIND INVERSE FOR NON-SQUARE MATRIX!\n";
        return A;
    }


    const float detA = Determinant(A);
    
    if (detA == 0)
        {
        cout << "Determinant is zero, cannot inverse!\n";
        return A;
        }

    
    Matrix tempA = Adjoint(A);

    tempA.ScaleMatrix(1/detA);

    return tempA;
}

