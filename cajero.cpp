#include "fajo.hpp"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct CompararFajos{
    bool operator()(const fajo& f1, const fajo& f2) const{
        return f1.valor() < f2.valor();
    }
};


fajos reintegrar(const fajos& caja, unsigned int cantidad){
    priority_queue<fajo, vector<fajo>, CompararFajos> monticulo(caja.begin(), caja.end());
    fajos reintegro;
    

    //Esquema devorador
    while(cantidad > 0 && !monticulo.empty()){
        fajo actual = monticulo.top();
        monticulo.pop();

        unsigned int valor = actual.valor();
        unsigned int unidades = actual.unidades();

        unsigned int billetesNecesarios = cantidad / valor;
        unsigned int billetesParaUsar = min(billetesNecesarios, unidades);

        if(billetesParaUsar > 0){
            reintegro.push_back(fajo(valor,billetesParaUsar));
            cantidad -= billetesParaUsar * valor;
        }
    }

    if (cantidad > 0){
        return fajos();
    }
    
    return reintegro;
}

int main(){
    ifstream datos("caja.dat");
    if(!datos){
        cerr << "ERROR: no se pudo abrir la caja" << endl;
        return 1;
    }
    
    fajos caja;
    datos >> caja;

    unsigned int cantidad;
    cout << "Introduzca una cantidad a reintegrar";
    cin >> cantidad;

    fajos resultado = reintegrar(caja, cantidad);

    if(resultado.empty() && cantidad > 0){
        cout << "No se puede proporcionar el reintegro solicitado" << endl;
    }else{
        cout << "Composicion del reintegro:" << endl;
        cout << resultado;
    }

    return 0;
}