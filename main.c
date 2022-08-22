#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "server.h"


#define LSIZ 128
#define RSIZ 10


void menuPrincipal();

void menuOperativo();
void menuAdministrativo();

void leerArchivo();
void transformarArchivo(FILE *archivo);
bool esNumero(char *token);
void pausa();
void salir();

int main(){
    system("clear");
    conectarServidor();
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú principal  #####\n\n");
        printf("1.Opciones operativas. \n");
        printf("2.Opciones administrativas. \n");
        printf("3.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 3:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            menuOperativo();
            break;
        
        case '2':
            menuAdministrativo();
            break;
        
        case '3':
            repetir = 0;
            break;
        
        default:
            break;
        }
    }while(repetir);
    printf("saliendo......\n");
    salir();
    return;
}

void  menuOperativo(){
    system("clear");
    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú operativo  #####\n\n");
        printf("1.Cargar productos. \n");
        printf("2.Listar Areas. \n");
        printf("3.Listar Empleados. \n");
        printf("4.Volver al menú principal.\n");
        printf("5.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 4:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            printf("cargar productos");
            leerArchivo();
            break;
        
        case '2':
            printf("listar areas");
            break;
        
        case '3':
            printf("listar empleados");
            break;

        case '4':
            repetir = 0;
            break;
        case '5':
            printf("saliendo......\n");
            salir();
        default:
            break;
        }
    }while(repetir);
    
    

    return;
}

void  menuAdministrativo(){


    system("clear");
    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú administrativo  #####\n\n");
        printf("1.Valores iniciales \n");
        printf("2.Registro de nomina \n");
        printf("3.Registro ventas. \n");
        printf("4.Consulta de nomina.\n");
        printf("5.Consulta de ventas.\n");
        printf("6.Volver al menú principal.\n");
        printf("7.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 7:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            printf("Valores iniciales");
            break;
        
        case '2':
            printf("registro de nomina");
            break;
        
        case '3':
            printf("registro de ventas");
            break;

        case '4':
            printf("Consulta de nominas");
            break;

        case '5':
            printf("Consulta de ventas");
            break;

        case '6':
            repetir = 0;
            break;
        case '7':
            printf("saliendo......\n");
            salir();
        default:
            break;
        }
    }while(repetir);
    
    

    return;
}


//////////////////////////////////


void leerArchivo(){

    FILE *archivo;
    int tamanio;
    int cantidadLineas = 0;
    char ultimoCaracter;
    char ruta[200];
    printf("\nPorfavor indique la ruta del archivo:");
    //scanf("%s",ruta);
    archivo = fopen(/*ruta*/ "test.txt", "r+");
    while((getchar()!='\n'));
    if(archivo == NULL){
        printf("\n\nLa ruta indicada no existe o no está disponible.\n");
        return;
    }
    else{
        fseek(archivo, 0L, SEEK_END);
        tamanio = ftell(archivo);
        fseek(archivo, tamanio-1, SEEK_SET);
        
        ultimoCaracter = fgetc(archivo);
        
        if(ultimoCaracter!='\n') fputc('\n', archivo);

        fseek(archivo, 0L, SEEK_SET); 

        transformarArchivo(archivo);
    }
    fclose(archivo);
    
    return;    
}


void transformarArchivo(FILE *archivo){
    char lineas[RSIZ][LSIZ];
    int i = 0;
    int j = 0;
    
    while(fgets(lineas[i], LSIZ, archivo)){
        lineas[i][strlen(lineas[i])-1]='\0';
        i++;
    }
    j = i;
    printf("\nSe incluiran las siguientes aulas\n");
    struct Producto Productos[i];
    for(i = 0; i<j; ++i){
        char *str = lineas[i];
        printf("%s\n",str);
        char *idProducto = strtok(str,",");
        char *nombre = strtok(NULL,",");
        char *costo = strtok(NULL,",");
        char *impAplicado = strtok(NULL,",");
        printf("id:%s\n",idProducto);
        printf("nombre:%s\n",nombre);
        printf("costo:%s\n",costo);
        printf("impAplicado:%s\n",impAplicado);

        if(idProducto != NULL &&
            esNumero(costo) && esNumero(impAplicado)){
            struct Producto pProducto;
            pProducto.idProducto = idProducto;
            pProducto.nombre = nombre;
            pProducto.costo = atoi(costo);
            pProducto.impAplicado = atof(impAplicado);
            printf("idProducto:%s\tnombre:%s\tcosto:%d\timpuesto Aplicado:%f\n\n", 
                        pProducto.idProducto,pProducto.nombre, pProducto.costo, pProducto.impAplicado);
            insertProducto(&pProducto);
        } 
    }
    printf("------------------------------------\n");
    pausa();

    return;

}
/*******************************************************************/


bool esNumero(char *token){
    bool res = true;
    for(int i = 0 ; token[i]!='\0';i++){
        if(!isdigit(token[i])){res = false;}
    }

    return res;
}
void pausa(){
    getchar();
    printf("\n\nPresione enter para continuar....");
    getchar();
    system("clear");
    return;
}
void salir(){
    exit(0);
}