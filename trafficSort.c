#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	char laneName[24];
	int prio;
	int seconds;
}Lane;

typedef struct{
	Lane list[10];
	int count;
}heapLane;

Lane newLane(char *lname, int prio, int sec){
	Lane l;
	
	strcpy(l.laneName, lname);
	l.prio = prio;
	l.seconds = sec;
	
	return l;
}

bool enqueue(heapLane * h, Lane l){
	FILE *fp;
	fp = fopen("traffic.dat", "rb");
    int i = 0;
    while (fread(&l, sizeof(Lane), 1, fp)) {
        printf("Lane %d: %s\n", i, l.laneName);
        i++;
		h->list[l.prio-1] = l;
		h->count++;
        // Stop if the array is full
        if (i >= 10) {
            break;
        }
    }
	fclose(fp);
}

int countSeconds(heapLane l, char *string){
	int retval=0, i;
	for(i=0; i<l.count && strcmp(string, l.list[i].laneName)!=0; i++){
		retval+=l.list[i].seconds;
		printf("[%d] = %d\n", i, retval);
	}
	return retval+=l.list[i].seconds;
}

int main(){
	Lane list[10];
	heapLane l;
	char string[20];
	strcpy(string, "Diversion Left");
	l.count = 0;
	enqueue(&l, list[0]);
	printf("\nHeres the total amount of seconds to reach %s: %d", string,countSeconds(l, string));
	return 0;
}
