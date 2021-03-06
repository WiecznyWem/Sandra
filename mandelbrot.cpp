#include "mandelbrot.h"
#include <complex>

Mandelbrot::Mandelbrot() : System()
{
    repository.Register("color_r", &c_r);
    repository.Register("color_g", &c_g);
    repository.Register("color_b", &c_b);
    repository.Register("iterations", &max_iter);
    repository.Register("pointX", &px);
    repository.Register("pointY", &py);
   // repository.Register("sps", &sps);
    repository.Register("coloring", &coloring);
    repository.Register("radius", &r);
    repository.Register("hole", &hole);
    repository.Register("sefby", &sefby);
    repository.Register("initial_width", &wid);
   // scale = 1;
}

void Mandelbrot::Before()
{
    d2 = 1.0 / (double)(width * height);

    cwidth = wid;



}

void Mandelbrot::After()
{

}

void Mandelbrot::DrawFrame(cv::Mat frame)
{
    // złap zmienne
    double pointX = px.Get(), pointY = py.Get(); // środek obszaru obserwowanego
    // scale per frame
  //  double spf = sps.Get() / fps;
    //scale += spf;
   // std::cout<<"s: "<<spf<<std::endl;
    // Proporcja obrazu
    double frameRatio = (double)width / (double)height;

    // Szerokość i wysokość obserwowanego fragmentu układu współrzędnych x = Re, y = Im
    // nie, niepamiętma dlaczego akurat C...
    double  cheight = 0;

    // !!!
    // To scale jest jakieś dziwne, szczególnie w przypadku oddalania w wideo
    //cwidth = 4.0 / ( 1.0 / scale ); // Pytasz dlaczego 4.0? GCC powiedział by że: "bo tak, inaczej nie kompiluje". Jest po to, żeby zmieścić rzutownie wszytskich jego kaprysów na klatke(glębkoie czarne dziury)



    cwidth  *= sefby.Get();  ;


    cheight =  cwidth / frameRatio;

    // Punk
    //ty graniczne układu tworzące prostokąt
    double minRe, maxRe;
    double minIm, maxIm;

    minRe = pointX - cwidth / 2.0;
    maxRe = pointX + cwidth / 2.0;

    minIm = pointY - cheight / 2.0;
    maxIm = pointY + cheight / 2.0;


    // iter
    unsigned int maxIterations = max_iter.Get();


    double radius = r.Get();




    Argument<double> color_r = c_r;
    Argument<double> color_g = c_g;
    Argument<double> color_b = c_b;

    color_r.Prepare();
    color_g.Prepare();
    color_b.Prepare();

    // Czy dziura ma być czarna?
    bool black_hole = hole;

    if(filetype == "image")
        WriteProcessInfo();
    // Lecimy dla każdeo punktu z klatki
    for(unsigned int y = 0; y < height; ++y)
    {
        double cIm = maxIm - (double)y*(double)(  (maxIm-minIm)/(height-1) );

        for(unsigned int x = 0; x < width; ++x)
        {
            double cRe = minRe + (double)x*(double)  (  (maxRe-minRe)/(width-1) );
            // Zmienna zespolona c, pozycja (x, y) w układzie współrzednych (Re, Im)

            //  Z, to dopiero prawdziwe wariacje
            double zRe = cRe;
            double zIm = cIm;


            bool inside = true;

            // nnn to niezykła zmienna, albo raczej jej nazwa
            // Mimo tego że jest kompletnie bez sensu, tak zapadła mi w głowie, że nie ma sansu zmieniać jej nazwy
            // A oznacza tyle, ile było iteracji przez zakończeniem iterowania
            unsigned int nnn=  0;

            double abs2 = 0;// = sqrt( zRe*zRe + zIm*zIm );

            // hmmm...
            //double m = std::exp(-1.0 * sqrt( zRe*zRe + zIm*zIm ) ) ;

            // Procent użytwany do palety z kolorami
            double m = 0;

            for(unsigned int i = 1; i <= maxIterations ; i++)
            {
                nnn = i; // :)



                // Jeden ze starych pomysłów, na wszelki przypadek go zostawię
                //m += std::exp(-1.0 * abs ) ;

                // Z = z^2 + c; Liczę na doublach, bo std::complex jest jakieś dziwne
                double zIm2 = zIm*zIm; // pomocnik
                zIm = 2 * zRe*zIm + cIm;
                zRe = zRe*zRe - zIm2 + cRe;

                // KWADRAT Z PIATORASA! (wartość bezwzględna do kwadratu)
                // cóż za sprytne optymalizacje ;)
                abs2 =  zRe*zRe + zIm*zIm ;

                if(coloring == "logarithmic_sinus"|| coloring == "logarithmic_sinus2" || coloring == "loglog")
                if(abs2 >= radius * radius) // standardowo ma być w, ale co tam...
                {
                    inside = false;
                    break;

                }

                if(coloring == "linear")
                if( abs2 > 4 /* 2 * 2 */)
                {
                    inside = false;

                    m = (double) i / (double) maxIterations;
                    frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                    frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                    frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);



                    break;
                }


            }

            if(coloring == "logarithmic_sinus2")
            {
                m = 0.5+ 0.5* sin (  (nnn + 1 - log( log( sqrt(abs2  ))) / log(2) ) / ( (double)(maxIterations)))  ;

                // Prawda że czytelnie wygląda, ale fajne jest
                // Tylko jakiś rewolucjonista wymyślił sobie format  koloru BGR
                frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);
            }

            if(coloring == "logarithmic_sinus")
            {
                m = 0.5+ 0.5* sin (  nnn -   (  log2 (  sqrt(abs2) ) / log2( radius )      ))  ;

                // Prawda że czytelnie wygląda, ale fajne jest
                // Tylko jakiś rewolucjonista wymyślił sobie format  koloru BGR
                frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);
            }

            if(coloring == "loglog")
            {
                //n + 1 - Math.log(Math.log(zn.abs()))/Math.log(2)
                m = (nnn + 1 - log( log( sqrt(abs2  ))) / log(2) ) / ( (double)(maxIterations));
                //m = 0.5+ 0.5* sin (  nnn -   (  log2 (  sqrt(abs2) ) / log2( radius )      ))  ;

                // Prawda że czytelnie wygląda, ale fajne jest
                // Tylko jakiś rewolucjonista wymyślił sobie format  koloru BGR
                frame.data[frame.step*y + frame.channels()* x + 0] = color_b.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x +1] = color_g.GetAbsolute(m);
                frame.data[frame.step*y + frame.channels()* x + 2] = color_r.GetAbsolute(m);
            }

            // Klient bierze w ciemno
            if(black_hole&& inside)
            {
                frame.data[frame.step*y + frame.channels()* x + 0] = 0;
                frame.data[frame.step*y + frame.channels()* x +1] = 0;
                frame.data[frame.step*y + frame.channels()* x + 2] = 0;
            }

            if(filetype == "image")
            {
                ReadProcessInfo(d2);
                WriteProcessInfo();
            }


        }
    }



}
