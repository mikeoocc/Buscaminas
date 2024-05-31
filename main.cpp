

// PROYECTO FINAL PROGRAMACION II
// Hecho por Miguel Oliver

// Notas:
// - La contraseña para ser admin es 2004. Ser admin permite ver las celdas descubiertas.
// - Para introducir fila y columna, primero se debe introducir fila, luego darle al enter y despues introducir columna

#include<iostream>
#include "header.h"
#include <memory>

using namespace std;

int menuPrincipal();

int main(){

    int opciones, dificultad, fila, columna, customFyC, customM, resp, codi, intentos=0;
    char respuesta, r, res;
    int cont;
    string n;
    bool finalizar, invalido{false};
    bool esAdmin{false};

    cout << endl;
    cout << "\n\n\t------- BIENVENIDO A BUSCAMINAS -------" << endl;

    Tablero t;
    Jugador jugador;
    Admin admin;

    do{
        cout << "\n\n\tEres Admin o Jugador? (1 o 2): ";
        cin >> resp;
    }while(resp<1 || resp>2);

    if(resp==1){

        do{
            cout << "\n\n\tIntroduzca la clave de acceso: ";
            cin >> codi;

            if(codi==2004){
                esAdmin = true;
                break;
            }
            else{
                cout << "\n\n\tClave incorrecta. . .\n\n";
                intentos++;
            }

        }while(intentos < 3);
    }
    else{
        esAdmin = false;
    }

    if(intentos >= 3){
        esAdmin = false;
        cout << "\n\n\tHa alcanzado el numero maximo de intentos. Se le asignara el rol de Jugador.\n\n";
    }

    cin.ignore();

    cout << "\n\n\tIntroduzca su nombre: ";
    getline(cin, n);
    jugador.setNombre(n);

    do{
        system("cls");

        opciones = menuPrincipal();

        switch(opciones){

        case 1:
        system("cls");
        cout << "\n\n\tSELECCIONAR DIFICULTAD " << endl;

        do{
            cout << "\n\n\tIntroduzca (1 facil,  2 dificil,  3 custom): ";
            cin >> dificultad;
        }while(dificultad<1 || dificultad>3);


        if(dificultad==1){
            t = Tablero(FIL_F, COL_F, NUM_MINAS_F);
        }else if(dificultad==2){
            t =Tablero(FIL_D, COL_D, NUM_MINAS_D);
        }else{

            cout << "\n\n\tIntroduzca numero de filas y columnas (debe ser simetrico): ";
            cin >> customFyC;

            cout << endl;

            cout << "\tIntroduzca el numero de minas: ";
            cin >> customM;

            t = Tablero(customFyC, customFyC, customM);

        }

        system("cls");

        finalizar = false;
        cont = t.getTotMinas();

        if(esAdmin == true){
            admin.mostrarTableroDebug(t);
        }
        else{
            cout << t;
        }

        cout << endl;

        cout << "\n\n\tIntroduzca el numero '-1' cuando se solicite fila y columna para finalizar el juego si no desea continuar." << endl;

        while(fila!=-1 || columna != -1){

            cout << "\n\tDesea marcar o desmarcar alguna celda? (s/n): ";
            cin >> r;

            if(r=='s'){

                do{

                    do{

                        cout << "\n\n\tIntroduzca fila y columna para marcar celda: ";
                        cin >> fila >> columna;

                        if(fila < 0 || fila > t.getFilass()-1 || columna < 0 || columna > t.getColss()-1){
                            cout << "\n\n\tEsa posicion es incorrecta! Vuelva a seleccionar fila y columna. . ." << endl;
                        }

                    }while(fila < 0 || fila > t.getFilass()-1 || columna < 0 || columna > t.getColss()-1);



                    if(t.getTab().at(fila).at(columna).estaMarcada()==true){
                        if(t.getTab().at(fila).at(columna).tieneMina()==true){
                            cont++;
                        }
                        t.desmarcarCelda(fila, columna);
                    }
                    else{
                        t.marcarCelda(fila, columna);
                        if(t.getTab().at(fila).at(columna).tieneMina()==true){
                            cont--;
                        }

                    }

                    if(cont==0){
                        finalizar = true;
                        break;
                    }

                    cout << "\n\n\tDesea volver a marcar o desmarcar una celda? (s/n): ";
                    cin >> res;

                }while(res=='s');

            }

            if(finalizar==true){

                cout << "\n\n\tHAS GANADO (todas las minas han sido marcadas). . ." << endl;
                mostrarTableroFinal(t);
                jugador++;
                crearFichero(jugador);
                break;

            }

            system("cls");

            cout << "\n\n\tMINAS RESTANTES: " << cont << endl;

            cout << endl;

            if(esAdmin == true){
                admin.mostrarTableroDebug(t);
            }
            else{
                cout << t;
            }

            cout << endl;

            do{
                try{
                    cout << "\n\n\tIntroduzca fila y columna: "; cin >> fila >> columna;
                    if(fila < -1 || fila > t.getFilass()-1 || columna < -1 || columna > t.getColss()-1){
                        throw 1;
                    }
                    else{
                        invalido = true;
                    }
                }catch(int a){
                    if(a==1){
                        cout << "\n\n\tError. . . El numero introducido es incorrecto. . ." << endl << endl;
                    }
                }
            }while(invalido==false);

            if(fila == -1 || columna == -1 || (fila==-1 && columna == -1)){
                break;
            }
            bool ganado = t.descubrirCelda(fila, columna);
            bool mina =false;
            if (t.getTab()[fila][columna].tieneMina()) {
                t.getTab()[fila][columna].descubrir();
                mina = true;
            }

            if(mina == true){
                cout << "\n\n\tHAS PERDIDO !!!" << endl;
                mostrarTableroFinal(t);
                crearFichero(jugador);
                break;
            }else{
                if(ganado==true && t.comprobarVictoria()==true){
                    cout << "\n\n\tHAS GANADO !!! (todas las celdas sin minas han sido descubiertas). . ." << endl;
                    mostrarTableroFinal(t);
                    jugador++;
                    crearFichero(jugador);
                    break;
                }

            }

            if(esAdmin == true){
                admin.mostrarTableroDebug(t);
            }
            else{
                cout << t;
            }

            cout << endl;

        }

        break;

        case 2:

            system("cls");

            cout << "\n\n\t- - - - - - R E G L A S   D E L   J U E G O - - - - - -" << endl;

            cout << "\n\t1. Si descubres una celda con mina, perderas la partida. " << endl;
            cout << "\n\t2. Si descubres todas las celdas sin mina, habras ganado. " << endl;
            cout << "\n\t3. Si marcas todas las celdas con mina, habras gando. " << endl;
            cout << "\n\t4. Al descubrir una celda sin mina, esta tendra un valor que representa" << endl;
            cout << "\tel numero total de minas que hay en las celdas adyacentes. " << endl;
            cout << "\n\t5. Si descubres una celda con el valor 0, se descubriran todas las celdas adyacentes. " << endl;
            cout << "\n\t6. Se puede descubrir una celda marcada sin necesidad de desmarcarla. " << endl;
            cout << "\n\t7. Se trata de un juego solitario, sin embargo, se pueden comparar resultados" << endl;
            cout << "\tcuando termine el juego. " << endl;

        break;

        case 3:
        system("cls");
        cout << "\n\n\tGracias por jugar!" << endl << endl;
        return 0;

        }

        cout << "\n\n\tVolver al menu (S/N): ";
        cin >> respuesta;
    }while(respuesta=='S');

    return 0;
}

int menuPrincipal(){

    int op;

    cout << "\n\n\n\t1. Seleccionar dificultad " << endl;
    cout << "\t2. Reglas " << endl;
    cout << "\t3. Terminar el juego " << endl;

    do{
        cout << "\n\tIntroduzca la opcion: ";
        cin >> op;
    }while(op<1 || op>3);

    return op;
}
