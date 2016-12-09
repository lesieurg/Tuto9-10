//
//  main.cpp
//  Tuto9-10
//
//  Created by Guillaume Lesieur on 02/12/2016.
//  Copyright © 2016 Guillaume Lesieur. All rights reserved.
//
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
#include <cmath>
#include "City.h"

#ifdef NAN
#endif
#ifdef INFINITY
#endif
using namespace std;

//
//typedef struct City
//{
//    string name;
//    long double lon;
//    long double lat;
//} City;



bool readFile(City tab[]){
    string fullString;
    string name;
    string val1, val2;
    double lon, lat;
    bool firstLine = true;
    int i = 0;

    cout << "Reading the file..." << endl;
    ifstream file("Cites.csv", ios::in); // a changer chez vous pour tester
    if (file.is_open())
    {

        while (getline(file, fullString))
        {
            if (!firstLine){
                cout << "New line : " << fullString << endl;

                string s = fullString;
                string delimiter = ",";

                size_t pos = 0;
                string token;

                // Get the name
                pos = s.find(delimiter);
                name = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());

                //Get the latitude
                pos = s.find(delimiter);
                val2 = s.substr(0, pos);

                stringstream myStream2(val2);// This code converts from string to number safely.
                if (myStream2 >> lat){
                    lat = atof(val2.c_str());
                    s.erase(0, pos + delimiter.length());
                }
                else{
                    cout << "ERROR, INVALID DATA !" << endl;
                    return 1;
                }

                //Get the longitude
                pos = s.find(delimiter);
                val1 = s.substr(0, pos);

                stringstream myStream(val1);// This code converts from string to number safely.
                if (myStream >> lon)
                {
                    s.erase(0, pos + delimiter.length());
                }
                else
                {
                    cout << "ERROR, INVALID DATA !" << endl;
                    return false;
                }

                cout << std::setprecision(17) << "New data : " << name << " | " << lat << " | " << lon << endl;
                cout << endl;

                City city;
                city.lat = lat;
                city.lon = lon;
                city.name = name;
                tab[i] = city;

                i++;

            }
            firstLine = false;
        }
        file.close();    }
    else cout << "Unable to open file";




    return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////


long double calculDistance(long double lat1, long double lon1, long double lat2, long double lon2){
    long double dist;
    //conversion des coordonnées en radian
    long double latA=(M_PI*lat1)/180;
    long double lonA=(M_PI*lon1)/180;
    long double latB=(M_PI*lat2)/180;
    long double lonB=(M_PI*lon2)/180;
    //calcul de la distance
    dist=60*acos(sin(latA)*sin(latB)+cos(latA)*cos(latB)*cos(lonA-lonB));
    dist = 1.1515 * dist * 180/M_PI;
    dist = dist * 1.609344;
    return dist;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void convert_in_graph(City tab[]){
    int i,j;
    City city1, city2;
    int numberCities=71;
    long double matrix[numberCities][numberCities];
    int dist;

    // Fill the distance with INFINITY
    for(i=0; i<numberCities; i++){
        for (j=0; j<numberCities; j++)
        {
            matrix[i][j] = INFINITY;
        }
    }

    for(i=0; i<numberCities; i++){
      for (j=0; j<numberCities; j++) {
          city1 = tab[i];
          city2 = tab[j];
          dist = calculDistance(city1.lat, city1.lon, city2.lat, city2.lon);

          if (i==j){
              dist= 0;
          }
          cout << city1.name << " to " << city2.name << " : " << dist << endl;
          //if (dist>100) matrix[i][j]=dist;
      }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Lin-Kernighan heuristic
//Choisir une ville A de départ et la suivante S(A)
//Choisir une ville B et la suivante S(B)
//Si le coût pour aller de A à B + S(A) à S(B) est inférieur au coût de A à S(A) + B à S(B), échanger ces solutions (faire ça pour tous les chemins possibles)


////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, const char * argv[]) {
    //on ouvre le fichier en lecture
    ifstream fichier("Cites.csv", ios::in);
    if(fichier){
        if (fichier){
            string ligne;
            cout << "Lecture de fichier : "<< endl;
            //while(getline(fichier, ligne)){
                //cout << ligne << endl;  // on l'affiche
            //}
        }
        City cities[71];
        readFile(cities);
        convert_in_graph(cities);
        fichier.close();  // on ferme le fichier
    }
    else
        cout << "Impossible d'ouvrir le fichier !" << endl;

    return 0;
}



