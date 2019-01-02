#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos primero una estructura que tenga un entero, un caracter y un string. Lo haremos con typedef

typedef struct datos
{
	int id;
	char letra;
	char nombre[20];
	struct datos* next;
} datos;

// Esta segunda estructura hace de contenedor para la primera, de esta forma, tenemos siempre presente cual es la cabeza de la lista

typedef struct lista
{
	struct datos* head;
} lista;

int is_empty(datos * head);
datos* crear_nodo_teclado();
datos* crear_nodo(int id, char letra, char nombre[20]);
int son_iguales(datos* node_1, datos* node_2);
int comparar_nodos_por_nombre(datos* node_1, datos* node_2);
void crear_lista(datos** head);
void invertir_lista(datos** head);
void invertir_lista_recursivo(datos **head, datos* prev, datos* cur, datos* next);
void insertar_adelante(datos **head, datos* new_node);
void insertar_atras(datos **head, datos* new_node);
void insercion_ordenada(datos **head, datos* new_node);
void insertar_atras_aux(datos* cur_node, datos* new_node);
void insertar_atras_recursivo(datos **head, datos* new_node);
void insercion_ordenada_aux(datos* cur_node, datos* new_node);
void insercion_ordenada_recursiva(datos **head, datos* new_node);
int borrar_nodo_por_id(datos** head, int id);
int eliminar_ocurrencias(datos** head, int id);
void borrar_comunes(datos **head_1, datos* head_2);
void imprimir_lista(datos* head);
