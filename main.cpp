/*
CARDENAS L
COMPILADOR CODEBLOCKS 13.12
DISPERSION CON COMPARTIMENTOS p8
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Constantes.h"
#include "Utilerias.h"
#include "Agenda.h"
#include "Dispersion.h"

using namespace std;
int menu();
void switchear();
/*========================================*/
Dispersion disp=* new Dispersion();
int main()
{
    remove(ARCH_DATOS);
    remove(ARCH_TEMP);
    fflush(stdin);
    disp.generaTrazado();
    switchear();

}

/*=========================================*/
int menu()
{
    int opc;
    system("color 02");
    imprimirCentrado(tituloApp(),"\x3");
    imprimirCentrado("CHAMBAMEX 2.0"," ");
    cout<<endl
        <<"                                \x10 1.-) AGREGAR "<<endl
        <<"                                \x10 2.-) MOSTRAR "<<endl
        <<"                                \x10 3.-) DENSIDAD DE EMPAQUETAMIENTO "<<endl
        <<"                                \x10 4.-) MODIFICAR"<<endl
        <<"                                \x10 5.-) BUSCAR"<<endl
        <<"                                \x10 6.-) ELIMINAR"<<endl
        <<"                                \x10 7.-) SALIR"<<endl<<endl<<
        "                          \x1 SELECCIONA UNA OPCION: ";
    cin>>opc;
    opc--;
    pauseAndClear();
    system("color 0e");

    return opc;
}

void switchear()
{
    bool volverAlMenu;
    do
        {

            volverAlMenu=true;
            switch(menu())
                {
                case AGREGAR:
                    imprimirCentrado("( AGREGAR CONTACTO )","*");
                    disp.agregar();
                    break;
                case MOSTRAR:
                    disp.mostrar();
                    break;
                case IMPRIMIR_DENSIDAD:
                    disp.densidadEmpaquetamiento();
                    break;
                case MODIFICAR:
                    disp.modificar();
                    break;
                case BUSCAR:
                    disp.buscar();
                    break;
                case ELIMINAR:
                    disp.eliminar();
                    break;
                case SALIR:
                    volverAlMenu=false;
                    break;
                default:
                    imprimirCentrado("OPCION INCORRECTA BITCH >:C "," ");
                    break;
                }

            pauseAndClear();
        }
    while(volverAlMenu);
}
