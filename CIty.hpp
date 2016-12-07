#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <fstream>
#include <string.h>
#include <limits.h>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

class City
{
public:
    City(string, long double, long double);
    City();
    string name;
    long double lat;
    long double lon;
    
protected:
    
private:
};

#endif // CITY_H
