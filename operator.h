#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <list>

#include "command.h"
#include "argument.h"
#include "operatoritem.h"
#include "convert.h"


/**
 * @brief Sprytne wczytywanie wejścia
 *
 * Operator... Marna nazwa, z czasem wymyśliłem fajniejszą - repozytorium.
 * Ale find&repleace może mi nieźle namieszać, a są ważniejsze rzeczy do roboty niż podłoże techniczne
 *
 * Po pierwsze, to sposób jest sprytny, a nie wykonanie. Na 100%
 * funkcję Add można by zapisać o wiele wiele lepiej. Zależało mi
 * na szbkim efekcie. Jeżeli będziesz mieć nadmiar czasu możesz usprawnić.
 *
 *
 * Wygodna wczytywania wejścia za pomocą tej klasy jest nastepująca:
 * - Za pomocą metody register można powiązać nazwę(jako ciąg znaków)
 * z realnym obiektem(double, int, unsined, Argument)
 *
 * - Funckaj Add sama zajmie się zczytaniem i wpisaniem
 * (wystarczy tylko dać jej argument Command)
 *
 * Liczne prywatne listy są to konrenery gdzie przechowuje nazwę powiązaną
 * z realnym obiektem.
 *
 * Uwaga: Metoda Add działa pesymistycznie(czyli dla głównie stringów ale i nie tylko, czytaj kod żeby wiedzieć czemu)
 * o złożoności O(N), gdzie N to ilość wszytstkich elementów we wsztskich listach
 * Można by to ztegować do O(LOG2(N)) ale nie chcę mi się, wolę zająć się głównym tematem pracy
 *
 *
 */
class Operator
{

private:
    std::list<OperatorItem<double> > _double;
    std::list<OperatorItem<int > > _int;
    std::list<OperatorItem<unsigned int> > _uint;
    std::list<OperatorItem<bool> > _bool;
    std::list<OperatorItem<std::string> > _string;

    std::list<OperatorItem< Argument<double> > > _arg_double;
    std::list<OperatorItem< Argument<int> > > _arg_int;
    std::list<OperatorItem< Argument<unsigned int> > > _arg_uint;

public:
    Operator();

    bool Add(Command *command);

    void Register(std::string name, double* object);
    void Register(std::string name, int* object);
    void Register(std::string name, unsigned int* object);
    void Register(std::string name, bool* object);
    void Register(std::string name, std::string* object);

    void Register(std::string name, Argument<double>* object);
    void Register(std::string name, Argument<int>* object);
    void Register(std::string name, Argument<unsigned int>* object);


    void PrepareArgs();
    void UpdateArgs(double dt);
};

#endif // OPERATOR_H
