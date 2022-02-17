#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
//Struct to create a vertex, it takes in a user_id, a next
// and an array of edges that vertex is connected to.
typedef struct vertex {
    int user_id;
    struct vertex* next;
    struct vertex* edges[SIZE];
    int filledEdges;
} vertex_t;

//Struct to create a graph with a number of vertices
// in a singly linked list.
typedef struct graph {
    int size;
    int filled_vertices;
    vertex_t* head;
    vertex_t* tail;
} graph_t;

//Function to create a vertex
vertex_t* createVertex(int user_id) {
    vertex_t* newVertex = (vertex_t*) malloc(sizeof(vertex_t));

    newVertex->user_id = user_id;
    for (int i = 0; i < SIZE; i++) {
        newVertex->edges[i] = NULL;
    }
    newVertex->filledEdges = 0;
    newVertex->next = NULL;
    
    return newVertex;
}

//Function to create a graph with a size parameter
graph_t* createGraph(int size) {
    graph_t* newGraph = (graph_t*) malloc(sizeof(graph_t));
    newGraph->filled_vertices = 0;
    newGraph->size = size;
    newGraph->head = NULL;
    newGraph->tail = NULL;
    return newGraph;
}

//Function to add vertex to the graph
void addVertex(graph_t* graph, vertex_t* vertex) {
    //returns if graph is NULL
    if (graph == NULL) {
        return;
    }
    //Returns if vertex is NULL
    if (vertex == NULL) {
        return;
    }

    //If graph is empty, this is how term is added
    if (graph->head == NULL && graph->tail == NULL) {
        graph->head = vertex;
        graph->tail = vertex;
        graph->filled_vertices += 1;
        return;
    }

    //If graph has at least one vertex, these steps are followed.
    if (graph->filled_vertices > 0) {
        graph->tail->next = vertex;
        graph->tail = vertex;
        graph->tail->next = NULL;
        graph->filled_vertices += 1;
        return;
    }
}

//Function to add an edge to the vertex
void addEdge(vertex_t* src, vertex_t* dest) {
    src->edges[src->filledEdges] = dest;
    src->filledEdges = src->filledEdges+1;
    dest->edges[dest->filledEdges] = src;
    dest->filledEdges = dest->filledEdges+1;
}

//Function to facilitate deletion of a vertex.
void deleteVertex(graph_t* graph, vertex_t* vertex) {
    vertex_t* itr = graph->head;
    int pos = 0;
    for (int i = 0; i < graph->filled_vertices-1; i++) {
        if (itr->user_id == vertex->user_id) {
            break;
        }
        itr = itr->next;
        pos++;
    }

    //If we are trying to delete the head
    if(pos == 0) {
		vertex_t* temp = graph->head;
		free(graph->head);
		graph->head = temp->next;
		graph->filled_vertices -= 1;
		return;
	}

    //If we are trying to delete the tail
    if(pos == graph->filled_vertices - 1) {
		vertex_t* newtail = graph->head;
		for (int i = 0; i<graph->filled_vertices-1; i++) {
			newtail = newtail->next;
		}
		free(graph->tail);
		graph->tail = newtail;
		newtail->next = NULL;
		graph->filled_vertices -= 1;
		return;
	}
    //If we are trying to delete a vertex in the middle of the adjacency list.
	vertex_t* tempprev = graph->head;
	vertex_t* tempnext = graph->head;
	vertex_t* temppos = graph->head;

	for (int i = 0; i<pos-1; i++) {
		tempprev = tempprev->next;
	}

        for(int i = 0; i < pos+1; i++) {
		tempnext = tempnext->next;
	}
	for(int i = 0; i <pos; i++) {
		temppos = temppos->next;
	}
	
	tempprev->next = tempnext;
	free(temppos);
	graph->filled_vertices -= 1;
	return;
}

//Searches for a vertex and returns its edges
void search(graph_t* graph, vertex_t* vertex) {
    vertex_t* itr = graph->head;
    for (int i = 0; i < graph->filled_vertices; i++) {
        if (itr->user_id == vertex->user_id) {
            printf("Vertex Found! Position: %d \n", i);
            break;
        }
        itr = itr->next;
    }
    if (itr == NULL) {
        printf("Vertex not found.\n");
    } else {
        printf("Edges: ");
        for (int i = 0; i < itr->filledEdges; i++) {
            printf(" %d ", itr->edges[i]->user_id);
        }
        printf("\n");
    }
}

//Calculates the degree centrality of the graph.
void degreeCentrality(graph_t* graph) {
    vertex_t* itr = graph->head;
    int degrees[graph->filled_vertices];
    vertex_t* vertices[graph->filled_vertices];
    for (int i = 0; i < graph->filled_vertices; i++) {
        degrees[i] = itr->filledEdges;
        vertices[i] = itr;
        itr = itr->next;
    }

    int max = 0;
    int j = 0;
    for (int i = 0; i < graph->filled_vertices; i++) {
        if (max <= degrees[i]) {
            max = degrees[i];
            j = i;
        }
    }
    int k;
    printf("Centers: ");
    for (int i = 0; i < graph->filled_vertices; i++) {
        if (degrees[i] == max) {
            printf("%d ", vertices[i]->user_id);
        }
    }
    printf("\n");
    
}

//Helper function to print the graph.
void printGraph(graph_t* graph) {
    vertex_t* itr = graph->head;
    for (int i = 0; i < graph->filled_vertices; i++) {
        printf("Vertex: %d Edges:", itr->user_id);
        for (int j = 0; j < itr->filledEdges; j++) {
            printf(" %d ", itr->edges[j]->user_id);
        }
        itr = itr->next;
        printf("\n");
    }
}

int main() {
    graph_t* graph = createGraph(10);
    vertex_t* v1 = createVertex(001);
    vertex_t* v2 = createVertex(002);
    vertex_t* v3 = createVertex(003);
    vertex_t* v4 = createVertex(004);
    vertex_t* v5 = createVertex(005);
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    addVertex(graph, v4);
    addVertex(graph, v5);
    addEdge(v1, v2);
    addEdge(v1, v3);
    addEdge(v2, v4);
    addEdge(v3, v4);
    addEdge(v4, v5);
    addEdge(v5, v2);
    printGraph(graph);
    printf("\n\n\n");

    search(graph, v1);
    search(graph, v4);
    
    vertex_t* v6 = createVertex(006);
    search(graph, v6);
    degreeCentrality(graph);
    //printf("center: %d \n", center->user_id);
    printf("\n\n\n");

    deleteVertex(graph, v2);
    printGraph(graph);
    printf("\n\n\n");

    deleteVertex(graph, v1);
    printGraph(graph);
    printf("\n\n\n");

    deleteVertex(graph, v3);
    printGraph(graph);
    printf("\n\n\n");
    
    return 0;
}

