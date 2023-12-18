/*
    *******************************************************************
    Arman Dindar Safa
    12 / 18 / 2023
    This script solves a differential equation
    using Runge-Kutta 2nd, 3rd and 4th order methods
    Writes the results to 3 different files. 
    A Python script is provided to post proccess the results.
    *******************************************************************
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// --------------------------------------------------------------------
// Problem declaration
// in this case : 
//      dy/dx = x + y

double yprime(double x, double y){
    return x + y; // Example function, you can replace it with your own
}

// --------------------------------------------------------------------
// 2nd Order Runge - Kutta

void rungeKutta2(double x0, double y0, double h, double xn) {
    ofstream file("runge_kutta_2nd_order.dat");
    double k1, k2;
    while (x0 < xn) {
        k1 = h * yprime(x0, y0);
        k2 = h * yprime(x0 + h, y0 + k1);
        y0 = y0 + 0.5 * (k1 + k2);
        x0 = x0 + h;
        file << x0 << " " << y0 << '\n';
    }
    file.close();
}

// --------------------------------------------------------------------
// 3rd Order Runge - Kutta

void rungeKutta3(double x0, double y0, double h, double xn) {
    ofstream file("runge_kutta_3rd_order.dat");
    double k1, k2, k3;
    while (x0 < xn) {
        k1 = h * yprime(x0, y0);
        k2 = h * yprime(x0 + 0.5 * h, y0 + 0.5 * k1);
        k3 = h * yprime(x0 + h, y0 - k1 + 2 * k2);
        y0 = y0 + (1.0 / 6.0) * (k1 + 4 * k2 + k3);
        x0 = x0 + h;
        file << x0 << " " << y0 << '\n';
    }
    file.close();
}

// --------------------------------------------------------------------
// 4th Order Runge - Kutta

void rungeKutta4(double x0, double y0, double h, double xn) {
    ofstream file("runge_kutta_4th_order.dat");
    double k1, k2, k3, k4;
    while (x0 < xn) {
        k1 = h * yprime(x0, y0);
        k2 = h * yprime(x0 + 0.5 * h, y0 + 0.5 * k1);
        k3 = h * yprime(x0 + 0.5 * h, y0 + 0.5 * k2);
        k4 = h * yprime(x0 + h, y0 + k3);
        y0 = y0 + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        x0 = x0 + h;
        file << x0 << " " << y0 << '\n';
    }
    file.close();
}

// --------------------------------------------------------------------
// Set initial conditions. 
// Keep in mind step size should preferably be smaller, but a big value
// is obtained to show the accuracy of different percisions. 

int main() {
    double x0 = 0, y0 = 1, xn = 5, h = 0.5; // Initial values and step size
    rungeKutta2(x0, y0, h, xn);
    rungeKutta3(x0, y0, h, xn);
    rungeKutta4(x0, y0, h, xn);
}