#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Tabla {
    int id;
    int veloc;
};

void ImprimirTablas(const vector <Tabla>  &tabla) {
    for (int i=0;i<tabla.size();i++) {
        cout << "{ id: " << tabla[i].id << ", veloc: " << tabla[i].veloc << "} ";
    }
}

struct Disco {
    int id;
    int veloc;
    int velocInicial = veloc; //copia veloc inicial;
    vector<Tabla> tablas_Asig;
};

void ImprimirDiscos(const vector<Disco> &discos) {

    for (int i=0;i<discos.size();i++) {
        cout<<"Disco "<<discos[i].id<<", velocidad inicial: "<<discos[i].velocInicial<<
            ", velocidad residual: "<<discos[i].veloc<<endl;
        cout<<"Tablas Asignadas: ";
        ImprimirTablas(discos[i].tablas_Asig);
        cout<<endl;
    }
}
//"Discos de mayor velocidad"
Disco *buscarMejorDisco(vector<Disco> &discos) {
    Disco *mejorDisco = &discos[0];
    for (int i=0;i<discos.size();i++) {
        Disco *disco = &discos[i];
        if (disco->veloc > mejorDisco->veloc) {
            mejorDisco = &discos[i];
        }
    }

    return mejorDisco;
}


void ProgramacionDeTareas(vector<Disco> &discos,const vector <Tabla> &tablas) {
    for (int i=0;i<tablas.size();i++) {
        Disco *disco = buscarMejorDisco(discos);
        disco->veloc-=tablas[i].veloc;
        disco->tablas_Asig.push_back(tablas[i]);
    }
}

int main() {
    vector<Tabla> tablas {
        {1,150},
        {2,100},
        {3,180},
        {4,50},
        {5,120},
        {6,10}
    };

    vector<Disco> discos {
        {1,250},
        {2,200},
        {3,200},
        {4,100}
    };

    //Heurística : "asignación de tablas con demanda de mayor velocidad..."
    std::sort(tablas.begin(), tablas.end(), [](const Tabla &a, const Tabla &b) {
        return a.veloc > b.veloc;
    });

    ProgramacionDeTareas(discos,tablas);
    ImprimirDiscos(discos);


}