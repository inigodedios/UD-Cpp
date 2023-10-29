//
//  main.c
//  EncuestasUD
//
//  Created by Mentxaka on 7/4/21.
//

#include "sqlite3.h"

#include "main.h"
#include "Usuario.h"
#include "Entrevistado.h"
#include <stdio.h>
#include <stdlib.h>
extern "C" {
	#include "Api.h"
	#include "Text.h"
	#include "BaseDeDatos.h"
}

//int main()	{
//
//    int result;
//
//    result = abrir();
//
//
//    ///ESCRITURA INICIAL DE LOS DATOS QUE HAY EN EL FICHERO
//    ArrayList *f;
//    FILE* infile = abrirFichero(1);
//    ArrayList temp = readFormulario(infile);
//    f = &temp;
//    nF = getNFormularios();
//    cerrarFichero(infile);
//
//    ///IMPRIME LOS FORMULARIOS LEIDOS DEL FICHERO AL INICIAR EL PROGRAMA
//    printF(f);
//
//    ///BUCLE PRINCIPAL DEL PROGRAMA
//    int boolean = 1;
//    while(boolean){
//        printf("\n********************************************************************************\n\nBienvenido a EncuestasUD! \n\nSeleccione las siguientes opciones:\n1. Iniciar sesion\n2. Realizar encuesta\n3. Visualizar estadisticas\n4. Registrar nuevo usuario\n5. Salir\n\n");
//        int intr = inputNumero(1);
//        switch (intr){
//            case 1:
//                CASO1(f);///CREACION DE FORMULARIO -- HECHO
//            break;
//
//            case 2:
//                CASO2();///REALIZACION DE ENCUESTA -- IÑIGO
//            break;
//
//            case 3:
//                CASO3();///VISUALIZACION DE ESTADISTICAS --
//            break;
//
//            case 4:
//                CASO4(); ///REGISTRO DE USUARIO -- HECHO
//            break;
//
//            case 5:
//                CASO5();///SALIR
//                boolean = 0;
//            break;
//
//            default:
//                CASOEXIT();
//                boolean = 0;
//            break;
//
//        }
//    }
//
//    ///ESCRITURA FINAL EN FICHERO
//    FILE* outfile = abrirFichero(0);
//    writeFormulario(f, outfile);
//    cerrarFichero(outfile);
//
//    ///IMPRIME LOS FORMULARIOS ESCRITOS EN EL FICHERO
//    printF(f);
//    result = cerrar();//TODO NO FUNCIONA DE MANERA CORRECTA (AJENO AL FUNCIONAMIENTO DEL PROGRAMA)
//    return 0;
//}

//int main()	{
//
//    sqlite3 *db;
//    int result;
//
//    result = abrir();
//
//    //LEE DE LA BASE DE DATOS EL OBJETO Y DEPENDIENDO DE SU TIPO TE DICE SI EXISTE O NO
//    //              TIPO 1 = FORMULARIO
//    //              TIPO 2 = PREGUNTA
//    //              TIPO 3 = RESPUESTA
//    printf("Lectura y comprobacion\n\n");
//    printf("Form 1: %i\n",existe(1,1));
//    printf("Form 2: %i\n",existe(2,1));
//    printf("Form 3: %i\n",existe(3,1));
//    printf("Form 4: %i\n",existe(4,1));
//    printf("Form 5: %i\n",existe(5,1));
//    printf("Preg 1: %i\n",existe(11,2));
//    printf("Preg 22: %i\n",existe(22,2));
//    printf("Preg 34: %i\n",existe(34,2));//NO EXISTE
//    printf("Resp 111: %i\n",existe(111,3));
//    printf("Resp 555: %i\n",existe(543,3));//NO EXISTE
//    //COMPRUEBA SI EXISTE EL USUARIO QUE SE PASA POR PARAMETRO
//    printf("Usu pPicapiedra: %i\n",existeUsu("pPicapiedra"));
//    //REGISTRA UN USUARIO EN LA BBDD DESPUES DE COMPROBAR SI EXISTE O NO
//    printf("USU prueba: %i\n", escribeU(getNUsuarios()+1,"oBubu","meGustaIrDePicnic"));
//    //ESCRIBE CADA UNA DE LAS COSAS
//    printf("nFor: %i\n",getNFormularios());
//    printf("FORM 9: %i\n", escribeF(8,"oBubu"));
//    printf("PREG 9: %i\n", escribeP(81,8));
//    printf("RESP 9: %i\n", escribeR(811,81));
//    //ESCRIBE UN ENTREVISTADO CON SU ID UNICAMENTE
//    printf("nEntr 1: %i\n",getNEntrevistados());
//    printf("Entrevistado 1: %i\n", escribeE(getNEntrevistados()+1, 14));
//    //ESCRIBE RESPUESTA DADA POR ENTREVISTADO
//    printf("RespuestaDada: %i\n",escribeSeleccion( getNEntrevistados(),811));
//    //DEVUELVE LA EDAD DEL ENTREVISTADO SOLICITADO POR PARAMETRO
//    printf("Edad del entrevistado 2: %i\n",getEdad(getNEntrevistados()));
//    //DEVUELVE EL NUMERO DE FORMULARIOS
//    printf("nFor: %i\n",getNFormularios());
//    //DEVUELVE EL NUMERO DE FORMULARIOS
//    printf("nPreg: %i\n",getNPreguntas(1));
//    //DEVUELVE EL NUMERO DE FORMULARIOS
//    printf("nResp: %i\n",getNRespuestas(11));
//    //DEVUELVE EL NUMERO DE VECES QUE SE HA SELECCIONADO LA RESPUESTA POR PARARMETRO
//    printf("nSelect: %i\n",getNSeleccionda(811));
//
//    result = cerrar();
//
//    return 0;
//}

int main()	{
    sqlite3 *db;
    int result;

    result = abrir();

    Entrevistado e(99,40);
    escribeE(e.getId(),e.getEdad());
    e.imprimir();
    Usuario u(99,"nick","pass");
    escribeU(u.getId(), u.getNick(),u.getPassword());
    u.imprimir();

    return 0;
}


//for(formularios){
//    n = formularios[i].nPreg;
//    for(preguntas){
//        n = preguntas[i].nResp;
//        print(preguntaActual.preg)
//        for(respuestas){
//            print(respuestaActual.resp);
//            n = getNSeleccionda(respuestaActual.id);
//            print("R i ha sido seleccionada; ")
//            for(i<n){
//                print("|");
//            }
//        }
//}
//}