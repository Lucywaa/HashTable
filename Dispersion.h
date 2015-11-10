#ifndef DISPERSION_H
#define DISPERSION_H
#include "Agenda.h"
#include "Constantes.h"
Agenda contacto = * new Agenda();

class Dispersion
{
public: //YOLO
    char campoLlave[TAMMAX_CHAR];
    long int direccionBase;
    long int pos;
    int contador;
    Dispersion()
    {
        contador= pos =direccionBase = 0;
    }
    virtual ~Dispersion()
    {
    }
    void generaTrazado();
    void dispersion();
    void agregar();
    void mostrar();
    void eliminar();
    void buscar();
    void modificar();
    bool buscarExistenciaLlave(char* llave);
    bool guardarEnArchivo(Agenda);
    void densidadEmpaquetamiento();
    void agrandarTabla();
};

void Dispersion::agregar()
{
    Agenda nuevoContacto;
    char nombre[TAMMAX_CHAR],telefono[TAMMAX_CHAR],
    correoElectronico[TAMMAX_CHAR];
    fflush(stdin);
    cout<<"Ingresa los datos del contacto por favor: "<<endl;
    cout<<"Nombre: ";
    cin.getline(nombre,TAMMAX_CHAR);
    cout<<"Telefono: ";
    cin.getline(telefono,TAMMAX_CHAR);
    cout<<"Correo Electronico: ";
    cin.getline(correoElectronico,TAMMAX_CHAR);
    nuevoContacto = * new Agenda(nombre,telefono,correoElectronico);
    strcpy(campoLlave,nombre);
    dispersion();
    if(guardarEnArchivo(nuevoContacto))
        {
            cout<<endl<<"Contacto registrado correctamente \x1 "<<endl;
            contadorRegistros++;
        }
    else
        {
            cout<<endl<<"Error al registrar el contacto >:c "<<endl;
        }
}
void Dispersion::mostrar()
{
    direccionBase=0;
    imprimirCentrado("CONTACTOS REGISTRADOS","_");
    fstream arch(ARCH_DATOS,ios::in);
    if(!arch.is_open())
        {
            cout<<"Error al leer archivo Agenda"<<endl;
        }
    else
        {
            while(!arch.eof())
                {
                    arch.seekg(direccionBase,ios::beg);
                    arch.read((char*)&contador,sizeof(int));
                    if(contador==0)
                        {
                            direccionBase=direccionBase+((NO_COMPARTIMENTOS*contadorDuplicaciones*sizeof(Agenda))+sizeof(int));
                        }
                    else
                        {
                            for(int i=0; i<contador; i++)
                                {
                                    arch.read((char*)&contacto,sizeof(Agenda));
                                    cout
                                            <<"NOMBRE:    "<<contacto.getNombre()<<endl
                                            <<"TELEFONO:  "<<contacto.getTelefono()<<endl
                                            <<"CORREO:    "<<contacto.getCorreoElectronico()<<endl<<endl;
                                    cout<<"_____________________________________"<<endl;
                                }
                            direccionBase=direccionBase+((NO_COMPARTIMENTOS*contadorDuplicaciones*sizeof(Agenda))+sizeof(int));
                        }
                }
        }
    arch.close();

}
void Dispersion::densidadEmpaquetamiento(){
    float densidad,cont=0;
    direccionBase=0;
    imprimirCentrado("DENSIDAD DE EMPAQUETAMIENTO","_");
    fstream arch(ARCH_DATOS,ios::in);
    if(!arch.is_open())
        {
            cout<<"Error al leer archivo de contactos"<<endl;
        }
    else
        {
            while(!arch.eof())
                {
                    arch.seekg(direccionBase,ios::beg);
                    arch.read((char*)&contador,sizeof(int));
                    if(contador==0)
                        {
                            direccionBase=direccionBase+((NO_COMPARTIMENTOS*sizeof(Agenda))*contadorDuplicaciones+sizeof(int));
                        }
                    else
                        {
                            for(int i=0; i<contador; i++)
                                {
                                    arch.read((char*)&contacto,sizeof(Agenda));
                                    cont++;
                                }
                            direccionBase=direccionBase+((NO_COMPARTIMENTOS*sizeof(Agenda))*contadorDuplicaciones+sizeof(int));
                        }
                }
        }
    arch.close();
    densidad=(cont/(TAM_ARCHIVO*NO_COMPARTIMENTOS*contadorDuplicaciones))*100;
    cout<< "DENSIDAD: "<<densidad<<" % "<<endl;
}

bool Dispersion::guardarEnArchivo(Agenda nuevoContacto)
{
    fstream arch(ARCH_DATOS,ios::in | ios::out);
    fflush(stdin);
    direccionBase=direccionBase* ((sizeof(Agenda)*NO_COMPARTIMENTOS*contadorDuplicaciones)+sizeof(int));
    arch.seekg(direccionBase,ios::beg);
    arch.read((char*)&contador,sizeof(int));
    if(contador<NO_COMPARTIMENTOS*contadorDuplicaciones)
        {
            pos=arch.tellg();
            pos=pos+(contador * sizeof(Agenda)); //mod sizeof(contacto)
            arch.seekp(pos,ios::beg);
            arch.write((char*)&nuevoContacto,sizeof(Agenda));
            contador++;
            arch.seekp(direccionBase,ios::beg);
            arch.write((char*)&contador,sizeof(int));
            arch.close();
            return true;
        }
    else
        {
            arch.close();
            cout<<"Error, todos los compartimentos para esa llave estan ocupados :3 "<<endl;
            //aqui se agrandaria el archivo en la sig practica
            //pauseAndClear();
            agrandarTabla();
            imprimirCentrado("SE AGRANDO LA TABLA"," ");
            return false;
        }
}
void Dispersion::agrandarTabla(){
    ofstream conf;
    fflush(stdin);
    Agenda aux=* new Agenda();
    conf.open(ARCH_DATOS, ios::out);
    int vecesDuplicadoAnt = contadorDuplicaciones;
    contadorDuplicaciones++;
    conf << contadorDuplicaciones;
    conf.close();
    fstream temporal(ARCH_TEMP, ios::app);
    int pos2 = 0;
    contador = 0;
    direccionBase =0;
     pos = 0;
    ifstream archivo;
    archivo.open(ARCH_DATOS,ios::in);
    if(!temporal.eof()){
        for(int i=0; i<TAM_ARCHIVO; i++){
                        cout << "1" << endl;

            temporal.write((char*)&contador, sizeof(int));
            //cout << "contador: " << &contador <<endl;
            for(int j=0; j<NO_COMPARTIMENTOS*contadorDuplicaciones; j++){
                temporal.write((char*)&aux, sizeof(Agenda));
                //cout << "contacto: " << aux.toString() <<endl;
            }
        }
        if(!archivo.is_open())
            cout << endl << "ERROR: No existe el archivo ORIGINAL" << endl;
        else{
            while(!archivo.eof()){
                archivo.seekg(direccionBase,ios::beg);
                temporal.seekg(pos2, ios::beg);
                archivo.read((char*)&contador, sizeof(int));
                contador=contador-'0';
                if(contador==0){
                    direccionBase += (NO_COMPARTIMENTOS*vecesDuplicadoAnt*sizeof(Agenda))+sizeof(int);
                    pos2 += (NO_COMPARTIMENTOS*contadorDuplicaciones*sizeof(Agenda))+sizeof(int);
                }
                else{
                    temporal.write((char*)&contador, sizeof(int));
                    archivo.seekg(direccionBase+sizeof(int)); //(direccionBase+sizeof(int));
                    cout<<contador<<endl;
                    pauseAndClear();
                    for(int i=0; i<contador; i++){
                        archivo.read((char*)&contacto, sizeof(Agenda));
                        aux=contacto;
                        temporal.write((char*)&aux, sizeof(Agenda));
                        cout << "contacto: " << aux.toString() <<endl;

                        cout<<"Contacto agregado al nuevo archivo"<<endl;

                    }
                    direccionBase += (NO_COMPARTIMENTOS*vecesDuplicadoAnt*sizeof(Agenda));
                    pos += (NO_COMPARTIMENTOS*contadorDuplicaciones*sizeof(Agenda)); //le quite +sizeof(int)
                    cout << direccionBase << endl;
                    cout << archivo.eof() << endl;
                }
            }
        }
    }
    else
        cout << endl << "ERROR: No se pudo abrir el archivo temporal:C " << endl << endl;

    archivo.close();
    cout << endl << "Se cerro el archivo original" << endl;
    if(archivo.is_open()){
        cout << endl << "El ORIGINAL sigue abierto >:c !! " << endl;
        cin.get();
    }
    temporal.close();
    cout << endl << "Se cerro el temporal" << endl;
    if(temporal.is_open()){
        cout << endl << "El TEMPORAL sigue abierto >:c !! " << endl;
        cin.get();
    }
    //remove(ARCH_DATOS);
    cout << endl << "SE REMOVIO EL ORIGINAL " << endl;
    //rename(ARCH_DATOS,"basurita.txt");
    //rename(ARCH_TEMP, ARCH_DATOS);
    cout << "SE RENOMBRO EL TEMP" << endl;

}
void Dispersion::generaTrazado()
{
    ofstream arch;
    arch.open(ARCH_DATOS,ios::app); //modificado
    if(arch.is_open())
        {
            for(int i=0; i<TAM_ARCHIVO; i++)
                {
                    arch.write((char*)&contador,sizeof(int));
                    for(int j=0; j<NO_COMPARTIMENTOS; j++)
                        {
                            arch.write((char*)&contacto,sizeof(Agenda));
                        }
                }
        }
    else
        {
            cout<<"Error al generar el trazado"<<endl;
        }
    arch.close();
}
void Dispersion::dispersion()
{
    unsigned  int i=0;
    direccionBase=0;

    while(i<strlen(campoLlave))
        {
            direccionBase= direccionBase+(TAM_ARCHIVO*campoLlave[i])+(campoLlave[i+1]%84645);
            i=i+2;
        }
    direccionBase=direccionBase % TAM_ARCHIVO;
}

void Dispersion::modificar()
{
    fstream archivo(ARCH_DATOS, ios::in | ios::out);

    char nombre[TAMMAX_CHAR];
    int pos2, indice, cuentaIguales=0;

    imprimirCentrado("MOFICAR CONTACTOS","_");
    cin.get();
    cout<<"INGRESA EL NOMBRE DEL CONTACTO A MODIFICAR: ";
    cin.getline(nombre,TAMMAX_CHAR);
    if(buscarExistenciaLlave(nombre))
        {
            archivo.seekp(direccionBase, ios::beg);
            contador--;
            archivo.write((char*)&contador, sizeof(int));
            if(contador==0)
                {
                }
            else
                {
                    for(int i=0; i<contador; i++)
                        {
                            archivo.read((char*)&contacto, sizeof(Agenda));
                            if(strcmp(nombre,contacto.getNombre())==0)
                                {
                                    ++cuentaIguales;
                                }
                        }
                    cout << endl <<"QUE INDICE DESEAS MODIFICAR? 7u7  (1-" << cuentaIguales << "): ";
                    cin >> indice;
                    indice--;
                                cin.get();

                    pos2 = direccionBase + ( sizeof(int)+ (sizeof(Agenda)*indice));
                    pos = pos2 + (sizeof(Agenda));
                    while(indice<contador)
                        {
                            archivo.seekp(pos, ios::beg);
                            archivo.read((char*)&contacto, sizeof(Agenda));
                            archivo.seekp(pos2, ios::beg);
                            archivo.write((char*)&contacto, sizeof(Agenda));
                            indice++;
                            pos+=sizeof(Agenda);
                            pos2+=sizeof(Agenda);
                        }
                    cin.get();
                }
            archivo.close();
            imprimirCentrado("INGRESA LOS NUEVOS DATOS DEL CONTACTO","=");
            agregar();
        } //Llave del if
    else
        {
            imprimirCentrado("( NOMBRE NO ENCONTRADO D: )","+");
        }
}

bool Dispersion::buscarExistenciaLlave(char* llave)
{
    direccionBase=0; int i,j;
    bool encontrado=false;
    ifstream archivo(ARCH_DATOS);
    if(!archivo.is_open())
        {
            imprimirCentrado("Error al abrir el archivo de contactos","_");
        }
    else
        {
            while((!archivo.eof())&&(!encontrado))
                {
                    archivo.seekg(direccionBase,ios::beg);
                    archivo.read((char*)&contador, sizeof(int));
                    if(contador==0)
                        {
                            direccionBase+=(NO_COMPARTIMENTOS*sizeof(Agenda)*contadorDuplicaciones)+sizeof(int);
                        }
                    else
                        {
                            for( i=0,j=0; i<contador; i++)
                                {
                                    archivo.read((char*)&contacto, sizeof(Agenda));
                                    if(strcmp(llave,contacto.getNombre())==0)
                                        {
                                            j=j+1;
                                            cout << endl << j << ") ";
                                            cout
                                                    <<"NOMBRE:    "<<contacto.getNombre()<<endl
                                                    <<"TELEFONO:  "<<contacto.getTelefono()<<endl
                                                    <<"CORREO:    "<<contacto.getCorreoElectronico()<<endl<<endl;
                                            cout<<"_____________________________________"<<endl;
                                            encontrado=true;
                                        }
                                }
                            if(!encontrado)
                                {
                                    direccionBase+=(NO_COMPARTIMENTOS*sizeof(Agenda)*contadorDuplicaciones)+sizeof(int);
                                }
                        }
                }
            archivo.close();
        }
    if(encontrado)
        {
            cout <<  "Se encontraron " << j << " registro(s) con el mismo nombre. >:3 " << endl;
        }
    return encontrado;
}

void Dispersion::buscar(){
    char nombre[TAMMAX_CHAR];
    imprimirCentrado("BUSCAR CONTACTO ","_");
    cout<<"INGRESA EL NOMBRE DEL contacto A BUSCAR: ";
    cin.getline(nombre,TAMMAX_CHAR);
    cin.ignore();
    if(buscarExistenciaLlave(nombre)){
        cout<<endl<<" n________n "<<endl;
    }else{
        cout<<"El nombre del contacto no coincide con nuestros registros :3 "<<endl;
    }
}

void Dispersion::eliminar(){
    imprimirCentrado("ELIMINAR UN CONTACTO","-");
    fstream archivo(ARCH_DATOS, ios::in | ios::out);
    char nombre[TAMMAX_CHAR];
    int pos2, indice, cuentaIguales=0;
    direccionBase=0;
    cin.get();
    cout<<"INGRESA EL NOMBRE DEL CONTACTO A ELIMINAR: ";
    cin.getline(nombre,TAMMAX_CHAR);
    cin.ignore();
    if(buscarExistenciaLlave(nombre))
        {
            archivo.seekp(direccionBase, ios::beg);
            contador--;
            archivo.write((char*)&contador, sizeof(int));
            if(contador==0)
                {
                }
            else
                {
                    for(int i=0; i<=contador; i++)
                        {
                            archivo.read((char*)&contacto, sizeof(Agenda));
                            if(strcmp(nombre,contacto.getNombre())==0)
                                {
                                    ++cuentaIguales;
                                }
                        }
                    cout << endl <<"QUE INDICE DESEAS ELIMINAR? 7u7  (1-" << cuentaIguales << "): ";
                    cin >> indice;
                    indice--;
                    cin.get();
                    pos2 = direccionBase + ( sizeof(int)+ (sizeof(Agenda)*indice));
                    pos = pos2 + (sizeof(Agenda));
                    while(indice<contador)
                        {
                            archivo.seekp(pos, ios::beg);
                            archivo.read((char*)&contacto, sizeof(Agenda));
                            archivo.seekp(pos2, ios::beg);
                            archivo.write((char*)&contacto, sizeof(Agenda));
                            indice++;
                            pos+=sizeof(Agenda);
                            pos2+=sizeof(Agenda);
                        }
                    cin.get();
                }
            archivo.close();
            imprimirCentrado("RIP, CONTACTO ELIMINADO :3 "," ");

        } //Llave del if
    else
        {
            imprimirCentrado("( NOMBRE NO ENCONTRADO D: )","+");
        }
}

#endif // DISPERSION_H
