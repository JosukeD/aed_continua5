#include <string>
#include <iostream>
using namespace std;

class Nodo {
public:
    int clave;
    int valor;
    Nodo* siguiente;
};

class Lista {
public:
    Nodo* cabeza;
    Lista() : cabeza(nullptr) {}

    void insertar(int clave, int valor) {
        Nodo* nuevoNodo = new Nodo();
        nuevoNodo->clave = clave;
        nuevoNodo->valor = valor;
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }

    void eliminar(int clave) {
        if (cabeza == nullptr) return;
        if (cabeza->clave == clave) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }
        Nodo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->clave == clave) {
                Nodo* temp = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                delete temp;
                return;
            }
            actual = actual->siguiente;
        }
    }

    Nodo* buscar(int clave) {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->clave == clave) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
};

class TablaHash {
public:
    int tamano;
    Lista** tabla;

    TablaHash(int tamano) : tamano(tamano) {
        tabla = new Lista*[tamano];
        for (int i = 0; i < tamano; i++) {
            tabla[i] = new Lista();
        }
    }

    int funcionHash(int clave) {
        return clave % tamano;
    }

    void insertar(int clave, int valor) {
        int indice = funcionHash(clave);
        tabla[indice]->insertar(clave, valor);
    }

    void eliminar(int clave) {
        int indice = funcionHash(clave);
        tabla[indice]->eliminar(clave);
    }

    void actualizar(int clave, int nuevoValor) {
        int indice = funcionHash(clave);
        Nodo* nodo = tabla[indice]->buscar(clave);
        if (nodo) {
            nodo->valor = nuevoValor;
        }
    }

    int obtenerValor(int clave) {
        int indice = funcionHash(clave);
        Nodo* nodo = tabla[indice]->buscar(clave);
        if (nodo) {
            return nodo->valor;
        }
        return -1; // Devuelve -1 si la clave no se encuentra en la tabla hash
    }

};

class Solution {
public:
    string minimizeStringValue(string s) {
        TablaHash letras(30); // el constructor recibe el tamaño de la tabla, lo defino en 30 porque hay 27 letras en el alfabeto ingles y el signo de interrogacion. Es un tamanho extra por si acaso
        int costo_total = 0;
        string result = "";

        for (auto l : s) {
            
            int costo_actual;
            int letra_ascci = int(l);

            if (letra_ascci == 63) { //si es un signo de interrogacion
                for (int i = 97; i <= 122; i++) {
                    if (letras.obtenerValor(i) == -1) {
                        letra_ascci = i;
                        break;
                    }
                }
            } 

            if (letras.obtenerValor(letra_ascci) == -1) {
                letras.insertar(letra_ascci, 0);
            } 
            else {
                letras.actualizar(letra_ascci, letras.obtenerValor(letra_ascci + 1));
            }

            costo_actual = letras.obtenerValor(letra_ascci);
            
            result += char(letra_ascci);
            costo_total += costo_actual;
        }

        return result;
    }   
};


int main() {
    

    cout << "-----Pregunta 3-----" << endl;
    cout << "Ejemplo 1: ???" << endl;
    Solution sol;
    cout <<  "Resultado: " << sol.minimizeStringValue("???") << endl;
    cout << "Ejemplo 2: a?a?" << endl;
    cout << "Resultado: " << sol.minimizeStringValue("a?a?") << endl;

    return 0;
}