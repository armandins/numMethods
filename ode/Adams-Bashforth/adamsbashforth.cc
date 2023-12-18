/*
    *******************************************************************
    Arman Dindar Safa
    12 / 18 / 2023
    This script approximates for a differential equation
    using Adams-Bashforth 4-th order method.
    Writes the results to a *.dat file. 
    A Python script is provided to post proccess the results.
    *******************************************************************
*/
#include <iostream>
#include <fstream>
#include <vector>

// --------------------------------------------------------------------
// Define the function y' = f(x, y)
// in this case : y' = x + y 

double f(double x, double y){
    return y + x;
}

// --------------------------------------------------------------------

int main() {
    // ------------------------------------
    // declare initial values and step size
    double x0 = 0.0; // Initial value of x
    double y0 = 1.0; // Initial value of y
    double h = 0.2; // Step size
    int numSteps = static_cast<int>((5 - x0) / h); // Number of steps

    std::vector<double> x(numSteps + 1);
    std::vector<double> y(numSteps + 1);

    x[0] = x0;
    y[0] = y0;

    // Using fourth-order Adams-Bashforth method
    // AB4th -----------------------------------
    for (int i = 0; i < 3; i++) {
        double k1 = h * f(x[i], y[i]);
        double k2 = h * f(x[i] + h / 2, y[i] + k1 / 2);
        double k3 = h * f(x[i] + h / 2, y[i] + k2 / 2);
        double k4 = h * f(x[i] + h, y[i] + k3);
        y[i + 1] = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x[i + 1] = x[i] + h;
    }

    for (int i = 3; i < numSteps; i++) {
        y[i + 1] = y[i] + h * (55 * f(x[i], y[i]) - 59 * f(x[i - 1], y[i - 1]) + 37 * f(x[i - 2], y[i - 2]) - 9 * f(x[i - 3], y[i - 3])) / 24;
        x[i + 1] = x[i] + h;
    }
    // --------------------------------
    // Write the results to a .dat file
    std::cout << "Initial Conditions: " << '\n';
    std::cout << "x_0 :" << x0 << '\n';
    std::cout << "y_0 :" << y0 << '\n';
    std::cout << "Step size :" << h << '\n';
    std::cout << "Writing Results to adams_bashforth_results.dat ..." << '\n';
    std::ofstream outFile("adams_bashforth_results.dat");
    for (int i = 0; i <= numSteps; i++) {
        outFile << x[i] << " " << y[i] << std::endl;
    }
    outFile.close();
    std::cout << '\n';
    std::cout << "Done." << '\n';
    std::cout << "adams_bashforth_results.dat generated." << '\n';

    return 0;
}