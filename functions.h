//
// Created by wanle on 4/25/2021.
//

#ifndef FINALPROJECT_FUNCTIONS_H
#define FINALPROJECT_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


vector<double> readNumbersFromFile(ifstream &inputFile);

vector<vector<double>> calcDesignMatrix(vector<double> &allNums);

vector<double> setObservationVector(vector<double> &allNums);

vector<vector<double>> createTranspose(vector<vector<double>> &xMatrix, const int nRows);

vector<vector<double>> computeTransposeTimesX(vector<vector<double>> &transpose, vector<vector<double>> &xMatrix, const int nRows);

vector<double> computeTransposeTimesObs(vector<vector<double>> &transpose, vector<double> &obsVect, const int nRows);

const double computeDet(vector<vector<double>> &transposeTimesX);

vector<vector<double>> createPartOfInverse(vector<vector<double>> &transposeTimesX);

vector<double> computePartOfInverseTimesATransposeObs(vector<vector<double>> &inversePortion, vector<double> &aTransposeObs);

vector<double> computeFinal(const double det, vector<double> &preludeToFinal);

#endif //FINALPROJECT_FUNCTIONS_H
