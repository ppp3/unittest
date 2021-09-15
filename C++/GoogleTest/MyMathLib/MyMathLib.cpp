// MyMathLib.cpp : Hiermit werden die Funktionen für die statische Bibliothek definiert.
//

#include "pch.h";
#include "framework.h";
#include "MyMathLib.h";
#include <math.h>;
#include <stdexcept>
#include <iostream>

double mySqrt(double x)
{
	if (x < 0)
	{
		throw std::runtime_error("Negative argument");
	}
	std::cout << "Aufruf";
	return sqrt(x);
}
