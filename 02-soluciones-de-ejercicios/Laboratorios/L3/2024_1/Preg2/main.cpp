#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Paquete {
    int id;
    int ganancia;
    int peso;
};

void ImprimirPaquetes(const vector<Paquete> &paquetes) {
    for (int i=0;i<paquetes.size();i++) {
        cout << "{ Id Paquete: "<<paquetes[i].id<<", peso: "<< paquetes[i].peso
            <<", ganancia: "<< paquetes[i].ganancia <<"}"<< endl;
    }
}

struct Contenedor {
    int peso;
    int pesoSobrante=peso;
    int ganancia=0;
    vector <Paquete> paquetesAsig;
};

void ImprimirContenedor(const Contenedor contenedor) {
    cout<<"Solucion empleando un algoritmo heuristico voraz"<<endl;
    cout<<"Peso sobrante: "<< contenedor.pesoSobrante<<" Tn"<<endl;
    cout<<"Ganancia de la exportacion: "<< contenedor.ganancia<<" en miles de dolares"<<endl;
    // cout<<"Paquetes asignados: "<<endl;
    // ImprimirPaquetes(contenedor.paquetesAsig);
}

void MejorSolucion(const vector<Paquete> &paquetes,Contenedor &contenedor) {
    for (int i=0;i<paquetes.size();i++) {
        if (contenedor.pesoSobrante-paquetes[i].peso>=0) {
            contenedor.paquetesAsig.emplace_back(paquetes[i]);
            contenedor.pesoSobrante-=paquetes[i].peso;
            contenedor.ganancia+=paquetes[i].ganancia;
        }
    }
}




int main() {

    vector<Paquete> paquetes {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,24,12},
        {5,8,2}
    };

    // vector<Paquete> paquetes {
    //     {1,10,2},
    //     {2,15,3},
    //     {3,10,5},
    //     {4,14,12},
    //     {5,8,2},
    //     {6,5,5}
    // };

    //Asiggnación peso contenedor
    Contenedor contenedor{16};

    std::sort(paquetes.begin(), paquetes.end(),[](const Paquete &a,const Paquete &b) {
        return a.ganancia/a.peso>b.ganancia/b.peso;
    });

    MejorSolucion(paquetes,contenedor);
    ImprimirContenedor(contenedor);

    return 0;
}