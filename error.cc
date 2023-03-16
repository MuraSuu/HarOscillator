#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_trig.h>
#include <cstdio>

//This is the graph of the harmonic oscillator, or to put
//it simply, of a spring going back and forth in one dimension.

/*
I have chosen k = 8, m = 2.
As initial conditions I have chosen x'(0) = 0 but x(0) = x_0.
*/

//The parameters are mass and then the spring constant.
int Func(double t, const double y[], double dydt[], void* param)
{
    double* temp = static_cast<double*>(param);
    double m = temp[0], k = temp[1];
    dydt[0] = y[1];
    dydt[1] = -k/m * y[0];
    
    return GSL_SUCCESS;
}

int Jac(double t, const double y[], double* dfdy, double dfdt[], void* param)
{
    double* temp = static_cast<double*>(param);
    double m = temp[0], k = temp[1];
    
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix* ma = &dfdy_mat.matrix;
    
    gsl_matrix_set(ma, 0, 0, 0.0);
    gsl_matrix_set(ma, 0, 1, 1.0);
    gsl_matrix_set(ma, 1, 0, -k/m);
    gsl_matrix_set(ma, 1, 1, 0.0);
    
    return GSL_SUCCESS;
}

int main()
{
    double constants[] = {2, 8};
    
    gsl_odeiv2_system system = {Func, Jac, 2, &constants};
    gsl_odeiv2_driver* d = gsl_odeiv2_driver_alloc_y_new(&system, gsl_odeiv2_step_rk4,
                                                         1e-6, 1e-6, 0.0);
    double t = 0.0, t1 = 100.0;
    double y[2] = {1.0, 0.0};
    
    for(int i = 1; i <= 100; ++i)
    {
        double ti = i*t1/100;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        
        if(status != GSL_SUCCESS)
        {
            std::fprintf(stderr, "Error, return value: %d\n", status);
            break;
        }
        
        double a1 = y[0] - gsl_sf_cos(2.0*t);
        double a2 = y[1] + 2*gsl_sf_sin(2.0*t);
        
        std::printf("%.5e %.5e %.5e\n", t, a1, a2);
    }
    std::printf("End\n");
    gsl_odeiv2_driver_free(d);
}