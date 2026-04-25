#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> idPredecesores;
};

struct Problema {
    int N;
    int P;
    int ganancia=0;
    vector<Proyecto> proyectosAsig;
};

bool CumplePredecesor(const vector<int> predecesores, const vector<Proyecto> &proyectosAsig) {
    if (predecesores.empty()) return true;
    int cont=0;
    for (int i=0;i<predecesores.size();i++) {
        for (int j=0;j<proyectosAsig.size();j++) {
            if (proyectosAsig[j].id==predecesores[i]) {
                cont++;
            }
        }
    }
    if (cont == predecesores.size()) return true;
    return false;
}

void MejorSolucion(vector<Proyecto> proyectos, Problema &problema) {
    bool agregado = true;
    //Bucle que recorre todos los proyectos , cuando un proyecto se agrega a la solución
    //puede hacer que un proyecto que antes no cumplía con los requisitos lo cumpla ahora
    while (agregado) {
        agregado = false;

        for (int i = 0; i < proyectos.size(); i++) {
            if (problema.P >= proyectos[i].costo &&
                CumplePredecesor(proyectos[i].idPredecesores, problema.proyectosAsig)) {

                problema.proyectosAsig.emplace_back(proyectos[i]);
                problema.ganancia += proyectos[i].ganancia;
                problema.P -= proyectos[i].costo;

                proyectos.erase(proyectos.begin() + i);

                agregado = true;
                break;
                }
        }
    }
}

void ImprimirProyectos(const vector<Proyecto> &proyectos) {
    for (int i=0;i<proyectos.size();i++) {
        double razon =  proyectos[i].ganancia * proyectos[i].beneficio / proyectos[i].costo;
        cout << "Id: "<<proyectos[i].id << " razon: " << razon << ", costo: "<< proyectos[i].costo << endl;
    }
}

void ImprimirSolucion(const Problema &problema) {
    cout<<"Proyectos seleccionados: "<<endl;
    ImprimirProyectos(problema.proyectosAsig);
    cout<<endl;
    cout<<"Ganancia: "<<problema.ganancia<<endl;
}

int main() {

    vector<Proyecto> proyectos{
        {1,80,150,2},
        {2,20,80,5,{4}},
        {3,100,300,1,{1,2}},
        {4,100,150,4},
        {5,50,80,2},
        {6,10,50,1,{2}},
        {7,50,120,2,{6}},
        {8,50,150,4,{6}}
    };

    Problema problema {8,250};

    //Heurística para maximizar ganancia y beneficio y minimizar costo
    std::sort(proyectos.begin(), proyectos.end(),[](const Proyecto& a, const Proyecto& b) {
        return a.ganancia*a.beneficio/a.costo> b.ganancia*b.beneficio/b.costo;
    });

    MejorSolucion(proyectos,problema);
    ImprimirSolucion(problema);

    return 0;
}