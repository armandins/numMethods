/*

  Arman Dindar Safa - 12 / 18 / 2024
  High Performance Runge-Kutta 4-th Order Solver
  Results are written to (filename.csv)
  Execute via: 

  g++ <FILE.cc> -o <FILE>
  ./<FILE>

  Note: Set compiler to C++20 or above.
  Note: Use std::numbers to have access to values for pi, e, etc. 
  https://en.cppreference.com/w/cpp/symbol_index/numbers

*/

/*
  Variables: 

  h        == Stepsize
  half_h   == Half the stepsize
  k1
  k2
  k3
  k4
  stepSize == h
  yNod     == Initial value of y (at point zero)
  tNod     == Initial value of t (at point zero)
  tFin     == Maximum time
  ODEFN    == Name of the output file

*/

#define PI 3.141592653589793238462643383279502884197169399375105820974944

#include <fstream>
#include <iostream>
#include <iomanip>
#include <numbers>
#include <string> 
#include <type_traits>
#include <vector>

// +++++++++++++++++++++++++++++++++++++++
// Boolean below controls SP and DP
// +++++++++++++++++++++++++++++++++++++++
constexpr bool DP  {false};
using real_t = std::conditional_t<DP, float, double>;

namespace RK4 {
template <typename Func>
std::vector<std::pair<real_t, real_t>> solve(Func&& f, real_t yNod, real_t tNod, real_t tFin, real_t stepSize) {
    // Memory Pre-allocation
    size_t num_steps = static_cast<size_t>((tFin - tNod) / stepSize) + 1;
    std::vector<std::pair<real_t, real_t>> results;
    results.reserve(num_steps);

    real_t t {tNod};
    real_t y {yNod};
    results.emplace_back(t, y);

    while (t < tFin) {
        real_t h = stepSize;
        if (t + h > tFin) h = tFin - t;

        // -------------------
        // ----    RK4    ----
        // -------------------

        real_t halfh   {h / 2};
        real_t k1      {h * f(t, y)};
        real_t k2      {h * f(t + halfh, y + k1 / 2)};
        real_t k3      {h * f(t + halfh, y + k2 / 2)};
        real_t k4      {h * f(t + h, y + k3)};
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        t += h;

        results.emplace_back(t, y);}
    return results;
}} 

namespace FILEIO {

void write_results(const std::vector<std::pair<real_t, real_t>>& results, const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file.");
    }

    file << std::fixed << std::setprecision(DP ? 8 : 14);
    //file << "t" << '\t' << "y" << '\n';

    for (const auto& [t, y] : results) {
        file << t << ", " << y << '\n';
    }}} 

int main() {
    // Explanation of how ODEs are defined using ODE function.
    // ---------------------------------------------------
    // ---   ODE => y'    + 2y - t^2 = 0               ---
    // ---          y' =  - 2y + t^2                   ---
    // ---         ODE =  - 2y + t^2                   ---
    // ---------------------------------------------------

    auto ODE = [](real_t t, real_t y) -> real_t {
        return -2.0 * y + t * t; //ODE Lambda
    };
    

    // -------------------
    // ---   Params.   ---
    // -------------------
    real_t      stepSize  {0.1};        // Step size
    real_t          yNod  {1.0};        // Initial value
    real_t          tNod  {0.0};        // Start time
    real_t          tFin  {2.0};        // End time    
    std::string    ODEFN  {"RES.csv"};  // Test ODE output file
    
    auto odeResults  = RK4::solve(ODE, yNod, tNod, tFin, stepSize);
    
    // File manipulator _ Error handler
    try {
        FILEIO::write_results(odeResults, ODEFN);
        std::cout << "Results written to 'results.csv' with "
                  << (DP ? "single precision" : "double precision") << '\n';
    } catch (const std::ios_base::failure& e){std::cerr << "Error: " << e.what() << '\n';}
    return 0.0;
}
