#include "Api.h"
#include "Text.h"
#include "BaseDeDatos.h"
#include "main.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//////////////////////////////////////////////////DECLARACIONES ADELANTADAS/////////////////////////////////////////////////////

int inputNumero(int size);

char *inputString(int size);

void printString(char *str);

int compare(char *c1, char *c2);

char *trimwhitespace(char *str);

char *sysdate();

int concatInt(int x, int y);

int getUnidad(int numero);

int getDecena(int numero);

int getCentena(int numero);

void printFormulario(Formulario f);

void printF(ArrayList *f);

Formulario creaForm(int k);

void anadirEspacio(ArrayList *f);

Formulario anadirEspacioPreg(Formulario f);

void CASO1(ArrayList *f);

void CASO1_1(ArrayList *f);

void CASO1_2(ArrayList *f);


////////////////////////////////////////////////////////FUNCIONES EN C/////////////////////////////////////////////////////////////

/**
 *
 * RECIBE UN NUMERO POR CONSOLA
 *
 * @PARAM size CANTIDAD DE DIGITOS DEL NUMERO
 * @RETURN NUMERO RECIBIDO POR CONSOLA
 *
 */
int inputNumero(int size) { //INTRODUCE UN NUMERO MAYOR QUE 0
    fflush(stdin);
    int num;
    size++;
    char str[size];
    fgets(str, size, stdin);
    sscanf(str, "%i", &num);
    return num;
}

/**
 *
 * RECIBE UN STRING POR CONSOLA
 *
 * @PARAM size CANTIDAD DE DIGITOS DEL STRING
 * @RETURN STRING RECIBIDO POR CONSOLA
 *
 */
char *inputString(int size) {
    fflush(stdin);
    char *str = malloc(sizeof(char) * (size + 1));
    fgets(str, size, stdin);
    sscanf(str, "%[^\n]", str);
    return str;
}

/**
 *
 * IMPRIME UN STRING
 *
 * @PARAM str STRING A IMPRIMIR
 *
 */
void printString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        printf("%c", str[i]);
        i++;
    }
}

/**
 *
 * COMPARA DOS CADENAS DE CARACTERES
 *
 * @PARAM c1 CADENA 1 A COMPARAR
 * @PARAM c2 CADENA 2 A COMPARAR
 * @RETURN 1 SI ES CORRECTO, 0 SI ES IGUAL
 *
 */
int compare(char *c1, char *c2) {
    return strcmp(c1, c2);
}

/**
 *
 * ELIMINA EL ULTIMO CARACTER DE UN STRING (NO EL /0)
 *
 * @PARAM str STRING AL QUE QUITAR EL PARAMETRO
 * @RETURN STRING SIN EL ULTIMO DIGITO
 *
 */
char *trimwhitespace(char *str) {
    char *end;
    // Trim leading space
    while (isspace((unsigned char) *str)) str++;
    if (*str == 0)  // All spaces?
        return str;
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    // Write new null terminator character
    end[1] = '\0';
    return str;
}

/**
 *
 * OBTENEMOS LA FECHA DEL SISTEMA
 *
 * @RETURN CADENA DE CARACTERES CON LA FECHA DEL SISTEMA
 */
char *sysdate() {
    time_t t;   // not a primitive datatype
    time(&t);
    char *var = ctime(&t);
    var = trimwhitespace(var);
    return var;
}

/**
 *
 * CONCATENA DOS DIGITOS
 *
 * @PARAM x PRIMER NUMERO A CONCATENAR
 * @PARAM y SEGUNDO NUMERO A CONCATENAR
 * @RETURN LOS DOS NUMEROS CONCATENADOR
 */
int concatInt(int x, int y) {
    int pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}

/**
 *
 * OBTENEMOS EL VALOR DE LA CIFRA DE UNIDAD DEL NUMERO
 *
 * @PARAM numero NUMERO DEL CUAL QUEREMOS OBTENER LA UNIDAD
 * @RETURN UN UNICO DIGITO QUE CORRESPONDE A LA UNIDAD
 */
int getUnidad(int numero) {
    return (numero % 100) % 10 / 1;
}

/**
 *
 * OBTENEMOS EL VALOR DE LA CIFRA DE CENTENA DEL NUMERO
 *
 * @PARAM numero CIFRA DEL CUAL QUEREMOS OBTENER LA CENTENA
 * @RETURN UN UNICO DIGITO QUE CORRESPONDE A LA CENTENA
 */
int getDecena(int numero) {
    return (numero % 100) / 10;
}
/**
 *
 * OBTENEMOS EL VALOR DE LA CIFRA DE CENTENA DEL NUMERO
 *
 * @PARAM numero CIFRA DEL CUAL QUEREMOS OBTENER LA CENTENA
 * @RETURN UN UNICO DIGITO QUE CORRESPONDE A LA CENTENA
 */
int getCentena(int numero) {
    return (numero % 1000) / 100;
}
/**
 *
 * SACA POR TERMINAL TODOS LOS DATOS DE UN FORMULARIO
 *
 * @PARAM f FORMULARIO DEL CUAL QUEREMOS OBTENER LA INFORMACION
 */
void printFormulario(Formulario f) {
    printf("*************** Imprimiendo formulario ***************\n");
    printf("Id: %i\n", f.id);
    printf("Titulo: %s\n", f.tit);
    printf("Descripcion: %s\n", f.desc);
    printf("Version: %i\n", f.ver);
    printf("Fecha de creacion: %s\n", f.fecha);
    for (int i = 0; i < (f.nPreg); i++) {
        printf("P.Id: %i\n", f.preguntas[i].id);
        printf("Pregunta: %s\n", f.preguntas[i].preg);// printString(f->preguntas[i].preg);
        for (int j = 0; j < f.preguntas[i].nResp; j++) {
            printf("R.Id: %i\n", f.preguntas[i].respuestas[j].id);
            printf("Respuesta: %s\n", f.preguntas[i].respuestas[j].resp);
        }
    }
    printf("*************** Formulario impreso ***************\n");
}

/**
 *
 * SACA POR TERMINAL TODOS LOS FORMULARIOS QUE HAY EN EL ARRAY
 *
 * @PARAM f ARRAYLIST DONDE SE ALMACENAN TODOS LOS FORMULARIOS EN MEMORIA
 */
void printF(ArrayList *f) {
    if (f->objetos[0].fecha != NULL) {
        for (int i = 0; i < f->nObjetos - 1; i++) {
            printFormulario(f->objetos[i]);
        }
    }
}

/**
 *
 * CREA UN NUEVO FORMULARIO CON UN ID EN ESPECIFICO
 *
 * @PARAM k ID QUE QUEREMOS QUE TENGA EL FORMULARIO
 *
 */
Formulario creaForm(int k) {
    Formulario f;
    f.id = k;
    printf("Introduzca el titulo (30 caracteres): ");
    f.tit = inputString(30);
    printf("Introduzca la descripcion (100 caracteres): ");
    f.desc = inputString(100);
    f.ver = 1;//printf("Introduzca la version");
    f.fecha = sysdate();//printf("Introduzca la fecha");
    printf("Introduzca el numero de preguntas (2 digitos maximo): ");
    f.nPreg = inputNumero(1);
    f.preguntas = malloc(f.nPreg * sizeof(Pregunta));
    escribeF(f.id,usu);
    for (int i = 0; i < f.nPreg; i++) {
        printf("---------------------------------------------------------\n");
        Pregunta p;
        p.id = concatInt(f.id, i);
        printf("Introduzca la pregunta que desea formular (50 caracteres): ");
        p.preg = inputString(50);
        printf("Introduzca la cantidad de respuestas que desea formular (1 digito): ");
        p.nResp = inputNumero(1);
        p.respuestas = malloc(p.nResp * sizeof(Respuesta));
        f.preguntas[i] = p;
        escribeP(p.id,f.id);
        printf("---------------------------------------------------------\n");
        for (int j = 0; j < p.nResp; j++) {
            Respuesta r;
            r.id = concatInt(p.id, j);
            printf("Introduzca la respuesta (50 caracteres): ");
            r.resp = inputString(50);
            p.respuestas[j] = r;
            escribeR(r.id,p.id);
        }
    }
    return f;
}

/**
 *
 * ANADE ESPACIO A UN ARRAY GENERANDO UNA ESPECIE DE ARRAYLIST
 *
 * @PARAM f ARRAYLIST AL QUE HAY QUE ANADIR ESPACIO
 *
 */
void anadirEspacio(ArrayList *f) {
    ArrayList *temp = malloc(sizeof(ArrayList));
    temp->nObjetos = f->nObjetos++;
    temp->objetos = malloc(sizeof(Formulario) * temp->nObjetos);
    for (int i = 0; i < f->nObjetos; i++) {
        temp->objetos[i] = f->objetos[i];
    }
    f = temp;
}

/**
 *
 * ANADE ESPACIO AL ARRAY DE UN FORMULARIO PARA ANADIR UNA NUEVA PREGUNTA
 *
 * @PARAM f FORMULARIO AL QUE HAY QUE ANADIRLE UNA PREGUNTA
 * @RETURN FORMULARIO CON NUEVA ESTRUCTURA DE MEMORIA
 */
Formulario anadirEspacioPreg(Formulario f) {
    Formulario temp;
    temp.id = f.id;
    temp.tit = f.tit;
    temp.ver = f.ver;
    temp.desc = f.desc;
    temp.fecha = f.fecha;
    temp.nPreg = f.nPreg + 1;

    temp.preguntas = malloc(sizeof(Formulario) * temp.nPreg);
    for (int i = 0; i < f.nPreg; i++) {
        temp.preguntas[i] = f.preguntas[i];
    }
    return temp;
}

///////////////////////////////////////////////////////CODIGO ESTRUCTURADO EN C////////////////////////////////////////////////////////////

char* usu;
char* cont;

void CASO1(ArrayList *f) { //ES USTED UN CLIENTE
    printf("CASO1\n");
    iniciarSesion(usu,cont);
    int boolean = 1;
    while (boolean) {
        printf("\n---------------------------------------------------------------\n\nBienvenido ");
        printString(usu);
        printf(" \n\nSeleccione las siguientes opciones:\n1. Anadir formulario\n2. Modificar formulario\n3. Salir\n\n");
        int intr = inputNumero(1);
        switch (intr) {
            case 1:
                CASO1_1(f);
                break;

            case 2:
                CASO1_2(f);
                printf("caso1.2\t");
                printF(f);
                break;

            case 3:
                CASO5();
                boolean = 0;
                break;

            default:
                CASOEXIT();
                boolean = 0;
                break;
        }
    }
}

void CASO1_1(ArrayList *f) { //CASO DE ANADIR NUEVO FORMULARIO
    printf("Caso 1.1\n");
    if(nF<9){
        Formulario form = creaForm(f->nObjetos);
        f->objetos[f->nObjetos - 1] = form;
        printFormulario(f->objetos[f->nObjetos - 1]);
        anadirEspacio(f);
        nF++;
    }
    else printf("No se puede añadir mas formilarios\n");
}

void CASO1_2(ArrayList *f) { //CASO DE MODIFICAR FORMULARIO
    printf("Imprimiendo todos los formularios...\n");
    for (int i = 0; i < f->nObjetos - 1; i++) {
        printf("- %i - %s.\n", f->objetos[i].id, f->objetos[i].tit);
    }
    printf("(Recuerde que solo puede modificar las preguntas y respuestas, asi como anadir preguntas nuevas. Los atributos del formulario no pueden ser modificados)\nSeleccione el que desea modificar: \t");
    int selForm = inputNumero(1);
    if (selForm > 0 && selForm < f->nObjetos) {
        printFormulario(f->objetos[selForm - 1]);
        Formulario temp = f->objetos[selForm - 1];
        printf("1. Modificar formulario actual\n2. Anadir pregunta\n3. Atras\n");
        int sel = inputNumero(1);
        switch (sel) {
            case 1: ///MODIFICAR EL FORMULARIO ACTUAL
                printf("Introduzca el del parametro que desea modificar:\t");
                sel = inputNumero(3);
                if (sel - 100 < 0) { //numero de dos digitos por ende pregunta
                    int unidad = getUnidad(sel);
                    printf("Usted esta modificando %s \n", temp.preguntas[unidad].preg);
                    printf("Escriba la nueva pregunta (50 caracteres): ");
                    temp.preguntas[unidad].preg = inputString(50);
                    printf("Modificado correctamente, la nueva pregunta es %s", temp.preguntas[unidad].preg);
                } else { //numero de 3 digitos, por ende respuesta
                    int unidad = getUnidad(sel);
                    int decena = getDecena(sel);
                    printf("Usted esta modificando %s \n", temp.preguntas[decena].respuestas[unidad].resp);
                    printf("Escriba la nueva respuesta (50 caracteres): ");
                    temp.preguntas[decena].respuestas[unidad].resp = inputString(50);
                    printf("Modificado correctamente, la nueva respuesta es %s",
                           temp.preguntas[decena].respuestas[unidad].resp);
                }
                break;
            case 2: ///ANADIR PREGUNTA
                temp = anadirEspacioPreg(temp);
                Pregunta p;
                p.id = temp.preguntas[temp.nPreg - 2].id + 1;
                printf("Introduzca la pregunta que desea formular (50 caracteres): ");
                p.preg = inputString(50);
                printf("Introduzca la cantidad de respuestas que desea formular (1 digito): ");
                p.nResp = inputNumero(1);
                p.respuestas = malloc(p.nResp * sizeof(Respuesta));
                for (int j = 0; j < p.nResp; j++) {
                    Respuesta r;
                    r.id = concatInt(p.id, j);
                    printf("Introduzca la respuesta (50 caracteres): ");
                    r.resp = inputString(50);
                    p.respuestas[j] = r;
                }
                temp.preguntas[temp.nPreg - 1] = p;
                break;
            case 3:
                CASO5();
                break;
            default:
                CASOEXIT();
                break;
        }
        f->objetos[selForm - 1] = temp;
    }
}

///////////////////////////////////////////////////////PARTE DE C++////////////////////////////////////////////////////////////


void CASO2() { //ES UN ENTREVISTADO
    printf("CASO2\n");
}

void CASO3() { //SACAR ESTADISTICAS
    printf("CASO3\n");
}

void CASO4() { //REGISTRAR USUARIO
    printf("CASO4\n");
    char* usu;
    char* cont;
    printf("Introduzca el nuevo usuario: ");usu = inputString(50);
    printf("Introduzca la contraseña: ");cont = inputString(50);
    printf("usu = %s,cont = %s\n",usu,cont);
    int i = escribeU(getNUsuarios()+1,usu,cont);
    if(i==0)printf("Usuario existente\n");
}

void CASO5() { //SALIR
    printf("Gracias por utilizar EncuestasUD\n\n");
}

void CASOEXIT() {
    printf("El numero introducido no ha podido ser reconocido.\nHa sido un placer atenderle!\n\n");
}
