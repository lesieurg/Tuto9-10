#include "City.hpp"
using namespace std;
City::City(string name, long double lat, long double lon)
{
    this->name=name;
    this->lat=lat;
    this->lon=lon;
}
City::City()
{
    name="NONE";
    lat=0;
    lon=0;
}
