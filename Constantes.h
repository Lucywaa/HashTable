//
//  Constantes.h
//  Dispersion
//
//  Created by Michelle Layseca on 8/11/15.
//

#ifndef Dispersion_Constantes_h
#define Dispersion_Constantes_h

const int TAMMAX_CHAR=30;
#define TAM_ARCHIVO 100
#define NO_COMPARTIMENTOS 3
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
int contadorRegistros;
int contadorDuplicaciones=1;
enum{AGREGAR,MOSTRAR,IMPRIMIR_DENSIDAD,MODIFICAR,BUSCAR,ELIMINAR,SALIR};


#define ARCH_DATOS "Agenda.txt"
#define ARCH_TEMP "Temporal.txt"
#define ARCH_CONF "Configuracion.txt"
#endif
