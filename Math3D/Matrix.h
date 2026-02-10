#pragma once
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
    
    void PrintMatrix() const
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                std::cout << M[r*columns+c] << ", "; 
            }
            std::cout << "\n";
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
};



struct OldMatrix
{
    int rows;
    int columns;
    
    // Max size of 5x5
    float M[5][5];

    
    // Constructor
    OldMatrix(int r, int c, float A[5][5])
    {
        // Saving the size of the Matrix (max 5x5)
        rows = r > 5 ? 5 : r;
        columns = c > 5 ? 5 : c;

        // Setting the matrix
        SetMatrix(A);
    }

    void SetMatrix(float newM[5][5])
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                M[r][c] = newM[r][c]; 
            }
        }
    }

    
    void PrintMatrix() const
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                std::cout << M[r][c] << ", "; 
            }
            std::cout << "\n";
        }
    }

    void TransposeMatrix()
    {
        float tempM[5][5];
        
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                tempM[r][c] = M[c][r];
            }
        }

        SetMatrix(tempM);
    }
    
    void ScaleMatrix(float scale)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                M[i][j] *= scale;
            }
        }
    }
};
