#ifndef LISSAJOUS_H
#define LISSAJOUS_H

#include "system.h"

/**
 * @brief Animacja: Zmodyikowane krzywe Lissajous
 *
 * Całkiem ciekawe obracanie krzywą z równania okręgu za pomocą zmiennych parametrów
 */
class Lissajous : public System
{
private:
    /**
     * @brief Promień okręgu
     */
    Argument<double> radius;
    /**
     * @brief Skalowanie na osi X
     */
    Argument<double> scale_x;
    /**
     * @brief Skalowani na osi Y
     */
    Argument<double> scale_y;
    /**
     * @brief Współczynnik cosinusa
     */
    Argument<double> factor_x_cos;
    /**
     * @brief Współczynnik sinusa
     */
    Argument<double> factor_y_sin;
    /**
     * @brief Rozmiar skoku
     */
    Argument<double> jump;
    /**
     * @brief Dokładność z jaką okrą będzie rysowany
     */
    Argument<unsigned int> precision;
    /**
     * @brief Ilość skoków
     *
     * Tak, ona jest wymierna! Daje to ładny efekt zwijania bądź rozwijania spirali
     */
    Argument<double> jumps;

    /**
     * @brief Kolor czerwony
     */
    Argument<double> color_r;
    /**
     * @brief Kolor zielony
     */
    Argument<double> color_g;
    /**
     * @brief Kolor niebieski
     */
    Argument<double> color_b;

    /**
     * @brief Czy robić spiralą cz okręgiem
     */
    bool spiral;

public:
    Lissajous();

    void Before();
    void After();

    /**
     * @brief Rendeuje animacje
     */
    void DrawFrame(cv::Mat frame);

};

#endif // LISSAJOUS_H
