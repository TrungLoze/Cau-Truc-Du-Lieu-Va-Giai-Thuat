#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// directed, weighted graph


#define NOT_EDGE NAN

typedef struct {
	int n;
	char** v;
	float** a;
} Graph;

void gCreate(Graph* g, int n) {
	g->n = n;

	g->v = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		g->v[i] = NULL;
	}

	g->a = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++) {
		g->a[i] = (float*)malloc(n * sizeof(float));

		for (int j = 0; j < n; j++)
			g->a[i][j] = NOT_EDGE;
	}
}

void gDestroy(Graph* g) {
	for (int i = 0; i < g->n; i++)
		if (g->v[i] != NULL) free(g->v[i]);
	free(g->v);
	g->v = NULL;

	for (int i = 0; i < g->n; i++)
		free(g->a[i]);
	free(g->a);
	g->a = NULL;
}

void gSetVertexName(Graph* g, int i, const char* name) {
	if (g->v[i] != NULL) free(g->v[i]);

	g->v[i] = (char*)malloc(strlen(name) + 1);
	strcpy(g->v[i], name);
}

const char* gGetVertexName(Graph* g, int i) {
	return g->v[i];
}

void gAddEdge(Graph* g, int i, int j, float weight) {
	g->a[i][j] = weight;
}

void gRemoveEdge(Graph* g, int i, int j) {
	g->a[i][j] = NOT_EDGE;
}

int gIsEdge(Graph* g, int i, int j) {
	return !isnan(g->a[i][j]);
}

int gIsPath(Graph* g, int* P, int k) {
	if (k <= 1) return 0;

	for (int i = 0; i < k - 1; i++)
		if (!gIsEdge(g, P[i], P[i + 1])) return 0;

	return 1;
}

int gIsSimplePath(Graph* g, int* P, int k) {
	if (!gIsPath(g, P, k)) return 0;

	for (int i = 0; i < k - 1; i++) {
		for (int j = i + 1; j < k; j++) {
			if (P[i] == P[j] && !(i == 0 && j == k - 1))
				return 0;
		}
	}

	return 1;
}

int gIsCycle(Graph* g, int* P, int k) {
	return gIsSimplePath(g, P, k) && P[0] == P[k - 1];
}

// checks if j is out-neighbor of i
int gIsOutNeighbor(Graph* g, int i, int j) {
	return gIsEdge(g, i, j);
}

// checks if j is in-neighbor of i
int gIsInNeighbor(Graph* g, int i, int j) {
	return gIsEdge(g, j, i);
}

int gAreNeighbors(Graph* g, int i, int j) {
	return gIsInNeighbor(g, i, j) || gIsOutNeighbor(g, i, j);
}


int gSumWeight(Graph* g, int* P, int k) {
	float sum = 0;
	for (int i = 0; i < k - 1; i++)
		sum += g->a[P[i]][P[i+1]];

	return sum;
}

int gAreConncected_checkVertex(Graph* g, int i, int j, int* visited) {
    visited[i] = 1;//đánh dấu điểm bắt đầu là đã qua

    for (int k = 0; k < g->n; k++) {//Chạy thử toàn bộ node trên graph
        if (gIsOutNeighbor(g, i, k) && !visited[k]) {//Nếu có kết nối giữa i và điểm đang xét
													 //Điểm đang xét chưa được đi qua
            if (k == j) {//Nếu điểm đang xét là điểm cuối
                return 1;// trả về có kết nối
            }

            if (gAreConncected_checkVertex(g, k, j, visited)) {//Gọi đệ quy với tham số từ điểm đang xét đến điểm cuối
                return 1;//Nếu có kết nối trả về có
            }
        }
    }

    return 0;// Nếu không thỏa mãn trả về không có kết nối
}

int gAreConnected(Graph* g, int i, int j) {
    int* visited = (int*)malloc(g->n * sizeof(int)); //Khởi tạo mảng động với n là số nút của Graph
	for(int k = 0;k<g->n;k++){//Chạy vòng lặp đánh dấu các phần tử mảng động 
        visited[k]=0;//gán tất cả phần tử bằng 0
    }

    int c = gAreConncected_checkVertex(g, i, j, visited);//Gọi hàm kiểm tra có kết nối không

    free(visited);//xóa mảng động 
    return c;//trả kết quả có kết nối không
}



int main() {
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

	gAddEdge(&g, 0, 1, 4);
	gAddEdge(&g, 0, 4, 3.3);

	gAddEdge(&g, 1, 2, 2.5);
	gAddEdge(&g, 1, 5, 3.2);
	gAddEdge(&g, 1, 6, 5);

	gAddEdge(&g, 2, 7, 1.2);

	gAddEdge(&g, 3, 1, 1.8);
	gAddEdge(&g, 3, 4, 2);
	gAddEdge(&g, 3, 5, 1.7);

	gAddEdge(&g, 4, 5, 2.6);
	gAddEdge(&g, 4, 6, 5.7);

	gAddEdge(&g, 5, 6, 3);

	gAddEdge(&g, 6, 7, 2.1);
	gAddEdge(&g, 6, 8, 3.8);

	gAddEdge(&g, 7, 8, 4.1);

	gAddEdge(&g, 8, 4, 4.9);

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

		float weight = path ? gSumWeight(&g, P[i], k[i]) : NAN;

		printf("P%d: %s, %s, %s, %g \n",
			i + 1,
			path ? "Path" : "Not path",
			simplePath ? "Simple path" : "Not simple path",
			cycle ? "Cycle" : "Not cycle",
			weight
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