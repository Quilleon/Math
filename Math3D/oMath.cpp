#include "oMath.h"
#include <cstdlib>
#include <iostream>
#include <string>



// --- Efficient way for computers to compute polynomials ---
// Value of x that you want to compute, polynomial degree, array of coefficients
double oMath::Horner(const double x, const int n, double a[])
{
    // Gives artifacts for some reason:
    //const int sizeA = sizeof(a) / sizeof(a[0]);
    
    double f = 0.0;
    for (int i = n; i >= 0; --i)
        f = x * f + a[i];
    return f;
}


// Both the function and it's derivative
//double f(double x) { return sin(x); }
//double df(double x) { return cos(x); }
double function[] = {-6, 11, -6, 1}; double f(double x) { return oMath::Horner(x, 3, function); } //double f(double x) { return x*x*x - 6*x*x + 11*x - 6; }
double derivative[] = {11, -12, 3}; double df(double x) { return oMath::Horner(x, 2, derivative); } //double df(double x) { return 3*x*x - 12*x + 11; }

std::pair<double, int> oMath::newton(double x0)
{
    int iter = 0;
    auto fx = f(x0);
    double x = x0;
    
    while (abs(fx) > 0.01)
    {
        x = x - fx/df(x);
        fx = f(x);
        iter++;
    }

    return std::pair<double, int>(x, iter);
}

double f(double x, double y) { return x * x * y; }

void oMath::NumericalIntegration() 
{
    
}

void oMath::oMathTests()
{
#pragma region Horners Method
    
    
    // Coefficients in order of degrees (c[0] is for x^0, c[1] is for x^1)
    double c[] = {-6, 11, -6, 1};
    
    // constexpr means it has to be computed/known in compile time and not in run-time
    constexpr int sizeC = std::size(c); //sizeof(c) / sizeof(c[0]);
    
    std::cout << oMath::Horner(2, sizeC-1, c) << std::endl;

    

#pragma endregion

    
#pragma region Newton Raphson Method

    
    // Run function with a guess at a zero (x0)
    auto par = oMath::newton(.5);//newton(0.785);
    std::cout << par.first << ", " << par.second << std::endl;
    
    
#pragma endregion
}
