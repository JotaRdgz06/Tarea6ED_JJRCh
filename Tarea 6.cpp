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
            if (stoi(tam) < 2) {
                throw runtime_error("Tamaño debe ser un entero mayor a 2");
            }
            string base;
			cout << "Ingrese la base numerica a usar en el ordenamiento: ";
			getline(cin, base);
			if (stoi(base) < 2) {
				throw runtime_error("Base debe ser un entero mayor o igual a 2");
			}
			LinkedList<int>* lista = new LinkedList<int>();
            srand(time(0));
            for (int i = 0; i < stoi(tam); i++) {
                int num = rand() % 9999;
                lista->append(num);
            }
			lista->print();
        delete lista;
			return 0;
            
        }
	}
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
}