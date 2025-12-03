#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int vertex;
    int weight;
    struct NODE *next;
} NODE;

typedef struct GRAPH
{
    int vertices;
    NODE **list;
    int is_directed;
}GRAPH;

NODE *createNode(int vertex, int weight)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }
    
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;

    return node;
}

GRAPH *createGraph(int vertices, int is_directed)
{
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    if (graph == NULL)
    {
        printf("Graph is not created\n");
        exit(1);
    }

    graph->vertices = vertices;
    graph->is_directed = is_directed;
    graph->list = (NODE **)malloc(vertices * sizeof(NODE *));
    if (graph->list == NULL)
    {
        printf("Adjacency list is not created\n");
        exit(1);
    }

    for (int i = 0; i < vertices; i++)
        graph->list[i] = NULL;

    printf("Graph is created with %d vertices\n", graph->vertices);
    return graph;
}

void addEdge(GRAPH *g, int u, int v, int weight)
{
    if (u < 0 || u >= g->vertices)
    {
        printf("Invalid Vertex(u) - %d\n", u);
        return;
    }
    else if (v < 0 || v >= g->vertices)
    {
        printf("Invalid Vertex(v) - %d\n", v);
        return;
    }

    NODE *node = createNode(v, weight);
    node->next = g->list[u];
    g->list[u] = node;
    if (!g->is_directed)
    {
        node = createNode(u, weight);
        node->next = g->list[v];
        g->list[v] = node;
    }

    printf("Added edge %d - %d (u - v) in the graph\n", u, v);
}

void removeEdge(GRAPH *g, int u, int v)
{
    if (u < 0 || u >= g->vertices)
    {
        printf("Invalid Vertex(u) - %d\n", u);
        return;
    }
    else if (v < 0 || v >= g->vertices)
    {
        printf("Invalid Vertex(v) - %d\n", v);
        return;
    }
    
    NODE *node = g->list[u], *prev = NULL;
    while (node && node->vertex != v)
    {
        prev = node;
        node = node->next;
    }
    
    if (node == NULL)
    {
        printf("Edge not found\n");
        return;
    }

    if (prev == NULL)
        g->list[u] = node->next;
    else
        prev->next = node->next;

    free(node);
    
    if(!g->is_directed)
    {
        node = g->list[v];
        prev = NULL;
        while (node && node->vertex != u)
        {
            prev = node;
            node = node->next;
        }

        if(prev == NULL)
            g->list[v] = node->next;
        else
            prev->next = node->next;

        free(node);
    }

    printf("Removed edge %d - %d (u - v) in the graph\n", u, v);
}

void BFS(GRAPH *g, int start)
{
    if (start < 0 || start >= g->vertices)
    {
        printf("Invalid start vertex\n");
        return;
    }

    int *visited = (int *)calloc(g->vertices, sizeof(int));
    int *queue = (int *)malloc(g->vertices * sizeof(int));
    int front = 0, rear = -1;
    
    visited[start] = 1;
    queue[++rear] = start;

    printf("The Graph Traversal using BFS: ");
    while(front <= rear)
    {
        int value = queue[front++];
        printf("%d ", value);

        NODE *temp = g->list[value];
        while (temp)
        {
            int vertex = temp->vertex;
            if(!visited[vertex])
            {
                visited[vertex] = 1;
                queue[++rear] = vertex;
            }
            temp = temp->next;
        }
    }

    printf("\n");
    free(queue);
    free(visited);
}

void DFS(GRAPH *g, int start, int visited[])
{
    visited[start] = 1;
    printf("%d ", start);

    NODE *temp = g->list[start];
    while (temp)
    {
        int vertex = temp->vertex;
        if(!visited[vertex])
            DFS(g, vertex, visited);
        temp = temp->next;
    }
}

void printGraph(GRAPH *g)
{
    if (g->vertices == 0)
    {
        printf("Graph is empty\n");
        return;
    }

    for (int i = 0; i < g->vertices; i++)
    {
        NODE *temp = g->list[i];
        printf("(%d) -> ", i);
        while (temp)
        {
            printf("[%d, %d] ", temp->vertex, temp->weight);
            if(temp->next)
                printf("-> ");
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    GRAPH *g;
    int vertices, is_directed, choice, u, v, weight, start;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Directed Graph? (1 = Yes, 0 = No): ");
    scanf("%d", &is_directed);
    g = createGraph(vertices, is_directed);

    while (1)
    {
        printf("\n1. Add Edge\n2. Remove Edge\n3. Display\n4. Breadth First Search\n5. Depth First Search\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter edge (u v): ");
            scanf("%d %d", &u, &v);
            printf("Enter weight: ");
            scanf("%d", &weight);
            addEdge(g, u, v, weight);
            break;
        case 2:
            printf("Enter edge to remove (u v): ");
            scanf("%d %d", &u, &v);
            removeEdge(g, u, v);
            break;
        case 3:
            printGraph(g);
            break;
        case 4:
            printf("Enter starting vertex: ");
            scanf("%d", &start);
            BFS(g, start);
            break;
        case 5:
        {
            printf("Enter starting vertex: ");
            scanf("%d", &start);
            if (start < 0 || start >= g->vertices)
            {
                printf("Invalid start vertex\n");
                break;
            }

            int *visited = (int *)calloc(g->vertices, sizeof(int));
            printf("The Graph Traversal using DFS: ");
            DFS(g, start, visited);

            printf("\n");
            free(visited);
            break;
        }
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    for (int i = 0; i < g->vertices; i++)
    {
        NODE *node = g->list[i];
        while (node)
        {
            NODE *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(g->list);
    free(g);
    printf("Program exited!\n");
    return 0;
}