#ifndef ARBOL_H
#define ARBOL_H
#define MAX 250
#define TEXTO_MAX 256
#include <string.h>
#define MAX1 50

struct linea{
    char texto[TEXTO_MAX];
	struct linea * ant;
    struct linea * sig;
};

typedef struct linea* Linea;

struct lineas{
    Linea  primero;
    Linea  ultimo;
};

typedef struct lineas* Contenido;

struct str_archivo{
	char nombre[20];
	Contenido c;
	struct str_archivo * sig;
	struct str_archivo * ant;
};

typedef struct str_archivo * Archivo;

struct sistema{
	Archivo primero;
	Archivo ultimo;
};

typedef struct sistema* ListaArchivo;


struct str_nodo{
    char nombre[MAX];
    struct str_nodo * sig;

};

typedef struct str_nodo * String;


struct str_ab{
    char nombre[15];
    ListaArchivo a;
    str_ab * hermano;
    str_ab * hijo;
    str_ab * padre;
};
typedef struct str_ab * AB;

struct str_sys{
    AB raiz;
    AB actual;

};

typedef struct str_sys * Systema;


enum retorno{
	OK, ERROR, NO_IMPLEMENTADA
};

typedef enum retorno TipoRet;

//pre:n/a
//post:crea un Systema vacio
Systema crear();
//post:borra el primer elemento de la lista String
void borrar(String &l);
//post:borra la lista String
void borrarString(String& l);
//post:guarda la ruta absoluta que pasan en el main
String ruta(char a[]);
//post:inserta ordenadamente un directorio hijo
void insertar(AB &a, char n[]);
//post:si el directorio actual tiene un hijo se mueve a el
AB mover(AB a, char n[]);
//post:si la ruta absoluta es valida retorna true y se mueve hasta el sub directorio dado
bool cda(Systema &a,char dir[]);
//post:si el directorio tiene un hijo valido retorna true y se mueve a el
bool cdr(Systema &a,char dir[]);
//post:retorna true si ya existe un sub directorio con el mismo nombre en el directorio actual
bool existe(AB a, char nombre[]);
//post:si no existe un hijo en el directorio acutal con el mismo nombre retorna true y crea un sub directorio vacio
bool mkr(AB a,char nombre[]);
//post:si la ruta absoluta es valida retorna true y crea un subdirectorio vacio
bool mka(AB a,char dir[]);
//post:imprime la ruta desde la raiz al directorio actual
void imprimirRuta(AB a);

void borrarAB(AB& a);


bool rmda(Systema a,char dir[]);
bool rmdr(AB a,char nombre[]);

TipoRet PWD(Systema &a);
TipoRet CD(Systema &a, char dir[],char error[]);
TipoRet MKDIR(Systema &a, char dir[],char error[]);
TipoRet DIR (Systema &s);
TipoRet RMDIR(Systema &a, char dir[],char error[]);


void Imprimir(String a);




//Archivos

//pre:n/a
//post: devuelve una Lista de Archivos vacia
ListaArchivo crear1();

//pre:El sistema debe estar creado
//post:crea un archivo vacio en el Sistema y lo inserta ordenado
TipoRet CREATE (Systema& s, char nombreArchivo[],char error[]);

//pre:el sistema debe estar creado
//post:borra un archivo del sistema
TipoRet DELETE (Systema &s, char nombreArchivo[],char error[]);

//pre:El sistema debe estar creado
//post:devuelve true si ya existe un archivo con el mismo nombre
bool existe(ListaArchivo s,char nombreArchivo[]);

//pre:El sistema debe estar creado
//post:inserta al principio del sistema un nuevo archivo
void insPrincipio(ListaArchivo &s, char nombreArchivo[]);

//pre:El sistema debe estar creado
//post:inserta al final del sistema un nuevo archivo
void insFinal(ListaArchivo &s, char nombreArchivo[]);

//pre:El sistema debe estar creado
//post:inserta ordenadamente un archivo al sistema
void insertarOrdenado(ListaArchivo &s,char nombreArchivo[]);

//pre:El sistema debe estar creado
//post:devuelve true si el sistema esta vacio
bool isEmpty(ListaArchivo s);

//pre:El sistema debe estar creado
//post:borra el primer elemento del sistema
void borrarPrimero(ListaArchivo s);

//pre:El sistema debe estar creado
//post:borra el ultimo elemento del sistmea
void borrarUltimo(ListaArchivo s);

//pre:el sistema debe estar creado
//post:devuelve true si el texto esta escrito entre comillas ej:"Esto es un ejemplo"
bool comillas(char texto[]);

//pre:n/a
//post:devuelve un arreglo sin las comillas
void cargarArreglo(char a[],char b[]);

//pre:el sistema debe estar creado
//post:devuelve la cantidad de carecteres del archivo
int Tam(Archivo a);


//pre:el sistema debe estar creado
//post:inserta al comienzo del archivo el texto
TipoRet IC (Systema &s, char nombreArchivo[], char texto[]);

//pre:el sistema debe estar creado
//post:imprime el nombre del archivo y el tamaño que tiene
void imprimirListaArchivo(ListaArchivo s);

//pre:el sistema debe estar creado
//post:imprime el contenido del archivo
TipoRet TYPE(Systema s,char nombreArchivo[], char error[]);

//pre:el sistema debe estar creado
//post:inserta al final del archivo el nuevo texto
TipoRet IF (Systema &s, char nombreArchivo[], char texto[],char error[]);

//pre:el sistema debe estar creado
//post:inserta al principio del archivo el nuevo texto
TipoRet IC (Systema &s, char nombreArchivo[], char texto[],char error[]);


//pre:el sistema debe estar creado
//post:concatena el archivo 2 al archivo 1
TipoRet CAT (Systema &s,char nombre1[],char nombre2[],char error1[]);

//pre:el sistema debe estar creado
//post:borra las k primeras lineas del archivo
TipoRet BC (Systema &s,char nombreArchivo[], int k,char error[]);

//pre:el sistema debe estar creado
//post:borra las k ultimas lineas del archivo
TipoRet BF (Systema &s,char nombreArchivo[], int k,char error[]);



//pre:el sistema debe estar creado
//post:devuelve un contenido vacio
Contenido crearTexto();

//pre:el sistema debe estar creado
//post:borra la ultima linea del archivo
void borrarUltimoContenido(Contenido c);

//pre:el sistema debe estar creado
//post:borra la primera linea del archivo
void borrarPrimerContenido(Contenido c);

//pre:el sistema debe estar creado
//post:inserta una linea al final del archivo
void insFinalContenido(Archivo &a, char texto[]);

//pre:el sistema debe estar creado
//post:inserta una linea inicio del archivo
void insPrincipioContenido(Archivo &a, char texto[]);

void borrarContenido(Contenido c);

void borrarListaArchivo(ListaArchivo a);

void borrarCabezal(ListaArchivo a);//ListaArchivo
void borrarCabezal2(Contenido c); //Lista de Contenido


#endif//ARBOL_H
