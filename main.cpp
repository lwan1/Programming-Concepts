/* CSCI 261 Final Project
 *
 * Author: Leon Wan
 *
 * Welcome to Project m.b.
 *
 * --> Using the least-squares solution algorithm to determine a
 *     a line of regression of y on x. In particular, the regression
 *     coefficients are calculated, a.k.a. the parameter vector.             */

#include <iostream>                     // for standard input/output
#include <string>                       // for strings
#include <vector>                       // for vectors
#include <iomanip>                      // for output formatting
#include <sstream>                      // for displaying equation in SFML
using namespace std;                    // using the standard namespace

#include <SFML/Graphics.hpp>            // include the SFML Graphics Library
using namespace sf;                     // using the sf namespace

#include "functions.h"                  // include custom functions
#include "MyPoints.h"                   // include custom class


int main() {

    ifstream inFS;
    inFS.open("points2.txt");
    if (!inFS.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    // read all the numbers in the file
    vector<double> allNums = readNumbersFromFile( inFS );
    inFS.close();
    const int ROW = allNums.size()/2;
    cout << "Read in " << ROW << " points" << endl;
    cout << endl;

    // GOAL: Solve  designMatrix * parameterVector = observationVector
    //          or  X(→β) = →y
    //         for  →β

    // calculate design matrix
    vector<vector<double>> designMatrix = calcDesignMatrix(allNums);

    // extract observation vector from points
    vector<double> obsVector = setObservationVector(allNums);

    // take the transpose of the design matrix
    vector<vector<double>> transposeOfX = createTranspose(designMatrix, ROW);

    // calculate the product of X^T and X
    vector<vector<double>> transposeTimesDesign = computeTransposeTimesX(transposeOfX, designMatrix, ROW);

    // calculate the product of X^T and →y
    vector<double> transposeTimesObs = computeTransposeTimesObs(transposeOfX, obsVector, ROW);

    // calculate the determinant of X^T*X to get the first half of (X^T*X)^-1
    const double determinantOfATransposeA = computeDet(transposeTimesDesign);

    // switch values in X^T*X matrix to get the last half of (X^T*X)^-1
    vector<vector<double>> inverseOfATransposeAPortion = createPartOfInverse(transposeTimesDesign);

    // calculate the vector from the multiplication of (X^T*X)^-1 and (X^T*→y)
    vector<double> preludeFinalVector = computePartOfInverseTimesATransposeObs(inverseOfATransposeAPortion, transposeTimesObs);

    // determine the parameter vector
    vector<double> finale = computeFinal(determinantOfATransposeA, preludeFinalVector);

    cout << setfill('=') << setw(40) << "=" << endl;
    cout << "Your estimated line of regression is:" << endl;
    cout << "y = " << finale.at(1) << "x + " << finale.at(0) << endl;
    cout << setfill('=') << setw(40) << "=" << endl;

    // store line of regression for later use
    ostringstream num1;
    num1 << finale.at(1);
    string m = num1.str();
    ostringstream num2;
    num2 << finale.at(0);
    string b = num2.str();
    string lineEquation = "y = " + m + "x + " +  b;

    // variables for SFML drawing
    const int WIDTH = 840;
    const int HEIGHT = 840;
    vector<MyPoints> unconvertedPtVector;
    vector<MyPoints> convertedPixelVector;
    double xCoord, yCoord;
    int xPixel, yPixel;

    // create a RenderWindow object
    // specify the size to be 840x840
    // set the title to be "SFML Example Window"
    RenderWindow window( VideoMode(840, 840), "SFML Graph" );

    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING BELOW HERE
    //********************************************
    inFS.open("points2.txt");
    if (!inFS.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    //********************************************
    //  PLACE ANY FILE INPUT PROCESSING ABOVE HERE
    //********************************************

    // while our window is open, keep it open
    // this is our draw loop
    while( window.isOpen() ) {
        window.clear( Color::Black );           // clear the contents of the old frame
                                                // by setting the window to black


        //****************************************
        //  ADD ALL OF OUR DRAWING BELOW HERE
        //****************************************

        // draw y-axis
        int y = 0;
        xCoord = 420;
        while (y < 840) {
            yCoord = y;
            unconvertedPtVector.push_back( MyPoints(xCoord, yCoord) );

            CircleShape dot;
            dot.setPosition( Vector2f(unconvertedPtVector.at(0).getX(), unconvertedPtVector.at(0).getY()) );
            dot.setRadius(1);
            dot.setFillColor(Color(246, 131, 112) );
            window.draw(dot);

            unconvertedPtVector.clear();
            y++;
        }

        // draw x-axis
        int x = 0;
        yCoord = 420;
        while (x < 840) {
            xCoord = x;
            unconvertedPtVector.push_back( MyPoints(xCoord, yCoord) );

            CircleShape dot;
            dot.setPosition( Vector2f(unconvertedPtVector.at(0).getX(), unconvertedPtVector.at(0).getY()) );
            dot.setRadius(1);
            dot.setFillColor(Color(246, 131, 112) );
            window.draw(dot);

            unconvertedPtVector.clear();
            x++;
        }

        // draw data from input file (shown as rectangular points)
        while(!inFS.eof()) {
            inFS >> xCoord >> yCoord;
            unconvertedPtVector.push_back( MyPoints(xCoord, yCoord) );

            xPixel = (int)( 2 * unconvertedPtVector.at(0).getX() + ( WIDTH / 2 ) );
            yPixel = (int)( 2 * -unconvertedPtVector.at(0).getY() + ( HEIGHT / 2 ) );
            convertedPixelVector.push_back( MyPoints(xPixel, yPixel) );

            RectangleShape pt;
            pt.setPosition( Vector2f(convertedPixelVector.at(0).getX(), convertedPixelVector.at(0).getY()) );
            pt.setSize( Vector2f( 6, 6) );
            pt.setFillColor(Color(255, 208, 141) );
            window.draw(pt);

            unconvertedPtVector.clear();
            convertedPixelVector.clear();
        }

        // draw calculated line of regression based on points (shown as small circles)
        int i = -840;
        while(i < 840) {
            xCoord = i;
            yCoord = finale.at(1) * xCoord + finale.at(0);
            unconvertedPtVector.push_back( MyPoints(xCoord, yCoord) );

            xPixel = (int)( 2 * unconvertedPtVector.at(0).getX() + ( WIDTH / 2 ) );
            yPixel = (int)( 2 * -unconvertedPtVector.at(0).getY() + ( HEIGHT / 2 ) );
            convertedPixelVector.push_back( MyPoints(xPixel, yPixel) );

            CircleShape dot;
            dot.setPosition( Vector2f(convertedPixelVector.at(0).getX(), convertedPixelVector.at(0).getY()) );
            dot.setRadius(1);
            dot.setFillColor(Color(137, 219, 236) );
            window.draw(dot);

            unconvertedPtVector.clear();
            convertedPixelVector.clear();
            i++;
        }

        // display the equation for the line of regression
        Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error opening file" << endl;
            // don't want the program to crash and burn
            // return -1 is omitted;
        }   else {
            Text text;
            text.setFont(font);
            text.setString(lineEquation);
            text.setCharacterSize(18);
            text.setFillColor(Color::White);
            text.setStyle(Text::Bold);
            window.draw(text);
        }

        // remove the eof flag
        inFS.clear();

        // start reading from the start of the file again
        inFS.seekg(0);

        //****************************************
        //  ADD ALL OF OUR DRAWING ABOVE HERE
        //****************************************

        window.display();                       // display the window

        //****************************************
        // HANDLE EVENTS BELOW HERE
        //****************************************
        Event event;
        while( window.pollEvent(event) ) {       // ask the window if any events occurred
            if( event.type == Event::Closed ) {     // if event type is a closed event
                                                    // i.e. they clicked the X on the window
                inFS.close();                       // close file stream
                window.close();                     // then close our window
            }

        }

    }

    return EXIT_SUCCESS;                        // report our program exited successfully

}

