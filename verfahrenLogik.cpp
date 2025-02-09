#include "matrix.hpp"

bool Matrix::verfahrenAnewendbar() {
    for (int i = 0; i < n; i++) {
        double diag = std::fabs(A[i][i]);
        double sumOffDiag = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                sumOffDiag += std::fabs(A[i][j]);
            }
        }
        if (diag <= sumOffDiag) {
            if (istTestMode) {
                testOutput = "Verfahren ist nicht anwendbar";
            }
            return false;
        }
    }

    if (istTestMode) {
        testOutput = "Verfahren ist anwendbar";
    }

    return true;
}

std::vector<double> Matrix::gleichungssystemLoesen(double epsilonParam, int maxIterParam)
{
    double epsilon = epsilonParam;
    int maxIter = maxIterParam;

    std::vector<double> xAlt(n, 0.0);
    std::vector<double> xNeu(n, 0.0);

    for (int k = 0; k < maxIter; k++) {
        for (int i = 0; i < n; i++) {
            double sigma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sigma += A[i][j] * xAlt[j];
                }
            }
            xNeu[i] = (b[i] - sigma) / A[i][i];
        }

        double diffNorm = 0.0;
        for (int i = 0; i < n; i++) {
            double d = xNeu[i] - xAlt[i];
            diffNorm += d * d;
        }
        diffNorm = std::sqrt(diffNorm);

        xAlt = xNeu;

        if (diffNorm < epsilon) {
            break;
        }
    }

    return xNeu;
}

bool Matrix::loesungValidieren(const std::vector<double>& xPruef)
{
    std::vector<double> r(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * xPruef[j];
        }
        r[i] = sum - b[i];
    }

    double normR = 0.0;
    for (double val : r) {
        normR += val*val;
    }
    normR = std::sqrt(normR);

    double tol = 1e-4;
    return (normR < tol);
}
