//
// Created by Michael Ludwig on 25.01.25.
//

#include "matrix.hpp"
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <iostream>

Matrix::Matrix() : n(0)
{
    // leer
}

void Matrix::readFromFile(const std::string &filename)
{
    std::ifstream in(filename);
    if(!in.is_open())
    {
        throw std::runtime_error("Fehler beim Öffnen der Datei: " + filename);
    }

    // 1) n lesen
    in >> n;
    if(!in.good() || n <= 0)
    {
        throw std::runtime_error("Ungueltiger Wert fuer n in der Datei.");
    }

    // Speicher für Matrix & Vektor reservieren
    A.resize(n*n);
    b.resize(n);

    // 2) Matrix-Eintraege lesen
    for(int i = 0; i < n*n; ++i)
    {
        if(!(in >> A[i]))
        {
            throw std::runtime_error("Fehler beim Einlesen der Matrixelemente.");
        }
    }

    // 3) Vektor-Eintraege lesen
    for(int i = 0; i < n; ++i)
    {
        if(!(in >> b[i]))
        {
            throw std::runtime_error("Fehler beim Einlesen des Vektors b.");
        }
    }
}

bool Matrix::checkProcedureApplicable() const
{
    if(n == 0) return false;

    // Einfaches Beispiel: Wir fordern a_{ii} != 0 für alle i
    // (erweiterte Prüfung auf Diagonaldominanz wäre möglich)
    for(int i = 0; i < n; ++i)
    {
        if(std::fabs(getA(i,i)) < 1e-15)
        {
            return false; // a_{ii} = 0 -> Verfahren nicht anwendbar
        }
    }
    return true;
}

std::vector<double> Matrix::solveIteratively(double epsilon,
                                            int maxIterations,
                                            bool &converged) const
{
    // Vorbedingung prüfen
    if(!checkProcedureApplicable())
    {
        throw std::runtime_error(
            "Iteratives Verfahren nicht anwendbar (evtl. a_{ii}=0?).");
    }

    // Startvektor x^(0) = (0,...,0)
    std::vector<double> xOld(n, 0.0);
    std::vector<double> xNew(n, 0.0);

    converged = false;
    for(int k = 0; k < maxIterations; ++k)
    {
        // Jacobi-Update: x_i^(k+1) = [ b_i - Sum_{j != i} a_{ij} * x_j^(k) ] / a_{ii}
        for(int i = 0; i < n; ++i)
        {
            double sum = 0.0;
            for(int j = 0; j < n; ++j)
            {
                if(j != i)
                {
                    sum += getA(i,j) * xOld[j];
                }
            }
            xNew[i] = (b[i] - sum) / getA(i,i);
        }

        // Abbruchkriterium: ||xNew - xOld|| < epsilon?
        double normDiff = 0.0;
        for(int i = 0; i < n; ++i)
        {
            double diff = xNew[i] - xOld[i];
            normDiff += diff * diff;
        }
        normDiff = std::sqrt(normDiff);

        if(normDiff < epsilon)
        {
            converged = true;
            return xNew;
        }

        // Vorbereitung nächste Iteration: xOld := xNew
        xOld = xNew;
    }

    // Falls maxIterations erreicht, hier zurück
    return xNew;
}

bool Matrix::checkSolution(const std::vector<double> &x, double tolerance) const
{
    if(x.size() != static_cast<size_t>(n)) return false;

    // Wir berechnen A*x und vergleichen mit b
    double normDiff = 0.0;
    for(int i = 0; i < n; ++i)
    {
        // Zeile i von A auf x anwenden:
        double Ax_i = 0.0;
        for(int j = 0; j < n; ++j)
        {
            Ax_i += getA(i,j) * x[j];
        }
        double diff = Ax_i - b[i];
        normDiff += diff * diff;
    }
    normDiff = std::sqrt(normDiff);

    return (normDiff < tolerance);
}
