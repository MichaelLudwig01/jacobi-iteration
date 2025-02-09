#include "matrix.hpp"

Matrix::Matrix(const std::string& filename, bool isTest)
{
    bool lesenErfolgreich = false;
    std::string dateiname = filename;
    std::string ausgabe;

    if (isTest) {
        this->isTestMode = true;
    }

    while (!lesenErfolgreich)
    {
        std::ifstream datei(dateiname);
        if (!datei.is_open()) {
            ausgabe = "Datei " + dateiname + " konnte nicht geöffnet werden.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        std::string zeile;

        if (!std::getline(datei, zeile)) {
            ausgabe = "Datei ist leer oder hat keine Zeilen.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }
        if (!validiereZahl(zeile)) {
            ausgabe = "Fehler: Erste Zeile ist keine gültige Zahl.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        n = static_cast<int>(konvertiereZahl(zeile));
        if (n <= 0) {
            ausgabe = "Fehler: n muss > 0 sein.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        A.clear();
        A.resize(n);
        b.clear();
        b.resize(n);

        bool matrixOk = true;
        for (int i = 0; i < n; i++) {
            if (!std::getline(datei, zeile)) {
                ausgabe = "Fehler: Zu wenige Zeilen für die Matrix.";
                matrixOk = false;
                break;
            }

            if (!validiereZeilenFormat(zeile)) {
                ausgabe = "Fehler in Zeile " + std::to_string(i+2) + ": enthaelt nicht nur Zahlen.";
                matrixOk = false;
                break;
            }

            std::vector<double> row = konvertiereZeilenFormat(zeile);
            if (static_cast<int>(row.size()) != n) {
                ausgabe = "Fehler in Zeile " + std::to_string(i+2) + ": falsche Anzahl Zahlen.";
                matrixOk = false;
                break;
            }
            A[i] = row;
        }

        if (!matrixOk) {
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        if (!std::getline(datei, zeile)) {
            ausgabe = "Fehler: Keine Zeile mehr für Vektor b.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        if (!validiereZeilenFormat(zeile)) {
            ausgabe = "Fehler bei Zeile für b: keine gültigen Zahlen.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        std::vector<double> tempB = konvertiereZeilenFormat(zeile);
        if (static_cast<int>(tempB.size()) != n) {
            ausgabe = "Fehler: b muss genau " + std::to_string(n) + " Zahlen enthalten.";
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }
        b = tempB;

        if (std::getline(datei, zeile)) {
            ausgabe = std::string("Fehler: Datei enthält mehr Zeilen als erwartet. Erlaubt: ") + std::to_string(n + 2) + " Zeilen, gefunden: mindestens " + std::to_string(n + 3);
            if (isTestMode) {
                importFehlerAusgabe(ausgabe);
                break;
            }
            dateiname = importFehlerAusgabe(ausgabe);
            continue;
        }

        lesenErfolgreich = true;
        this->filename   = dateiname;
    }

    if (!isTestMode) {
        std::cout << "Eingelesen:\n";
        std::cout << "n = " << n << "\nMatrix A:\n";
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                std::cout << A[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\nVektor b: ";
        for (int i=0; i<n; i++) {
            std::cout << b[i] << " ";
        }
        std::cout << "\n";
    }
}

Matrix::~Matrix()
{
    A.clear();
    b.clear();
}

bool Matrix::validiereZahl(const std::string& zahl) {
    try {
        std::size_t pos = 0;
        std::stod(zahl, &pos);
        return (pos == zahl.size());
    }
    catch (...) {
        return false;
    }
}

double Matrix::konvertiereZahl(const std::string& zahl) {
    return std::stod(zahl);
}

bool Matrix::validiereZeilenFormat(const std::string& zeile) {
    std::size_t start = 0;
    while (true) {
        std::size_t end = zeile.find(' ', start);
        std::string token = (end == std::string::npos)
                            ? zeile.substr(start)
                            : zeile.substr(start, end - start);

        if (!token.empty() && !validiereZahl(token)) {
            return false;
        }

        if (end == std::string::npos) {
            break;
        }
        start = end + 1;
    }
    return true;
}

std::vector<double> Matrix::konvertiereZeilenFormat(const std::string& zeile) {
    std::vector<double> werte;
    std::size_t start = 0;
    while (true) {
        std::size_t end = zeile.find(' ', start);
        std::string token = (end == std::string::npos)
                            ? zeile.substr(start)
                            : zeile.substr(start, end - start);

        if (!token.empty()) {
            werte.push_back(konvertiereZahl(token));
        }

        if (end == std::string::npos) {
            break;
        }
        start = end + 1;
    }
    return werte;
}

std::string Matrix::importFehlerAusgabe(std::string ausgabe) {

    if (isTestMode) {
        testOutput = ausgabe;
        return "";
    }

    std::string dateiname;
    std::cerr << ausgabe << std::endl;
    std::cout << "Bitte neuen Dateinamen eingeben: ";
    std::cin >> dateiname;
    return dateiname;
}

std::string Matrix::getTestOutput() {
    return testOutput;
}