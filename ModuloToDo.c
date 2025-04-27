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
void moverNodoTarea(Nodo **Lista,Nodo **ListaRealizadas,int id);
void consultarTarea(Nodo **ListaPendientes,Nodo **ListaRealizadas,int id);

int main(){
    int realizada = 0,seguir = 0, consulta = 0;
    Nodo *ListaPendientes = crearListaVacia();
    Nodo *ListaRealizadas = crearListaVacia();

    pedirTareas(&ListaPendientes);
    printf("\nLista de tareas pendientes:\n");
    mostrarLista(&ListaPendientes);

    
    printf("Desea actualizar tareas realizadas?\n 1.Si 0.No");
    scanf("%i",&seguir);

    while (ListaPendientes && seguir != 0)
    {
        printf("Ingrese el id de la tarea que ya realizo: ");
        scanf("%i",&realizada);

        moverNodoTarea(&ListaPendientes,&ListaRealizadas,realizada);

        printf("\nLista de tareas Realizadas:\n");
        mostrarLista(&ListaRealizadas);
        printf("\nLista de tareas pendientes actualizada:\n");
        mostrarLista(&ListaPendientes);
        printf("\nQuiere seguir completando tareas?\n1.Si 0.No");
        scanf("%i", &seguir);
    }

    printf("Ingrese el id de la tarea a consultar");
    scanf("%i",&consulta);
    consultarTarea(&ListaPendientes,&ListaRealizadas,consulta);

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
        idTarea += 1;
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
        printf("Id: %i;Duracion: %ihs;\n",Aux->Tarea.TareaID,Aux->Tarea.Duracion);
        Aux = Aux->Siguiente;
    }
    
}

void moverNodoTarea(Nodo **ListaPendientes,Nodo **ListaRealizadas, int id)
{
    Nodo *Aux = *ListaPendientes;
    Nodo *Ant = Aux;
    while (Aux && Aux->Tarea.TareaID != id)
    {
        Ant = Aux;
        Aux = Aux->Siguiente;
    }

    if (Aux)
    {
        if (Aux == *ListaPendientes)
        {
            *ListaPendientes = Aux->Siguiente;
        }
        else{
           Ant->Siguiente = Aux->Siguiente;
        }
        Aux->Siguiente = NULL;
        agregarNodo(ListaRealizadas,Aux);
    }
    
}

void consultarTarea(Nodo **ListaPendientes, Nodo **ListaRealizadas, int id)
{
    int lista = 0;
    Nodo *Aux = *ListaPendientes;   
    while (Aux && Aux->Tarea.TareaID != id)
    {
        Aux = Aux->Siguiente;
    }
    if (Aux)
    {
        lista = 1;
    }
    else
    {
        Aux = *ListaRealizadas;
        while (Aux && Aux->Tarea.TareaID != id)
        {
            Aux = Aux->Siguiente;
        }
        if (Aux)
        {
            lista = 2;
        }
    }
    
    if (Aux)
    {
        printf("Tarea: ");
        puts(Aux->Tarea.Descripcion);
        printf("Id: %i;Duracion: %ihs;\n",Aux->Tarea.TareaID,Aux->Tarea.Duracion);
        printf("\nPertenecia a la lista de ");   
        switch (lista)
        {
        case 1:printf("Pendientes");
            break;
        case 2:printf("Realizadas");
            break;
        }
    }
    
}
