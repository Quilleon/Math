#pragma once
#include <iomanip>
#include <iostream>
#include <utility>

struct Matrix
{
    int rows;
    int columns;
    
    std::vector<float> M;

    Matrix(int r, int c, std::vector<float> A)
    {
        rows = r;
        columns = c;

        SetMatrix(std::move(A));
    }

    // Return the position of the float in the matrix
    float P(int r, int c)
    {
        return r*columns + c;
    }

    void SetMatrix(std::vector<float> A)
    {
        M = std::move(A); // What is move??
    }
    
    void PrintMatrix(int precision = 3) const
    {
        for (int r = 0; r < rows; ++r)
        {
            // Frame
            std::cout << "|";
            
            for (int c = 0; c < columns; ++c)
            {
                // Set decimal precision to 3 for all numbers
                std::cout << std::fixed << std::setprecision(precision) << M[r*columns+c];

                // Print comma between column-values
                if (c+1 < columns)
                    std::cout << ", ";
            }
            
            // Frame
            std::cout << "|\n";
        }
    }

    void TransposeMatrix()
    {
        std::vector<float> tempM(rows*columns);
        
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                tempM[r*rows+c] = M[c*columns+r];
            }
        }

        M = tempM;
    }

    void ScaleMatrix(float scale)
    {
        for (float& i : M)
            i *= scale;
    }


    // Getter I implemented late
    float Mat(int r, int c) const { return M[r*columns+c]; }
    void SetMat(int r, int c, float x) { M[r*columns+c] = x; }
    
    void LU()
    {
        for (int k=0; k<rows-1; k++)
        {
            if (Mat(k, k) == 0)
            {
                std::cout << "Zero pivot! LU without pivot failed! \n";
                return;
            }
            
            // pivot(k);
            // By row operations we obtain 0 under diagonal element
            // in all rows below (column k)
            // We subtract a multiplum of kth row
            // from the rows below, starting from left
            
            for (int i=k+1; i<rows; i++)
            {
                // Multiply with this and subtract from row i
                // This becomes zero, store factor here
                //M[i][k] = M[i][k]/M[k][k];
                SetMat(i, k, Mat(i, k)/Mat(k, k));
                
                for (int j=k+1; j<columns; j++)
                {
                    // column to the right of the column which gets zeros
                    //M[i][j] = M[i][j] - M[i][k]* M[k][j];
                    SetMat(i, j, Mat(i, j) - Mat(i, k)*Mat(k, j));
                }

                // Set zeros in the triangle
                SetMat(i, k, 0);
            }
        }
    }
};