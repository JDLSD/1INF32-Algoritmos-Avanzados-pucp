#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>


using namespace std;

struct Orden {
    int id;
    int tipo;
    int peso;
    int tiempo;
};

struct Maquina {
    int id;
    int tiempoAcumulado;
    vector<Orden> ordenesRealizadas;
};

void ImprimirTareas(const vector <Orden> &ordenes) {
    int suma=0;
    for (int i=0; i < ordenes.size(); i++) {
        suma+=ordenes[i].tiempo;
        cout << "{Tarea: "<< ordenes[i].id << ", peso: "<<ordenes[i].peso<<"kg} ";
        //cout <<" Tiempo :"<< ordenes[i].tiempo<<" ";
    }
    cout<<"Tiempo acumulado:"<<suma;
    cout <<endl;
}

void ImprimirMaquinas(const vector <Maquina> & maquina) {
    for (int i=0 ; i<maquina.size() ; i++) {
        cout << "Maquina:"<<maquina[i].id << " Tiempo acumulado: " <<maquina[i].tiempoAcumulado<<endl;
        ImprimirTareas(maquina[i].ordenesRealizadas);

    }
}

Maquina *buscarMejorMaquin(vector<Maquina> &maquinas) {
    Maquina *mejorMaquina=&maquinas[0];
    for (int i=0; i < maquinas.size(); i++) {
        Maquina *maquina = &maquinas[i];
        //menor tiempo acumulado
        if (maquina->tiempoAcumulado<mejorMaquina->tiempoAcumulado) {
            mejorMaquina = &maquinas[i];
        }
    }

    return mejorMaquina;
}

int CalcularTiempo(Orden orden) {
    if (orden.tipo==1) {
        return orden.peso*4;
    }
    else {
        return orden.peso*2;
    }
}

int ProgramacionTareas(int m,vector <Orden> &listaOrdenes) {
    vector<Maquina> maquinas;
    for (int i=0;i<m;i++) {
        maquinas.push_back(Maquina{i+1,0});
    }

    for ( int i=0;i<listaOrdenes.size();i++){
        Maquina *maquina = buscarMejorMaquin(maquinas);
        maquina->tiempoAcumulado+=listaOrdenes[i].tiempo;
        maquina->ordenesRealizadas.emplace_back(listaOrdenes[i]);
    }

    ImprimirMaquinas(maquinas);

    int mayorTiempo=-1;
    for (int i=0; i < maquinas.size(); i++) {
        if (mayorTiempo<maquinas[i].tiempoAcumulado) {
            mayorTiempo=maquinas[i].tiempoAcumulado;
        }
    }

    return mayorTiempo;
}



int main() {
    vector<Orden> listaOrdenes = {
        {1,1,10},
        {2,1,10},
        {3,2,8},
        {4,1,15},
        {5,2,9},
        {6,2,11},
        {7,1,12},
        {8,2,15},
        {9,1,6},
        {10,2,10},
        {11,1,8},
        {12,2,15},
        {13,1,11},
        {14,1,7},
        {15,1,7},
        {16,2,8},
        {17,2,9},
        {18,1,11},
        {19,2,12},
        {20,1,15}
    };

    for (int i=0;i<listaOrdenes.size();i++) {
        int tiempoTarea=CalcularTiempo(listaOrdenes[i]);
        listaOrdenes[i].tiempo=tiempoTarea;
    }

    std::sort (listaOrdenes.begin(), listaOrdenes.end(),[] (const Orden &lhs, const Orden &rhs) {
        return lhs.tiempo > rhs.tiempo;
    });

    int resultado = ProgramacionTareas(5,listaOrdenes);

    //El tiempo mínimo en que todas las máquinas terminarán el trabajo
    cout<<"tiempo minimo: "<<resultado<<endl;

    return 0;

}