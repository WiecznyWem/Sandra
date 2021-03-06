#ifndef ATTRACTOR_CONNECTIONS_H
#define ATTRACTOR_CONNECTIONS_H

#include "system.h"

class AttractorConnections : public System
{
private:


    Argument<unsigned  int> iterations;


    Argument<double> c_r ;
    Argument<double> c_g ;
    Argument<double> c_b ;


    Argument<double> A_a;
    Argument<double> A_b;
    Argument<double> A_c;
    Argument<double> A_d;

    Argument<double> A_e;
    Argument<double> A_f;
    Argument<double> A_g;
    Argument<double> A_h;

    double x0, y0, m0, x, y, z, z0, x00, y00;

    double **licznik;
    double maks;
     double a, b, c, d, e, f, g, h;

public:
    AttractorConnections();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);
};

#endif // ATTRACTOR_CONNECTIONS_H
