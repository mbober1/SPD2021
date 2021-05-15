
#include "RandomNumberGenerator.h"
#include "scheduling.hpp"
#include <chrono>
#include <iostream>
#include <math.h>

typedef std::vector<Job*> (*fun)(std::vector<Job*>);

/**
 * Generuje dane.
 *
 * @param n Ilość zadań.
 * @param m Ilość maszyn.
 * @return Zwraca nieuporządkowane zadania.
 */
std::vector<Job*> generateOperations(const int &n, const int &m, const int &seed) {
    RandomNumberGenerator randf(seed);
    std::vector<Job*> J;
    int dupa[] = {1,9,2,9,6,6,4,5,8,9,4,6,8,9,2};
    int d = 0;

    for(int j = 1; j <= n; ++j) {
        Job* tmp = new Job();
        for(int i = 1; i <= m; ++i) {
            randf.nextInt(1, floor(m* 1.2));
            tmp->addOperation(Operation(j, dupa[d++]));
        }
        J.push_back(tmp);
    }
    return J;
}



/**
 * Wypisywanie raportu.
 *
 * @param name Nazwa zadania.
 * @param pi Wektor z uporządkowanymi zadaniami.
 */
void log(const char* name, const std::vector<Job*> &pi) {
    printf("%s\npi: [", name);

    for(int i = 0; i < pi.size(); ++i) {
        printf("%3d", pi[i]->op[0].number);
        if(i != pi.size() - 1) printf(", ");
    }
    printf("]\n");
    printf("Cmax %d \n", Cemaks(pi));
    printf("\n\n");
}


int main() {
    int seed = 752;
    int n = 5;
    int m = 3;

    printf("seed: %d\nrozmiar: %dx%d\n\n", seed, n, m);
    std::vector<Job*> J = generateOperations(n, m, seed);

    log("Naturalna", J);
    log("Jonson", Jonson(J));
    log("NEH", NEH(J));

    std::vector<Operation> path = CriticalPath(NEH(J));

    // log("BruteForce", BruteForce(J));
    // log("BnB", initBranchAndBound(J));

    return 0;
}

