#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Este modelo esta orientado a ser como el código que les dio la profesora. Trabajaremos las listas usando solo las cabezas.



// Definimos primero una estructura que tenga un entero, un caracter y un string. Lo haremos con typedef

typedef struct datos
{
	int id;
	char letra;
	char nombre[20];
	struct datos* next;
} datos;


// Utilidades 	


// Retorna 1 si la lista esta vacía, 0 de lo contrario
int is_empty(datos * lista)
{
	// Si la cabeza de la  lista es NULL
	return lista == NULL;
}


// Funcion para crear un nodo pidiendo los atributos por teclado.
datos* crear_nodo_teclado()
{
	// Creamos el nodo
	datos* new_node = (datos*)malloc(sizeof(datos));

	// Aislamos el nodo
	new_node->next = NULL;

	// Pedimos el id por teclado
	printf("Ingrese un numero identificador para el nodo: ");
	scanf("%d", &new_node->id)
	fflush(stdin);

	// Pedimos la letra por teclado
	char letra;
	printf("\nIngrese una letra para el nodo: ");
	// Limpiamos el buffer antes de pedir un char
	fflush(stdin);
	scanf("%c", &new_node->letra);
	fflush(stdin);


	// Pedimos el nombre por teclado.
	printf("\nIngrese el nombre para el nodo: ");
	// Aqui usamos fgets. Es lo mismo que gets, pero mas seguro. Por lo que lei, gets ya no se usa en ningun lado y el
	// compilador arroja muchas advertencias al usarlo.
	fgets(new_node->nombre, 20, stdin);
	// Por las dudas, dejo comentado el uso de gets aquí:
	//gets(nombre);
	fflush(stdin);

	return new_node;

}

// Funcion para crear un nodo pasando los atributos como argumentos de la funcion

datos* crear_nodo(int id, char letra, char nombre[20])
{
	// Creamos el nodo
	datos* new_node = (datos*)malloc(sizeof(datos));
	
	// Aislamos el nodo
	new_node->next = NULL;

	// Llenamos los datos con lo que nos pasaron por parametros
	new_node->id = id;
	new_node->letra = letra;
	strcpy(new_node->nombre, nombre);

	return new_node;
}

// Verifica si dos nodos tienen la misma información, es decir, si son "iguales"

int son_iguales(datos* node_1, datos* node_2)
{
	return 	node_1->id == node_2->id 		&&
			node_1->letra == node_2->letra	&&
			strcmp(node_1->nombre, node_2->nombre) == 0;
}

// Esta función retorna 1, si nodo_1->nombre es mayor o igual que nodo_2->nombre
int comparar_nodos_por_nombre(datos* node_1, datos* node_2)
{
	// Recordar que strcmp(a,b) retorna 1 si a > b, 0 si a == b y -1 si a < b. 
	// Al considerar los >= 0, tomamos el 0 y el 1, es decir, mayor o igual.

	return strcmp(node_1->nombre, node_2->nombre) >= 0; 
}



// Función para asignarle NULL a un nodo
void crear_lista(datos** head)
{
	*head = NULL;
}

// Invertir una lista enlazada (Version iterativa)

// ANIMACION DEL ALGORITMO: https://www.geeksforgeeks.org/wp-content/uploads/RGIF2.gif


void invertir_lista(datos** head)
{
	// Guardia!
	if(is_empty(*head)) return;

	// Creamos 3 auxiliares:
	//	- prev: Nodo anterior al nodo que tenemos en este momento (Convengamos que el prev de la cabeza es NULL)
	//	- cur: Nodo que tenemos en este momento
	//	- next: Siguiente al nodo que tenemos en este momento (Lo inicializamos en NULL, pero en el ciclo se le asigna un valor)
	datos *prev = NULL, *cur = *head, *next = NULL;

	while(cur != NULL)
	{
		// Actualizamos el siguiente
		next = cur->next;

		// El siguiente de cur ahora será prev
		cur->next = prev;

		// El anterior será el actual ahora y el actual será el siguiente
		prev = cur;
		cur = next;

	}

	// Si cur es NULL, entonces prev es el último nodo de la lista original y el primero de la lista invertida.
	*head = prev;
}

// Invertir una lista enlazada (Versión recursiva)

void invertir_lista_recursivo(datos **head, datos* prev, datos* cur, datos* next)
{
	// Guardia!
	if(is_empty(*head)) return;

	//Condición de parada
	// Si cur es NULL, entonces prev es el último nodo de la lista original y el primero de la lista invertida.
	if(cur == NULL)
	{
		*head = prev;
		return ;
	}

	// Actualizamos el siguiente
	next = cur->next;

	// El siguiente de cur ahora será prev
	cur->next = prev;

	// El anterior será el actual ahora y el actual será el siguiente
	prev = cur;
	cur = next;

	// Llamada recursiva
	invertir_lista_recursivo(head, prev, cur, next);
}

// La inserción adelante es un caso especial, no es iterativa ni recursiva. 
void insertar_adelante(datos **head, datos* new_node)
{
	// El siguiente del nuevo nodo ahora es la cabeza
	new_node->next = *head;
	// La cabeza es ahora el nuevo nodo
	*head = new_node;
}

/************************
  Inserciones iterativas
*************************/
//////////////////////////////////////////////////////////////////////////////////////

void insertar_atras(datos **head, datos* new_node)
{

	// Si la lista esta vacía, le asignamos el nuevo nodo a la cabeza de una vez
	if(is_empty(head))
	{
		*head = new_node;
		return;
	}


	// Definimos un auxiliar para iterar sobre la lista.
	datos *aux = *head;

	// Iteramos hasta posicionarnos en el último
	while(aux->next != NULL) aux = aux->next;

	// El siguiente del último será ahora el nuevo nodo
	aux->next = new_node;

}

//////////////////////////////////////////////////////////////////////////////////////

// Inserción ordenada

void insercion_ordenada(datos **head, datos* new_node)
{
	// Guardia!
	if(is_empty(*head))
	{
		*head = new_node;
		return;
	}

	// Definimos un auxiliar para iterar sobre la lista.
	datos *aux = *head;

	// Buscamos el nodo anterior al primero que sea mayor o igual al que tratamos de insertar
	while(aux->next != NULL)
	{
		// Si el siguiente es mayor o igual al nodo que trato de insertar, sal del ciclo
		if(comparar_nodos_por_nombre(new_node, aux->next)) break;
	}

	// CASO 1: aux->next es NULL y por ende, el nodo que trato de insertar es mayor a todos los de la lista

	if(aux->next == NULL)
	{
		aux->next = new_node;
	}

	// CASO 2: aux->next NO es NULL y tenemos que insertar el nodo justo antes del primero mayor o igual.

	else
	{
		// El siguiente del nuevo nodo será el siguiente del que tenemos ahora
		new_node->next = aux->next;

		// EL siguiente del que tenemos ahora, será el nuevo nodo
		aux->next = new_node;
	}

	// Y listo! \o/
}

//////////////////////////////////////////////////////////////////////////////////////

/**************************
   Inserciones recursivas
***************************/

/* Para este caso, definimos dos funciones para cada cosa:

	 - Una función auxiliar que va a recibir la cabeza y el nuevo nodo, esta función será exclusivamente recursiva
	 - Una función principal que va a recibir la lista y el nuevo nodo. Esta función es la que será llamada desde el main 
*/


// Función auxiliar para inserción atras

void insertar_atras_aux(datos* cur_node, datos* new_node)
{
	// Condición de parada
	if(cur_node->next == NULL)
	{
		cur_node->next = new_node;
		return ;
	}

	// Pasamos al siguiente
	insertar_atras_aux(cur_node->next, new_node);
}

// Función principal para insertar atras.

void insertar_atras_recursivo(datos **head, datos* new_node)
{
	// Guardia!
	if(is_empty(*head))
	{
		*head = new_node;
		return;
	}

	// Llamamos al auxiliar con la cabeza de la lista
	insertar_atras_aux(*head, new_node);
}

//////////////////////////////////////////////////////////////////////////////////////

// Función auxiliar recursiva para la inserción ordenada

void insercion_ordenada_aux(datos* cur_node, datos* new_node)
{
	// Si llegamos al último nodo, le asignamos el nuevo como siguiente
	if(cur_node->next == NULL)
	{
		cur_node->next = new_node;
		return ;
	}

	// No estamos ahora en el ultimo nodo, pero hay que ver si el siguiente es mayor o igual que el nuevo
	if(comparar_nodos_por_nombre(new_node, cur_node->next))
	{
		// El siguiente del nuevo nodo será el siguiente del que tenemos ahora
		new_node->next = cur_node->next;

		// EL siguiente del que tenemos ahora, será el nuevo nodo
		cur_node->next = new_node;

		// Ya insertamos el nuevo nodo, cortamos aquí
		return ;
	}

	// Llegados a este punto, no llegamos al último nodo y el siguiente no era mayor que el actual, así que probamos con el siguiente
	insercion_ordenada_aux(cur_node->next, new_node);
}

// Función principal para la inserción ordenada

void insercion_ordenada_recursiva(datos **head, datos* new_node)
{
	// Guardia!
	if(is_empty(*head))
	{
		*head = new_node;
		return;
	}

	// Llamamos al auxiliar con la cabeza de la lista
	insercion_ordenada_aux(*head, new_node);
}

// Veamos ahora las distintas formas de borrar nodos de la lista


// Función que borra un nodo con cierto id

int borrar_nodo_por_id(datos** head, int id)
{
	// Guardia!
	if(is_empty(*head)) return 0;

	// Mantenemos un prev y un cur. La funcion del prev es notificar cuando es la cabeza

	datos *prev = NULL, *cur = *head;

	while(cur != NULL)
	{
		// Si encontramos un nodo con el id.
		if(cur->id == id)
		{	
			// Si estamos en la cabeza
			if(prev == NULL)
			{
				// Movemos la cabeza al siguiente
				*head = *head->next;
			}
			// No estamos en la cabeza
			else
			{
				// Enlazamos el anterior con el siguiente.
				prev->next = cur->next;
			}
			// Liberamos el nodo actual.
			free(cur);
			return 1;
		}
		prev = cur;
		cur = cur->next;

	}
	return 0;
}

// Este es el segundo enfoque: Eliminar nodos a medida que vamos recorriendo la lista.

int eliminar_ocurrencias(datos** head, int id)
{
	// Guardia!
	if(is_empty(*head)) return 0;

	int result = 0;

	// Mantenemos un prev y un cur. La funcion del prev es notificar cuando es la cabeza

	datos *prev = NULL, *cur = *head;

	while(cur != NULL)
	{
		// Si encontramos un nodo con el id.
		if(cur->id == id)
		{
			// Informamos que hay al menos 1 elemento para eliminar.
			result++;

			// Si estamos en la cabeza
			if(prev == NULL)
			{
				// Movemos la cabeza al siguiente
				*head = *head->next;

				// Liberamos el nodo actual.
				free(cur);
				// Actualizamos SOLO cur porque el prev sigue siendo el mismo
				cur = *head;
			}
			// No estamos en la cabeza
			else
			{
				// Enlazamos el anterior con el siguiente.
				prev->next = cur->next;
				// Liberamos el nodo actual.
				free(cur);
				// Actualizamos SOLO cur porque el prev sigue siendo el mismo
				cur = prev->next;
			}
		}
		else
		{		
			prev = cur;
			cur = cur->next;
		}

	}

	// result es 1 si se eliminó al menos una cosa, 0 de lo contrario.
	return result;
}


// Funcion que recibe 2 listas enlazadas y borra de la primera lista, los elementos comunes en ambas

void borrar_comunes(datos **head_1, datos* head_2)
{
	datos* aux = head_2;
	
	while(aux != NULL)
	{
		eliminar_ocurrencias(head_1, aux->id);
		aux = aux->next;
	}
}


void imprimir_lista(datos* head){
	datos *aux = head;
	int cnt = 0;
	while(aux != NULL){
		printf("%d.-\n",cnt);
		printf("id: %d\n", aux->id);
		printf("letra: %c\n", aux->letra);
		printf("nombre: %s\n", aux->nombre);
		aux = aux->next;
	}
}