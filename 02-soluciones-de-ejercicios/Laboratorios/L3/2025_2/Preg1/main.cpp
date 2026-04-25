#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Pais {

    int id;
    string nombre;
    int cantidadFrontera;
    vector <int> frontera;

};

struct Color {
    int id;
    vector <Pais> coloreados;
};


void RellenarPaises(vector <Pais> &paises) {
    Pais pais1{1,"Argentina",5,{4,2,8,3,11}};
    paises.push_back(pais1);
    Pais pais2{2,"Bolivia",5,{9,3,8,1,4}};
    paises.push_back(pais2);
    Pais pais3{3,"Brasil",9,{11,1,8,2,9,5,12,7,10}};
    paises.push_back(pais3);
    Pais pais4{4,"Chile",3,{9,2,1}};
    paises.push_back(pais4);
    Pais pais5{5,"Colombia",4,{12,3,9,6}};
    paises.push_back(pais5);
    Pais pais6{6,"Ecuador",2,{5,9}};
    paises.push_back(pais6);
    Pais pais7{7,"Guyana",3,{12,3,10}};
    paises.push_back(pais7);
    Pais pais8{8,"Paraguay",3,{2,3,1}};
    paises.push_back(pais8);
    Pais pais9{9,"Peru",5,{6,5,3,2,4}};
    paises.push_back(pais9);
    Pais pais10{10,"Surinam",2,{7,3}};
    paises.push_back(pais10);
    Pais pais11{11,"Uruguay",2,{3,1}};
    paises.push_back(pais11);
    Pais pais12{12,"Venezuela",3,{5,3,7}};
    paises.push_back(pais12);
}

bool ColorValido(Pais paisTratado, vector <Pais> &paises, Color &colores) {
    for (int i = 0; i < colores.coloreados.size(); i++) {
        for (int j=0; j<colores.coloreados[i].cantidadFrontera; j++) {
            if (paisTratado.id==colores.coloreados[i].frontera[j]) {
                return false;
            }
        }
    }
    return true;
}

int MejorColor(Pais paisTratado, vector <Pais> &paises, vector <Color> &colores) {
    int mejorColor= 0;
    for (int i=0;i<colores.size();i++) {
        if (ColorValido(paisTratado,paises,colores[i])) {
            mejorColor=i;
            return mejorColor;
        }
    }

    return mejorColor;
}

void ImprimirPaises(vector <Pais> &paises) {
    for (int i = 0; i < paises.size(); i++) {
        cout<< paises[i].nombre<<" ";
    }
    cout<<endl;
}

void ImprimirColor(vector <Color> &colores) {
    for (int i = 0; i < colores.size(); i++) {
        cout<<"Color: "<<colores[i].id<<" ";
        ImprimirPaises(colores[i].coloreados);
    }
    cout<<endl;
}

void MejorSolucion(vector <Color> &colores,vector <Pais> &paises) {
    for (int i=0;i < paises.size();i++) {
        int posicion = MejorColor(paises[i],paises,colores);
        colores[posicion].coloreados.push_back(paises[i]);
    }

    ImprimirColor(colores);
}

int main() {

    vector <Pais> paises;
    RellenarPaises(paises);
    //Consideré solo 4 colores , ya que el limite eran 4
    vector <Color> colores{{1},
    {2},
    {3},
    {4}};

    std::sort(paises.begin(),paises.end(),[](const Pais &pais1,const Pais &pais2) {
        return pais1.cantidadFrontera > pais2.cantidadFrontera;
    });

    MejorSolucion(colores,paises);

    return 0;

}