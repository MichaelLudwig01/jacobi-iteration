/**
 * @brief Hauptdatei für das Lösen von Gleichungssystemen mittels Jacobi-Iteration.
 *
 * Projekt: Gleichungssysteme
 * Datei: main.cpp
 * Autor: Michael Ludwig
 * Erstellt am: 25. Januar 2025
 * Beschreibung:
 *   Dieses Programm löst iterativ ein lineares Gleichungssystem mit einer Matrix-Klasse.
 *
 * Aufrufbeispiel:
 *   ./solver input.txt
 */


#include "matrix.hpp"
#include "test.hpp"
#include <iostream>
#include <string>

/**
 * @brief main-Funktion zum Einlesen und Lösen eines LGS via Jacobi-Iteration.
 *
 * Aufrufbeispiel:
 *   ./solver input.txt
 */
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Aufruf: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = argv[1];

    if (filename == "test" || filename == "Test" || filename == "TEST") {

        Test testClass;
        std::cout << "Testdaten wurden erstellt.\n";
        testClass.testeAlles();

    } else {
        Matrix solver(filename);

        if (!solver.verfahrenAnewendbar()) {
            std::cerr << "Dieses Verfahren ist nicht anwendbar!\n";
            return 2;
        }

        std::vector<double> loesung = solver.gleichungssystemLoesen();
        std::cout << "Lösung wurde berechnet:\n";
        for (unsigned long i = 0; i < loesung.size(); i++) {
            std::cout << "x[" << i << "] = " << loesung[i] << "\n";
        };
        std::cout << "\n";
        if (!solver.loesungValidieren(loesung)) {
            std::cerr << "Die Lösung hat den Test nicht bestanden.\n";
            return 3;
        } else {
            std::cout << "Die Lösung hat den Test bestanden.\n";
        }
    }

    return 0;
}
