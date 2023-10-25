//
// Created by wanle on 5/1/2021.
//

#include "MyPoints.h"

MyPoints::MyPoints() {
    _x = 1;
    _y = 1;
}

MyPoints::MyPoints(double x, double y) {
    _x = x;
    _y = y;
}

double MyPoints::getX() {
    return _x;
}

double MyPoints::getY() {
    return _y;
}
void MyPoints::setPoint(double x, double y) {
    _x = x;
    _y = y;
}