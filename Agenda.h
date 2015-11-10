#ifndef AGENDA_H
#define AGENDA_H
#include "Constantes.h"
#include <sstream>
class Agenda
{
public:
    Agenda(char* nombre, char* telefono, char*  correo){
            setNombre(nombre);
            setTelefono(telefono);
            setCorreoElectronico(correo);
    }
    Agenda(){

    }
    virtual ~Agenda(){
    }
    char* getNombre()
    {
        return nombre;
    }
    void setNombre(char* val)
    {
        strcpy(nombre,val);
    }

    char* getTelefono()
    {
        return telefono;
    }
    void setTelefono(char* val)
    {
        strcpy(telefono,val);
    }
    char* getCorreoElectronico()
    {
        return correoElectronico;
    }
    void setCorreoElectronico(char* val)
    {
        strcpy(correoElectronico,val);
    }
    string toString(){
        stringstream info;
        info<< "Nom: "<<getNombre()<<"Correo: "<< getCorreoElectronico()<<"Tel: "<<getTelefono()<<endl;
        return info.str();
    }
private:
    char nombre[TAMMAX_CHAR];
    char telefono[TAMMAX_CHAR];
    char correoElectronico[TAMMAX_CHAR];
};

#endif // EMPLEADO_H
