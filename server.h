#ifndef server
#define server

#include <mysql/mysql.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *sqlServer = "localhost";
char *user = "root";
char *password = "JpHv0410";
char *database = "gestionAgricola";

void freeMysql();


int conectarServidor(){
    printf("Estableciendo conexión con el servidor...");
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, sqlServer, user, password, database, 0, NULL, 0)){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nconexion establecida \n");
    }
}


/////////////////////////////////
void insertProducto(struct Producto *pProducto){
    printf("insertproducto \n\n");
    char query[2000];
    sprintf(query, "call insertProducto('%s','%s', %f,%f)",pProducto->idProducto, pProducto->nombre, pProducto->costo,pProducto->impAplicado);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl producto se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


void insertNomina(struct Nomina *pNomina, int *pIdNomina){
    char query[2000];
    sprintf(query, "call insertNomina('%d','%d', %f,%f)",pNomina->mes, pNomina->anio, pNomina->subtotal, pNomina->total);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nLa nomina se ha insertado correctamente!\n");
        res = mysql_store_result(conn);
        *pIdNomina = atoi(mysql_fetch_row(res)[0]);
    }
    return;
}

void insertEmpleadoXNomina(int cedula, int pIdNomina, int pCantidadNomina){
    char query[2000];    
    sprintf(query, "call insertEmpleadoXNomina('%d','%d')", cedula, pIdNomina);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl empleado se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


void insertFactura(struct Factura *pFactura,int *pIdFactura, struct ValoresIniciales *pValoresIniciales){
    char query[2000];
    sprintf(query, "call insertFactura('%s',%d,%d,'%d-%d-%d','%s',%f,%f,%f)",
            pValoresIniciales->nombreComercio, pValoresIniciales->cedulaJuridica,pValoresIniciales->telefono,
            pFactura->anio, pFactura->mes, pFactura->dia, pFactura->nombreCliente, pFactura->subtotal,pFactura->impuestosVenta,pFactura->Total/*pFactura->subtotal, pFactura->impuestosVenta, pFactura->Total*/);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    
    }else{
        printf("\nLa factura se ha insertado correctamente!\n");
        res = mysql_store_result(conn);
        *pIdFactura = atoi(mysql_fetch_row(res)[0]);
    }

    return;
}

void insertProductoXFactura(char *pIdProducto, int pIdFactura, int pCantidad){
    char query[2000];    
    sprintf(query, "call insertProductoXFactura('%s','%d','%d')", pIdProducto, pIdFactura, pCantidad);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl producto se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}

int getAllAreas(){
    char *query = "call getAllAreas()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}

int getAllEmpleados(){
    char *query = "call getAllEmpleados()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}

int getAllNominas(){
    char *query = "call getAllNominas()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}

int getAllProductos(){
    char *query = "call getAllProductos()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}

int getEmpleadosByNomina(int nomina){
    char query[2000];
    sprintf(query, "call getEmpleadosByNomina('%d')",nomina);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}


int getUsuario(struct Usuario *pUsuario){
    char query[2000];
    sprintf(query, "call getUserByUsuario('%s','%s')",pUsuario->usuario,pUsuario->clave);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}

int getValoresIniciales(){
    
    char *query = "call getValoresIniciales()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}
/////////////////////
void freeMysql(){
    do
    {
        if(res = mysql_store_result(conn)){
            mysql_free_result(res);
        }
    } while (mysql_more_results(conn)&&mysql_next_result(conn));
    
    return;
}
#endif