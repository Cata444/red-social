// Integrantes: Mariana Morales, Elias gonzalez, Catalina Ibanez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int ID; 
    char nombre[100];
    char titulo[100];
    char imagen[100];
    int me_gusta;
    int comentario;
    int compartido;
} publicacion;

// 1. Definición del nodo
typedef struct nodo {
    publicacion dato;
    struct nodo* siguiente;
} nodo;

// 2. Crear un nuevo nodo
nodo* crearNodo(publicacion dato) {
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

// 3. Insertar al principio
void insertarInicio(nodo** cabeza, publicacion dato) {
    nodo* nuevo = crearNodo(dato);
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

// 4. Insertar al final
void insertarFinal(nodo** cabeza, publicacion dato) {
    nodo* nuevo = crearNodo(dato);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
    } else {
        nodo* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// 5. Eliminar el primero
void eliminarPrimero(nodo** cabeza) {
    if (*cabeza == NULL) {
        printf("Lista vacia, no hay nada que eliminar.\n");
        return;
    }

    nodo* temp = *cabeza;
    *cabeza = (*cabeza)->siguiente;
    printf("Eliminado el primer nodo con valor: %d\n", temp->dato);
    free(temp);
}

// 6. Eliminar el último
void eliminarFinal(nodo** cabeza) {
    if (*cabeza == NULL) {
        printf("No queda mas para eliminar \n");
        return;
    }

    if ((*cabeza)->siguiente == NULL) {
        printf("Eliminado el unico nodo con valor: %d\n", (*cabeza)->dato);
        free(*cabeza);
        *cabeza = NULL;
        return;
    }

    nodo* actual = *cabeza;
    while (actual->siguiente->siguiente != NULL) {
        actual = actual->siguiente;
    }

    printf("Eliminado el ultimo nodo con valor: %d\n", actual->siguiente->dato);
    free(actual->siguiente);
    actual->siguiente = NULL;
}

// 7. Imprimir lista
void imprimirLista(nodo* cabeza) {
    nodo* temp = cabeza;
    printf("\n=== Lista de publicaciones ===\n");
    while (temp != NULL) {
        printf("ID: %d | Nombre: %s | Titulo: %s | Imagen: %s\n", 
               temp->dato.ID, temp->dato.nombre, temp->dato.titulo, temp->dato.imagen);
        printf("Me gusta: %d | Comentarios: %d | Compartido: %d\n", 
               temp->dato.me_gusta, temp->dato.comentario, temp->dato.compartido);
        printf("___________________\n");
        temp = temp->siguiente;
    }
}

// mostrar publicacion ordenado por algo ej "me gusta", "comentarios", "compartidos"

void ordenarPorMeGusta(nodo* cabeza) {
    int cambio;
    nodo* actual;
    do {
        cambio = 0;
        actual = cabeza;
        while (actual != NULL && actual->siguiente != NULL) {
            if (actual->dato.me_gusta < actual->siguiente->dato.me_gusta) {
                int temp = actual->dato.me_gusta;
                actual->dato.me_gusta = actual->siguiente->dato.me_gusta;
                actual->siguiente->dato.me_gusta = temp;
                cambio = 1;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

void ordenarPorComentarios(nodo* cabeza) {
    int cambio;
    nodo* actual;
    do {
        cambio = 0;
        actual = cabeza;
        while (actual != NULL && actual->siguiente != NULL) {
            if (actual->dato.comentario < actual->siguiente->dato.comentario) {
                int temp = actual->dato.comentario;
                actual->dato.comentario = actual->siguiente->dato.comentario;
                actual->siguiente->dato.comentario = temp;
                cambio = 1;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

void ordenarPorCompartido(nodo* cabeza) {
    int cambio;
    nodo* actual;
    do {
        cambio = 0;
        actual = cabeza;
        while (actual != NULL && actual->siguiente != NULL) {
            if (actual->dato.compartido < actual->siguiente->dato.compartido) {
                int temp = actual->dato.compartido;
                actual->dato.compartido = actual->siguiente->dato.compartido;
                actual->siguiente->dato.compartido = temp;
                cambio = 1;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

int main() {
    nodo* cabeza = NULL;
    char linea[300];
    int opcion;
    publicacion p;

    FILE* archivo;

archivo = fopen("status_ini_social_net.txt", "r");

if (archivo == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 1;
}

while (!feof(archivo)) {
    int resultado = fscanf(archivo, "%d; %99[^;]; %99[^;]; %99[^;]; [%d, %d, %d];\n",
                           &p.ID, p.nombre, p.titulo, p.imagen,
                           &p.me_gusta, &p.comentario, &p.compartido);

    if (resultado == 7) {
        insertarFinal(&cabeza, p);
    } else {
        // Limpia línea malformada
        fgets(linea, sizeof(linea), archivo);
    }
}

fclose(archivo);

    do {
        printf("\n── ✦ ── MENU RED SOCIAL ── ✦ ──\n");
        printf("1. Añadir una publicacion al inicio\n");
        printf("2. Añadir una publicacion al final\n");
        printf("3. Quitar primera publicación\n");
        printf("4. Quitar última publicación\n");
        printf("5. Mostrar todas las publicaciones\n");
        printf("6. Ordenar por me gusta\n");
        printf("7. Ordenar por comentarios\n");
        printf("8. Ordenar por compartido\n");
        printf("9. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
case 1:
    printf("ID: ");
    scanf("%d", &p.ID);

    printf("Nombre: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);

    printf("Título: ");
    fgets(p.titulo, sizeof(p.titulo), stdin);

    printf("Imagen: ");
    fgets(p.imagen, sizeof(p.imagen), stdin);

    printf("Me gusta: ");
    scanf("%d", &p.me_gusta);

    printf("Comentarios: ");
    scanf("%d", &p.comentario);

    printf("Compartido: ");
    scanf("%d", &p.compartido);

    insertarInicio(&cabeza, p);
    printf("Publicación agregada al inicio.\n");
    break;

case 2:
    printf("ID: ");
    scanf("%d", &p.ID);

    printf("Nombre: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);

    printf("Título: ");
    fgets(p.titulo, sizeof(p.titulo), stdin);

    printf("Imagen: ");
    fgets(p.imagen, sizeof(p.imagen), stdin);

    printf("Me gusta: ");
    scanf("%d", &p.me_gusta);

    printf("Comentarios: ");
    scanf("%d", &p.comentario);

    printf("Compartido: ");
    scanf("%d", &p.compartido);

    insertarFinal(&cabeza, p);
    printf("Publicación agregada al final.\n");
    break;
            case 3:
                eliminarPrimero(&cabeza);
                break;

            case 4:
                eliminarFinal(&cabeza);
                break;

            case 5:
                imprimirLista(cabeza);
                break;

case 6:
    ordenarPorMeGusta(cabeza);
    printf("Lista en orden decresciente por me gusta\n");
    imprimirLista(cabeza);
    break;

case 7:
    ordenarPorComentarios(cabeza);
    printf("Lista ordenada por comentarios.\n");
    imprimirLista(cabeza);
    break;

case 8:
    ordenarPorCompartido(cabeza);
    printf("Lista ordenada por compartido.\n");
    imprimirLista(cabeza);
    break;

            case 9:
                printf("Cerrar programa\n");
                break;

            default:
                printf("Indique una opción valida\n");
                break;
        }
    } while (opcion != 9);

    return 0;
}