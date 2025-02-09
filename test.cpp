#include "test.hpp"
#include "matrix.hpp"
//
// Created by Michael Ludwig on 07.02.25.
//

TestData::TestData(
    std::string n,
    std::vector<std::vector<std::string>> A,
    std::vector<std::string> b,
    std::string erwartetesEgebnis
){
    this->n = n;
    this->A = A;
    this->b = b;
    this->erwartetesEgebnis = erwartetesEgebnis;
}

Test::Test() {

    TestData data1(
        "A",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "7"},
        "Fehler: Erste Zeile ist keine gültige Zahl.");

    TestData data2(
        "-1",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "7"},
        "Fehler: n muss > 0 sein.");

    TestData data3(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}},
        {"7", "7", "7"},
        "Fehler: Keine Zeile mehr für Vektor b.");

    TestData data4(
        "3",
        {{"10", "-1", "A"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "7"},
        "Fehler in Zeile 2: enthaelt nicht nur Zahlen.");

    TestData data5(
        "3",
        {{"10", "-1", "2", "4"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "7"},
        "Fehler in Zeile 2: falsche Anzahl Zahlen.");

    TestData data6(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}},
        {"7", "7", "7"},
        "Fehler: Keine Zeile mehr für Vektor b.");

    TestData data7(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "A"},
        "Fehler bei Zeile für b: keine gültigen Zahlen.");

    TestData data8(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7"},
        "Fehler: b muss genau 3 Zahlen enthalten.");

    TestData data9(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}, {"7", "7", "7"}},
        {"1", "2", "3"},
        "Fehler: Datei enthält mehr Zeilen als erwartet. Erlaubt: 5 Zeilen, gefunden: mindestens 6");

    TestData data10(
        "3",
        {{"10", "-1", "2"},{"1", "11", "-1"}, {"2", "-1", "10"}},
        {"7", "7", "7"},
        "Lösbar");

    TestData data11(
    "5",
    {{"1", "2", "3", "4", "5"},
     {"2", "3", "4", "5", "6"},
     {"3", "4", "5", "6", "7"},
     {"4", "5", "6", "7", "8"},
     {"5", "6", "7", "8", "9"}},
    {"1", "2", "3", "4", "5"},
    "Verfahren nicht anwendbar"
    );

    testDaten.push_back(data1);
    testDaten.push_back(data2);
    testDaten.push_back(data3);
    testDaten.push_back(data4);
    testDaten.push_back(data5);
    testDaten.push_back(data6);
    testDaten.push_back(data7);
    testDaten.push_back(data8);
    testDaten.push_back(data9);
    testDaten.push_back(data10);
    testDaten.push_back(data11);
}

TestData::~TestData() {}
Test::~Test(){}

void Test::testeAlles() {
    testeFalscherDateiname();
    testeLeereDatei();
    testeFehlerhafteEingabeErsteZeile();
    testeNdarfNichtNullSein();
    testeZuwEnigZeilen();
    testeFehlerhafteEingabeErsteZeileWeitereZeilen();
    testefalscheAnzahlAnZahlen();
    testeForhandenSeinVektorB();
    testeFehlerhafteEingabeVektorB();
    testeZuVieleZahlenVektorB();
    testeZuVieleZeilen();
    testeEefolgreicheValidierung();
    testeFehlerhafteValidierung();
    testeJacobiIteration();
    testeUeberpruefung();
}

void Test::testeFalscherDateiname() {
    Matrix testMatrix("falscherDateiname", true);
    if (testMatrix.getTestOutput() == "Datei falscherDateiname konnte nicht geöffnet werden.") {
        std::cout << "Test erfolgreich: Falscher Dateiname" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Falscher Dateiname" << std::endl;
    }
}

void Test::testeLeereDatei() {
    std::ofstream neueDatei("testDatei");

    if (neueDatei.is_open()) {
        neueDatei.close();
    } else {
        std::cerr << "Datei konnte nicht erstellt werden" << std::endl;
    }
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == "Datei ist leer oder hat keine Zeilen.") {
        std::cout << "Test erfolgreich: Leere Datei" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Leere Datei" << std::endl;
    }
}

void Test::testeFehlerhafteEingabeErsteZeile() {
    schreibeInDatei(testDaten[0]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[0].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehlerhafte Eingabe Erste Zeile" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehlerhafte Eingabe Erste Zeile" << std::endl;
    }
}

void Test::testeNdarfNichtNullSein() {
    schreibeInDatei(testDaten[1]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[1].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: n darf nicht null sein" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: n darf nicht null sein" << std::endl;
    }
}

void Test::testeZuwEnigZeilen() {
    schreibeInDatei(testDaten[2]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[2].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Zu wenig Zeilen" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Zu wenig Zeilen" << std::endl;
    }
}

void Test::testeFehlerhafteEingabeErsteZeileWeitereZeilen() {
    schreibeInDatei(testDaten[3]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[3].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehlerhafte Eingabe Erste Zeile Weitere Zeilen" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehlerhafte Eingabe Erste Zeile Weitere Zeilen" << std::endl;
    }
}

void Test::testefalscheAnzahlAnZahlen() {
    schreibeInDatei(testDaten[4]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[4].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Falsche Anzahl Zahlen" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Falsche Anzahl Zahlen" << std::endl;
    }
}

void Test::testeForhandenSeinVektorB() {
    schreibeInDatei(testDaten[5]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[5].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehler: Keine Zeile mehr für Vektor b" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehler: Keine Zeile mehr für Vektor b" << std::endl;
    }
}

void Test::testeFehlerhafteEingabeVektorB() {
    schreibeInDatei(testDaten[6]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[6].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehler bei Zeile für b: keine gültigen Zahlen" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehler bei Zeile für b: keine gültigen Zahlen" << std::endl;
    }
}

void Test::testeZuVieleZahlenVektorB() {
    schreibeInDatei(testDaten[7]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[7].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehler: b muss genau 3 Zahlen enthalten" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehler: b muss genau 3 Zahlen enthalten" << std::endl;
    }
}

void Test::testeZuVieleZeilen() {
    schreibeInDatei(testDaten[8]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.getTestOutput() == testDaten[8].erwartetesEgebnis) {
        std::cout << "Test erfolgreich: Fehler: Datei enthält mehr Zeilen als erwartet" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehler: Datei enthält mehr Zeilen als erwartet" << std::endl;
    }
}

void Test::testeEefolgreicheValidierung() {
    schreibeInDatei(testDaten[9]);
    Matrix testMatrix("testDatei", true);
    if (testMatrix.verfahrenAnewendbar()) {
        std::cout << "Test erfolgreich: Erfolgreiche Validierung" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Erfolgreiche Validierung" << std::endl;
    }
}

void Test::testeFehlerhafteValidierung() {
    schreibeInDatei(testDaten[10]);
    Matrix testMatrix("testDatei", true);
    if (!testMatrix.verfahrenAnewendbar()) {
        std::cout << "Test erfolgreich: Fehlerhafte Validierung" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Fehlerhafte Validierung" << std::endl;
    }
}

void Test::testeJacobiIteration() {
    schreibeInDatei(testDaten[9]);
    Matrix testMatrix("testDatei", true);
    std::vector<double> loesung = testMatrix.gleichungssystemLoesen();
    double tolerance = 1e-6;
    if (std::fabs(loesung[0] - 0.636364) < tolerance &&
        std::fabs(loesung[1] - 0.636364) < tolerance &&
        std::fabs(loesung[2] - 0.636364) < tolerance) {
        std::cout << "Test erfolgreich: Jacobi Iteration" << std::endl;
        } else {
            std::cout << loesung[0] << " " << loesung[1] << " " << loesung[2] << std::endl;
            std::cerr << "Test fehlgeschlagen: Jacobi Iteration" << std::endl;
        }
}

void Test::testeUeberpruefung() {
    schreibeInDatei(testDaten[9]);
    Matrix testMatrix("testDatei", true);
    std::vector<double> loesung = testMatrix.gleichungssystemLoesen();
    if (testMatrix.loesungValidieren(loesung)) {
        std::cout << "Test erfolgreich: Überprüfung" << std::endl;
    } else {
        std::cerr << "Test fehlgeschlagen: Überprüfung" << std::endl;
    }
}

void Test::schreibeInDatei(const TestData& data) {
    std::ofstream neueDatei("testDatei");

    if (neueDatei.is_open()) {
        neueDatei << data.n << std::endl;
        for (const auto& row : data.A) {
            for (const auto& val : row) {
                neueDatei << val << " ";
            }
            neueDatei << std::endl;
        }
        for (const auto& val : data.b) {
            neueDatei << val << " ";
        }
        neueDatei << std::endl;
        neueDatei.close();
    } else {
        std::cerr << "Datei konnte nicht erstellt werden" << std::endl;
    }
}