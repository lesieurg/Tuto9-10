
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
//#include "City.h" uncomment if there is an error
#include "City.hpp"
#define MAX 71


#ifdef NAN
#endif
#ifdef INFINITY
#endif
using namespace std;

bool readFile(City tab[], string filename){
    string fullString;
    string name;
    string val1, val2;
    double lon, lat;
    bool firstLine = true;
    int i = 0;
    
    cout << "Reading the file..." << endl;
    ifstream file(filename, ios::in);
    if (file.is_open()){
        while (getline(file, fullString)){
            if (!firstLine){
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
                if (myStream >> lon){
                    s.erase(0, pos + delimiter.length());
                }
                else{
                    cout << "ERROR, INVALID DATA !" << endl;
                    return false;
                }
                
                cout << std::setprecision(17) << name << " | " << lat << " | " << lon << endl;
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
        file.close();
    }
    else cout << "Unable to open file";
    
    return true;
    
}

// Fill the distance with 999999
void fill_distance(City tab[], long double matrix[MAX][MAX]){
    int i,j;
    for(i=0; i<MAX; i++){
        for (j=0; j<MAX; j++){
            matrix[i][j] = 999999;
        }
    }
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

void convert_in_graph(City tab[], long double matrix[MAX][MAX]){
    int i,j;
    City city1, city2;
    int numberCities=71;
    int dist;
    
    fill_distance(tab, matrix);
    for(i=0; i<numberCities; i++){
        for (j=0; j<numberCities; j++) {
            city1 = tab[i];
            city2 = tab[j];
            dist = calculDistance(city1.lat, city1.lon, city2.lat, city2.lon);
            
            if (i==j){
                dist= 0;
            }
            cout << city1.name << " to " << city2.name << " : " << dist << endl;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isCityExists(City tab[], string name){
    int i,j=0;
    City city2;
    long double matrix[MAX][MAX];
    int dist;
    
    fill_distance(tab, matrix);
    for(j=0; j<MAX; j++){
        city2 = tab[j];
        if (i==j) dist= 0;
        if (!name.compare(city2.name)){ // true
            return true;
        }
    }
    return false;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////

long double getLat(City tab[], string name){
    int i,j;
    City city1, city2;
    int numberCities=71;
    long double matrix[MAX][MAX];
    int dist;
    long double lat=0;
    
    fill_distance(tab, matrix);
    for(i=0; i<numberCities; i++){
        for (j=0; j<numberCities; j++) {
            city2 = tab[j];
            if (i==j){
                dist= 0;
            }
            if (!name.compare(city2.name)){ // true
                lat = city2.lat;
            }
        }
    }
    return lat;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

long double getLong(City tab[], string name){
    int i,j;
    City city1, city2;
    int numberCities=71;
    long double matrix[MAX][MAX];
    int dist;
    long double lon=0;
    
    fill_distance(tab, matrix);
    for(i=0; i<MAX; i++){
        for (j=0; j<MAX; j++) {
            city2 = tab[j];
            
            if (i==j){
                dist= 0;
            }
            if (!name.compare(city2.name)){ // true
                lon = city2.lon;
            }
        }
    }
    return lon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_lat(City city){
    return city.lat;
}

int get_lon(City city){
    return city.lon;
}

string get_name(City city){
    return city.name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// return the distance for a city input
int dist(City tab[], string name){
    
    int dist = 0;
    
    if (isCityExists(tab, name)){
        //dist = getDist(tab,name);
    }
    else cout << "This city doesn't exist " << endl;
    
    return dist;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//Lin-Kernighan heuristic
//Choisir une ville A de départ et la suivante S(A)
//Choisir une ville B et la suivante S(B)
//Si le coût pour aller de A à B + S(A) à S(B) est inférieur au coût de A à S(A) + B à S(B), échanger ces solutions (faire ça pour tous les chemins possibles)

int searchNumberByName(string cityName, City tab[]){
    int res=-1;
    for (int i=0; i<MAX; i++){
        if (cityName==tab[i].name) {
            res = i;
        }
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

long double sum(int lap[], long double matrix[MAX][MAX]){
    long double sum = 0;
    for (int i=0; i<MAX-1; i++)
    {
        sum += matrix[lap[i]][lap[i+1]];
    }
    sum += matrix[lap[MAX-1]][lap[0]];
    return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void twoOpt(City tab[], long double matrix[MAX][MAX], int city_numb){
    int lap[MAX];
    int degOpti = 20;
    int cmpt = 0;
    int city = city_numb;
    // Création d'un tour primaire
    for (int i=0; i<MAX; i++){
        lap[i] = i;
    }
    
    // On place la premiere ville en premiere place dans la liste lap
    lap[city_numb] = 0;
    lap[0] = city_numb;
    
    int bestDist;
    while (cmpt<degOpti){
        for (int i=1; i<MAX; i++) {
            for (int j=i; j<MAX; j++){
                bestDist = sum(lap, matrix);
                if ((i!=city_numb || j!=city_numb) && matrix[lap[i]][lap[j]]!=INFINITY){
                    int temp = lap[i];
                    lap[i] = lap[j];
                    lap[j] = temp;
                }
                int newDist = sum(lap, matrix);
                if (newDist>bestDist && newDist != INFINITY){
                    int temp = lap[i];
                    lap[i] = lap[j];
                    lap[j] = temp;
                }
            }
        }
        cmpt++;
    }
    long double sum=0;
    for (int i=0; i<MAX-1; i++){
        cout << tab[lap[i]].name << " - " << tab[lap[i+1]].name << " => " << matrix[lap[i]][lap[i+1]] << endl;
        sum += matrix[lap[i]][lap[i+1]];
    }
    
    cout << "the total distance is " << sum << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, const char * argv[]) {
    //on ouvre le fichier en lecture
    string filename = "/Users/guillaumelesieur/Downloads/city.txt";
    //string filename = ifstream("Cites.csv"); // a changer chez vous pour tester
    
    City cities[MAX];
    long double matrix[MAX][MAX];
    if (readFile(cities, filename)){
        cout << "------------------------------" << endl;
        convert_in_graph(cities,matrix);
    }
    else cout << "ERROR " << endl;
    
    cout << "------------------------------" << endl;
    cout << "Test with MARSEILLE" << endl;
    cout << "latitude = " << getLat(cities, "MARSEILLE") << " longitude  = " <<  getLong(cities, "MARSEILLE") << endl;
    //cout << "distance from Paris = " << getDist(cities, "MARSEILLE") << endl;
    
    string city_name;
    int city_int=- 1;
    
    cout << "------------------------------" << endl;
    cout << "Enter a city name : " << endl;
    cin >> city_name;
    if (isCityExists(cities, city_name)){
        city_int = searchNumberByName(city_name, cities);
        if (city_int!=-1){
            cout << city_int <<  endl;
        }
        twoOpt(cities, matrix, city_int);
    }
    else cout << "Invalid city name" << endl;
    
    return 0;
}
