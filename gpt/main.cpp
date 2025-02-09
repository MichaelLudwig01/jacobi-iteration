/*
* Project: Gleichungssysteme
 * File: main.cpp
 * Author: Michael Ludwig
 * Created on: 25. Januar 2025
 * Description: This program solves a system of linear equations iteratively using a matrix class.
 */


#include "matrix.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

/**
 * @brief main-Funktion zum Einlesen und Lösen eines LGS via Jacobi-Iteration.
 *
 * Aufrufbeispiel:
 *   ./solver input.txt 1e-7 100
 *
 * wobei:
 *   - input.txt die zu lesende Datei ist,
 *   - 1e-7      die Konvergenz-Schranke epsilon,
 *   - 100       die maximale Anzahl Iterationen (optional).
 */
int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "Aufruf: " << argv[0]
                  << " <dateiname> [epsilon] [maxIter]\n";
        return 1;
    }

    std::string filename = argv[1];
    double epsilon = 1e-6;    // Standardwert
    int maxIter    = 100;     // Standardwert

    if(argc >= 3)  // epsilon auslesen
    {
        epsilon = std::atof(argv[2]);
    }
    if(argc >= 4)  // maxIter auslesen
    {
        maxIter = std::atoi(argv[3]);
    }

    try
    {
        Matrix M;
        M.readFromFile(filename);

        if(!M.checkProcedureApplicable())
        {
            std::cerr << "Verfahren nicht anwendbar (z.B. Diagonaleintrag = 0)\n";
            return 2;
        }

        bool converged = false;
        std::vector<double> x = M.solveIteratively(epsilon, maxIter, converged);

        if(converged)
        {
            std::cout << "Konvergenz erreicht!\n";
        }
        else
        {
            std::cout << "Maximale Iterationsanzahl erreicht, evtl. nicht konvergent.\n";
        }

        // Lösung ausgeben:
        std::cout << "Loesungsvektor x':\n";
        for(double val : x)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";

        // Check mit z.B. Toleranz=1e-4
        bool ok = M.checkSolution(x, 1e-4);
        if(ok)
        {
            std::cout << "Test: A*x' ~ b -> OK\n";
        }
        else
        {
            std::cout << "Test: A*x' weicht zu stark von b ab.\n";
        }
    }
    catch(const std::exception &ex)
    {
        std::cerr << "Fehler: " << ex.what() << "\n";
        return 3;
    }
    return 0;
}
