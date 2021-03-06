#include "stdafx.h"
#include <cstdio>
#include <iostream>
#pragma once
#include <string>
using namespace std;

class Circle {
private:
	double radius;
	double pi = 3.14159;
public:
	Circle();
	Circle(double r);

	void setRadius(double r);
	double getRadius();
	double getArea();
	double getDiameter();
	double getCircumference();

};

Circle::Circle() {
	radius = 0.0;
}

Circle::Circle(double r) {
	radius = r;
}

void Circle::setRadius(double r) {
	radius = r;
}

double Circle::getRadius() {
	return radius;
}

double Circle::getArea() {
	return pi * radius * radius;
}

double Circle::getDiameter() {
	return radius * 2;
}

double Circle::getCircumference() {
	return 2 * pi * radius;
}

int main()
{
	double radius;
	cout << "Please enter a radius" << endl;
	cin >> radius;

	Circle circ(radius);
	cout << "Area: " << circ.getArea() << endl;
	cout << "Diameter: " << circ.getDiameter() << endl;
	cout << "Circumference: " << circ.getCircumference() << endl;
    return 0;
}

