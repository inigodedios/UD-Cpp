//
//  Text.c
//  EncuestasUD
//
/// ESTA LECTURA DE FICHEROS TIENE COMO LOGICA LEER ELFICHERO TXT DE LETRA EN LETRA, TENIENDO ASI QUE CONTAR CADA UNO DE LOS PARAMETROS Y
/// UTILIZANDO SWITCH CASE PARA PODER DESIGNAR QUE DATOS PERTENECEN A QUE ESTRUCTURAS.
//
//  Created by Mentxaka on 7/4/21.
//

#include "Text.h"
#include "Api.h"

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////DECLARACIONES ADELANTADAS/////////////////////////////////////////////////////

ArrayList readFormulario(FILE *infile);

void readPregunta(FILE *infile);

void readRespuesta();

void writeRespuesta(Pregunta p, FILE *f);

void writePregunta(Formulario form, FILE *f);

void writeFormulario(ArrayList *p, FILE *infile);

int countLines();

FILE *abrirFichero(int i);

void cerrarFichero(FILE *f);

///////////////////////VARIABLES/////////////////////////

ArrayList outputArray;
char c;
int contLetras = 0;
int opcion = 0;
char *prov;

int contForm;
Formulario form;

int contPreg = 0;
Pregunta preg;

int contResp = 0;
Respuesta resp;

//////////////////////////////////LECTURA///////////////////////////////////

/**
 *
 * LEE LOS FORMULARIOS ALMACENADOS EN EL FICHERO
 *
 * @PARAM infile FICHERO EL CUAL POSEE TODOS LOS FORMULARIOS
 * @RETURN EXPORTA UNA ESTRUCTURA DE TIPO ARRAYLIST CON TODOS LOS FORMULARIOS
 *
 */
ArrayList readFormulario(FILE *infile) {
    outputArray.nObjetos = countLines();
    outputArray.objetos = malloc(sizeof(Formulario) * outputArray.nObjetos);
    prov = malloc(sizeof(char) * 200);
    while (contForm < countLines() && (c = fgetc(infile)) != EOF) {
        if (c != ',' && c != '\n') {
            prov[contLetras] = c;
            contLetras++;
        } else {
            contLetras = 0;
            opcion++;
            switch (opcion) { ///OPCION QUE INDICA QUE PARAMETRO ES EL QUE ESTAMOS LEYENDO
                case 1:
                    form.id = atoi(prov);
                    break;
                case 2:
                    form.tit = prov;
                    break;
                case 3:
                    form.desc = (prov);
                    break;
                case 4:
                    form.ver = atoi(prov);
                    break;
                case 5:
                    form.fecha = (prov);
                    break;
                case 6:
                    form.nPreg = atoi(prov);
                    form.preguntas = malloc(sizeof(Pregunta) * form.nPreg);
                    opcion = 0;
                    contPreg = 0;
                    while (contPreg < form.nPreg && (c = fgetc(infile)) != EOF) {
                        readPregunta(infile); ///CUANDO DETECTA UNA PREGUNTA
                    }
                    opcion = 0;
                    outputArray.objetos[contForm] = form;
                    contForm++;
                    break;
            }
            prov = malloc(sizeof(char) * 200);
        }
    }
    outputArray.nObjetos = contForm + 1;
    return outputArray;
}

/**
 *
 * LEE LAS PREGUNTAS ALMACENADAS EN CADA FORMULARIO DEL FICHERO
 *
 * @PARAM infile FICHERO DONDE SE ENCUENTRAN LAS PREGUNTAS
 */
void readPregunta(FILE *infile) {
    if (c != ',' && c != '\n') {
        prov[contLetras] = c;
        contLetras++;
    } else {
        opcion++;
        contLetras = 0;
        switch (opcion) { ///OPCION QUE INDICA QUE PARAMETRO ES EL QUE ESTAMOS LEYENDO
            case 1:
                preg.id = atoi(prov);
                break;
            case 2:
                preg.preg = prov;
                break;
            case 3:
                preg.nResp = atoi(prov);
                preg.respuestas = malloc(sizeof(Respuesta) * preg.nResp);
                opcion = 0;
                contResp = 0;
                while (contResp < preg.nResp && (c = fgetc(infile)) != EOF) {
                    readRespuesta();///CUANDO DETECTA UNA RESPUESTA
                }
                form.preguntas[contPreg] = preg;
                contPreg++;
                opcion = 0;
                break;
        }
        prov = malloc(sizeof(char) * 200);
    }
}

/**
 *
 * LEE LAS RESPUESTAS ALMACENADAS EN CADA PREGUNTA DEL FICHERO
 *
 */
void readRespuesta() {
    if (c != ',' && c != '\n') {
        prov[contLetras] = c;
        contLetras++;
    } else {
        opcion++;
        contLetras = 0;
        switch (opcion) { ///OPCION QUE INDICA QUE PARAMETRO ES EL QUE ESTAMOS LEYENDO
            case 1:
                resp.id = atoi(prov);
                break;
            case 2:
                resp.resp = prov;
                preg.respuestas[contResp] = resp;
                opcion = 0;
                contResp++;
                break;
        }
        prov = malloc(sizeof(char) * 200);
    }
}


//////////////////////////////////ESCRITURA///////////////////////////////////

/**
 *
 * ESCRIBE LOS FORMULARIOS ALMACENADOS EN EL FICHERO
 *
 * @PARAM a ARRAYLIST CON TODOS LOS FORMULARIOS
 * @PARAM f FICHERO DONDE SE PRETENDEN GUARDAR LOS FORMULARIOS
 *
 */
void writeFormulario(ArrayList *a, FILE *f) {
    for (int i = 0; i < a->nObjetos - 1; i++) {
        fprintf(f, "%i,%s,%s,%i,%s,%i",
                a->objetos[i].id,
                a->objetos[i].tit,
                a->objetos[i].desc,
                a->objetos[i].ver,
                a->objetos[i].fecha,
                a->objetos[i].nPreg);
        //fwrite (&f->objetos[i], sizeof(Formulario), 1, f); //ESCRIBIMOS EL FORMULARIO EN CURSO
        writePregunta(a->objetos[i], f); //ESCRIBIMOS LAS PREGUNTAS
        if (i == a->nObjetos - 1 - 1) fprintf(f, ",");
        else fprintf(f, "\n");
    }
}

/**
 *
 * ESCRIBE LAS PREGUNTAS ALMACENADAS EN CADA FORMULARIO EN EL FICHERO
 *
 * @PARAM form FORMULARIO EN CURSO
 * @PARAM f FICHERO DONDE SE PRETENDEN GUARDAR LOS FORMULARIOS
 *
 */
void writePregunta(Formulario form, FILE *f) {
    for (int i = 0; i < form.nPreg; i++) {
        fprintf(f, ",%i,%s,%i,", form.preguntas[i].id, form.preguntas[i].preg, form.preguntas[i].nResp);
        //fwrite (&f.preguntas[i], sizeof(Pregunta), 1, f); //SE ESCRIBE LA PREGUNTA EN CURSO
        writeRespuesta(form.preguntas[i], f); //ESCRIBIMOS LAS RESPUESTAS
    }
}

/**
 *
 * ESCRIBE LAS PREGUNTAS ALMACENADAS EN CADA FORMULARIO EN EL FICHERO
 *
 * @PARAM p FORMULARIO EN CURSO
 * @PARAM f FICHERO DONDE SE PRETENDEN GUARDAR LOS FORMULARIOS
 *
 */
void writeRespuesta(Pregunta p, FILE *f) {
    for (int i = 0; i < p.nResp; i++) {
        if (i == p.nResp - 1) fprintf(f, "%i,%s", p.respuestas[i].id, p.respuestas[i].resp);
        else fprintf(f, "%i,%s,", p.respuestas[i].id, p.respuestas[i].resp);
        //fwrite (&p.respuestas[i], sizeof(Respuesta), 1, f); //ESCRIBIMOS LA RESPUESTA EN CURSO
    }
}

///////////////////////FUNCIONES/////////////////////////

/**
 *
 * CUENTA LAS LINEAS QUE HAY EN EL FICHERO, POR ENDE, CUENTA LA CANTIDAD DE FORMULARIOS GUARDADOS
 *
 * @RETURN ENTERO CON LA CANTIDAD DE FORMULARIOS
 *
 */
int countLines() {
    FILE *f = abrirFichero(1);
    char c;
    int i = 1;
    while ((c = fgetc(f)) != EOF) {
        if (c == '\n')
            i++;
    }
    cerrarFichero(f);
    return i;
}

//////////////////////////////////ABRIR FICHERO///////////////////////////////////

/**
 *
 * ABRE EL FICHERO EN EL QUE GUARDAMOS TODOS LOS DATOS
 *
 * @PARAM i ELECCION DEL MODO EN EL QUE SE GUARDAN LOS FICHEROS
 * i = 0 ESCRITURA W
 * i = 1 LECTURA R
 * i = 2 ESCRITURA CONCATENADA A
 *
 * @RETURN FICHERO DONDE SE ENCUENTRAN LOS DATOS ALMACENADOS
 *
 */
FILE* abrirFichero(int i) {
    FILE *f;
    if (i == 0) {
        f = fopen("/Users/mentxaka/eclipse-workspace/prueba/Debug/prueba.txt", "w"); //ESCRITURA W
    }
    if (i == 1) {
        f = fopen("/Users/mentxaka/eclipse-workspace/prueba/Debug/prueba.txt", "r"); //LECTURA
    }
    if (i == 2) {
        f = fopen("/Users/mentxaka/eclipse-workspace/prueba/Debug/prueba.txt", "a"); //ESCRITURA CONCATENADA A
    }
    return f;
}

//////////////////////////////////CIERRA FICHERO///////////////////////////////////

/**
 *
 * CIERRA EL FICHERO EN EL QUE GUARDAMOS TODOS LOS DATOS
 *
 * @PARAM f FICHERO EN EL QUE SE GUARDAN LOS FICHEROS
 *
 */
void cerrarFichero(FILE *f) {
    fclose(f);
}
