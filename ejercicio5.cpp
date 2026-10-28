#include "grafo-ponderado.hpp"
#include "particion.hpp"
#include "cronometro.hpp" // De la Práctica 0
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


GrafoPonderado<int, double> generarGrafoPeorCaso(int v) {
    GrafoPonderado<int, double> g(v);
    // Unimos (0 con i) con peso muy alto (estos formarán el árbol al final)
    for (int i = 1; i < v; ++i) {
        g.insertar(AristaPonderada<int, double>(0, i, 1000.0));
    }
    // El resto de aristas forman ciclos entre sí con pesos muy bajos
    for (int i = 1; i < v; ++i) {
        for (int j = i + 1; j < v; ++j) {
            g.insertar(AristaPonderada<int, double>(i, j, 1.0));
        }
    }
    return g;
}

int main() {
    cronometro c;
    std::cout << "V\tT_Preordenacion\tT_Monticulo\n";

    for (int v = 10; v <= 500; v += 10) {
        auto g = generarGrafoPeorCaso(v);

        // Medir Kruskal con Preordenación
        c.activar();
        Kruskal(g);
        c.parar();
        double t_pre = c.tiempo();

        // Medir Kruskal con Montículos
        c.activar();
        KruskalMonticulo(g);
        c.parar();
        double t_monticulo = c.tiempo();

        std::cout << v << "\t" << t_pre << "\t" << t_monticulo << "\n";
    }
    return 0;
}