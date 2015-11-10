//
//  Utilerias.h
//  TareaIndices
//
//  Created by Michelle Layseca on 28/09/15.
//

#ifndef _Utilerias_h
#define _Utilerias_h
#include <sstream>
#include <iostream>
#include <cstdlib>
#ifdef _WIN32
#define BORRAR "cls"
#else
#define BORRAR "clear"
#endif // _WIN32

const int CARACTERES_POR_FILA=80;
using namespace  std;

string tituloApp() {
    stringstream info;
    info<<"\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
    <<"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB"<<endl
    <<"\t\t\t\xBA        AGENDA DE CONTACTOS   \xBA"<<endl
    <<"\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
    <<"\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC"<<endl;
    return info.str();
} //ESTA DECORACION SOLO FUNCIONA EN WINDOWS POR EL HEXA

void imprimirCentrado(string texto,string relleno) {
    double longitudTexto=texto.length();
    int espacios=(CARACTERES_POR_FILA-longitudTexto)/2;
    int i;
    for(i=0; i<CARACTERES_POR_FILA; i++) {
        cout<<relleno;
    }
    for(i=0; i<espacios; i++) {
        cout << relleno;
    }
    cout << texto;
    i+=longitudTexto;
    for(; i<CARACTERES_POR_FILA; i++) {
        cout << relleno;
    }
    for(i=0; i<CARACTERES_POR_FILA; i++) {
        cout<<relleno;
    }
    cout<<endl;
}

void imprimirCentradoSinDecor(string texto) {
    string relleno=" ";
    double longitudTexto=texto.length();
    int espacios=(CARACTERES_POR_FILA-longitudTexto)/2;
    int i;
    for(i=0; i<CARACTERES_POR_FILA; i++) {
        cout<<relleno;
    }
    for(i=0; i<espacios; i++) {
        cout << relleno;
    }
    cout << texto;
    i+=longitudTexto;
    for(; i<CARACTERES_POR_FILA; i++) {
        cout << relleno;
    }
}


void pauseAndClear() {
    imprimirCentrado("Presiona enter para continuar... "," ");
    cin.get();
    cin.get();
    system(BORRAR);
}

#endif
