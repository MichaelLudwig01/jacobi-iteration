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
 *   ./solver example
 *   ./solver test
 */


#include "matrix.hpp"
#include "test.hpp"
#include <iostream>
#include <string>

/**
 * @brief main-Funktion zum Einlesen und Lösen eines LGS via Jacobi-Iteration.
 * @brief main-Funktion zum testen aller Testszenarien..
 * Aufrufbeispiel:
 *   ./solver example
 */
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Aufruf: " << argv[0] << " <filename>" << std::endl;;
        return 1;
    }

    std::string filename = argv[1];

    if (filename == "test" || filename == "Test" || filename == "TEST") {

        Test testClass;
        std::cout << "Testdaten wurden erstellt." << std::endl;;
        testClass.testeAlles();

    } else {
        Matrix solver(filename);

        if (!solver.verfahrenAnewendbar()) {
            std::cerr << "Dieses Verfahren ist nicht anwendbar!" << std::endl;;
            return 2;
        }

        std::vector<double> loesung = solver.gleichungssystemLoesen();
        std::cout << "Lösung wurde berechnet:" << std::endl;;
        for (unsigned long i = 0; i < loesung.size(); i++) {
            std::cout << "x[" << i << "] = " << loesung[i] << "" << std::endl;;
        };
        std::cout << "" << std::endl;;
        if (!solver.loesungValidieren(loesung)) {
            std::cerr << "Die Lösung hat den Test nicht bestanden." << std::endl;;
            return 3;
        } else {
            std::cout << "Die Lösung hat den Test bestanden." << std::endl;;
        }
    }

    return 0;
}
