#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h> // Estas bibliotecas son para el system("cls") y para random shuffle
#include <time.h>

#define FIL_F 6
#define COL_F 6
#define NUM_MINAS_F 5

#define FIL_D 9
#define COL_D 9
#define NUM_MINAS_D 10

using namespace std;

class Celda{

    private:
    bool mina{false};
    bool descubierta{false};
    bool marcada{false};
    int numMinasCerca;

    public:
    Celda():mina(false), descubierta(false), marcada(false), numMinasCerca(0){}

    void descubrir(){
        descubierta = true;
    }
    void marcar(){
        marcada = true;
    }
    void desmarcar(){
        marcada = false;
    }
    void ponerMina(){
        mina = true;
    }
    bool tieneMina(){
        return mina;
    }
    bool estaDescubierta(){
        return descubierta;
    }
    bool estaMarcada(){
        return marcada;
    }
    int getNumMinasCerca(){
        return numMinasCerca;
    }
    void setNumMinasCerca(int numMinas){
        numMinasCerca=numMinas;
    }
};

class Tablero{

    protected:
    vector<vector<Celda>> tablero;
    int filass;
    int colss;
    int totMinas;
    void colocarMinas(int numMinas){

        srand(time(NULL));

        int numFilas = tablero.size();
        int numColumnas = tablero[0].size();
        int numCeldas = numFilas * numColumnas;

        vector<int> posiciones(numCeldas);

        for(int i = 0; i < numCeldas; i++){
            posiciones[i] = i;
        }

        random_shuffle(posiciones.begin(), posiciones.end());

        for(int i = 0; i < numMinas; i++){
            int pos = posiciones[i];
            int fila = pos / numColumnas;
            int columna = pos % numColumnas;
            tablero[fila][columna].ponerMina();
        }
    }



    public:
    Tablero(){}
    Tablero(int filas, int columnas, int numMinas){
        filass = filas;
        colss = columnas;
        totMinas = numMinas;
        tablero = vector<vector<Celda>>(filas, vector<Celda>(columnas));
        colocarMinas(numMinas);

        for(int i = 0; i < tablero.size(); i++){
            for(int j = 0; j < tablero[0].size(); j++){
                if(!tablero[i][j].tieneMina()){
                    int numMinasCerca = 0;
                    for(int k = i-1; k <= i+1; k++){
                        for(int l = j-1; l <= j+1; l++){
                            if(k >= 0 && k < tablero.size() && l >= 0 && l < tablero[0].size()){
                                if(tablero[k][l].tieneMina()){
                                    numMinasCerca++;
                                }
                            }
                        }
                    }
                tablero[i][j].setNumMinasCerca(numMinasCerca);
               }
            }
        }
    }
    Tablero(const Tablero & t){
        this->tablero = t.tablero;

    }

    int getFilass() const{
        return filass;
    }
    int getColss() const{
        return colss;
    }
    int getTotMinas() const {return totMinas;}
    void setFilass(int filass){
        this->filass =  filass;
    }
    void setColss(int colss){
        this->colss = colss;
    }
    void setTotMinas(int totMinas){
        this->totMinas = totMinas;
    }

    bool descubrirCelda(int fila, int columna);
    void marcarCelda(int fila, int columna);
    void desmarcarCelda(int fila, int columna);
    bool comprobarVictoria();
    friend ostream& operator<<(ostream &os , const Tablero & tablero);

    vector<vector<Celda>> getTab() const{
        return tablero;
    }

};

class Jugador{

    private:
    string nombre;
    int victorias=0;

    public:
    Jugador():nombre(""), victorias(0){}
    Jugador(const string & n):nombre(n){}
    virtual void mostrarTableroDebug(const Tablero & tablero){

        cout << "No se puede realizar esta funcion. . .";

    }
    void setNombre(const string & nombre){
        this->nombre = nombre;
    }
    void setVictorias(int victorias){
        this->victorias = victorias;
    }
    string getNombre() const{
        return nombre;
    }
    int getVictorias() const{
        return victorias;
    }
    Jugador& operator ++(int){
        this->victorias++;
        return *this;
    }

};

class Admin : public Jugador{

    private:
    int ID;

    public:
    Admin():Jugador(), ID(0){}
    void setID(int ID){
        this->ID = ID;
    }
    int getID() const{
        return ID;
    }
    void mostrarTableroDebug(const Tablero & tablero){ // Esta funcion la desarrollo aqui porque me da problemas en el cpp

        cout << "  ";
        for (int j = 0; j < tablero.getTab()[0].size(); j++){
            cout << j << " ";
        }
        cout << endl;

        for(int i = 0; i < tablero.getTab().size(); i++){
            cout << i << " ";
            for(int j = 0; j < tablero.getTab()[0].size(); j++){

                tablero.getTab()[i][j].descubrir();
                if(tablero.getTab()[i][j].tieneMina() == true){
                    cout << "X ";
                }
                else{
                    cout << tablero.getTab()[i][j].getNumMinasCerca() << " ";
                }


            }
            cout << endl;
        }

    }

};

void crearFichero(const Jugador & j);
void mostrarTableroFinal(const Tablero & tablero);

#endif // HEADER_H
