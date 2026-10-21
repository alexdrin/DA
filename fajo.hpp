#ifndef fajo_hpp
#define fajo_hpp

#include <iostream>
#include <vector>


class fajo{
    public:
        fajo(): v{0}, u{0} {}
        fajo(unsigned int v, unsigned int u): v{v}, u{u} {}

        unsigned int valor() const { return v; }
        unsigned int& valor() { return v; }

        unsigned int unidades() const { return u; }
        unsigned int& unidades() { return u; }
    private:
        unsigned int v, u;  // Valor y número de unidades de cada billete
};

using fajos = std::vector<fajo>;

std::istream& operator>>(std::istream& entrada, fajo& f);
std::istream& operator>>(std::istream& entrada, fajos& f);
std::ostream& operator<<(std::ostream& salida, const fajo& f);
std::ostream& operator<<(std::ostream& salida, const fajos& f);







#endif