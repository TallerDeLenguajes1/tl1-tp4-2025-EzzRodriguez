#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  
    int Duracion; // entre 10 – 100  
}Tarea;  

typedef struct Nodo{ 
    Tarea Tarea;  
    struct Nodo *Siguiente;  
}Nodo; 

Nodo *crearListaVacia();
Nodo *crearNodo(Tarea *tarea);
void agregarNodo(Nodo **Lista,Nodo *nodo);
void pedirTareas(Nodo **Lista);
void mostrarLista(Nodo **Lista);


int main(){
    Nodo *ListaPendientes = crearListaVacia();
    Nodo *ListaRealizadas = crearListaVacia();

    pedirTareas(&ListaPendientes);
    printf("\nLista de tareas pendientes:\n");
    mostrarLista(&ListaPendientes);

}

Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(Tarea *tarea)
{
    Nodo *nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo->Tarea = *tarea;
    nodo->Siguiente = NULL;
    return nodo;
}

void agregarNodo(Nodo **Lista, Nodo *nodo)
{
    nodo->Siguiente = *Lista;
    *Lista = nodo;
}

void pedirTareas(Nodo **Lista)
{
    int bandera = 1,idTarea = 1000;
    while (bandera == 1)
    {
        Tarea *tareaNueva = (Tarea*) malloc(sizeof(Tarea));
        char *descripcion = (char*)malloc(sizeof(char)*100);
        
        tareaNueva->TareaID = idTarea;
        idTarea ++;
        printf("\nIngrese la descripcion de la tarea: ");
        gets(descripcion);
        tareaNueva->Descripcion = (char*)malloc(sizeof(char)*strlen(descripcion));
        strcpy(tareaNueva->Descripcion,descripcion);
        printf("\nIngrese la duracion (en hs) de la tarea: ");
        scanf("%i",&(tareaNueva->Duracion));

        Nodo *nodoTarea = crearNodo(tareaNueva);
        agregarNodo(Lista,nodoTarea);

        
        printf("\nQuiere seguir agregando tareas?\n1.Si 0.No");
        scanf("%i", &bandera);
        fflush(stdin);
    }
    
}

void mostrarLista(Nodo **Lista)
{
    Nodo *Aux = *Lista;
    while (Aux)
    {
        printf("Tarea: ");
        puts(Aux->Tarea.Descripcion);
        printf("Id: %i;Duracion: %i;\n",Aux->Tarea.TareaID,Aux->Tarea.Duracion);
        Aux = Aux->Siguiente;
    }
    
}
