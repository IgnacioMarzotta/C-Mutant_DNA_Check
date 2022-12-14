//Tarea 1 - Algoritmos y Estructuras de Datos
//Ignacio Marzotta (23.601.779-6)
//Cristobal Zapata (19.962.025-8)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Definicion de estructura basica nodo
struct Node
{
    char data;
    struct Node *next;
};

typedef struct Node tNode;
typedef tNode *List;

//Funcion para crear un nuevo nodo
List createNode(char x)
{
    List aux;

    aux = malloc(sizeof(tNode));
    if (aux != NULL)
    {
        aux->data = x;
        aux->next = NULL;
    }
    else
    {
        printf("\n No se pudo reservar memoria suficiente para un nuevo nodo, el programa se va a cerrar.\n");
        system ( "PAUSE" );
        exit(1);
    }
    return aux;
}

//Funcion para insertar nuevo nodo con valor newValue en la lista L en posicion pos.
List insertInPosition(List L, int pos, char newValue)
{
    List pNode, aux;
    int i;

    pNode = createNode(newValue);
    if(pos == 1)
    {
        pNode->next = L;
        L = pNode;
    }
    else
    {
        aux = L;
        i = 1;
        while(i < pos-1)
        {
            aux = aux->next;
            i++;
        }
        pNode->next = aux->next;
        aux->next = pNode;
        aux = NULL;
    }
    pNode = NULL;
    return L;
}

//Funcion de chequeo de triple guanina
bool checkGuanina(List L)
{
    List aux;
    aux = L;
    int count = 0;
    while(aux != NULL)
    {
        if(aux->data == 'g')
        {
            count++;
            if(count == 3)
            {
                aux = NULL;
                return false;
            }
        }
        else
        {
            count = 0;
        }
        
        aux = aux->next;
    }
    aux = NULL;
    return true;
}

//Funcion de chequeo de Doble Adenina
bool checkAdenina(List L)
{
    List aux;
    aux = L;
    int count = 0;
    while(aux != NULL)
    {
        if(aux->data == 'a')
        {
            count++;
            if(count == 2)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
        
        aux = aux->next;
    }
    return false;
}

//Funcion de chequeo de Doble Citosina
bool checkCitosina(List L)
{
    List aux;
    aux = L;
    int count = 0;
    while(aux != NULL)
    {
        if(aux->data == 'c')
        {
            count++;
            if(count == 2)
            {
                return true;
            }
        }
        else
        {
            count = 0;
        }
        
        aux = aux->next;
    }
    return false;
}

//Funcion de chequeo de Timina final
bool checkTimina(List L)
{
    List aux;
    aux = L;
    while(aux != NULL)
    {
        if(aux->next == NULL && aux->data == 't')
        {
            aux = NULL;
            return true;
        }
        aux = aux->next;
    }
    aux = NULL;
    return false;
}

//Funcion extra encargada de asegurarse que los caracteres del archivo sean validos y pertenezcan a una cadena de ADN
bool charIsValid(char ch)
{
    char validInputs[] = {'a', 'c', 'g', 't',0}; 

    int i;
    for(i = 0; i < sizeof(validInputs) / sizeof(validInputs[0]); i++)
    {
        if(validInputs[i] == ch)
        {
            return true;
        }
    }
    return false;
}

//Lista que lee abre y lee el archivo de la cadena de ADN, y agrega cada char a la lista L
List readFile(List L)
{
    //Definicion nombre archivo
    char fileName[100]="";
    //Var temporal para lectura de caracteres de archivo
    char ch;

    //Pedir nombre de archivo a usuario
    printf("Ingresa el nombre del archivo: ");
    scanf("%s",&fileName);

    FILE *fp;
    int i=1;

    //Abrir archivo
    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        //Si no se puede reservar la memoria para el archivo, o no se encontro un archivo con ese nombre, cerrar programa.
        printf("Archivo invalido, el programa se va a cerrar. \n");
        system ( "PAUSE" );
        exit(1);
    }
    else
    {
        //Leer letra por letra hasta alcanzar fin de archivo
        while ((ch = fgetc(fp)) != EOF)
        {
            if(charIsValid(ch))
            {
                L=insertInPosition(L, i, ch);
                i++;
            }
            else
            {
                printf("\nSe detecto que el caracter %c en la cadena de ADN es invalido, el programa se va a cerrar.\n", ch);
                fclose(fp);
                system ( "PAUSE" );
                exit(1);
            }
        }
    }
    //Cerrar archivo
    fclose(fp);

    //Devolver lista llena
    return L;
}

int main()
{
    //Definicion inicial de lista vacia
    List L=NULL;

    //Popular la lista con los caracteres de la cadena de ADN
    L = readFile(L);

    //Para que un ADN sea mutante, tiene que cumplir con las 3 condiciones:
    //Poseer a lo mas 2 guaninas consecutivas. (Si posee 3 o mas, es humano)
    //Poseer al menos 2 adeninas o 2 citocinas consecutivas.
    //Terminar con una tiamina.
    if(checkGuanina(L) && checkTimina(L) && (checkCitosina(L) || checkAdenina(L)))
    {
        //Mostrar resultado mutante, terminar ejecucion.
        printf("\nMUTANTE\n\n");
        system ( "PAUSE" );
        return 0;
    }

    //Sino, es humano, terminar ejecucion.
    printf("\nHUMANO\n\n");
    system ( "PAUSE" );
    return 0;
}