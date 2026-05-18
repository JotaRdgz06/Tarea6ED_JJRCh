#include <iostream>
#include <string>
#include <stdexcept>
#include <random>
#include "time.h"
#include "LinkedList.h"
#include "List.h"

using std::cout;
using std::getline;
using std::string;
using std::cin;
using std::runtime_error;
using std::exception;

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    try {
        while (true) {
            string tam;
            cout << "Ingrese el tamaño de la lista a ordenar: ";
            getline(cin, tam);
			int tamint = stoi(tam);
            if (tamint < 2) {
                throw runtime_error("Tamaño debe ser un entero mayor a 2");
            }
            string base;
			cout << "Ingrese la base numerica a usar en el ordenamiento: ";
			getline(cin, base);
			int baseint = stoi(base);
			if (baseint < 2) {
				throw runtime_error("Base debe ser un entero mayor o igual a 2");
			}
			LinkedList<int>* lista = new LinkedList<int>();
            srand(time(0));
            for (int i = 0; i < tamint; i++) {
                int num = rand() % 9999;
                lista->append(num);
            }
			radixSort(lista, baseint);
        }
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

int obtenerDigito(int numero, int base, int divisor) {
    for (int i = 0; i < divisor; i++) {
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

    }
        
}