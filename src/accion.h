#include <iostream>
#include <string>
#include "utils.h"

class Accion{
    public:
        std::string pila;
        bool io;
        int monto;
        std::string razon;
        std::string fecha;
        Accion(){
            std::string sio, smonto;
            std::cout<<"pila: ";
            std::cin>>pila;
            std::cout<<"monto: ";
            std::cin>>smonto;
            std::cout<<"ingreso(+) egreso(-): ";
            std::cin>>sio;
            std::cout<<"fecha: ";
            std::cin>>fecha;
            std::cout<<"razon: ";
            std::cin.get();
            std::getline(std::cin, razon);

            this->io = (sio=="+" || sio=="1") ? true : false;
            this->monto=stoi(smonto);
        }
        Accion(std::string pila, bool io, int monto, std::string fecha, std::string razon=""){
            this->pila=pila;
            this->io=io;
            this->monto=monto;
            this->razon=razon;
            this->fecha=fecha;
        }

        Accion(std::string pila, std::string sio/*string io*/, std::string smonto/*string monto*/, std::string fecha, std::string razon=""){
            this->pila=pila;
            this->io = (sio=="+" || sio=="1") ? true : false;
            this->monto=stoi(smonto);
            this->razon=razon;
            this->fecha=fecha;
        }

        std::string to_string(int pila_s, int monto_s, int fecha_s, int razon_s){
            std::string out = "| "+space(pila,pila_s)+" | "+((io)?"+":"-")+" "+space(std::to_string(monto),monto_s)+" | "+space(fecha, fecha_s)+" | "+space(razon, razon_s)+" |";
            return out;
        }

        int net(){
            return (io)?monto:-monto;
        }
};