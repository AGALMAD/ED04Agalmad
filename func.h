/*
    Autor : Alejandro Gálvez Madueño
    Fecha : 16/03/2024
    Versión : 1.0
    Nombre del programa : Proyecto Final C
    Descripción :  Prototipos de las funciones necesarias
*/


/******** LIBRERIAS NECESARIAS ********** */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<string.h>


#ifndef _PROCFINAL_
#define _PROCFINAL_


/************ CONSTANTES NECESARIAS *************/

#define MIN 1
#define MAX 20 // Tamaño máximo de alumnos

#define NUMNODOS 3 // Ultimos vehiculos que va a recuperar del fichero binario

#define TAM_NOMBRE 20 // Tamaño del nombre del fichero de texto

#define MAXCADENA 50 // Maximo para la cadena de datos del fichero

#define DELIMITER ":" // Delimitador del strtok

/********* ESTRUCTURAS***********/

/* Carga para cada vehiculo*/
enum carga { LIGERA, MEDIA, PESADA, DESCONOCIDA }; 

typedef enum carga Tcarga;

/* Estructura que tiene cada vehiculo*/
struct vehiculo
{
    int idVehiculo;
    char marcaModelo[50];
    float kms;
    Tcarga carga;
    int potencia;
    
};

typedef struct vehiculo Tvehiculo;

/* Nodo en el que se almacena la lista de todos los vehiculos con un maximo de vehiculos a introducir*/
struct nodoVehiculo
{
    Tvehiculo vehiculo;
    struct nodoVehiculo *sig;

};

typedef struct nodoVehiculo Tnodo;


/*********** PROTOTIPOS ************/

void menu(); // MENU
void creaLista(Tnodo **lista); // Inicialización de la lista

/* 1. Pide los datos del vehiculo que se va a introducir y lo inserta ordenado en la lista*/
int introduceVehiculo(Tnodo **lista);

/* Dice si la lista está llena o no*/
int llena(Tnodo *lista);

/* 2. Elimina un vehiculo por su ID*/
int bajaVehiculo(Tnodo **lista, int id);

/* 3. Aumenta el kilometraje de un vehiculo, pasandole el id y el aumento*/
int aumentaKilometraje(Tnodo *lista, int id, float aumento);

/* 4. Muestra todos los vehiculos*/
int mostrarVehiculos(Tnodo *lista);

/* 5. Muestra los vehiculos que tienen una potencia mayor a la que se le pasa por teclado*/
int mostrarPotenciaMayor(Tnodo *lista, int potencia);

/* 6. Vuelca los datos de la lista a fichero de texto*/
int  copiaSeguridadFichero(Tnodo *lista, char *fichero);

/* 7. Realiza un volcado de los datos del fichero a la lista de los vehiculos*/
int restaurarDesdeFichero(Tnodo **lista, char *fichero);

/* 8. Vuelca los datos de la lista a fichero Binario*/
int  copiaSeguridadBinario(Tnodo *lista, char *fichero);

/* 9. Realiza un volcado de los datos del fichero Binario a la lista de los vehiculos*/
int restaurarBinario(Tnodo **lista, char *fichero);

/* 10. Recupera los datos del número de vehiculos que se introduzca empezando por el final*/
int  recuperaUltimosVehiculos(Tnodo **lista, char *nombreFichero, int nVehiculos);

/* 11. Elimina toda la lista nodo a nodo*/
void eliminaLista( Tnodo **lista);


#endif