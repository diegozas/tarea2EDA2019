#include "arbol.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

String ruta(char a[]){
    String aux=new struct str_nodo;
    String pos=aux;
    int i=0;
    char c = a[0];
    while(c!='\0'){
        int j=i;
        char d[MAX];
		i++;
        c=a[i];
        while(c!='/' && c!='\0'){
            d[i-j-1]=a[i];
            i++;
            c=a[i];
        }
        d[i-j-1]='\0';
        strcpy(pos->nombre,d);
        if(c=='\0'){
            pos->sig=NULL;
        }
        else{
            pos->sig=new struct str_nodo;
            pos=pos->sig;
        }
    }
    return aux;
}

void Imprimir(String a){
    String aux=a;
    while(aux!=NULL){
        printf("%s\n",aux->nombre);
        aux=aux->sig;
    }

}
void borrar(String &l){
    String aux = l->sig;
    delete l;
    l = aux;
}

void borrarString(String& l){
	if(l!=NULL){
		borrar(l);
		borrarString(l);
	}
}

Systema crear(){
    AB aux=new str_ab;
	strcpy(aux->nombre,"/");
	aux->padre=NULL;
	aux->hijo=NULL;
	aux->hermano=NULL;
	aux->a=crear1();
	Systema s=new struct str_sys;
	s->raiz=aux;
	s->actual=aux;
	return s;
}

void insertar(AB &a, char n[]){
    AB aux=a;
    if (aux->hijo==NULL){
        aux->hijo = new struct str_ab;
        aux=aux->hijo;
        strcpy(aux->nombre,n);
        aux->hermano = NULL;
        aux->hijo = NULL;
        aux->padre=a;
        aux->a=crear1();
    }else if (strcmp(aux->hijo->nombre,n)>0){
        AB str = new struct str_ab;
        strcpy(str->nombre,n);
        str->hermano = aux->hijo;
        str->hijo = NULL;
        str->padre=a;
        aux->hijo=str;
        str->a=crear1();
    }else if (strcmp(aux->hijo->nombre,n)<0){
        aux=aux->hijo;
        while((aux->hermano!=NULL)&&(strcmp(aux->hermano->nombre,n) < 0)){
            aux=aux->hermano;
        }
        AB str = new struct str_ab;
        strcpy(str->nombre,n);
        str->hermano = aux->hermano;
        str->hijo = NULL;
        str->padre=a;
        aux->hermano=str;
        str->a=crear1();
    }
}

AB mover(AB a, char n[]){
    while((a!=NULL) && (strcmp(a->nombre,n)!=0)){
        a=a->hermano;
    }
    return a;
}

void borrarAB(AB& a){
    if(a->hijo!=NULL){
        borrarAB(a->hijo);
    }
    if(a->hermano!=NULL){
        borrarAB(a->hermano);
    }
    borrarListaArchivo(a->a);
    delete a;
    a=NULL;
}

bool rmdr(AB a,char nombre[]){
	  if(a->hijo!=NULL){
        if(strcmp(a->hijo->nombre,nombre)==0){
            AB d=a->hijo;
            a->hijo=a->hijo->hermano;
            d->hermano=NULL;
            d->padre=NULL;
            borrarAB(d);
            return true;
		}
	}
    if(existe(a,nombre)){
        AB aux=a->hijo;
        while(strcmp(aux->hermano->nombre,nombre)!=0){
            aux=aux->hermano;
        }
        AB d=aux->hermano;
        aux->hermano=aux->hermano->hermano;
        d->hermano=NULL;
        d->padre=NULL;
        borrarAB(d);
        return true;
    }else{
        return false;
    }
}

bool rmda(Systema a,char dir[]){
    if(dir[1]!='\0'){
        String s=ruta(dir);
        AB aux=a->actual;   //te guardas la posicion actual
        a->actual=a->raiz;  //vas a la raiz
        bool flag=true;
        while ((s->sig!=NULL)&&flag){
            flag=cdr(a,s->nombre);
            s=s->sig;
        }
        if(flag){
            flag=rmdr(a->actual,s->nombre);
            borrarString(s);
        }else{
        	borrarString(s);
            flag=false;
        }
        a->actual=aux;  //volves al directorio que estabas
        return flag;
    }else{
        return false;
    }
}

bool cda(Systema &a,char dir[]){
    if(dir[1]!='\0'){
        String s=ruta(dir);
        AB aux=a->raiz;
        bool flag=true;
        while (flag){ //(a->sig!=NULL)&&(aux->hijo!=NULL)
            if((s!=NULL)&&(aux->hijo!=NULL)){
                aux= mover(aux->hijo,s->nombre);
                if((aux==NULL)||(s->sig==NULL)){
                    flag=false;
                }else{
                    s=s->sig;
                }
            }
        }
        borrarString(s);
        if(aux!=NULL){
        	a->actual=aux;
        	return true;
        	
		}else{
			return false;
		}
        
    }
}

bool cdr(Systema &a,char dir[]){
    AB aux=a->actual;
    aux=mover(aux->hijo,dir);
    if(aux!=NULL){
        a->actual=aux;
        return true;
    }else{
        return false;
    }
}

TipoRet CD (Systema &a, char dir[],char error[]){
    bool flag;
    if((dir[0]=='/') && (dir[1]=='\0')){
        a->actual = a->raiz;
        return OK;
    }
    else if((dir[0]=='/') && (dir[1]!='\0')){
        flag=cda(a,dir);
        strcpy(error,"ERROR: no existe la ruta ingresada");
    }else{
        flag=cdr(a,dir);
        strcpy(error,"ERROR: no existe el subdirectorio ingresado");
    }
    if(flag){
        return OK;
    }else{
        return ERROR;
    }
}

bool existe(AB a, char nombre[]){
    AB aux=a->hijo;
    if(strcmp(a->nombre,nombre)==0){
    	return true;
	}else{
		while((aux!=NULL) && (strcmp(aux->nombre,nombre)!=0)){
        	aux=aux->hermano;
		}
    	if(aux==NULL){
       	    return false;
    	}else{
        	return true;
    	}
    }
}

bool mkr(AB a,char nombre[]){
    if(existe(a,nombre)){
        return false;
    }else{
        insertar(a,nombre);
        return true;
    }
}
bool mka(Systema a,char dir[]){
    if(dir[1]!='\0'){
        String s=ruta(dir);
        AB aux=a->actual;   //te guardas la posicion actual
        a->actual=a->raiz;  //vas a la raiz
        bool flag=true;
        while ((s->sig!=NULL)&&flag){
            flag=cdr(a,s->nombre);  //te moves a la ultima carpeta ya creada
            s=s->sig;
        }
        flag=mkr(a->actual,s->nombre);    //creas la carpeta nueva
        a->actual=aux;  //volves al directorio que estabas
        borrarString(s);
        return flag;
    }else{
        return false;
    }
}

TipoRet MKDIR (Systema &a, char dir[],char error[]){
    bool flag;
    if(dir[0]=='/'){
        flag=mka(a,dir);
        strcpy(error,"ERROR: no existe la ruta ingresada");
    }else{
        flag=mkr(a->actual,dir);
        strcpy(error,"ERROR: ya existe un directorio con ese nombre");
    }
    if(flag){
        return OK;
    }else{
        return ERROR;
    }

}

TipoRet RMDIR (Systema &s, char dir[],char error[]){
    bool flag;
    if(dir[0]=='/'){
        flag=rmda(s,dir);
        strcpy(error,"ERROR: no existe la ruta ingresada");
    }else if(dir[0]!='/'){
       flag=rmdr(s->actual,dir);
    	strcpy(error,"ERROR: no existe un directorio con ese nombre");

 	}
    if(flag){
        return OK;
    }else{
        return ERROR;
    }
}

TipoRet DIR (Systema &s){
    AB aux=s->actual->hijo;
    imprimirListaArchivo(s->actual->a);
    if(aux==NULL){
        printf("Vacio\n");
    }else{
    	while(aux!=NULL){
        	printf("%s     Directorio\n",aux->nombre);
        	aux=aux->hermano;
    }
    return OK;
    }
}

void imprimirRuta(AB a){
    AB aux=a;
	if(aux!=NULL){
		imprimirRuta(aux->padre);
		if(aux->padre!=NULL){
            printf("/%s",aux->nombre);
		}
	}
}

TipoRet PWD(Systema &a){
	AB aux=a->actual;
	if(aux->padre==NULL){
		printf("/");
		return OK;
	}else{ 
		imprimirRuta(aux);
		return OK;
	}
}






//Archivos



ListaArchivo crear1(){
	ListaArchivo aux  = new struct sistema;
	aux->primero = NULL;
	aux->ultimo  = NULL;
	return aux;
}


bool isEmpty(ListaArchivo s){
    return s->primero == NULL;
}

bool existe(ListaArchivo s,char nombreArchivo[]){
	bool repetido = false;
	Archivo aux = s->primero;
	while(aux!=NULL && !repetido){
		if(strcmp(nombreArchivo,aux->nombre)==0){
			repetido = true;
		}else{
			aux=aux->sig;
		}
	}
	return repetido;
}

Contenido crearTexto(){
    Contenido aux = new struct lineas;
    aux->primero = NULL;
    aux->ultimo = NULL;
    return aux;
}

void insPrincipio(ListaArchivo &s, char nombreArchivo[]){
		Archivo aux = new struct str_archivo;
		strcpy(aux->nombre,nombreArchivo);
		aux->c=crearTexto();
		aux->ant = NULL;
		aux->sig = s->primero;
		if(s->primero != NULL){
        	aux->sig->ant = aux;
    	}else{
        	s->ultimo = aux;
    	}
    	s->primero = aux;
}


void borrarUltimoContenido(Contenido a){
		if(a->ultimo!=NULL){
		if(a->ultimo->ant != NULL){
        	a->ultimo = a->ultimo->ant;
        	delete a->ultimo->sig;
        	a->ultimo->sig = NULL;
    	}else{
        	delete a->ultimo;
        	a->primero = NULL;
        	a->ultimo = NULL;
    	}
	}
}
int Tam(Archivo a){
    int i = 0;
    if(a->c->primero==NULL){
        return 0;
    }else{
        Linea aux = a->c->primero;
        while(aux != NULL){
            i = i + strlen(aux->texto);
            aux = aux->sig;
        }
    }
    return i;
}


void borrarPrimerContenido(Contenido a){
    if(a->primero!=NULL){
		if(a->primero->sig != NULL){
            a->primero=a->primero->sig;
        	delete a->primero->ant;
            a->primero->ant = NULL;
        }else{
            delete a->primero;
            a->primero = NULL;
            a->ultimo = NULL;
        }
	}
}

void insFinalContenido(Archivo &a, char texto[]){
    Linea l = new struct linea;
    strcpy(l->texto, texto);
    l->sig = NULL;
    l->ant = a->c->ultimo;
    if(a->c->primero == NULL){
        a->c->primero = l;
    }else{
        a->c->ultimo->sig = l;
    }
    a->c->ultimo = l;
}

void insPrincipioContenido(Archivo &a, char texto[]){
    Linea l = new struct linea;
    strcpy(l->texto, texto);
    l->ant = NULL;
    l->sig = a->c->primero;
    if(a->c->ultimo == NULL){
        a->c->ultimo = l;
    }else{
        a->c->primero->ant = l;
    }
    a->c->primero = l;
}

void insFinal(ListaArchivo &s, char nombreArchivo[]){
	Archivo aux=new struct str_archivo;
    strcpy(aux->nombre,nombreArchivo);
   	aux->c=crearTexto();
	aux->sig=NULL;
    aux->ant=s->ultimo;
    if(s->ultimo!=NULL){
        aux->ant->sig=aux;
    }else{
        s->primero=aux;
    }
    s->ultimo=aux;
}


void insertarOrdenado(ListaArchivo &s,char nombreArchivo[]){
    bool inserte=false;
    if(isEmpty(s)){
        insPrincipio(s,nombreArchivo);
        inserte=true;
    }else if(strcmp(s->ultimo->nombre,nombreArchivo)>0){
        insFinal(s,nombreArchivo);
        inserte=true;
    }else{
        Archivo aux = s->primero;
        while (aux!=NULL && !inserte){
            if(strcmp(aux->nombre,nombreArchivo)<0){
                if(aux->ant == NULL){
                    insPrincipio(s,nombreArchivo);
                    inserte=true;
                }else{
                    Archivo aux2 = new struct str_archivo;
                    strcpy(aux2->nombre,nombreArchivo);
                  	aux2->c=crearTexto();
                    aux2->sig = aux;
                    aux2->ant = aux->ant;
                    aux->ant->sig = aux2;
                    aux->ant = aux2;
                    inserte=true;
                }

            }else{
                aux=aux->sig;
            }

        }
    }
}

TipoRet CREATE (Systema& s, char nombreArchivo[],char error[]){
		if(existe(s->actual->a,nombreArchivo)){
			strcpy(error,"ERROR: ya existe un archivo con ese nombre");
			return ERROR;
        }else{
            insertarOrdenado(s->actual->a,nombreArchivo);
            return OK;
			}
}

void borrarPrimero(ListaArchivo s){
    if (s->primero->sig != NULL){
        s->primero = s->primero->sig;
        delete s->primero->ant;
        s->primero->ant = NULL;
    }else{
        delete s->primero;
        s->primero = NULL;
        s->ultimo = NULL;
    }

}

void borrarUltimo(ListaArchivo s){
    if(s->ultimo->ant!=NULL){
        s->ultimo=s->ultimo->ant;
     	delete s->ultimo->sig;
        s->ultimo->sig=NULL;
    }else{
    	delete s->ultimo;
    	s->primero=NULL;
    	s->ultimo=NULL;

	}
}

TipoRet DELETE (Systema &s, char nombreArchivo[],char error[]){
	bool borre=false;
	if(existe(s->actual->a,nombreArchivo)){
		Archivo aux=s->actual->a->primero;
    	while(aux!=NULL && !borre){
    		if(strcmp(aux->nombre,nombreArchivo)==0){
           		if(aux->ant==NULL){
                    borrarContenido(aux->c);
                	borrarPrimero(s->actual->a);
                	borre=true;
            	}else if(aux->sig == NULL){
                    borrarContenido(aux->c);
                    borrarUltimo(s->actual->a);
                	borre=true;
            	}else{
                	Archivo aux2 = aux->sig;
                	aux2->ant=aux->ant;
                	aux->ant->sig=aux2;
                    borrarContenido(aux->c);
                	delete aux;
                	borre=true;
            	}
        	}else{
            	aux=aux->sig;
        	}
    	}
		return OK;
	}else{
		strcpy(error,"ERROR: no existe un archivo con ese nombre");
		return ERROR;
	}
}

void imprimirListaArchivo(ListaArchivo s){
	Archivo aux=s->ultimo;
	int i;
	if(aux==NULL){
		printf("Lista de Archivos vacia\n");
	}else{
		while(aux!=NULL){
			i=Tam(aux);
			printf("%s    Archivo     %d\n",aux->nombre,i);
			aux=aux->ant;
		}
	}
}
bool comillas(char texto[]){
	if(texto[0]!='"'){
		return false;
	}else{
		int comillas=1;
		int i=1;
		while(texto[i]!='\0'){
			if(texto[i]=='"'){
				comillas++;
			}
			i++;
		}

		if(comillas==2){
			return true;
		}else{
			return false;
		}
	}
}

void cargarArreglo(char a[],char b[]){
	int i=1;
	while(a[i]!='"'){
        b[i-1]=a[i];
		i++;
	}
	b[i-1]='\0';
}

TipoRet TYPE (Systema s,char nombreArchivo[],char error[]){
    Archivo aux=s->actual->a->primero;
    if(existe(s->actual->a,nombreArchivo)){
        while(aux!=NULL){
            if(strcmp(aux->nombre,nombreArchivo)==0){
                Linea l = aux->c->primero;
                if(l != NULL){
                    while(l != NULL){
                        cout << l->texto <<endl;
                        l = l->sig;
                    }
                }else{
                    strcpy(error, "El archivo esta vacio.");
                    return ERROR;
                }
            }
            aux = aux->sig;
        }
    }else{
        strcpy(error, "ERROR: El archivo no existe.");
        return ERROR;
    }
    return OK;
}

TipoRet IF (Systema &s, char nombreArchivo[], char texto[],char error[]){
   	Archivo aux=s->actual->a->primero;
    bool inserte=false;
    if(existe(s->actual->a,nombreArchivo)){
        if(comillas(texto)){
            while(aux!=NULL&& !inserte){
                if(strcmp(aux->nombre,nombreArchivo)==0){
                    char b[250];
                    cargarArreglo(texto,b);
                    insFinalContenido(aux,b);
                    inserte=true;
                }else{
                	aux=aux->sig;
            	}
            }
            return OK;
        }else{
            strcpy(error,"ERROR: El texto no esta entre comillas");
            return ERROR;
        }
    }else{
        strcpy(error,"ERROR: El archivo no existe");
        return ERROR;
    }
}


TipoRet IC (Systema &s, char nombreArchivo[], char texto[],char error[]){
   	Archivo aux=s->actual->a->primero;
    bool inserte=false;
    if(existe(s->actual->a,nombreArchivo)){
        if(comillas(texto)){
            while(aux!=NULL&& !inserte){
                if(strcmp(aux->nombre,nombreArchivo)==0){
                    char b[250];
                    cargarArreglo(texto,b);
                   	insPrincipioContenido(aux,b);
                    inserte=true;
                }else{
                	aux=aux->sig;
            	}
            }
            return OK;
        }else{
            strcpy(error,"ERROR: El texto no esta entre comillas");
            return ERROR;
        }
    }else{
        strcpy(error,"ERROR: El archivo no existe");
        return ERROR;
    }
}

TipoRet BC (Systema &s,char nombreArchivo[], int k,char error[]){
	Archivo aux=s->actual->a->primero;
	bool noborre=true;
	if(existe(s->actual->a,nombreArchivo)){
		if(aux->c->primero==NULL){
			strcpy(error,"El archivo esta vacio\n");
			return ERROR;
		}else{
		while(aux!=NULL && noborre){
			if(strcmp(aux->nombre,nombreArchivo)==0){
                Contenido a = aux->c;
				while(a->primero!=NULL && k!=0){
					borrarPrimerContenido(a);
					k--;
				}
				noborre=false;
			}else{
            	aux=aux->sig;
            }

		 }
		return OK;
		
		}
	}else{
		strcpy(error,"ERROR: No existe un archivo con ese nombre\n");
		return ERROR;
	}

}

TipoRet BF (Systema &s,char nombreArchivo[], int k,char error[]){
	Archivo aux=s->actual->a->primero;
	bool noborre=true;
	if(existe(s->actual->a,nombreArchivo)){
		if(aux->c->primero==NULL){
			strcpy(error,"El archivo esta vacio\n");
			return ERROR;
		}else{
		while(aux!=NULL && noborre){
			if(strcmp(aux->nombre,nombreArchivo)==0){
                Contenido a = aux->c;
				while(a->ultimo!=NULL && k!=0){
					borrarUltimoContenido(a);
					k--;
				}
				noborre=false;
			}else{
                    aux=aux->sig;
                }

		 }
		return OK;
		}
	}else{
		strcpy(error,"ERROR: No existe un archivo con ese nombre\n");
		return ERROR;
	}

}

TipoRet CAT (Systema &s,char nombre1[],char nombre2[],char error1[]){
		Archivo aux=s->actual->a->primero;
		Archivo a1=NULL;
		Archivo a2=NULL;
		if(existe(s->actual->a,nombre1)){
			if(existe(s->actual->a,nombre2)){
				if(strcmp(nombre1,nombre2)==0){
					strcpy(error1,"ERROR: Los archivos deben ser distintos");
					return ERROR;
				}else{
				while(aux!=NULL && (a1==NULL || a2==NULL)){
                    if(strcmp(aux->nombre,nombre1)==0){
                        a1 = aux;
                    }
                    else if(strcmp(aux->nombre,nombre2)==0){
                        a2 = aux;
                    }
                    aux=aux->sig;
				}
				Linea l = a2->c->primero;
				while(l!=NULL){
                    insFinalContenido(a1,l->texto);
                    l=l->sig;
				}
				return OK;
			}
			}else{
                strcpy(error1,"ERROR: No existe el archivo 2");
                return ERROR;
			}
		}else{
            strcpy(error1,"ERROR: El archivo 1 no existe");
            return ERROR;
		}
	return OK;
}

void borrarCabezal2(Contenido c){
    if((c->primero==NULL)&& (c->ultimo==NULL)){
        delete c;
        c=NULL;
    }
}

void borrarCabezal(ListaArchivo a){
    if((a->primero==NULL) && (a->ultimo==NULL)){
        delete a;
        a=NULL;
    }

}

void borrarContenido(Contenido c){
	Contenido aux=c;
	while (aux->primero!=NULL){
		borrarPrimerContenido(aux);
	}
	borrarCabezal2(aux);
}

void borrarListaArchivo(ListaArchivo a){
	while (a->primero!=NULL){
		Contenido aux=a->primero->c;
		borrarContenido(aux);
        borrarPrimero(a);
    }
    borrarCabezal(a);
}
