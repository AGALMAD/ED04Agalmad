/*
    Autor : Alejandro Gálvez Madueño
    Fecha : 16/03/2024
    Versión : 1.0
    Nombre del programa : Proyecto Final C
    Descripción :  Funciones necesarias para el correcto funcionamiento del programa
*/

#include "func.h"

int funcMejora1(){

    return 0;
}




/********* FUNCIONES INTERNAS ********/

/* Devuelve el tamaño que tiene la lista*/
int tamanoLista(Tnodo *lista){

    int l = 0;

    while (lista != NULL)
    {
        l++;
        lista = lista->sig; //pasa al siguiente elemento
    }

    return l;
}


/* Dice si la lista está llena o no*/
int llena(Tnodo *lista){

    int l = 0;

    l = tamanoLista(lista);

    /* Si se encuentran todos los elementos, la lista está llena */
    if (l == MAX)
    {
        return 1;
    }
    
    return 0;
}

/* Dice si la lista está vacia o no*/
int vacia(Tnodo *lista){
    
    if (lista == NULL)
    {
        return 1;
    }
    
    return 0;
}


/* Busca el id en la lista y retorna 1 si lo encuentra y 0 si no lo encuentra*/
int idUsado(Tnodo *lista, int n ){

    if (!vacia(lista))
    {
        while (lista != NULL)
        {
            if (lista->vehiculo.idVehiculo == n)
            {
                return 1;
            }

            lista = lista->sig; //pasa al siguiente elemento de la lista
        }
    }
    
    return 0;
}


/*Retorna un número random entre un minimo y un máximo*/
int numRandom(Tnodo *lista){

    int n;

    // Si la lista esta vacia devuelve un número cualquiera
    if (vacia(lista))
    {
        n = rand() % (MAX - MIN + 1) + MIN;
        return n;
    }
    
    /* Si no, devuelve un número que no este usado*/
    do
    {
        n = rand() % (MAX - MIN + 1) + MIN;
        
    } while (idUsado(lista,n));

    return n;

}


/* Inserta el vehiculo en la lista ordenado por el ID*/
void insertaOrdenado(Tnodo **lista, Tvehiculo vehiculo){

    /* Punteros para recorrer la lista*/
    Tnodo *ptrAux = *lista; // Puntero al siguiente nodo
    Tnodo *ptrAnt = NULL; // Puntero al nodo anterior

    /* Reserva la memoria para el nuevo nodo que se va a introducir*/
    Tnodo *nuevoNodo = malloc(sizeof(Tnodo));
    nuevoNodo->sig = NULL;
    nuevoNodo->vehiculo = vehiculo;

    // Si no hay memoria, no se puede introducir el nodo
    if (nuevoNodo == NULL) { 
        
        printf("\nNo queda memoria");
        return ; 
    }


    /* Si la lista está vacía o el nuevoNodo va el primero, lo coloca */
    if (vacia(*lista) || (*lista)->vehiculo.idVehiculo > vehiculo.idVehiculo) {
        nuevoNodo->sig = *lista;
        *lista = nuevoNodo;
        return;
    }

    /* Recorre la lista*/
    while (ptrAux != NULL && ptrAux->vehiculo.idVehiculo < vehiculo.idVehiculo) {
        ptrAnt = ptrAux; // se queda en el anterior
        ptrAux = ptrAux->sig; // se queda en el siguiente al vehiculo a introducir
    }

    /* Conecta el nuevo nodo entre ptrAnt que es el nodo anterior y ptrAux que es el nodo siguiente*/
    ptrAnt->sig = nuevoNodo;
    nuevoNodo->sig = ptrAux;

}

/* Introduce un estring de la carga, según la carga que tenga asignada*/
void recogeCarga(Tvehiculo vehiculo,char *carga){

    switch (vehiculo.carga) {
        case LIGERA:
            strcpy(carga,"LIGERA");
            break;
        case MEDIA:
            strcpy(carga,"MEDIA");
            break;
        case PESADA:
            strcpy(carga,"PESADA");
            break;
        default:
            strcpy(carga,"DESCONOCIDA");
            break;
    }

}

void introduceCarga(Tvehiculo *vehiculo, char carga){

    switch (carga)
    {
    case 'l':
        vehiculo->carga = LIGERA;
        break;
    case 'm':
        vehiculo->carga = MEDIA;
        break;
    case 'p':
        vehiculo->carga = PESADA;
        break;    
    default:
        vehiculo->carga = DESCONOCIDA; // Si introduce un valor incorrecto pone la carga como DESCONOCIDA
        break;
    }
}

//Muestra un solo vehiculo
void muestraVehiculo(Tvehiculo vehiculo){

    printf("\n\n-------------------------------------------------");
    printf("\nID : %d", vehiculo.idVehiculo);
    printf("\nMarca y modelo : %s",vehiculo.marcaModelo);
    printf("\nKilometros : %.2f",vehiculo.kms);
    printf("\nPontencia : %d",vehiculo.potencia);

    char carga[TAM_NOMBRE];
    recogeCarga(vehiculo,carga);
    printf("\nCarga : %s ",carga);
}



/******* FUNCIONES PARA EL MAIN ***********/

/* Muestra el menu con las opciones*/
void menu(){
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
    printf("\n-                                 -GESTION VEHICULOS EMPRESA-                                                         -");
    printf("\n-                                                                                                                     -");
    printf("\n-     1. Insertar nuevo vehiculo                                                                                      -");
    printf("\n-     2. Dar de baja un vehiculo                                                                                      -");
    printf("\n-     3. Incrementar kilometraje de vehiculo                                                                          -");
    printf("\n-     4. Mostrar todos los vehiculos                                                                                  -");
    printf("\n-     5. Mostrar los datos de todos los vehiculos de pontencia superior a la introducida                              -");
    printf("\n-     6. Volcar toda la lista a fichero de texto                                                                      -");
    printf("\n-     7. Restaurar desde fichero de texto                                                                             -");
    printf("\n-     8. Volcar lista a fichero binario                                                                               -");
    printf("\n-     9. Restaurar lista desde fichero binario                                                                        -");
    printf("\n-     10. Recuperar los ultimos tres vehiculos del fichero binario                                                    -");
    printf("\n-     11. Borrar lista. Evidentemente nodo a nodo                                                                     -");
    printf("\n-     12. Salir                                                                                                       -");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");


}


/* Inicializa la lista de los vehiculos*/
void creaLista(Tnodo **lista) {
    *lista = NULL;
}



/************** APARTADO 1 INTRODUCIR UN VEHÍCULO DESDE TECLADO******************/

/* Pide un vehiculo al usuario si la lista no está llena*/
void pedirVehiculo(Tvehiculo *vehiculo){


    //Pide marca y modelo
    while (getchar() != '\n');
    printf("\nMarca y modelo : ");
    gets(vehiculo->marcaModelo);

    //Pide potencia
    printf("\nPotencia : ");
    scanf("%d",&vehiculo->potencia);

    //Pide kilometros;
    printf("\nKilometros : ");
    scanf("%f",&vehiculo->kms);

    //Pide carga
    char carga;
    printf("\nCarga: \n\tLIGERA(L)\n\tMEDIA(M)\n\tPESADA(P)\n ");
    while (getchar() != '\n');
    carga = (char)getchar();

    /*La pasa a minuscula para que se pueda introducir mayusculas y minusculas*/
    carga = (char)tolower(carga);
    introduceCarga(vehiculo,carga);
    

}

/*Pide los datos del vehiculo y lo inserta en la lista*/
int introduceVehiculo(Tnodo **lista){
    
    /* Si la lista está llena, sale de la función*/
    if (llena(*lista))
        return 1;
    
    Tvehiculo vehiculo; /* Vehiculo en el que se va a introducir los datos del usuario*/

    //Se le asigna un id del vehiculo
    vehiculo.idVehiculo = numRandom(*lista); 
    /* Se le pide los datos al usuario*/
    pedirVehiculo(&vehiculo);

    /* Introduce el vehiculo ordenado en la lista*/
    insertaOrdenado(lista,vehiculo);
    
    return 0;
}


/************** APARTADO 2 DAR DE BAJA UN VEHÍCULO ******************/

/* Elimina un vehiculo por su ID*/
int bajaVehiculo(Tnodo **lista, int id){

    Tnodo *ptrAux = *lista;
    Tnodo *ptrAnt = NULL;

    /* Si la lista está vacia no se eliminan vehiculos*/
    if (vacia(*lista))
        return 1;

    /* Si el id no está en la lista lo dice*/
    if (!idUsado(*lista,id))
        return 2;

    /* Se muestran los datos del vehiculo que se va a eliminar*/
    printf("\nVehiculo con ID : %d ELIMINADO",id);
    printf("\nDATOS:");

    /* Si es el primero lo elimina*/
    if ((*lista)->vehiculo.idVehiculo == id)
    {
        *lista = (*lista)->sig;
        muestraVehiculo(ptrAux->vehiculo); //Muestra los datos del vehiculo que se ha eliminado
        free(ptrAux);
        return 0;
    }
    

    /* Recorre la lista*/
    while (ptrAux != NULL && ptrAux->vehiculo.idVehiculo < id) {
        ptrAnt = ptrAux; // se queda en el anterior
        ptrAux = ptrAux->sig; // se queda en el siguiente al vehiculo a introducir
    }

    if (ptrAux == NULL)
       ptrAnt->sig = NULL;  // Si está insertado al final, pone el anterior como NULL
    else
       ptrAnt->sig = ptrAux->sig; // Si no el anterior lo pone como el siguiente del vehiculo a eliminar

    muestraVehiculo(ptrAux->vehiculo);
    free(ptrAux); // Elimina el vehiculo que se requiere eliminar


    return 0;

}


/************** APARTADO 3 INCREMENTAR KILOMETRAJE DE VEHICULO******************/

int aumentaKilometraje(Tnodo *lista, int id, float aumento){ //Elimina vehiculos si se pasa por referencia

    /* Si la lista está vacia no se eliminan vehiculos*/
    if (vacia(lista))
        return 1;

    /* Si el id no está en la lista lo dice*/
    if (!idUsado(lista,id))
        return 2;

    /* Recorre la lista en busca del id*/
    while (lista->vehiculo.idVehiculo != id)
    {
        lista = lista->sig;
    }
    

    /* Aumenta los kilomentros*/
    lista->vehiculo.kms += aumento;

    return 0;

}



/************** APARTADO 4 MOSTRAR TODOS LOS VEHÍCULOS******************/


/* Muestra todos los vehiculos*/
int mostrarVehiculos(Tnodo *lista){

    while (lista != NULL)
    {
        muestraVehiculo(lista->vehiculo);
        lista = lista->sig; 
    }

    return 0;   
}


/************** APARTADO 5 MOSTRAR TODOS LOS VEHÍCULOS CUYA POTENCIA SEA MAYOR A LA INTRODUCIDA******************/


/* Muestra los vehiculos que tienen una potencia mayor a la que se le pasa por teclado*/
int mostrarPotenciaMayor(Tnodo *lista, int potencia){

    
    /* Recorre la lista y si encuentra un vehiculo con la potencia superior a la indicada imprime sus datos*/
    while (lista != NULL)
    {   
        if (lista->vehiculo.potencia >= potencia)
        {
            muestraVehiculo(lista->vehiculo);

        }
        lista = lista->sig; 
    }   

    return 0;
}


/************** APARTADO 6 VOLVAR A FICHERO DE TEXTO******************/


int copiaSeguridadFichero(Tnodo *lista, char *nombreFichero ){ /* No imprime igual*/

    FILE *ptrFile; /* Puntero al fichero*/

    /* Si la lista esta vacia no puede volcar ningun vehiculo*/
    if (vacia(lista))
        return 1;
    

    ptrFile = fopen(nombreFichero, "w"); // Si no existe, lo crea

    /* Si no se puede abrir el archivo lo dice*/
    if (ptrFile == NULL)
        return 2;


    
    /*Imprime todos los datos de la lista al fichero*/
    while (lista != NULL)
    {
        fprintf(ptrFile,"%d:",lista->vehiculo.idVehiculo);
        fprintf(ptrFile,"%s:",lista->vehiculo.marcaModelo);
        fprintf(ptrFile,"%d:",lista->vehiculo.potencia);
        fprintf(ptrFile,"%.2f:",lista->vehiculo.kms);
        char carga[TAM_NOMBRE];
        recogeCarga(lista->vehiculo,carga);
        fprintf(ptrFile,"%s\n",carga);

        lista = lista->sig; 
    }

    fclose(ptrFile);
    
    return 0;
}


/************** APARTADO 7 RESTAURAR DESDE FICHERO DE TEXTO******************/

/* Recoge los datos de una lineas de fichero de texto y lo introduce al vehiculo*/
void recogeDatosFichero(char datos[MAXCADENA], Tvehiculo *vehiculo){ 

    /* Divide la cadena del fichero en tokens */
    char *ptrDatos = strtok(datos,DELIMITER);
    char carga[MAXCADENA];
    if (ptrDatos != NULL) {

        /* Introduce el ID */
        vehiculo->idVehiculo = atoi(ptrDatos);
        ptrDatos = strtok(NULL, DELIMITER);
        
        /* Introduce la marca y el modelo */
        if (ptrDatos != NULL)
            strcpy(vehiculo->marcaModelo, ptrDatos);
        ptrDatos = strtok(NULL, DELIMITER);
        
        /* Introduce la potencia */
        if (ptrDatos != NULL)
            vehiculo->potencia = atoi(ptrDatos);
        ptrDatos = strtok(NULL, DELIMITER);
        
        /* Introduce los kilómetros */
        if (ptrDatos != NULL)
            vehiculo->kms = (float) atof(ptrDatos);
        ptrDatos = strtok(NULL, DELIMITER);
        if (ptrDatos != NULL)
        {
            strcpy(carga,ptrDatos);
            *carga = (char)tolower(*carga);
            introduceCarga(vehiculo,*carga);
        }

    }
    
    
}


/* Recoge los datos del fichero y lo inserta en la lista*/
int restaurarDesdeFichero(Tnodo **lista, char *nombreFichero){

    Tvehiculo vehiculo; /* Vehiculo en el que se van a insertar los datos*/

    FILE *ptrFile; /* Puntero al fichero*/

    /* Borra la lista para liberar la memoria usada */
    eliminaLista(lista);

    ptrFile = fopen(nombreFichero, "r"); // Intenta abrir el fichero

    /* Si no se puede abrir el archivo lo dice*/
    if (ptrFile == NULL)
        return 1;

    /* Cadena para leer la linea del fichero*/
    char datos[MAXCADENA];

    while ( fgets(datos,MAXCADENA,ptrFile) != NULL) /* No pongo fin de fichero por que el prime vehiculo no lo introduce*/
    {
        recogeDatosFichero(datos,&vehiculo); /* Recoge los datos del fichero*/
        insertaOrdenado(lista,vehiculo); /* Da problema en el ordena*/
    }
    
    /* Se cierra el fichero*/
    fclose(ptrFile);

    return 0;
}


/************** APARTADO 8 VOLVAR LOS DATOS DE LA LISTA A FICHERO BINARIO******************/

int copiaSeguridadBinario(Tnodo *lista, char *nombreFichero){

    FILE *ptrFile; /* Puntero al fichero*/
        
    /* Si la lista esta vacia no puede volcar ningun vehiculo*/
    if (vacia(lista))
        return 1;

    ptrFile = fopen(nombreFichero, "wb"); // Si no existe, lo crea

    /* Si no se puede abrir el archivo lo dice*/
    if (ptrFile == NULL)
        return 2;
    
    /*Imprime todos los datos de la lista al fichero*/
    while (lista != NULL)
    {
        fwrite( &lista->vehiculo, sizeof(Tvehiculo), 1, ptrFile );
        lista = lista->sig; 
    }

    fclose(ptrFile);

    return 0;
}



/************** APARTADO 9 RESTAURAR DESDE FICHERO BINARIO******************/

int restaurarBinario(Tnodo **lista, char *nombreFichero){

    Tvehiculo vehiculo; /* Vehiculo en el que se van a insertar los datos*/

    FILE *ptrFile; /* Puntero al fichero*/

    /* Borra la lista para liberar la memoria usada */
    eliminaLista(lista);

    ptrFile = fopen(nombreFichero, "rb"); // Intenta abrir el fichero

    /* Si no se puede abrir el archivo lo dice*/
    if (ptrFile == NULL)
        return 1;

    /* Pasa los datos del fichero binario al vehiculo*/
    fread( &vehiculo, sizeof(Tvehiculo), 1, ptrFile );
   
    /* Recorre el fichero hasta que llega al fin de este*/
    while ( !feof(ptrFile))
    {
        insertaOrdenado(lista,vehiculo); /* Inserta el vehiculo en la lista*/

        fread( &vehiculo, sizeof(Tvehiculo), 1, ptrFile );
    }
    
    /* Se cierra el fichero*/
    fclose(ptrFile);

    return 0;
}


/************** APARTADO 10 RECUPERA LOS DATOS DE LOS ULTIMOS 3 VEHICULOS DESDE FICHERO BINARIO******************/

int  recuperaUltimosVehiculos(Tnodo **lista, char *nombreFichero, int nVehiculos){

    Tvehiculo vehiculo; /* Vehiculo en el que se van a insertar los datos*/

    FILE *ptrFile; /* Puntero al fichero*/

    /* Borra la lista para liberar la memoria usada */
    eliminaLista(lista);


    ptrFile = fopen(nombreFichero, "rb"); // Intenta abrir el fichero

    /* Si no se puede abrir el archivo lo dice*/
    if (ptrFile == NULL)
        return 1;
    
    /* Mueve el puntero al numero de vuhiculos que queremos recuperar desde el final del fichero*/
    fseek(ptrFile, -( nVehiculos * ((long int)sizeof(Tvehiculo))), SEEK_END);

    fread( &vehiculo, sizeof(Tvehiculo), 1, ptrFile );

    /*  Si el número de vehiculos que se quieren recuperar el mayor a los que tiene el fichero 
        Se recuperan todos los que tiene*/
    while ( !feof(ptrFile))
    {
        insertaOrdenado(lista,vehiculo); /* Inserta el vehiculo en la lista*/
        fread( &vehiculo, sizeof(Tvehiculo), 1, ptrFile );
    }

    /* Se cierra el fichero*/
    fclose(ptrFile);

    return 0;
}



/************** APARTADO 11 ELIMINA LA LISTA NODO A NODO******************/

/* Borra todos los nodos de la lista*/
void eliminaLista( Tnodo **lista){

    Tnodo *ptrAux;

    /* Recorre la lista eliminando nodo a nodo cada vehiculo*/
    while (*lista != NULL)
    {
        ptrAux = *lista;
        *lista = (*lista)->sig;
        free(ptrAux);
    }
    
    creaLista(lista);
       
}






