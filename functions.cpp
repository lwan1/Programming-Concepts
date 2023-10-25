//
// Created by wanle on 4/25/2021.
//

#include "functions.h"

using namespace std;


// take the file stream and read in numbers to a vector
vector<double> readNumbersFromFile(ifstream &inputFile) {
    vector<double> allNums;
    double n;
    while (inputFile >> n) {
        allNums.push_back(n);
    }
    return allNums;
}

vector<vector<double>> calcDesignMatrix(vector<double> &allNums) {
    vector<vector<double>> matrix;
    for (int i = 0; i < allNums.size()/2; i++) {
        vector<double> v;
        for (int j = 0; j < 2; j++) {
            v.push_back(1);
        }
        matrix.push_back(v);
    }
    int x = 0;
    for (int i = 0; i < allNums.size()/2; i++) {
        matrix.at(i).at(1) = allNums.at(x);
        x += 2;
    }
    return matrix;
}

vector<double> setObservationVector(vector<double> &allNums) {
    vector<double> vect;
    int y = 1;
    for (int i = 0; i < allNums.size()/2; i++) {
        vect.push_back(allNums.at(y));
        y += 2;
    }
    return vect;
}

vector<vector<double>> createTranspose(vector<vector<double>> &xMatrix, const int nRows) {
    vector<vector<double>> transpose;
    vector<double> v;
    int x = 1;
    for (int i = 0; i < nRows; i++) {
        v.push_back(1);
    }
    transpose.push_back(v);
    v.clear();
    for (int i = 0; i < nRows; i++) {
        v.push_back(xMatrix.at(i).at(x));
    }
    transpose.push_back(v);
    return transpose;
}

vector<vector<double>> computeTransposeTimesX(vector<vector<double>> &transpose, vector<vector<double>> &xMatrix, const int nRows) {
    vector<vector<double>> matrix;
    vector<double> v;
    int i = 0;
    double sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(0).at(i) * xMatrix.at(i).at(0);
    }
    v.push_back(sum);
    sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(0).at(i) * xMatrix.at(i).at(1);
    }
    v.push_back(sum);
    matrix.push_back(v);
    v.clear();
    sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(1).at(i) * xMatrix.at(i).at(0);
    }
    v.push_back(sum);
    sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(1).at(i) * xMatrix.at(i).at(1);
    }
    v.push_back(sum);
    matrix.push_back(v);
    return matrix;
}

vector<double> computeTransposeTimesObs(vector<vector<double>> &transpose, vector<double> &obsVect, const int nRows) {
    vector<double> vect;
    int i = 0;
    double sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(0).at(i) * obsVect.at(i);
    }
    vect.push_back(sum);
    sum = 0;
    for (i = 0; i < nRows; i++) {
        sum += transpose.at(1).at(i) * obsVect.at(i);
    }
    vect.push_back(sum);
    return vect;
}

const double computeDet(vector<vector<double>> &transposeTimesX) {
    const double det = (transposeTimesX.at(0).at(0) * transposeTimesX.at(1).at(1)) -(transposeTimesX.at(0).at(1) * transposeTimesX.at(1).at(0));
    return det;
}

vector<vector<double>> createPartOfInverse(vector<vector<double>> &transposeTimesX) {
    vector<vector<double>> matrix;
    vector<double> v;
    v.push_back(transposeTimesX.at(1).at(1));
    v.push_back(-1 * transposeTimesX.at(0).at(1));
    matrix.push_back(v);
    v.clear();
    v.push_back(-1 * transposeTimesX.at(1).at(0));
    v.push_back(transposeTimesX.at(0).at(0));
    matrix.push_back(v);
    return matrix;
}

vector<double> computePartOfInverseTimesATransposeObs(vector<vector<double>> &inversePortion, vector<double> &aTransposeObs) {
    vector<double> vect;
    double sum = 0;
    for (int i = 0; i < 2; i++) {
        sum += inversePortion.at(0).at(i) * aTransposeObs.at(i);
    }
    vect.push_back(sum);
    sum = 0;
    for (int i = 0; i < 2; i++) {
        sum += inversePortion.at(1).at(i) * aTransposeObs.at(i);
    }
    vect.push_back(sum);
    return vect;
}

vector<double> computeFinal(const double det, vector<double> &preludeToFinal) {
    vector<double> vect;
    double calc;
    calc = (1 / det) * preludeToFinal.at(0);
    vect.push_back(calc);
    calc = (1 / det) * preludeToFinal.at(1);
    vect.push_back(calc);
    return vect;
}


