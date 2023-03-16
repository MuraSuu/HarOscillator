#include <cstdio>
#include <gsl/gsl_sf_trig.h>
#include <cmath>

//Plot: phase space of the Harmonic Oscillator in the hamiltonian system
//using the exact solutions.
#define Sin gsl_sf_sin
#define Cos gsl_sf_cos
int main()
{
    const double k = 4.0; const double m = 2.0;
    const double a = std::sqrt((k*k)/m);
    double x = 0.0, p = 0.0;
    double t = 0.0;
    
    for(int j = 1; j <= 4; ++j)
    {
        double x_0 = 1*j;
        double p_0 = 2/j;
        for(int i = 1; i <= 2000; ++i)
        {
            t = i*0.05;
            x = x_0*Cos(a*t) - (p_0/(m*a))*Sin(a*t);
            p = p_0*Cos(a*t) + ((k*k*x_0)/a)*Sin(a*t);
            std::printf("%.5e %.5e\n", x, p);
        }
        std::printf("End\n");
    }
}