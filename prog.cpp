#include "arbol.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
int main(){
	bool seguir=true;
	Systema s;
	s=crear();
	TipoRet a;
	char a1[MAX];
    while(seguir){
    	cin >>a1;
    	if(strcmp(a1,"MKDIR")==0||strcmp(a1,"mkdir")==0){
    		char p1[MAX];//guardo la ruta absoluta o relativa
			char p2[MAX];//guardo el mensaje de error
			cin >> p1;
			a=MKDIR(s,p1,p2);
			if(a==ERROR){
				cout<<p2<<endl;
			}
		}
		else if(strcmp(a1,"CD")==0||strcmp(a1,"cd")==0){
			char j1[MAX];//guardo la ruta absoluta o relativa
			char j2[MAX];//guardo el mensaje de error
			cin >>j1;
			a=CD(s,j1,j2);
			if(a==ERROR){
				cout<<j2<<endl;
			}
		}
		else if(strcmp(a1,"RMDIR")==0||strcmp(a1,"rmdir")==0){
			char q1[MAX];//guardo la ruta absoluta o relativa
			char q2[MAX];//guardo el mensaje de error
			cin>>q1;
			a=RMDIR(s,q1,q2);
			if(a==ERROR){
				cout<<q2<<endl;
			}
		}
		else if(strcmp(a1,"DIR")==0||strcmp(a1,"dir")==0){
			a=DIR(s);
        }
		else if(strcmp(a1,"PWD")==0||strcmp(a1,"pwd")==0){
			a=PWD(s);
			printf("\n");
		}
		else if (strcmp(a1, "CREATE") == 0||strcmp(a1,"create")==0){
        	char nombre_archivo[250];
        	cin >> nombre_archivo;
        	char b[250];
        	a=CREATE(s,nombre_archivo,b);
        	if(a==ERROR){
        		cout<<b;
        		printf("\n");
        	}
    	}
		else if(strcmp(a1,"DELETE")==0||strcmp(a1,"delete")==0){
			char r[250];
			char nombre_archivo1[250];
        	cin >> nombre_archivo1;
        	a=DELETE(s,nombre_archivo1,r);
        	if(a==ERROR){
                cout<<r<<endl;
        	}

		}
		else if(strcmp(a1,"TYPE")==0||strcmp(a1,"type")==0){
            char error[250];
            char nombre_nombrearchivo2[250];
            cin>>nombre_nombrearchivo2;
            a=TYPE(s,nombre_nombrearchivo2,error);
            if(a == ERROR){
                cout <<error <<endl;
            }
		}
		else if(strcmp(a1,"IF")==0||strcmp(a1,"if")==0){
			char s1[250];//guardo el nombre del arcivo
			char s2[250];//guardo el texto a ingresar
			char s3[250];//guardo el mensaje de error
			int i;
			scanf("%s ",&s1);//guarda el caracter espacio entre el nombre del archivo y el texto a ingresar
			cin.getline(s2,250);
			a=IF(s,s1,s2,s3);
			if(a==ERROR){
				cout<<s3<<endl;
			}
		}
		else if(strcmp(a1,"IC")==0||strcmp(a1,"ic")==0){
			char s1[250];//guardo el nombre del arcivo
			char c;
			char s2[250];//guardo el texto a ingresar
			char s3[250];//guardo el mensaje de error
			scanf("%s ",&s1);//guarda el caracter espacio entre el nombre del archivo y el texto a ingresar
			cin.getline(s2,250);
			a=IC(s,s1,s2,s3);
			if(a==ERROR){
				cout<<s3<<endl;
			}

		}
		else if(strcmp(a1,"BC")==0||strcmp(a1,"bc")==0){
			char g1[250];//guardo el nombre del archivo
			char g2[250];//guardo el mensaje de error
			int q;
			cin>>g1;
			cin>>q;
			a=BC(s,g1,q,g2);
			if(a==ERROR){
				cout<<g2;
			}
		}
		else if(strcmp(a1,"BF")==0||strcmp(a1,"bf")==0){
            char t1[250];//guarda el nombre del archivo
            char t2[250];//guarda el mensaje de error
            int v;
            cin>>t1;
            cin>>v;
            a=BF(s,t1,v,t2);
            if(a==ERROR){
                cout<<t2;
            }
        }
		else if(strcmp(a1,"CAT")==0||strcmp(a1,"cat")==0){
			char r1[250];//guardo el nombre del primer archivo
			char r2[250];//guardo el nombre del segundo archivo
			char r3[250];//guardo el mensaje de error
			cin>>r1;
			cin>>r2;
			a=CAT(s,r1,r2,r3);
			if(a==ERROR){
				cout<<r3<<endl;
			}

		}
		else if(strcmp(a1,"CLEAR")==0 || strcmp(a1,"clear")==0){
			system("cls");
		}
		else if(strcmp(a1,"EXIT")==0 || strcmp(a1,"exit")==0){
			seguir=false;
		}
    a1[0]='\0';
    }
return 0;}
