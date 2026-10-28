#include "particion.hpp"
#include "grafo-ponderado.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <queue>
#include <vector>

template <typename G>
G Kruskal (const G& g){
    using std::size_t;
    using std::list;
    using Arista = typename G::Arista;
    size_t n = g.vertices();
    G s(n);
    Particion p(n);
    list <Arista> c(g.aristas());

    //Preordenacion de las aristas lambda
    c.sort([](const Arista& a, const Arista& b){
        return a.peso() < b.peso(); 
    });

    size_t aristas_arbol = 0;
    for(const auto& arista : c){
        if(aristas_arbol == n - 1) break; //Minimo tiene n-1 aristas

        int u = p.buscar(arista.primero());  
        int v = p.buscar(arista.segundo());

        if(u != v){
            p.unir(u, v);
            s.insertar(arista);
            aristas_arbol++;
        }
    }   
    return s;
}

template <typename G>
G KruskalMonticulo(const G& g){
    using std::size_t;
    using Arista = typename G::Arista;  

    size_t n = g.vertices();
    G s(n);
    Particion p(n);

    auto comp = [](const Arista& a, const Arista& b) {return a.peso() > b.peso();};
    std::priority_queue<Arista, std::vector<Arista>, decltype(comp) > monticulo(comp);

    for(const auto& arista : g.aristas()){
        monticulo.push(arista);
    }

    size_t aristas_arbol = 0;
    while(!monticulo.empty() && aristas_arbol < n - 1){
        Arista arista = monticulo.top();
        monticulo.pop();

        int u = p.buscar(arista.primero());
        int v = p.buscar(arista.segundo()); 

        if(u != v){
            p.unir(u,v);
            s.insertar(arista);
            aristas_arbol++;
        } 
    }
    return s;
}

int main(){
    std::ifstream archivo("grafo.dat");
    if(!archivo) return 1;

    GrafoPonderado<int, double> g;
    archivo >> g; 

    auto arbol1 = Kruskal(g);
    std::cout << "Kruskal (Preordenacion):\n" << arbol1 << "\n";

    auto arbol2 = KruskalMonticulo(g);
    std::cout << "Kruskal (Monticulos):\n" << arbol2 << "\n";

    return 0;
}