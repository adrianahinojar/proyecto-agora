#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "geo.c"
#include "geo.h"

#define DIM 200
#define NPARAMETROS 12
#define DIM2 60
#define DIM3 16500
#define DIM4 20
#define DIM5 10
#define U_LINEA 1257
#define CERO "0"
#define UNO "1"
#define DOS "2"
#define TRES "3"
#define ENCONTRADO 0
#define ACCESO "2"
#define ESTACION "1"
#define MINUSVALIDO "1\n"

typedef struct{
    char stop_id[DIM];
    char stop_code[DIM];
    char stop_name[DIM];
    char stop_desc[DIM];
    char stop_lat[DIM];
    char stop_lon[DIM];
    char zone_id[DIM];
    char stop_url[DIM];
    char location_type[DIM];
    char parent_station[DIM];
    char stop_timezone[DIM];
    char wheelchair_boarding[DIM];
} tRegistro;
tRegistro fichero[DIM3];

void almacenarDatosFichero();
int main() {

    char cadena[DIM5];
    int opcion;

    do{  printf("\n");
        printf("-------------------------------AGORA-------------------------------------\n");
        printf("\t1 - Determinar el acceso de metro mas cercano a una ubicacion\n\t2 - Mostrar los accesos de una estacion de metro\n\t3 - Generar un fichero con los accesos de metro accesibles\n\n\t0 - Terminar\n");
    printf("-------------------------------------------------------------------------\n");

    do{
        printf("Pulse una opcion:\n"); //repetir en caso de que no se introduzca un 0,1,2 o 3
        gets(cadena);
    }while((strcmp(cadena,CERO) != ENCONTRADO) && (strcmp(cadena,UNO) != ENCONTRADO) && (strcmp(cadena,DOS) != ENCONTRADO) && (strcmp(cadena,TRES) != ENCONTRADO));

    opcion= atoi(cadena); //string a entero para el switch

        almacenarDatosFichero();//llamamiento

  switch(opcion){

      case 1:{
          //printf("%s\n",fichero[0].stop_id);//la posicion O es la segunda línea del fichero
          //printf("%s\n",fichero[1257].stop_id);//la posicion 1257 es la ultima linea del fichero, nos sirve para poder hacer bucles (for)

           float latA, longA,latB, longB;

          printf("Introduce una latitud:\n");
          scanf("%f",&latA);
          printf("Introduce una longitud:\n");
          scanf("%f",&longA);

          int i, parada;
          float distancia, minima=DIM3;
          char estacion[DIM4]="";


          for(i=0; i<=U_LINEA; i++){

              if(strcmp(fichero[i].location_type,ACCESO) == ENCONTRADO){ //Comparar entre solo los accesos

                  latB = strtof(fichero[i].stop_lat,NULL); //Pasar de string a float
                  longB = strtof(fichero[i].stop_lon,NULL);

                  distancia = distanciaGeografica(latA, longA, latB, longB);//LLamamiento

                  if(distancia<minima){
                      minima=distancia;
                      parada=i;
                  }

              }
          }
          for(i=0; i<=U_LINEA; i++){
              if(strcmp(fichero[parada].parent_station,fichero[i].stop_id) == ENCONTRADO){ //Para saber cual es su estación
                  strcpy(estacion,fichero[i].stop_name);
          }
              }

              printf("\n>Estacion: %s\n\t>Acceso mas cercano: %s\n\t>Latitud %s ; Longitud %s",estacion,fichero[parada].stop_name,fichero[parada].stop_lat,fichero[parada].stop_lon);
              printf("\n");
          gets(cadena);//necesario para evitar que en el bucle de "Pulse una opcion" se repita una vez mas el bucle debido al valor residual del salto de linea que dejan los scanf
          break;
      }

      case 2:{
          int i;
          char estacion[DIM2]="";
          char codigo[DIM4]="";

          for(i=0; i<=U_LINEA; i++){
              if(strcmp(fichero[i].location_type,ESTACION) == ENCONTRADO){ //Imprimir los nombres de solo las estaciones
                  printf("%s\n",fichero[i].stop_name);}
          }

          printf("\n");
          printf("Escribe la estacion de la que se piden los accesos al METRO:\n");

          gets(estacion);//guardar estacion metida por teclado

          printf(">Accesos de la estacion %s: \n",estacion);


              i=0;

              while(((strcmp(fichero[i].stop_name,estacion)!= ENCONTRADO) && (i<=U_LINEA)) || (strcmp(fichero[i].location_type,ESTACION) != ENCONTRADO)) {//hasta encontrar la estacion escrita por teclado
                  i++;
              }

                  strcpy(codigo,fichero[i].stop_id);//guardar id de esa estacion
                  for(int j=0;j<=U_LINEA;j++){
                      if((strcmp(fichero[j].parent_station,codigo) == ENCONTRADO) && (strcmp(fichero[j].location_type, ACCESO) == ENCONTRADO))//solo accesos de esa estacion
                          printf("\t- %s\n",fichero[j].stop_name);
                  }

          printf("\n");
          break;
      }

      case 3:{
          FILE *pFile2;
          int j;
          if((pFile2=fopen("output.txt","w")) != NULL){ //crear fichero
              for(j=0;j<=U_LINEA;j++){
                  if((strcmp(fichero[j].location_type,ACCESO) == ENCONTRADO)&&(strcmp(fichero[j].wheelchair_boarding,MINUSVALIDO) == ENCONTRADO)){ //solo accesos para minusvalidos
                      fprintf(pFile2,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",fichero[j].stop_id,fichero[j].stop_code,fichero[j].stop_name,fichero[j].stop_desc,fichero[j].stop_lat,fichero[j].stop_lon,fichero[j].zone_id,fichero[j].stop_url,fichero[j].location_type,fichero[j].parent_station,fichero[j].stop_timezone,fichero[j].wheelchair_boarding);//hacer que imprima esa linea de los 12 parámetros
                    }
                  }
              if(fclose(pFile2) != 0){//cerrar fichero
                  printf("Se ha producido un error al cerrar el fichero.\n");
              }
          }
          break;
     }
  }

 }while(opcion !=0);

    return 0;
}

void almacenarDatosFichero() {
    FILE *pFile;
    char linea[DIM] = "";

    if ((pFile = fopen("stops.txt", "r")) == NULL) {// Comprobacion de que se ha abierto el fichero de datos
        printf("No se ha abierto correctamente el fichero.\n");
    }

    fgets(linea, DIM, pFile);//Lee la primera línea de parámetros solamente

    int longitud = 0;
    int longitudaux=0;
    int contador = 0;

    while (fgets(linea, DIM, pFile) != NULL) {


        for (int i=1;i<=NPARAMETROS;i++) {
            char palabra[DIM2] = "";


            switch (i) {//teniendo en cuenta la separacion de las comas guarde cada cadena en una de las secciones
                case 1: {
                    longitud = strcspn(linea, ",");//lee hasta la primera coma
                    strncpy(palabra, linea, longitud);//extrae la palabra de esa longitud
                    strcpy(fichero[contador].stop_id, palabra);//la guarda en el primer parametro
                    break;
                }
                case 2: {

                    longitud += 1;//para que pase la coma
                    longitudaux = strcspn(&linea[longitud], ",");//tenga en cuenta la longitud anterior
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_code, palabra);
                    longitud += longitudaux;

                    break;
                }
                case 3: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_name, palabra);
                    longitud += longitudaux;

                    break;
                }
                case 4: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_desc, palabra);
                    longitud += longitudaux;

                    break;
                }
                case 5: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_lat, palabra);
                    longitud += longitudaux;

                    break;
                }
                case 6: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_lon, palabra);
                    longitud += longitudaux;

                    break;
                }
                case 7:{

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].zone_id, palabra);
                    longitud += longitudaux;

                    break;}
                case 8:{

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_url, palabra);
                    longitud += longitudaux;

                    break;}
                case 9:{

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].location_type, palabra);
                    longitud += longitudaux;

                    break;}
                case 10:{

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].parent_station, palabra);
                    longitud += longitudaux;

                    break;}
                case 11: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].stop_timezone, palabra);
                    longitud += longitudaux;

                    break;}

                case 12: {

                    longitud += 1;
                    longitudaux = strcspn(&linea[longitud], ",");
                    strncpy(palabra, linea + longitud, longitudaux);
                    strcpy(fichero[contador].wheelchair_boarding, palabra);
                    contador++;

                    break;}



            }

        }
    }
    if (fclose(pFile) != 0) { //Comprobacion del cierre del fichero
        printf("Se ha producido un error al cerrar el fichero.\n");
    }
}