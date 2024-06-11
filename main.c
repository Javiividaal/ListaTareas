#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo{
  char * tarea;
  int hora;
  int minuto;
  int estado; // ESTADO = 0; SIN COMPLETAR / ESTADO == 1; COMPLETADO
  struct Nodo * sig;
  
};
typedef struct Nodo * NodoPtr;

NodoPtr crea_lista(){
    NodoPtr nuevo = malloc(sizeof(struct Nodo ) );
    nuevo->sig = NULL;
    nuevo->estado = 0;
    
  return nuevo;
}

void inserta_tarea(NodoPtr lista, char * tareaNueva, int hora, int minuto){
  NodoPtr nuevo = malloc(sizeof(struct Nodo) );
  nuevo->sig = lista->sig;
  nuevo->estado = 0;
  nuevo->hora = hora;
  nuevo->minuto = minuto;
  nuevo->tarea = tareaNueva;
  lista->sig = nuevo;

}
NodoPtr ordena_lista(NodoPtr lista){
    NodoPtr nuevo = crea_lista(); // Crea una nueva lista para almacenar los elementos ordenados
    NodoPtr aux = lista->sig;
    while(aux != NULL){
        NodoPtr siguiente = aux->sig;
        NodoPtr actual = nuevo; 
        
        // Insertar el nodo actual en la lista ordenada según su hora y minuto
        while (actual->sig != NULL && 
               (actual->sig->hora < aux->hora || 
               (actual->sig->hora == aux->hora && actual->sig->minuto < aux->minuto))) {
            actual = actual->sig;
        }
        
        
        aux->sig = actual->sig;
        actual->sig = aux;
        
        aux = siguiente;
    }
    
    return nuevo;
}

void imprime_lista(NodoPtr lista){
  if(lista->sig == NULL){
    printf("No hay tareas pendientes \n");
    return;
  }
  NodoPtr imprimir = ordena_lista(lista);
  NodoPtr aux = imprimir->sig;
  int contador = 1;
  while(aux != NULL){
    printf("%d - %d:%d - %s - ",contador,aux->hora, aux->minuto,aux->tarea );
    if(aux->estado == 0){
      printf(" Sin completar \n");
      
    }else{printf("Completado \n");}
    
    aux = aux->sig;
    contador = contador + 1;
  }
  
}
void cambiar_estado_tarea(NodoPtr lista, int tarea){
  NodoPtr aux = lista->sig;
  tarea = tarea-1;
  int i = 0;
  while(aux!=NULL && i < tarea){
    aux = aux->sig;
    i = i+1;
  }
  if(aux->estado == 0){
    aux->estado = 1;
  }else{
    aux->estado = 0;
  }
}

char * copia_cadena(char *tarea){
  int n = strlen(tarea);
  char*nuevo = malloc(sizeof(char) * (n+1));
  int i = 0;
  while(i < n){
    nuevo[i] = tarea[i];
    i = i+1;
  }
  nuevo[n] = '\0';
  return nuevo;  
}
void eliminar_tarea(NodoPtr lista, int tarea ){ //EMPIEZA EN 0
tarea = tarea-1;
NodoPtr aux = lista;
int i = 0;
  while(aux->sig != NULL && i<tarea){
    aux = aux->sig;
    i = i+1;
  }
  if(aux->sig != NULL){
    NodoPtr borrar = aux->sig;
    aux->sig = borrar->sig;
    free(borrar->tarea);
    free(borrar);
  }
  
}

int main(){
int accion = 0;
  NodoPtr lista = crea_lista();
  while(accion == 0){
  printf("\n\n\n----------- TO DO LIST -----------\n");
  printf("           Elige acción \n");
  printf("1- Consultar lista de tareas\n");
  printf("2- Añadir una tarea nueva\n");
  printf("3- Eliminar tarea\n");
  printf("4- Cambiar estado de la tarea\n");
  printf("5- Salir\n");
  printf("----------------------------------\n");
  
  scanf("%d", &accion);
  getchar();
  if(accion == 1){imprime_lista(lista); accion = 0;}
  if(accion == 2){
    char tarea[100];
    printf("Introduce la nueva tarea \n");
    fgets(tarea, 100, stdin);
    tarea[strcspn(tarea, "\n")] = '\0';
    char * tareacop = copia_cadena(tarea);
    int hora = -1;
    int minuto = -1;
    while(hora > 23 || hora < 0){
    printf("Introduce hora: ");
    scanf("%d", &hora);
    }
    while(minuto < 0 || minuto > 59){
    printf("Introduce minuto: ");
    scanf("%d", &minuto);
    }
    inserta_tarea(lista, tareacop, hora, minuto);
    printf("Tarea añadida\n");
    accion = 0;
    
  }
  if(accion == 3){
    int borrar = 0;
    if(lista->sig != NULL){
    printf("Selecciona la tarea a eliminar \n");
    }
    imprime_lista(lista);
    if(lista->sig != NULL){
    scanf("%d",&borrar);
    eliminar_tarea(lista,borrar);
    printf("Tarea eliminada\n");
    }
    accion = 0;
    
  }
  if(accion == 4){
    int cambiar = 0;
    if(lista->sig != NULL){
    printf("Selecciona la tarea a cambiar \n");
    }
    imprime_lista(lista);
    if(lista->sig != NULL){
    scanf("%d",&cambiar);
    cambiar_estado_tarea(lista,cambiar);
    printf("Tarea actualizada\n");
    }
    accion = 0;
  }
  if(accion == 5){ return 0;}
  }
return 0;
}
