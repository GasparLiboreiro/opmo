#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "accion.h"

class Opmo{
    private:
        std::vector<Accion> acciones;

        std::string pila_en_pantalla="";
        std::string dia_en_pantalla="";

        std::string nombre_archivo="archivo";

        bool cargar_archivo(){
            acciones.clear();
            bool out=true;

            std::ifstream file("saves/"+nombre_archivo+".opmo");
            if(file.is_open()){
                std::string linea;
                std::string data[5];
                int data_id=0;
                while(std::getline(file, linea)){
                    data[0].clear();
                    data[1].clear();
                    data[2].clear();
                    data[3].clear();
                    data[4].clear();
                    data_id=0;

                    for(int i=0; i<linea.size(); i++){
                        if(linea.c_str()[i]=='~')
                            data_id++;
                        else {
                            data[data_id]+=linea.c_str()[i];
                        }
                    }
                    acciones.push_back(Accion(data[0],data[1],data[2],data[3],data[4]));
                }
                file.close();
            } else {
                out = false;
            }
            return out;
        }

        bool guardar_archivo(){
            bool out = true;
            std::ofstream save("saves/"+nombre_archivo+".opmo");
            if(save.is_open()){
                for(int i=0; i<acciones.size(); i++){
                    save<<acciones[i].pila<<"~"<<(int)acciones[i].io<<"~"<<std::to_string(acciones[i].monto)<<"~"<<acciones[i].fecha<<"~"<<acciones[i].razon<<"\n";
                }
                save<<std::flush;
            } else {
                out=false;
            }
            return out;
        }

        void interaccion_cargar_archivo(){
            std::string res;
            while(cargar_archivo()==false){
                std::cout<<" Uh, el archivo parece no existir en ./saves/*"<<std::endl;
                std::cout<<" Queres intentar con otro nombre o queres crear un nuevo archivo?\n0 = intentar de nuevo\n1 = crear archivo"<<std::endl;
                std::cin>>res;
                if(res=="1"){
                    std::ofstream("saves/"+nombre_archivo+".opmo").flush();
                } else {
                    std::cout<<" Ingresa otro nombre:"<<std::endl;
                    std::cin>>nombre_archivo;
                }
            }
        }

        void interaccion_guardar_archivo(){
            bool state;
            std::string res;
            do {
                state = guardar_archivo();
                if(!state){
                    std::cout<<"ERROR AL GUARDAR EL SAVE!"<<std::endl<<std::endl;
                    std::cout<<"esto pudo ser por mil razones, una puede ser un nombre de archivo invalido"<<std::endl;
                    std::cout<<"actualmente esta establecido el nombre \""+nombre_archivo+"\" (uno valido es uno que puedas crear en tu escritorio [sin extencion de archivo])"<<std::endl;
                    std::cout<<"1) ingresar otro nombre para el save"<<std::endl;
                    std::cout<<"2) reintentar"<<std::endl;
                    std::cout<<"3) cancelar guardado"<<std::endl;
                    std::cin>>res;
                    if(res=="1"){
                        std::cout<<"nuevo nombre: ";
                        std::cin>>nombre_archivo;
                    } else if(res=="3"){
                        break;
                    }
                }
            } while(!state);
        }
        
        int get_total_pila(std::string pila){
            int tot=0;
            for(int i=0; i<acciones.size(); i++){
                if(acciones[i].pila==pila){
                    tot+=acciones[i].net();
                }
            }
            return tot;
        }
        
        int get_total(){
            int tot=0;
            for(int i=0; i<acciones.size(); i++){
                tot+=acciones[i].net();
            }
            return tot;
        }
        
        void print_total_pilas(){
            if(acciones.size()!=0){
                std::vector<std::string> pilas;
                bool repe=false;
                for(int i=0; i<acciones.size(); i++){
                    if(acciones[i].pila == pila_en_pantalla || pila_en_pantalla == ""){
                        for(int j=0; j<pilas.size(); j++)
                            if(pilas[j]==acciones[i].pila)
                                repe=true;
                        if(!repe)
                            pilas.push_back(acciones[i].pila);
                        repe=false;
                    }
                }

                for(int i=0; i<pilas.size(); i++)
                    std::cout<<pilas[i]+" : $"<<get_total_pila(pilas[i])<<std::endl;
            }

        }

        void print_total(){
            std::cout<<"total : $"<<get_total()<<std::endl;
        }

        void print_renglon(){
            std::cout<<std::endl;
        }

        void print(std::string pila=""){
            std::cout<<"["<<nombre_archivo<<"]"<<std::endl;
            int pila_s=4, monto_s=5, fecha_s=5, razon_s=5;
            for(int i=0; i<acciones.size(); i++){
                if((acciones[i].pila==pila || pila == "") && (acciones[i].fecha==dia_en_pantalla || dia_en_pantalla=="")){
                    if(pila_s<acciones[i].pila.size())
                        pila_s=acciones[i].pila.size();
                    if(monto_s<std::to_string(acciones[i].monto).size())
                        monto_s=std::to_string(acciones[i].monto).size();
                    if(fecha_s<acciones[i].fecha.size())
                        fecha_s=acciones[i].fecha.size();
                    if(razon_s<acciones[i].razon.size())
                        razon_s=acciones[i].razon.size();
                }
            }
            int ancho_total = 2+pila_s+3+1/*io display*/+1+monto_s+3+fecha_s+3+razon_s+2;
            for(int i=0; i<ancho_total; i++)
                std::cout<<"-";
            std::cout<<std::endl;

            std::cout<<"| "+space("pila",pila_s)+" |   "+space("monto",monto_s)+" | "+space("fecha",fecha_s)+" | "+space("razon",razon_s)+" |\n";

            for(int i=0; i<ancho_total; i++)
                std::cout<<"-";
            std::cout<<std::endl;

            for(int i=0; i<acciones.size(); i++){
                if((acciones[i].pila==pila || pila == "") && (acciones[i].fecha==dia_en_pantalla || dia_en_pantalla==""))
                    std::cout<<acciones[i].to_string(pila_s, monto_s, fecha_s, razon_s)<<std::endl;
            }
            
            for(int i=0; i<ancho_total; i++)
                std::cout<<"-";
            std::cout<<std::endl;
        }
    public:
        Opmo(){
        }

        

        void run(){
            system("cls");
            std::cout<<"                BIENVENIDO A MI PROGRAMA :)"<<std::endl<<std::endl;
            std::cout<<" Este programa es una agenda de mis operaciones monetarias,"<<std::endl;
            std::cout<<"me sirve principalmente para llevar registro, no hace falta"<<std::endl;
            std::cout<<"q sean movimientos gigantes"<<std::endl;
            std::cin.get();
            system("cls");
            std::cout<<" Vamos al uso:"<<std::endl;
            std::cout<<"Que archivo queres cargar? (nombre sin extencion de archivo)(vacio significa el archivo  \"archivo\")"<<std::endl;
            
            std::string res;// input respuesta
            
            std::getline(std::cin, nombre_archivo);
            if(nombre_archivo=="")
                nombre_archivo="archivo";

            interaccion_cargar_archivo();

            bool loop=true;
            
            while(loop){

                
                system("cls");
                print(pila_en_pantalla);
                print_renglon();
                print_total_pilas();
                print_renglon();
                print_total();
                print_renglon();
                std::cout<<std::endl;
                std::cout<<"e)editar  v)vista  a)archivo  x)exit"<<std::endl;
                std::cin>>res;

                switch(res.at(0)){
                    case 'e':
                        print_renglon();
                        std::cout<<"a)aniadir accion"<<std::endl;
                        std::cout<<"e)editar accion"<<std::endl;// <0> TODO
                        std::cin>>res;
                        
                        switch(res.at(0)){
                            case 'a':
                                acciones.push_back(Accion());
                                break;

                            case 'e':
                                //TODO, idealmente dejar clickear donde quieren  editar y usando las coords del cursor(de escritura) se que campo de que accion quieren editar
                                break;

                            default:
                                std::cout<<"opcion '"+res+"' inexistente"<<std::endl;
                                std::cin.get();
                                std::cin.get();
                        }


                        break;
                    
                    case 'v':
                        std::cout<<"p)mostrar pila especifica"<<std::endl;
                        std::cout<<"d)mostrar dia especifico"<<std::endl;
                        std::cin>>res;
                        switch(res.at(0)){
                            case 'p':
                                std::cout<<"pila: ";
                                std::cin.get();
                                std::getline(std::cin, pila_en_pantalla);
                                break;
                            case 'd':
                                std::cout<<"dia: ";
                                std::cin.get();
                                std::getline(std::cin, dia_en_pantalla);
                                break;
                            default:
                                std::cout<<"opcion '"+res+"' inexistente"<<std::endl;
                                std::cin.get();
                                std::cin.get();
                        }
                        break;
                    
                    case 'a':
                        std::cout<<"c)guardar y cambiar archivo(actualmente \""<<nombre_archivo<<"\")"<<std::endl;
                        std::cout<<"g)guardar archivo"<<std::endl;
                        std::cout<<"e)guardar archivo especifico"<<std::endl;
                        std::cin>>res;
                        switch(res.at(0)){
                            case 'c':
                                interaccion_guardar_archivo();
                                std::cout<<"nuevo archivo: ";
                                std::cin>>nombre_archivo;
                                interaccion_cargar_archivo();
                                break;

                            case 'g':
                                interaccion_guardar_archivo();
                                break;
                            
                            case 'e':
                                print_renglon();
                                std::cout<<"aviso: Al hacer esta operacion cambiara el archivo default por el que vaya a ingresar, las proximas veces que guarde sera en este mismo archivo y no hara falta repetir el nombre"<<std::endl;
                                std::cout<<"nuevo nombre de archivo: ";
                                std::cin>>nombre_archivo;
                                interaccion_guardar_archivo();
                                break;
                            default:
                                std::cout<<"opcion '"+res+"' inexistente"<<std::endl;
                                std::cin.get();
                                std::cin.get();
                        }
                        break;
                    
                    case 'x':
                        loop=false;
                        break;
                    
                    default:
                        std::cout<<"opcion '"+res+"' inexistente"<<std::endl;
                        std::cin.get();
                        std::cin.get();
                }

            }
        }
};

//https://stackoverflow.com/questions/35800020/how-do-i-find-the-coordinates-of-the-cursor-in-a-console-window