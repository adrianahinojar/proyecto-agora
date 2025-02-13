//
// Created by ahin on 14/12/2022.
//


#include <math.h>

#define PI 3.14159
#define RADIO_TIERRA 6371 //EN KM
//Definicion
float distanciaGeografica(float latA, float longA, float latB, float longB) {
    float incLat, incLong, incLatRadianes, incLongRadianes;
    float a, c, distancia;

    incLat= latA-latB;
    incLong= longA-longB;

    incLatRadianes = incLat * (PI/180);
    incLongRadianes = incLong * (PI/180);

    a= pow(sin(incLatRadianes/2),2)+cos(latA)* cos(latB)* pow(sin(incLongRadianes/2),2);
    c= 2* pow(atan(sqrt(a)/sqrt(1-a)),2);

    //Distancia en km
    distancia = RADIO_TIERRA*c;

    return distancia;
}
