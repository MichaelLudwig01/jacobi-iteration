//
// Created by Michael Ludwig on 25.01.25.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

/**
 * @class Matrix
 * @brief Verwaltet eine n x n-Matrix A und einen n-dimensionalen Vektor b.
 *
 * Diese Klasse ermöglicht das Einlesen aus einer Datei, das Prüfen der
 * Anwendbarkeit des iterativen Verfahrens, das Lösen des Gleichungssystems
 * A*x = b mittels Jacobi-Iteration sowie das Testen der Lösung (A*x' ≈ b).
 */
class Matrix
{
public:
    /**
     * @brief Standard-Konstruktor.
     */
    Matrix();

    /**
     * @brief Liest die Matrix und den Vektor b aus der angegebenen Datei.
     * @param filename Name der Eingabedatei.
     * @throw std::runtime_error bei Einlesefehlern oder ungültigem Format.
     */
    void readFromFile(const std::string &filename);

    /**
     * @brief Prüft, ob das Verfahren anwendbar ist (z.B. a_{ii} != 0 für alle i).
     * @return true, falls anwendbar, sonst false.
     */
    bool checkProcedureApplicable() const;

    /**
     * @brief Löst das Gleichungssystem A*x=b iterativ (Jacobi-Verfahren).
     * @param epsilon Abbruchschranke für ||x^(k) - x^(k-1)||.
     * @param maxIterations Maximale Anzahl Iterationen (falls gewünscht).
     * @param converged Gibt am Ende an, ob Konvergenz (true) oder Abbruch (false).
     * @return Der approximierte Lösungsvektor.
     * @throw std::runtime_error falls Verfahren nicht anwendbar.
     */
    std::vector<double> solveIteratively(double epsilon,
                                         int maxIterations,
                                         bool &converged) const;

    /**
     * @brief Testet mit Hilfe von ||A*x' - b|| < tolerance, ob die Lösung gut ist.
     * @param x Zu testender Lösungsvektor.
     * @param tolerance Toleranzschwelle.
     * @return true, falls ||A*x - b|| < tolerance, sonst false.
     */
    bool checkSolution(const std::vector<double> &x, double tolerance) const;

private:
    int n;                  ///< Dimension der Matrix bzw. des Vektors.
    std::vector<double> A;  ///< Einträge der Matrix im Zeilenformat (size = n*n).
    std::vector<double> b;  ///< Einträge des rechten Seitenvektors (size = n).

    /**
     * @brief Hilfsfunktion: Zugriff auf A(i,j).
     */
    double getA(int i, int j) const
    {
        return A[i*n + j];
    }

    /**
     * @brief Hilfsfunktion: Setzen von A(i,j).
     */
    void setA(int i, int j, double val)
    {
        A[i*n + j] = val;
    }
};

#endif // MATRIX_HPP

