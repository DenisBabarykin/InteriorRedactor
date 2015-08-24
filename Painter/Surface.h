#ifndef SURFACE
#define SURFACE

#define VERTEX_COUNT 3

struct Surface
{
    unsigned int visiblePixelsCount;
    unsigned int vertexIndexes[VERTEX_COUNT];
    unsigned int normalIndexes[VERTEX_COUNT];
    unsigned int materialIndex;
};

#endif // SURFACE

