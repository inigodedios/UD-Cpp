#include "BaseDeDatos.h"
#include <string.h>
#include <stdio.h>
#include "sqlite3.h"
#include "Api.h"
#include "main.h"

int abrir(){
    int result = sqlite3_open("/Users/mentxaka/Documents/F - C & C++ Files/UD-ProyectoProgIV/Debug/Datos.sqlite", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return result;
    }
    printf("Database opened\n") ;
    return result;
}

int existeUsu(char* usu) {
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT * FROM Usuario WHERE nick = '%s';",usu);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    if(result == SQLITE_ROW) {return 1;}
    else {return 0;}
}

int existe(int i,int tipo){ //1 FORMULARIO, 2 PREGUNTA Y 3 RESPUESTA
    sqlite3_stmt *stmt;
    int result;
    if(tipo == 1){
        char sql[] = "SELECT * FROM Formulario WHERE ID = N";
        sql[36] = i+'0';
        result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    }
    if(tipo == 2){
        char sql[] = "SELECT * FROM Pregunta WHERE ID = NN";
        sql[34] = getDecena(i)+'0';
        sql[35] = getUnidad(i)+'0';
        result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    }
    if(tipo == 3){
        char sql[] = "SELECT * FROM Respuesta WHERE ID = NNN";
        sql[35] = getCentena(i)+'0';
        sql[36] = getDecena(i)+'0';
        sql[37] = getUnidad(i)+'0';
        result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    }
    if (result != SQLITE_OK) {
        printf("Error preparing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    result = sqlite3_step(stmt) ;

    if(result == 100) return 1;
    else return 0;
}

int escribeF(int i,char* nick) {
    sqlite3_stmt *stmt;
    int result;
    if(1!=existe(i,1)){
        char sql[200];
        sprintf(sql,"INSERT INTO Formulario (ID, ID_U) VALUES (%i,'%s')",i,nick);
        result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
        printf("SQL query prepared (INSERT)\n");
        result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            printf("Error inserting new data into table\n");
            return result;
        }
        result = sqlite3_finalize(stmt);
        if (result != SQLITE_OK) {
            printf("Error finalizing statement (INSERT)\n");
            printf("%s\n", sqlite3_errmsg(db));
            return result;
        }
        printf("Prepared statement finalized (INSERT)\n");
        return 1;
    }
    return 0;
}

int escribeP(int i, int f){
    sqlite3_stmt *stmt;
    int result;
    if(1!=existe(i,2)) {
        char sql[200];
        sprintf(sql,"INSERT INTO Pregunta (ID, ID_P) VALUES (%i,%i)",i,f);
        result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
        printf("SQL query prepared (INSERT)\n");
        result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            printf("Error inserting new data into table\n");
            return result;
        }
        result = sqlite3_finalize(stmt);
        if (result != SQLITE_OK) {
            printf("Error finalizing statement (INSERT)\n");
            printf("%s\n", sqlite3_errmsg(db));
            return result;
        }
        printf("Prepared statement finalized (INSERT)\n");
        return 1;
    }
    return 0;
}
int escribeR(int i,int p){
    sqlite3_stmt *stmt;
    int result;
    if(1!=existe(i,3)) {
        char sql[200];
        sprintf(sql,"INSERT INTO Respuesta (ID,ID_P) VALUES (%i,%i)",i,p);
        result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        printf("SQL query prepared (INSERT)\n");
        result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            printf("Error inserting new data into table\n");
            return result;
        }
        result = sqlite3_finalize(stmt);
        if (result != SQLITE_OK) {
            printf("Error finalizing statement (INSERT)\n");
            printf("%s\n", sqlite3_errmsg(db));
            return result;
        }
        printf("Prepared statement finalized (INSERT)\n");
        return 1;
    }
    return 0;
}
int escribeU(int i,char* nick, char* pass){
    sqlite3_stmt *stmt;
    int result;
    if(1!=existeUsu(nick)){
        char sql[200];
        sprintf(sql,"INSERT INTO Usuario VALUES (%i,'%s','%s');",i,nick,pass);
        result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        printf("SQL query prepared (INSERT)\n");
        result = sqlite3_step(stmt);
        if (result != SQLITE_DONE) {
            printf("Error inserting new data into table\n");
            return result;
        }
        result = sqlite3_finalize(stmt);
        if (result != SQLITE_OK) {
            printf("Error finalizing statement (INSERT)\n");
            printf("%s\n", sqlite3_errmsg(db));
            return result;
        }
        printf("Prepared statement finalized (INSERT)\n");
        return result;
    }
    return 0;
}
int getEdad(int i){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT edad FROM Entrevistado where id = %i;",i);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int edad;
    if(result == SQLITE_ROW) edad = sqlite3_column_int(stmt, 0);
    return edad;
}

int getNEntrevistados(){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Entrevistado;");
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}

int getNFormularios(){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Formulario;");
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}

int getNPreguntas(int i){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Pregunta WHERE id_p = %i;",i);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}

int getNRespuestas(int i){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Respuesta WHERE id_p = %i;",i);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}

int getNSeleccionda(int i){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Selecciona WHERE id_r = %i;",i);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}

int getNUsuarios(){
    sqlite3_stmt *stmt;
    int result;
    char sql[200] ;
    sprintf(sql,"SELECT count(*) FROM Usuario;");
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    result = sqlite3_step(stmt) ;
    int cant;
    if(result == SQLITE_ROW) cant = sqlite3_column_int(stmt, 0);
    return cant;
}
int escribeE(int i,int e){
    sqlite3_stmt *stmt;
    int result;
    char sql[200];
    sprintf(sql,"INSERT INTO Entrevistado VALUES (%i,%i);",i,e);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    printf("SQL query prepared (INSERT)\n");
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error inserting new data into table\n");
        return result;
    }
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (INSERT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    printf("Prepared statement finalized (INSERT)\n");
    if(result == 100) return 1;
    else return 0;
}

int escribeSeleccion(int e,int r){
    sqlite3_stmt *stmt;
    int result;
    char sql[200];
    sprintf(sql,"INSERT INTO Selecciona VALUES (%i,%i);",e,r);
    result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    printf("SQL query prepared (INSERT)\n");
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error inserting new data into table\n");
        return result;
    }
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (INSERT)\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    printf("Prepared statement finalized (INSERT)\n");
    if(result == 100) return 1;
    else return 0;
}

int coinciden(char* c1,char* c2){
    for(int i = 0; i<10;i++) if(c1[i]!=c2[i]) return 0;
    return 1;
}

void iniciarSesion(char* usu, char* cont){
    printf("Recuerde que su usuario no tiene mas de 10 caracteres\n");
    printf("Usuario: ");
    usu = inputString(10);
    if (existeUsu(usu)) {
        char* orig = "";
        sqlite3_stmt *stmt;
        char sql[200];
        sprintf(sql,"SELECT pass FROM usuario WHERE nick = '%s';",usu);
		strcpy(orig, (char *) sqlite3_column_text(stmt, 0));
        int result = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL) ;
        result = sqlite3_step(stmt) ;
        strcpy(orig, (char *) sqlite3_column_text(stmt, 0));
        do {
            printf("Contrasena: ");
            cont = inputString(10);
        }while (0==coinciden(cont,orig));
    }

        printf("\nUsuario: %s, contrasena: %s\n", usu, cont);
        printf("Nombre de usuario o contrasena incorrectos\n");

}

int cerrar(){
    int result = sqlite3_close(&db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    printf("Database closed\n") ;
    return result;
}
