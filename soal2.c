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

struct Item* getLeft(struct Item* items, int count){
	struct Item* min = NULL;
	for(int i = 0; i < count; ++i){
		struct Item* cur = &items[i];

		char isLess = (min == NULL) ||
			(cur->bobot < min->bobot) ||
			(cur->bobot == min->bobot && cur->nilai > min->nilai) ||
			(cur->bobot == min->bobot && cur->nilai == min->nilai && (strcmp(cur->name, min->name) > 0));

		if(cur->flag && isLess) min = cur;
	}

	min->flag = 0;
	return min;
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

	int MAX[W + 1];
	char TAKEN[W + 1][N];
	MAX[0] = 0;

	for(int i = 0; i < (W + 1); ++i)
		for(int j = 0; j < N; ++j)
			TAKEN[i][j] = 0;

	int maxBobot = 1;
	while(maxBobot < (W + 1)){
		int max = MAX[maxBobot - 1]; // Don't take anything
		for(int j = 0; j < N; ++j)
			TAKEN[maxBobot][j] = TAKEN[maxBobot - 1][j];
		
		// Try to take one, that hasn't been taken
		for(int i = 0; i < N; ++i){
			int bobot = items[i].bobot;
			int prevBobot = maxBobot - bobot;

			// Skip if can't take it
			if(prevBobot < 0) continue;

			// Skip if already taken previously
			if(TAKEN[prevBobot][i]) continue;

			// Try to take it
			int new = MAX[prevBobot] + items[i].nilai;

			if(new > max) {
				max = new;
				for(int j = 0; j < N; ++j)
					TAKEN[maxBobot][j] = TAKEN[prevBobot][j];
				TAKEN[maxBobot][i] = 1;
			}
		}

		MAX[maxBobot++] = max;
	}

	for(int i = 0; i < (W + 1); ++i){
		printf("%d: ", i);
		for(int j = 0; j < N; ++j){
			printf("%d ", TAKEN[i][j]);
		}
		printf("\n");
	}



	for(int i = 0; i < (W + 1); ++i)
		printf("%d ", MAX[i]);
}
