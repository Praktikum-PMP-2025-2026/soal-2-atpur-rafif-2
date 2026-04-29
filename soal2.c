#include <stdio.h>
#include <string.h>

#define MAX_NAME 100

struct Item {
	char name[MAX_NAME];
	int bobot;
	int nilai;
	double ratio;
	char flag;
};

struct Item* getMax(struct Item* items, int count){
	struct Item* max = NULL;
	for(int i = 0; i < count; ++i){
		struct Item* cur = &items[i];

		char isLess = (max == NULL) ||
			(cur->ratio > max->ratio) ||
			(cur->ratio == max->ratio && (strcmp(cur->name, max->name) < 0));

		if(cur->flag && isLess) max = cur;
	}

	max->flag = 0;
	return max;
}

int main(){
	int N, W;
	scanf("%d %d", &N, &W);

	struct Item items[N];
	for(int i = 0; i < N; ++i){
		struct Item* item = &items[i];
		scanf("%s %d %d", (char*) &item->name, &item->bobot, &item->nilai);
		item->flag = 1;
		item->ratio = (double) item->nilai / (double) item->bobot;
	}

	struct Item* taken[N];
	int n = 0, w = 0, v = 0;

	for(int i = 0; i < N; ++i){
		struct Item* max = getMax(items, N);
		if(w + max->bobot <= W) {
			w += max->bobot;
			v += max->nilai;
			taken[n++] = max;
		}
	}

	printf("MAX_VALUE %d\n", v);
	for(int i = 0; i < n; ++i)
		printf("ITEM %s\n", taken[i]->name);
}
