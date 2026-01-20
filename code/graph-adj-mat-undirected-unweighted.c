#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int n;
    char** v;
    int** a;
} Graph;

void gCreate(Graph* g, int n){
    g->n=n;
    g->v=(char**)malloc(n * sizeof(char*));
    for(int i = 0;i<n;i++){
        g->v[i] = NULL;
    }

    g->a=(int**)malloc(n * sizeof(int*));
    for(int i = 0;i<n;i++){
        g->a[i]=(int*)malloc(n * sizeof(int));

        for(int j = 0;j<n;j++){
            g->a[i][j]=0;
        }
    }
}

void gDestroy(Graph* g){
    for(int i = 0;i<g->n;i++){
        free(g->a[i]);
        
    }
    free(g->a);

    for(int i = 0;i<g->n;i++){
        if(g->v[i] != NULL){
            free(g->v[i]);
        }
    }
    free(g->v);

    g->a = NULL;
    g->v = NULL;
}

void gSetVertexName(Graph* g, int i,const char* name){
    if(g->v[i] != NULL) free(g->v[i]);

    g->v[i]=(char*)malloc(strlen(name)+1);
    strcpy(g->v[i],name);
}

const char* gGetVertexName(Graph* g, int i) {
	return g->v[i];
}

void gAddEdge(Graph* g, int i, int j){
    g->a[i][j] = g->a[i][j] = 1;
}

void gRemoveEdge(Graph* g, int i, int j){
    g->a[i][j] = g->a[i][j] = 0;
}

int gIsEdge(Graph* g, int i, int j){
    return g->a[i][j];
}

int gIsPath(Graph* g, int* P, int k){
    for(int i = 0; i<k-1;i++){
        if(!gIsEdge(g,P[i],P[i+1])){
            return 0;
        }
    }

    return 1;
}

int gIsSimplePath(Graph* g, int* P, int k) {
    if(k <= 1) return 0;

	if (!gIsPath(g, P, k)) return 0;

	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (P[i] == P[j] && !(i == 0 && j == k - 1))
				return 0;
		}
	}

	return 1;
}

int gIsCycle(Graph* g, int* P, int k){
    return gIsSimplePath(g, P, k) && P[0] == P[k-1];
}

int gAreNeighbors(Graph* g, int i, int j){
    return gIsEdge(g, i, j);
}

int gAreConncected_checkVertex(Graph* g, int i, int j, int* visited){
    visited[i] = 1;

    for(int k = 0;k<g->n;k++){
        if(gAreNeighbors(g,i,k) && !visited[k]){
            if(k == j){
                return 1;
            }

            if(gAreConncected_checkVertex(g,k,j,visited)){
                return 1;
            }
        }
    }

    return 0;
}

int gAreConnected(Graph* g, int i, int j){
    int* visited = (int*)malloc(g->n * sizeof(int));
    for(int k = 0;k<g->n;k++){
        visited[k]=0;
    }

    int c = gAreConncected_checkVertex(g,i,j,visited);

    free(visited);

    return c;
}

int main(){
    Graph g;

    gCreate(&g, 9);

    gSetVertexName(&g, 0, "v1");
    gSetVertexName(&g, 1, "v2");
    gSetVertexName(&g, 2, "v3");
    gSetVertexName(&g, 3, "v4");
    gSetVertexName(&g, 4, "v5");
    gSetVertexName(&g, 5, "v6");
    gSetVertexName(&g, 6, "v7");
    gSetVertexName(&g, 7, "v8");
    gSetVertexName(&g, 8, "v9");

    gAddEdge(&g, 0, 1);
	gAddEdge(&g, 0, 4);

	gAddEdge(&g, 1, 2);
	gAddEdge(&g, 1, 5);
	gAddEdge(&g, 1, 6);

	gAddEdge(&g, 2, 7);

	gAddEdge(&g, 3, 1);
	gAddEdge(&g, 3, 4);
	gAddEdge(&g, 3, 5);

	gAddEdge(&g, 4, 5);
	gAddEdge(&g, 4, 6);

	gAddEdge(&g, 5, 6);

	gAddEdge(&g, 6, 7);
	gAddEdge(&g, 6, 8);

	gAddEdge(&g, 7, 8);

	gAddEdge(&g, 8, 4);

    int P1[] = {0, 1, 5, 6, 8},
		P2[] = {0, 1, 7, 8},
		P3[] = {0, 1, 6, 8, 4, 6, 7},
		P4[] = {4, 5, 6, 7, 8, 4};
	int k[] = {
		sizeof(P1) / sizeof(P1[0]),
		sizeof(P2) / sizeof(P2[0]),
		sizeof(P3) / sizeof(P3[0]),
		sizeof(P4) / sizeof(P4[0]),
	};
	int* P[] = {P1, P2, P3, P4};

	for (int i = 0; i < sizeof(P) / sizeof(P[0]); i++) {
		int path = gIsPath(&g, P[i], k[i]),
			simplePath = gIsSimplePath(&g, P[i], k[i]),
			cycle = gIsCycle(&g, P[i], k[i]);

        printf("P%d: %s, %s, %s\n",
			i + 1,
			path ? "Path" : "Not path",
			simplePath ? "Simple path" : "Not simple path",
			cycle ? "Cycle" : "Not cycle"
		);
    }

    int c[][2] = { {1, 8}, {2, 4}, {3, 7} };
	for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++) {
		int connected = gAreConnected(&g, c[i][0], c[i][1]);
		printf("%s and %s are %s\n",
			gGetVertexName(&g, c[i][0]),
			gGetVertexName(&g, c[i][1]),
			connected ? "connected" : "not connected"
		);
	}

    gDestroy(&g);
    
    return 0;
}