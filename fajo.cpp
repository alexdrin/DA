#include "fajo.hpp"
#include <iterator>
#include <algorithm>

using namespace std;

istream& operator>>(istream& entrada, fajo& f){
    return entrada >> f.valor() >> f.unidades();
}

istream& operator>>(istream& entrada, fajos& f){
    istream_iterator<fajo> inicio(entrada), fin;
    copy(inicio, fin, back_inserter(f));
    return entrada;
}

ostream& operator<<(ostream& salida, const fajo& f){
    return salida << f.unidades() << "billete" << (f.unidades() == 1 ?  "" : "s") << " de " << f.valor();
}

ostream& operator<<(ostream& salida, const fajos& f){
    copy(begin(f), end(f), ostream_iterator<fajo>(salida, "\n"));
    return salida;
}