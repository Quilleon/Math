#pragma once
#include <utility>

// NOTE: This is the horner and newton methods from earlier lecture notes and is not relevant for the matrices

class oMath
{
public:
    
    static double Horner(const double x, const int n, double a[]);
    
    static std::pair<double, int> newton(double x0);

    void NumericalIntegration();

    void oMathTests();
    
};
