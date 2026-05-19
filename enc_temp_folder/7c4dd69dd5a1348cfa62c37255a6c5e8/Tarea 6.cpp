#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include "LinkedList.h"
#include "List.h"

using std::cout;
using std::getline;
using std::string;
using std::cin;
using std::runtime_error;
using std::exception;
using std::streamsize;
using std::numeric_limits;

int obtenerMayor(LinkedList<int>* lista);
int obtenerDigito(int numero, int base, int divisor);
void radixSort(LinkedList<int>* lista, int base);

bool esNumero(string& tam) {
    for (char c : tam) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "es_ES.UTF-8");
    try {
        string seguir;
        do {
            string tam;
            int tamint;
            do {
                cout << "Ingrese el tamaño de la lista a ordenar: ";
                getline(cin, tam);
                if (!esNumero(tam) || stoi(tam) < 2) {
                    throw runtime_error("tamaño debe ser un entero mayor o igual a 2");
                }
                tamint = stoi(tam);
			} while (stoi(tam) < 2 || !esNumero(tam));

            string base;
            int baseint;
            do {
                cout << "Ingrese la base numerica a usar en el ordenamiento: " << endl;
                getline(cin, base);
                if (!esNumero(base) || stoi(base) < 2) {
                    throw runtime_error("Base debe ser un entero mayor o igual a 2");
                }
                baseint = stoi(base);
			} while (stoi(base) < 2 || !esNumero(base));
            auto inicio = std::chrono::high_resolution_clock::now();
            LinkedList<int>* lista = new LinkedList<int>();
            for (int i = 0; i < tamint; i++) {
                int num = rand() % 9999;
                lista->append(num);
            }
            cout << "lista sin ordenar: " << endl;
			lista->print();
            cout << endl;
			radixSort(lista, baseint);
            auto fin = std::chrono::high_resolution_clock::now();
            auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
            cout << endl;
            cout << "Tiempo de ejecución: " << duracion << " ms" << endl;


            cout << endl;
			cout << "Desea continuar? (s/n): ";
			getline(cin, seguir);
			if (seguir != "s" && seguir != "S" && seguir != "n" && seguir != "N") {
				throw runtime_error("Opción no válida, ingrese s o n.");
			}
        } while (seguir == "s" || seguir == "S");
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
}

int obtenerMayor(LinkedList<int>* lista) {
    lista->goToStart();
    int maximo = lista->getElement();
    lista->next();
    while (!lista->atEnd()) {
        int actual = lista->getElement();
        if (actual > maximo) {
            maximo = actual;
        }
        lista->next();
    }
    return maximo;
}

int obtenerDigito(int numero, int base, int posicion) {
    int divisor = 1;
    for (int i = 0; i < posicion; i++) {
        divisor *= base;
    }
    return (numero / divisor) % base;
}

void radixSort(LinkedList<int>* lista, int base) {
    int mayor = obtenerMayor(lista);
    LinkedList<int>** baldes = new LinkedList<int>*[base];
    for (int i = 0; i < base; i++) {
        baldes[i] = new LinkedList<int>();
    }

    int posicion = 0;
    int divisor = 1;
    while (divisor <= mayor) {
        lista->goToStart();
        while (!lista->atEnd()) {
            int numero = lista->getElement();
            int digito = obtenerDigito(numero, base, posicion);
            baldes[digito]->append(numero);
            lista->next();
        }

        lista->goToStart();
        for (int j = 0; j < base; j++) {
            baldes[j]->goToStart();
            while (!baldes[j]->atEnd()) {
                int numeroBalde = baldes[j]->getElement();
                lista->setElement(numeroBalde);
                lista->next();
                baldes[j]->next();
            }
            baldes[j]->clear();
        }
        posicion++;
        divisor *= base;
    }
    for (int i = 0; i < base; i++) {
        delete baldes[i];
    }
    delete[] baldes;
	cout << "lista ordenada: " << endl;
    lista->print();
    cout << endl;
}