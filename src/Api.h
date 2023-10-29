#ifndef API_H_
#define API_H_

////////////////////////////////////////////////////////ESTRUCTURAS/////////////////////////////////////////////////////////////

typedef struct{
    int id;
    char* resp;
} Respuesta;

typedef struct{
    int id;
    char* preg;
    int nResp;
    Respuesta *respuestas;
} Pregunta;

typedef struct{
    int id;
    char* tit;
    char* desc;
    int ver;
    char* fecha;
    int nPreg;
    Pregunta *preguntas;
} Formulario;

typedef struct{
    int nObjetos;
    Formulario *objetos;
} ArrayList;

char* usu;
char* cont;

////////////////////////////////////////////////////////PARTE DE C/////////////////////////////////////////////////////////////

int inputNumero(int size);
char *inputString(int size);

void CASO1(ArrayList *f);
void anadirEspacio(ArrayList *f);
void printF(ArrayList *f);
char* sysdate();
void CASO1_1(ArrayList *f);
void CASO1_2(ArrayList *f);
int getUnidad(int numero);
int getDecena(int numero);
int getCentena(int numero);

///////////////////////////////////////////////////////PARTE DE C++////////////////////////////////////////////////////////////

void CASO2();
void CASO3();
void CASO4();
void CASO5();
void CASOEXIT();


#endif
