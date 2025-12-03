#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int vertices;
    int **arr;
    int is_directed;
} GRAPH;

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
    graph->arr = (int **)malloc(vertices * sizeof(int *));
    if (graph->arr == NULL)
    {
        printf("Adjacency matrix is not created\n");
        free(graph);
        exit(1);
    }

    for (int i = 0; i < vertices; i++)
        graph->arr[i] = (int *)calloc(vertices, sizeof(int));

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
    
    g->arr[u][v] = weight;
    if(!g->is_directed)
        g->arr[v][u] = weight;

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
    
    g->arr[u][v] = 0;
    if(!g->is_directed)
        g->arr[v][u] = 0;

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

        for (int i = 0; i < g->vertices; i++)
            if(g->arr[value][i] != 0 && !visited[i])
            {
                visited[i] = 1;
                queue[++rear] = i;
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

    for (int i = 0; i < g->vertices; i++)
        if(g->arr[start][i] != 0 && !visited[i])
            DFS(g, i, visited);
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
        for (int j = 0; j < g->vertices; j++)
            printf("%d ", g->arr[i][j]);
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
        free(g->arr[i]);

    free(g->arr);
    free(g);
    printf("Program exited!\n");
    return 0;
}