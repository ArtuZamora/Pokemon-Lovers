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
    printf("Ingrese 1 para s� o 2 para no: ");
Incorrect:
    while(!scanf("%i", &tempOpt))
    {
        printf("\nOpci�n incorrecta, vuelva a ingresar: ");
        flushBufferOf(tempOpt);
    }
    if(tempOpt != 1 && tempOpt != 2)
    {
        printf("\nOpci�n incorrecta, vuelva a ingresar: ");
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
    NODE* DB = createNode("El�ctrico");
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
        printf("  3 - Impresion de datos del �rbol\n");
        printf("  4 - Salir del juego\n\n");
        printf(" Ingrese la opcion deseada: ");
        while(!scanf("%i", &option))
        {
            printf("\nOpci�n incorrecta, vuelva a ingresar: ");
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
            printf("\n�Est� pensando en un p�kemon de tipo %s?\n", DB->detail);
            option = selectYesNo();
            if(option == 1)
            {
                DB = DB->left;
Loop:
                printf("\nTu pokemon, �%s?\n", DB->detail);
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
                    printf("\n�Est�s pensando en %s?\n", DB->right->detail);
                    option = selectYesNo();
                    if(option != 1)
                    {
                        while(DB->left != NULL) DB = DB->left;
                        flag2 = false;
                    }
                    else
                    {
                        printf("\n\nHemos adivinado! �Deseas volver a jugar?\n");
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
            printf("\n\n\n�De qu� tipo es el pokemon en el que piensas?\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertCategory(&DB, string);
            printf("\n�Qu� caracter�stica en especial tiene ese pokem�n?\n");
            printf("e.g. <<Tiene cola>><<No puede caminar>><<Tiene colmillos>>\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertLeft(DB, string);
            printf("\n�En qu� pokemon est�s pensando?\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertRight(DB->left, string);
        }
        else if(!flag2)
        {
            flag2 = true;
            printf("\n\n\n�Qu� caracter�stica en especial tiene ese pokemon que piensas?\n");
            printf("e.g. <<Tiene cola>><<No puede caminar>><<Tiene colmillos>>\n");
            scanf("%c", &temp);
            scanf("%20[^\n]s", string);
            insertLeft(DB, string);
            printf("\n�En qu� pokemon est�s pensando?\n");
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
        printf("\nLos Pok�mon son una clase de criaturas inspiradas en animales reales,");
        printf("\n insectos, objetos, plantas o criaturas mitol�gicas,");
        printf("\n cada una de estas criaturas se pueden clasificar en diferentes tipos");
        printf("\n y tienen caracter�sticas diferentes.\n\n");
        printf("Se requiere crear una base de datos por medio de interrogantes que se hacen al usuario,");
        printf("\n se van quitando alternativas hasta que queda una. El objetivo es �instruir� a la base de datos,");
        printf("\n en un inicio la base de datos solo sabe un pokemon ");
        printf("\n y cuestionar� si ese pokemon es el que el usuario est� pensando,");
        printf("\n de lo contrario preguntar� en que pokemon pensaba el usuario ");
        printf("\n y en qu� lo diferencia del que nos �predice�,");
        printf("\n se debe hacer uno de arbol binario que despues de introducir cualquier dato");
        printf("\ npodr� predecir cualquier pokemon.\n\n");
        printf(">Presione cualquier tecla para regresar al men�<");
        _getche();
        goto Home;
    }
    else if(option == 3)
    {
        int cont=0;
        printf("\n\nImpresi�n del �rbol (In-Order):\n");
        inorderTraversal(DB);
        printf("\n\n>Presione cualquier tecla para regresar al men�<");
        _getche();
        goto Home;
    }
    return 0;
}











