// Integrantes: Mariana Morales, Elias gonzalez, Catalina Ibanez

#include <stdio.h>
#include <stdlib.h>

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
        printf("La lista se encuentra vacia.\n");
        return;
    }
    nodo* temp = *cabeza;
    *cabeza = (*cabeza)->siguiente;
    free(temp);
}

// 6. Eliminar el último
void eliminarFinal(nodo** cabeza) {
    if (*cabeza == NULL) {
        printf("No queda mas para eliminar.\n");
        return;
    }
    if ((*cabeza)->siguiente == NULL) {
        free(*cabeza);
        *cabeza = NULL;
        return;
    }
    nodo* actual = *cabeza;
    while (actual->siguiente->siguiente != NULL) {
        actual = actual->siguiente;
    }
    free(actual->siguiente);
    actual->siguiente = NULL;
}

// 7. Imprimir lista
void imprimirLista(nodo* cabeza) {
    nodo* temp = cabeza;
    printf("\n=== Lista de publicaciones ===\n");
    while (temp != NULL) {
        printf("___________________\n");
        printf("ID: %d\n", temp->dato.ID);
        printf("Nombre: %s\n", temp->dato.nombre);
        printf("Título: %s\n", temp->dato.titulo);
        printf("Imagen: %s\n", temp->dato.imagen);
        printf("Me gusta: %d | Comentarios: %d | Compartido: %d\n",
            temp->dato.me_gusta, temp->dato.comentario, temp->dato.compartido);
        printf("___________________\n");
        temp = temp->siguiente;
    }
}

// Insertar una publicacion por ubicacion
void insertarPorUbicacion(nodo** cabeza, publicacion dato, int posicion) {
    nodo* nuevo = crearNodo(dato);
    if (posicion <= 1 || *cabeza == NULL) {
        nuevo->siguiente = *cabeza;
        *cabeza = nuevo;
        return;
    }
    nodo* actual = *cabeza;
    int i = 1;
    while (i < posicion - 1 && actual->siguiente != NULL) {
        actual = actual->siguiente;
        i++;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

// Eliminar una publicacion por ubicacion 
void eliminarPorUbicacion(nodo** cabeza, int posicion) {
    if (*cabeza == NULL || posicion < 1) {
        printf("La lista se encuentra vacia.\n");
        return;
    }
    nodo* temp;
    if (posicion == 1) {
        temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        return;
    }
    nodo* actual = *cabeza;
    int i = 1;
    while (i < posicion - 1 && actual->siguiente != NULL) {
        actual = actual->siguiente;
        i++;
    }
    if (actual->siguiente == NULL) {
        printf("La posicion no existe.\n");
        return;
    }
    temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    free(temp);
}

// mostrar publicacion ordenado por "me gusta" de mayor y menor
void ordenarPorMeGustamayor(nodo* cabeza) {
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
// mostrar publicacion ordenado por "me gusta" de menor a mayor
void ordenarPorMeGustamenor(nodo* cabeza) {
    int cambio;
    nodo* actual;
    do {
        cambio = 0;
        actual = cabeza;
        while (actual != NULL && actual->siguiente != NULL) {
            if (actual->dato.me_gusta > actual->siguiente->dato.me_gusta) {
                int temp = actual->dato.me_gusta;
                actual->dato.me_gusta = actual->siguiente->dato.me_gusta;
                actual->siguiente->dato.me_gusta = temp;
                cambio = 1;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

// iniciamos el programa
int main() {
    nodo* cabeza = NULL;
    char fotitos[100];
    int opcion, i;
    publicacion p;

FILE* archivo = fopen("status_ini_social_net.txt", "r");
if (archivo == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 1;
}
while (fscanf(archivo, "%d; %99[^;]; %99[^;]; %99[^;]; [%d, %d, %d];\n", //el 99 es para evitar desbordamiento, es un limitadorde lectura
            &p.ID, p.nombre, p.titulo, p.imagen,
            &p.me_gusta, &p.comentario, &p.compartido) == 7) {
    insertarFinal(&cabeza, p);
    printf("___________________\n");
    printf("ID: %d\n", p.ID);
    printf("Nombre: %s\n", p.nombre);
    printf("Título: %s\n", p.titulo);
    printf("Imagen: %s\n", p.imagen);
    printf("Me gusta: %d | Comentarios: %d | Compartido: %d\n",
        p.me_gusta, p.comentario, p.compartido);
    printf("___________________\n");
}

fclose(archivo);

    do {
        printf("\n      MENU RED SOCIAL       \n");
        printf("Bienvenido a esta red social, indiqueme la opcion que desea realizar: \n");
        printf("[1]. Aniadir una publicacion al inicio\n");
        printf("[2]. Aniadir una publicacion al final\n");
        printf("[3]. Eliminar primera publicacion\n");
        printf("[4]. Eliminar ultima publicacion\n");
        printf("[5]. Mostrar todas las publicaciones\n");
        printf("[6]. Ordenar por 'me gusta' de manera ascendente\n");
        printf("[7]. Ordenar por 'me gusta' de manera descendente\n");
        printf("[8]. Eliminar publicacion por ubicacion \n");
        printf("[9]. Insertar publicacion por ubicacion \n");
        printf("[10]. Cerrar aplicacion\n");
        printf("Seleccione una opcion del 1 al 10: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("ID: ");
                scanf("%d", &p.ID);
                getchar();
                printf("Nombre: ");
                fgets(p.nombre, sizeof(p.nombre), stdin);
                    for (i = 0; p.nombre[i] != '\0'; i++) {
                    if (p.nombre[i] == '\n') {
                    p.nombre[i] = '\0';
            break;
        }
    }
                printf("Título: ");
                fgets(p.titulo, sizeof(p.titulo), stdin);
                    for (i = 0; p.titulo[i] != '\0'; i++) {
                    if (p.titulo[i] == '\n') {
                    p.titulo[i] = '\0';
            break;
        }
    }
                printf("Ingrese Imagenes todas separadas entre comas: ");
                fgets(fotitos, sizeof(fotitos), stdin);
                i = 0;
                while (fotitos[i] != '\0') {
                    if (fotitos[i] == '\n') {
                    fotitos[i] = '\0';
            break;
        }
        i++;
    }
                sprintf(p.imagen, "[%s]", fotitos);
                printf("Me gusta: ");
                scanf("%d", &p.me_gusta);
                printf("Comentarios: ");
                scanf("%d", &p.comentario);
                printf("Compartido: ");
                scanf("%d", &p.compartido);
                insertarInicio(&cabeza, p);
            break;

            case 2:
                printf("ID: ");
                scanf("%d", &p.ID);
                getchar();
                printf("Nombre: "); 
                fgets(p.nombre, sizeof(p.nombre), stdin);
                    for (i = 0; p.nombre[i] != '\0'; i++) {
                    if (p.nombre[i] == '\n') {
                    p.nombre[i] = '\0';
            break;
        }
    }
                printf("Título: ");
                fgets(p.titulo, sizeof(p.titulo), stdin);
                    for (i = 0; p.titulo[i] != '\0'; i++) {
                    if (p.titulo[i] == '\n') {
                    p.titulo[i] = '\0';
            break;
        }
    }
                printf("Ingrese Imagenes todas separadas entre comas: ");
                fgets(fotitos, sizeof(fotitos), stdin);
                i = 0;
                while (fotitos[i] != '\0') {
                    if (fotitos[i] == '\n') {
                    fotitos[i] = '\0';
            break;
        }
        i++;
    }
                sprintf(p.imagen, "[%s]", fotitos);
                printf("Me gusta: ");
                scanf("%d", &p.me_gusta);
                printf("Comentarios: ");
                scanf("%d", &p.comentario);
                printf("Compartido: ");
                scanf("%d", &p.compartido);
                insertarFinal(&cabeza, p);
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
                ordenarPorMeGustamenor(cabeza);
                printf("Ordenado por 'me gusta' de manera ascendente\n");
                imprimirLista(cabeza);
                break;

            case 7:
                ordenarPorMeGustamayor(cabeza);
                printf("Ordenado por 'me gusta' de manera descendente\n");
                imprimirLista(cabeza);
                break;

            case 8:
                printf("Ingrese la ubicacion de la publicacion que desea eliminar: ");
                int posEliminar;
                scanf("%d", &posEliminar);
                eliminarPorUbicacion(&cabeza, posEliminar);
                break;

            case 9: {
                int posInsertar;
                printf("Ingrese la ubicacion donde quiere insertar la publicacion: ");
                scanf("%d", &posInsertar);
                getchar();
                printf("ID: ");
                scanf("%d", &p.ID);
                getchar();
                printf("Nombre: ");
                fgets(p.nombre, sizeof(p.nombre), stdin);
                    for (i = 0; p.nombre[i] != '\0'; i++) {
                    if (p.nombre[i] == '\n') {
                    p.nombre[i] = '\0';
            break;
        }
    }
                printf("Título: ");
                fgets(p.titulo, sizeof(p.titulo), stdin);
                    for (i = 0; p.titulo[i] != '\0'; i++) {
                    if (p.titulo[i] == '\n') {
                    p.titulo[i] = '\0';
            break;
        }
    }
                printf("Ingrese Imagenes todas separadas entre comas: ");
                fgets(fotitos, sizeof(fotitos), stdin);
                i = 0;
                while (fotitos[i] != '\0') {
                    if (fotitos[i] == '\n') {
                fotitos[i] = '\0';
            break;
        }
        i++;
    }
                sprintf(p.imagen, "[%s]", fotitos);
                printf("Me gusta: ");
                scanf("%d", &p.me_gusta);
                printf("Comentarios: ");
                scanf("%d", &p.comentario);
                printf("Compartido: ");
                scanf("%d", &p.compartido);
                insertarPorUbicacion(&cabeza, p, posInsertar);
            break;
}
            case 10:
                printf("Salir de la red social\n");
                break;
            default:
                printf("Opcion invalida\n");
                break;
        }
    } while (opcion != 10);

return 0;
}

