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

	struct Item* sorted[N];
	for(int i = 0; i < N; ++i){
		struct Item* min = getLeft(items, N);
		sorted[i] = min;
	}

	int MAX[W + 1];
	MAX[0] = 0;

	int itemIndex = 0;
	int maxBobot = 1;
	while(1){
		if(itemIndex == N || maxBobot == W + 1) break;

		int currentBobot = sorted[itemIndex]->bobot;

		int max = MAX[maxBobot - 1];
		if(currentBobot <= maxBobot){
			int new = MAX[maxBobot - currentBobot] + sorted[itemIndex]->nilai;

			// We take one
			if(new > max) {
				itemIndex += 1;
				max = new;
			}
		}

		MAX[maxBobot++] = max;
	}

	for(int i = 0; i < (W + 1); ++i)
		printf("%d ", MAX[i]);
}
