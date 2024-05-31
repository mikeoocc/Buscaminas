
#include "header.h"
#include <fstream> // Lo usamos para crear ficheros donde se guardan las puntuaciones. El nombre del fichero es "puntuaciones"

bool Tablero::descubrirCelda(int fila, int columna){
    if (fila < 0 || fila >= tablero.size() || columna < 0 || columna >= tablero[0].size()) {
        return false;
    }

    Celda& celda = tablero[fila][columna];

    if (!celda.estaDescubierta()) {
        celda.descubrir();

        if (celda.getNumMinasCerca() == 0) {
            for (int i = fila - 1; i <= fila + 1; i++) {
                for (int j = columna - 1; j <= columna + 1; j++) {
                    descubrirCelda(i, j);
                }
            }
        }
        return !celda.tieneMina() && comprobarVictoria();
    }

    return false;
}
void Tablero::marcarCelda(int fila, int columna){
    if (fila < 0 || fila >= tablero.size() || columna < 0 || columna >= tablero[0].size()) {
        return;
    }

    Celda& celda = tablero[fila][columna];

    if (!celda.estaDescubierta()){

        celda.marcar();
    }
}
void Tablero::desmarcarCelda(int fila, int columna){
    if (fila < 0 || fila >= tablero.size() || columna < 0 || columna >= tablero[0].size()) {
        return;
    }

    Celda& celda = tablero[fila][columna];

    if (!celda.estaDescubierta()){
        celda.desmarcar();
    }
}
bool Tablero::comprobarVictoria(){
    bool terminar{false};
    int cont = 0;
    for (int i = 0; i < tablero.size(); i++) {
        for (int j = 0; j < tablero[0].size(); j++) {
            Celda& celda = tablero[i][j];
            if(celda.estaDescubierta()){
                cont++;
            }
        }
    }

    if(cont == this->getFilass()*this->getColss()-this->getTotMinas()){
        terminar = true;
    }

    return terminar;
}
void crearFichero(const Jugador & j){

    ofstream outFile;

    outFile.open("puntuaciones.txt", ios::app);

    outFile<<" PUNTUACION " <<endl;

    outFile<<" ------------ ";

    outFile<<endl;

    outFile << "El jugador " << j.getNombre() << " ha conseguido " << j.getVictorias() << " victorias " << endl;

    outFile<<endl;

    outFile.close();
}
ostream& operator<<(ostream &os , const Tablero & tablero){

    os << "  ";
    for (int j = 0; j < tablero.getTab()[0].size(); j++){
        os << j << " ";
    }
    os << endl;

    for (int i = 0; i < tablero.getTab().size(); i++){
        os << i << " ";
        for (int j = 0; j < tablero.getTab()[0].size(); j++){
            if (tablero.getTab()[i][j].estaDescubierta()){
                if(tablero.getTab()[i][j].tieneMina()==true){
                    os << "X ";
                }
                else{
                    os << tablero.getTab()[i][j].getNumMinasCerca() << " ";
                }
            }
            else if (tablero.getTab()[i][j].estaMarcada()){
                os << "M ";
            }
            else{
                os << "- ";
            }

        }
        os << endl;
    }

    return os;

}
void mostrarTableroFinal(const Tablero & tablero){
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

