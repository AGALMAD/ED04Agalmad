/*
    Autor : Alejandro Gálvez Madueño
    Fecha : 16/03/2024
    Versión : 1.0
    Nombre del programa : Proyecto Final C
    Descripción :   Programa con menú de 12 opciones para la administración de una 
                    flota de camiones de una empresa
*/


#include "func.h"


/* Programa principal*/
int main(){

    srand(time(NULL));

    int opcion = 0; // Variable para elegir una opción
    int errores = 0; // Para la lectura de los errores
    int id = 0; // Para pedir el id
    int potencia = 0; // Para la potencia que se pide
    float aumento = 0.0; // Para el aumento de kilometros

    char nombreFichero[TAM_NOMBRE]; // Nombre del fichero que se va a utilizar

    Tnodo *listaVehiculos; /* Lista donde se introducen todos los vehiculos*/

    /*Inicializa la lista*/
    creaLista(&listaVehiculos); 

    /* Muestra el menu hasta que introduce el número 12*/    
    while (opcion != 12)
    {
        menu();
        printf("\n\nOpcion: ");
        scanf("%d",&opcion);
        errores = 0; 

        switch (opcion) {
            case 1: // Inserta un vehiculo en una lista ordenada
                errores = introduceVehiculo(&listaVehiculos);

                if (errores)
                    printf("\nLa lista está llena, no se pueden introducir vehiculos");

                break;

            case 2: // Da de baja a un vehiculo, pide ID
                printf("\nID del vehiculo a eliminar : ");
                scanf("%d",&id);
                errores = bajaVehiculo(&listaVehiculos,id);
                /* Se imprimen los errores*/
                if (errores == 1)
                    printf("\nLa lista esta vacia, NO se pueden eliminar vehiculos");
                else if (errores == 2)
                    printf("\nNo existe el id %d",id);
                
                break;
            case 3: // Aumenta los kilometros de un vehiculo
                    // Pide id y kilometros que se van a aumentar
                printf("\nID del vehiculo al que se le quiere incrementar los Kilomentros : ");
                scanf("%d",&id);
                do
                {
                    /* Pide los kilometros que se van aumentar hasta que introduzca un número positivo*/
                    printf("\nKilometros a aumentar : ");
                    scanf("%f",&aumento);
                } while (aumento <= 0);

                errores = aumentaKilometraje(listaVehiculos, id ,aumento);
                /* Se imprimen los errores*/
                if (errores == 1)
                    printf("\nLa lista esta vacia");
                else if (errores == 2)
                    printf("\nNo existe el id %d",id);
                else
                    printf("\nKilomentros aumentados correctamente");
            
                break;

            case 4: //Muestra todos los vehiculos de la lista
                errores = mostrarVehiculos(listaVehiculos);
                break;

            case 5: //Muestra los vehiculos que tengan una potencia mayor a la pasada por teclado
                /* Pide la potencia hasta que se introduzca una potencia positiva*/
                do
                {
                    printf("\nPotencia : ");
                    scanf("%d",&potencia);
                } while (potencia <= 0);
                errores = mostrarPotenciaMayor(listaVehiculos, potencia); 

                break;

            case 6: //Volcar los datos de la lista a un fichero que se pide por teclado
                /* Pide el nombre del fichero*/
                printf("\nFichero de texto en el que se van a volvar los datos : ");
                while (getchar() != '\n'); // Limpia el buffer
                gets(nombreFichero);
                errores = copiaSeguridadFichero(listaVehiculos, nombreFichero);

                if (errores == 1)
                    printf("\nLa lista esta vacia, no se puede realizar la copia de seguridad :(");
                else if (errores == 2)
                    printf("Error al abrir el archivo.\n");
                else
                    printf("\nCopia de seguridad terminada con exito :)");
                
                break;
            case 7:
                /* Pide el nombre del fichero*/
                printf("\nFichero de texto desde el que se van a volcar los datos : ");
                while (getchar() != '\n'); // Limpia el buffer
                gets(nombreFichero);

                errores = restaurarDesdeFichero(&listaVehiculos, nombreFichero);

                if (errores)
                    printf("Error al abrir el archivo.\n");
                else
                    printf("\nLista restaurada con exito :)");

                break;
            case 8:
                /* Pide el nombre del fichero*/
                printf("\nFichero Binario en el que se van a volvar los datos : ");
                while (getchar() != '\n'); // Limpia el buffer
                gets(nombreFichero);

                errores = copiaSeguridadBinario(listaVehiculos, nombreFichero);
                if (errores == 1)
                    printf("\nLa lista esta vacia, no se puede realizar la copia de seguridad :(");
                else if (errores == 2)
                    printf("Error al abrir el archivo.\n");
                else
                    printf("\nCopia de seguridad en Fichero Binario terminada con exito :)");

                break;
            case 9:
                /* Pide el nombre del fichero*/
                printf("\nFichero Binario desde el que se va a restaurar los datos : ");
                while (getchar() != '\n'); // Limpia el buffer
                gets(nombreFichero);

                errores = restaurarBinario(&listaVehiculos, nombreFichero);
                if (errores)
                    printf("Error al abrir el archivo.\n");
                else
                    printf("\nLista restaurada con exito :)");

                break;
            case 10:
                /* Pide el nombre del fichero*/
                printf("\nFichero Binario desde el que se va a restaurar los datos : ");
                while (getchar() != '\n'); // Limpia el buffer
                gets(nombreFichero);

                errores =  recuperaUltimosVehiculos(&listaVehiculos,nombreFichero,NUMNODOS);
                if (errores)
                    printf("Error al abrir el archivo.\n");
                else
                    printf("\nLista restaurada con exito :)");

                break;
            case 11: // Elimina la lista completa nodo a nodo
                eliminaLista(&listaVehiculos);
                break;
            case 12: // Sale del programa
                break;
            default:
                printf("Opcion no valida. Ingresa un numero del 1 al 12.\n");
                break;
        }

    }
    
    /* Libera la memoria cuando ha terminado el programa*/
    eliminaLista(&listaVehiculos);
    printf("\nFIN DEL PROGRAMA ");

    return 0;
}
