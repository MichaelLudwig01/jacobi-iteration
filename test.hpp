//
// Created by Michael Ludwig on 27.01.25.
//

#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

/**
 * @class TestData
 * @brief Klasse zur Speicherung von Testdaten für Matrix und Vektor.
 */
class TestData {
public:
    /**
     * @brief Konstruktor zur Initialisierung der Testdaten.
     * @param n Dimension der Matrix.
     * @param A Matrixdaten als Vektor von Vektoren von Strings.
     * @param b Vektordaten als Vektor von Strings.
     * @param erwartetesEgebnis Erwartetes Ergebnis als String.
     */
    TestData(
        std::string n,
        std::vector<std::vector<std::string>> A,
        std::vector<std::string> b,
        std::string erwartetesEgebnis
    );

    std::string n; ///< Dimension der Matrix.
    std::vector<std::vector<std::string>> A; ///< Matrixdaten.
    std::vector<std::string> b; ///< Vektordaten.
    std::string erwartetesEgebnis; ///< Erwartetes Ergebnis.

    /**
     * @brief Destruktor.
     */
    ~TestData();
};

/**
 * @class Test
 * @brief Klasse zur Durchführung verschiedener Tests auf Matrixoperationen.
 */
class Test {
public:
    std::vector<TestData> testDaten; ///< Sammlung von Testdaten.

    /**
     * @brief Konstruktor zur Initialisierung der Testdaten.
     */
    Test();

    /**
     * @brief Destruktor.
     */
    ~Test();

    /**
     * @brief Funktion zum Ausführen aller Tests.
     */
    void testeAlles();

private:
    /**
     * @brief Schreibt Testdaten in eine Datei.
     * @param data Zu schreibende Testdaten.
     */
    void schreibeInDatei(const TestData& data);

    /**
     * @brief Test für den Umgang mit falschem Dateinamen.
     */
    void testeFalscherDateiname();

    /**
     * @brief Test für den Umgang mit leerer Datei.
     */
    void testeLeereDatei();

    /**
     * @brief Test für den Umgang mit ungültiger Eingabe in der ersten Zeile.
     */
    void testeFehlerhafteEingabeErsteZeile();

    /**
     * @brief Test zur Sicherstellung, dass n nicht null ist.
     */
    void testeNdarfNichtNullSein();

    /**
     * @brief Test für den Umgang mit zu wenigen Zeilen.
     */
    void testeZuwEnigZeilen();

    /**
     * @brief Test für den Umgang mit ungültiger Eingabe in der ersten Zeile und weiteren Zeilen.
     */
    void testeFehlerhafteEingabeErsteZeileWeitereZeilen();

    /**
     * @brief Test für den Umgang mit falscher Anzahl an Werten.
     */
    void testefalscheAnzahlAnZahlen();

    /**
     * @brief Test zur Sicherstellung, dass der Vektor b vorhanden ist.
     */
    void testeForhandenSeinVektorB();

    /**
     * @brief Test für den Umgang mit ungültiger Eingabe im Vektor b.
     */
    void testeFehlerhafteEingabeVektorB();

    /**
     * @brief Test für den Umgang mit zu vielen Werten im Vektor b.
     */
    void testeZuVieleZahlenVektorB();

    /**
     * @brief Test für den Umgang mit zu vielen Zeilen.
     */
    void testeZuVieleZeilen();

    /**
     * @brief Test für die erfolgreiche Validierung der Methode.
     */
    void testeEefolgreicheValidierung();

    /**
     * @brief Test für die fehlerhafte Validierung der Methode.
     */
    void testeFehlerhafteValidierung();

    /**
     * @brief Test für die Jacobi-Iteration.
     */
    void testeJacobiIteration();

    /**
     * @brief Test für die Überprüfung der Lösung.
     */
    void testeUeberpruefung();
};

#endif