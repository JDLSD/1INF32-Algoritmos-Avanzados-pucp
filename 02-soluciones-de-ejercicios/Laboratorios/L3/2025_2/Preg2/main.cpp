#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

struct Paquete {
    int id;
    int tamanho;

};

struct Camion {
    int id;
    int capacidad;
    vector<Paquete> paquetes;
};

void ImprimirPaquete(const vector<Paquete> &paquetes){
    if (paquetes.empty())
        cout<<"Ningun paquete";
    for(int i = 0; i < paquetes.size(); i++) {
        cout << "{ Id Paquete:" << paquetes[i].id << ", peso: "<<paquetes[i].tamanho<<"kg }  ";
    }
    cout << endl;
}

void ImprimirCamion(const vector<Camion> &camiones) {
    for(int i = 0; i < camiones.size(); i++) {
        cout << "Camion:" << camiones[i].id << " ,Capacidad Restante:"<<camiones[i].capacidad<<endl;
        cout << "Paquetes almacenados: "<<endl;
        ImprimirPaquete(camiones[i].paquetes);
        cout << endl;
    }
}

Camion *MejorCamion(Paquete paquete,vector <Camion> &camiones) {
    Camion *mejorCamion = &camiones[0];
    int menor=9999;
    for (int i=0; i < camiones.size(); i++) {
        Camion *camion = &camiones[i];
        int capacidadHipotetica = camiones[i].capacidad - paquete.tamanho;
        if (capacidadHipotetica >=0) {
            if (capacidadHipotetica < menor) {
                menor = capacidadHipotetica;
                mejorCamion = &camiones[i];
            }
        }
    }

    return mejorCamion;
}


void MejorSolucion(vector <Paquete> &paquetes,vector <Camion> &camiones) {

    for (int i=0; i < paquetes.size(); i++) {
        Camion *camion = MejorCamion(paquetes[i],camiones);
        camion->capacidad=camion->capacidad-paquetes[i].tamanho;
        camion->paquetes.push_back(paquetes[i]);
    }

    ImprimirCamion(camiones);
}

int main() {
    vector <Camion> camiones {      {1,250},
                                    {2,200},
                                    {3,200},
                                    {4,100},
                                    {5,300}
                            };

    vector <Paquete> paquetes {
        {1,150},
        {2,100},
        {3,180},
        {4,50},
        {5,120},
        {6,10}
    };


    std::sort(paquetes.begin(), paquetes.end(),[](const Paquete &p1, const Paquete &p2) {
        return p1.tamanho > p2.tamanho;
    });

    //ImprimirPaquete(paquetes);

    MejorSolucion(paquetes,camiones);

    return 0;

}