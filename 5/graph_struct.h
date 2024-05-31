#ifndef INC_5_GRAPH_STRUCT_H
#define INC_5_GRAPH_STRUCT_H

typedef struct Edge {
    int mark;
    struct Vertex *to;
    struct Edge *next;
} Edge;

typedef struct Vertex {
    char *name;
    Edge *edges;
    int path;
} Vertex;

typedef struct Graph {
    Vertex* *vertex_vector;
    uint64_t c_size;
    uint64_t m_size;
} Graph;

#endif //INC_5_GRAPH_STRUCT_H
