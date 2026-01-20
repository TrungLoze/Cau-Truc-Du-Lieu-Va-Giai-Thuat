#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "linked-list.h"

typedef struct {
	int n;
	char** v;
	LinkedList e;
} Graph;

typedef struct {
    int from;
    int to;
	float weight;
} GraphEdge;

void gCreate(Graph* g, int n) {
	g->n = n;

	g->v = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) {
		g->v[i] = NULL;
	}

	llInit(&(g->e));
}

void gDestroy(Graph* g) {
	for (int i = 0; i < g->n; i++)
		if (g->v[i] != NULL) free(g->v[i]);
	free(g->v);
	g->v = NULL;

	llDeleteAll(&(g->e));
}

void gSetVertexName(Graph* g, int i, const char* name) {
	if (g->v[i] != NULL) free(g->v[i]);

	g->v[i] = (char*)malloc(strlen(name) + 1);
	strcpy(g->v[i], name);
}

const char* gGetVertexName(Graph* g, int i) {
	return g->v[i];
}

int gIsEdge(Graph* g, int i, int j) {
    for(ListElement* p = g->e,*q = NULL; p != NULL; p=p->next){
        GraphEdge* pe = (GraphEdge*)(p->data);
        if(pe->from == i && pe->to == j){
            
            return 1;
        }
    }
	
    return 0;
}

void gAddEdge(Graph* g, int i, int j, int weight) {
    if(gIsEdge(g,i,j)) return;
    
    GraphEdge ge = {.from=i, .to=j};
    llInsertHead(&(g->e), &ge, sizeof(ge));
}

void gRemoveEdge(Graph* g, int i, int j) {
	for(ListElement* p = g->e,*q = NULL; p != NULL; p=p->next){
        GraphEdge* pe = (GraphEdge*)(p->data);
        if(pe->from == i && pe->to == j){
            if(q == NULL){
                llDeleteHead(&(g->e));
            }
            llDeleteAfter(&(g->e),q);
        }
    }
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

int gIsCycle(Graph* g, int* P, int k) {
	return gIsSimplePath(g, P, k) && P[0] == P[k - 1];
}

int gGetWeight(Graph*g, int i ,int j){

}

int gSumWeight(Graph* g, int* P, int k) {
	float sum = 0;
	for (int i = 0; i < k - 1; i++)
		sum += gGetWeight(g,P[i],P[i+1]);

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

void gBFS(Graph* g, int s){
	LinkedList frontier;
	llInit(&frontier);

	int* visited = (int*)malloc(g->n * sizeof(int));

	for(int i=0; i<g->n;i++){
		visited[i] = 0;
	}

	llInsertTail(&frontier, &s, sizeof(s));

	while (llCount(&frontier) > 0){
		int nk = *(int*)frontier->data;
		llDeleteHead(&frontier);

		if(visited[nk]) continue;

		printf("%d(%s) ", nk,gGetVertexName(g,nk));
		visited[nk] = 1;

		for(int i=0; i<g->n;i++){
			if(i != nk && gIsOutNeighbor(g,nk, i)){
				llInsertTail(&frontier,&s,sizeof(int));
			}
		}
	}
	

	free(visited);
	llDeleteAll(&frontier);
}

void gDijiktra(Graph* g, int s){
	typedef struct {
		int vertex;
		float dist;
	} VertexDist;
	LinkedList Q;
	llInit(&Q);
	int* visited = (int*)malloc(g->n * sizeof(int));
	for(int i=0; i<g->n;i++){
		visited[i] = 0;
		VertexDist vd = {.vertex = i, .dist = (i==s)?0:INFINITY};
		llInsertTail(&Q,&vd,sizeof(vd));
	}
	while(llCount(Q) > 0){
		//tìm đỉnh có khoảng cách nhỏ nhất
		ListElement* pMin = Q;
		for(ListElement* p = Q; p != NULL; p=p->next){
			VertexDist* vd = (VertexDist*)(p->data);
			VertexDist* vdMin = (VertexDist*)(pMin->data);
			if(vd->dist < vdMin->dist){
				pMin = p;
			}
		}
		VertexDist* u = (VertexDist*)(pMin->data);
		llDeleteElement(&Q,pMin);

		if(visited[u->vertex]) continue;
		visited[u->vertex] = 1;

		printf("Vertex %d (%s) - Distance from source: %g\n", u->vertex, gGetVertexName(g,u->vertex), u->dist);

		for(int v=0; v<g->n; v++){
			if(!visited[v] && gIsOutNeighbor(g,u->vertex,v)){
				float alt = u->dist + gGetWeight(g,u->vertex,v);
				//Cập nhật khoảng cách nếu tìm được đường đi ngắn hơn
				for(ListElement* p = Q; p != NULL; p=p->next){
					VertexDist* vd = (VertexDist*)(p->data);
					if(vd->vertex == v && alt < vd->dist){
						vd->dist = alt;
						break;
					}
				}
			}
		}
	}
	free(visited);
	llDeleteAll(&Q);
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

	gDijiktra(&g, 0);

	gDestroy(&g);

	return 0;

}