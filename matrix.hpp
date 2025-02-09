#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

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
     * @brief Konstruktor, der aus einer Datei mit festgelegtem Format
     *        (n, dann n Zeilen für A, dann 1 Zeile für b) einliest.
     * @param filename Name der Textdatei.
     * @param isTest Gibt an, ob der Konstruktor im Testmodus aufgerufen wird.
     */
    Matrix(const std::string& filename, bool istTest = false);

    /**
     * @brief Destruktor.
     */
    ~Matrix();

    /**
     * @brief Prüft, ob das Jacobi-Verfahren auf diese Matrix anwendbar ist.
     * @return true, wenn anwendbar, sonst false.
     */
    bool verfahrenAnewendbar();

    /**
     * @brief Löst das LGS A*x = b via Jacobi-Iteration.
     * @params epsilonParam Genauigkeit der Lösung. Standardwert: 1e-7. Iteration bricht ab, wenn ||xNeu - xAlt|| < epsilon.
     * @return Lösungsvektor x.
     */
    std::vector<double> gleichungssystemLoesen(double epsilonParam = 1e-7, int maxIterParam = 100);

    /**
     * @brief Testet, ob eine Lösung x' tatsächlich A*x' ≈ b erfüllt.
     * @param xPruef Zu prüfender Lösungsvektor.
     * @return true, wenn die Lösung innerhalb einer Toleranz korrekt ist.
     */
    bool loesungValidieren(const std::vector<double>& xPruef);

    /**
     * @brief Gibt die Testausgabe zurück.
     * @return Testausgabe.
     */
    std::string getTestOutput();

private:
    int n;  ///< Dimension der Matrix.
    std::vector<std::vector<double>> A;  ///< Matrix A.
    std::vector<double> b;  ///< Vektor b.
    std::string filename;  ///< Dateiname.
    bool istTestMode;  ///< Gibt an, ob die Klasse im Testmodus ist.
    std::string testOutput;  ///< Testausgabe.

    /**
     * @brief Prüft, ob ein String als double konvertierbar ist.
     * @param zahl Zu prüfender String.
     * @return true, wenn der String eine gültige Zahl ist, sonst false.
     */
    bool validiereZahl(const std::string& zahl);

    /**
     * @brief Wandelt einen String in double um (kein Fehler-Check, da vorher validiert).
     * @param zahl Zu konvertierender String.
     * @return Konvertierter double-Wert.
     */
    double konvertiereZahl(const std::string& zahl);

    /**
     * @brief Prüft, ob eine Zeile nur Zahlen enthält, die durch Leerzeichen getrennt sind.
     * @param zeile Zu prüfende Zeile.
     * @return true, wenn die Zeile gültig ist, sonst false.
     */
    bool validiereZeilenFormat(const std::string& zeile);

    /**
     * @brief Zerlegt eine Zeile in Tokens und wandelt sie in double um.
     * @param zeile Zu konvertierende Zeile.
     * @return Vektor von double-Werten.
     */
    std::vector<double> konvertiereZeilenFormat(const std::string& zeile);

    /**
     * @brief Gibt eine Fehlermeldung aus und fordert einen neuen Dateinamen.
     * @param ausgabe Fehlermeldung.
     * @return Neuer Dateiname.
     */
    std::string importFehlerAusgabe(std::string ausgabe);
};

#endif