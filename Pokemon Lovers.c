#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

void flushBufferOf(int option);
int selectYesNo();

typedef struct node
{
    char *detail;
    struct node* left;
    struct node* right;
} NODE;

NODE* createNode(char *value);
void insertCategory(NODE** root, char *value);
void insertLeft(NODE* root, char *value);
void insertRight(NODE* root, char *value);
void inorderTraversal(NODE* root);

NODE* createNode(char *value)
{
    NODE* newNode = malloc(sizeof(NODE));
    char *newDetail = (char*) calloc(20, sizeof(char));
    memcpy(newDetail, value, 20);
    newNode->detail = newDetail;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Insertar
//{
void insertLeft(NODE* root, char *value)
{
    root->left = createNode(value);
}

void insertRight(NODE* root, char *value)
{
    root->right = createNode(value);
}

//}
//{
void insertCategory(NODE** root, char *value)
{
    NODE* newCat = createNode(value);
    newCat->right = *root;
    *root = newCat;
}
//}
void inorderTraversal(NODE* root)
{
    if(root == NULL) return;
    inorderTraversal(root->left);
    printf("\n->%s", root->detail);
    inorderTraversal(root->right);
}

//Otros
//{
void flushBufferOf(int option)
{
    while((option = getchar()) != '\n' && option != EOF);
}
int selectYesNo()
{
    __label__ Incorrect;
    int tempOpt;
    printf("Ingrese 1 para sí o 2 para no: ");
Incorrect:
    while(!scanf("%i", &tempOpt))
    {
        printf("\nOpción incorrecta, vuelva a ingresar: ");
        flushBufferOf(tempOpt);
    }
    if(tempOpt != 1 && tempOpt != 2)
    {
        printf("\nOpción incorrecta, vuelva a ingresar: ");
        flushBufferOf(tempOpt);
        goto Incorrect;
    }
    return tempOpt;
}
//}
int main()
{
    __label__ Home, Loop, Again;
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    int option;
    char temp;
    char string[20];
    bool flag = true;
    bool flag2 = true;
    NODE* DB = createNode("Eléctrico");
    insertLeft(DB,"Pikachu");
    insertLeft(DB, "Tiene cola");
    insertRight(DB->left, "Pikachu");

    NODE* tmpNode;
Home:
    do
    {
        system("cls");
        printf("+++++Bienvenido a Pokemon Lovers+++++\n\n");
        printf("  1 - Encontrar un pokemon\n");
        printf("  2 - Detalle del juego\n");
        printf("  3 - Impresion de datos del árbol\n");
        printf("  4 - Salir del juego\n\n");
        printf(" Ingrese la opcion deseada: ");
        while(!scanf("%i", &option))
        {
            printf("\nOpción incorrecta, vuelva a ingresar: ");
            flushBufferOf(option);
        }
    }
    while(!(option == 1 || option == 2 || option == 3 || option == 4));
    if(option == 1)
    {
Again:
        tmpNode = DB;
        do
        {
            printf("\n¿Está pensando en un pókemon de tipo %s?\n", DB->detail);
            option = selectYesNo();
            if(option == 1)
            {
                DB = DB->left;
Loop:
                printf("\nTu pokemon, ¿%s?\n", DB->detail);
                option = selectYesNo();
                if(option != 1)
                {
                    if(DB->left == NULL) flag2 = false;
                    else
                    {
                        DB = DB->left;
                        goto Loop;
                    }
                }
                else
                {
                    printf("\n¿Estás pensando en %s?\n", DB->right->detail);
                    option = selectYesNo();
                    if(option != 1)
                    {
                        while(DB->left != NULL) DB = DB->left;
                        flag2 = false;
                    }
                    else
                    {
                        printf("\n\nHemos adivinado! ¿Deseas volver a jugar?\n");
                        option = selectYesNo();
                        DB = tmpNode;
                        if(option != 1) goto Home;
                        else goto Again;
                    }
                }
            }
            else
            {
                if(DB->right == NULL) flag = false;
                else DB = DB->right;
            }
        }
        while(flag && flag2);
        if(!flag)
        {
            DB = tmpNode;
            flag = true;
            printf("\n\n\n¿De qué tipo es el pokemon en el que piensas?\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertCategory(&DB, string);
            printf("\n¿Qué característica en especial tiene ese pokemón?\n");
            printf("e.g. <<Tiene cola>><<No puede caminar>><<Tiene colmillos>>\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertLeft(DB, string);
            printf("\n¿En qué pokemon estás pensando?\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertRight(DB->left, string);
        }
        else if(!flag2)
        {
            flag2 = true;
            printf("\n\n\n¿Qué característica en especial tiene ese pokemon que piensas?\n");
            printf("e.g. <<Tiene cola>><<No puede caminar>><<Tiene colmillos>>\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertLeft(DB, string);
            printf("\n¿En qué pokemon estás pensando?\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertRight(DB->left, string);
            DB = tmpNode;
        }
        printf("\n");
        goto Home;
    }
    else if(option == 2)
    {
        system("cls");
        printf("Detalles de Pokemon Lovers:\n");
        printf("\nLos Pokémon son una clase de criaturas inspiradas en animales reales,");
        printf("\n insectos, objetos, plantas o criaturas mitológicas,");
        printf("\n cada una de estas criaturas se pueden clasificar en diferentes tipos");
        printf("\n y tienen características diferentes.\n\n");
        printf("Se requiere crear una base de datos por medio de interrogantes que se hacen al usuario,");
        printf("\n se van quitando alternativas hasta que queda una. El objetivo es “instruir” a la base de datos,");
        printf("\n en un inicio la base de datos solo sabe un pokemon ");
        printf("\n y cuestionará si ese pokemon es el que el usuario está pensando,");
        printf("\n de lo contrario preguntará en que pokemon pensaba el usuario ");
        printf("\n y en qué lo diferencia del que nos “predice”,");
        printf("\n se debe hacer uno de arbol binario que despues de introducir cualquier dato");
        printf("\ npodrá predecir cualquier pokemon.\n\n");
        printf(">Presione cualquier tecla para regresar al menú<");
        _getche();
        goto Home;
    }
    else if(option == 3)
    {
        int cont=0;
        printf("\n\nImpresión del árbol (In-Order):\n");
        inorderTraversal(DB);
        printf("\n\n>Presione cualquier tecla para regresar al menú<");
        _getche();
        goto Home;
    }
    return 0;
}











