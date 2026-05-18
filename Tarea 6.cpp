#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include "LinkedList.h"
#include "List.h"

using std::cout;
using std::getline;
using std::string;
using std::cin;
using std::runtime_error;
using std::exception;

int obtenerMayor(LinkedList<int>* lista);
int obtenerDigito(int numero, int base, int divisor);
void radixSort(LinkedList<int>* lista, int base);

int main() {
    srand(time(0));
    setlocale(LC_ALL, "es_ES.UTF-8");
    try {
        while (true) {
            string tam;
            cout << "Ingrese el tamaño de la lista a ordenar: ";
            getline(cin, tam);
            int tamint = stoi(tam);
            if (tamint < 2 || isalpha(tamint)) {
                throw runtime_error("Tamaño debe ser un entero mayor a 2");
            }
            string base;
            cout << "Ingrese la base numerica a usar en el ordenamiento: ";
            getline(cin, base);
            int baseint = stoi(base);
            if (baseint < 2 || isalpha(baseint)) {
                throw runtime_error("Base debe ser un entero mayor o igual a 2");
            }
            LinkedList<int>* lista = new LinkedList<int>();
            for (int i = 0; i < tamint; i++) {
                int num = rand() % 9999;
                lista->append(num);
            }
            lista->goToStart();
			int num1 = lista->getElement();
            lista->print();
            int mayorint = obtenerMayor(lista);
            cout << mayorint << endl;
			cout << obtenerDigito(mayorint, baseint, 0) << endl;
            delete lista;
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
            int digito = obtenerDigito(numero, base, divisor);
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
    lista->print();
}