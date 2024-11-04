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
	
	size_t itemsRead;
    int i = 0;
    while (fread(&l, sizeof(Lane), 1, fp)) {
        // Print lane name of each read entry
        printf("Lane %d: %s\n", i, l.laneName);
        i++;
		h->list[l.prio] = l;
		
        // Stop if the array is full
        if (i >= 10) {
            break;
        }
    }
	fclose(fp);
}

int countSeconds(heapLane l, char *string){
	int retval=0, i;
	
	for(i=0; i<10 && strcmp(string, l.list[i].laneName)!=0; i++){
		retval+=l.list[i].seconds;
		printf("[%d] = %d\n", i, retval);
	}
	retval=retval + l.list[i+1].seconds;
	printf("[%d] = %d\n", i, retval);
	return retval;
}

int main(){
	Lane list[10];
	heapLane l;
	l.count = 0;
	enqueue(&l, list[0]);
	printf("\nHeres the total amount of seconds to reach Pedestrian Diversion: %d",countSeconds(l, "Diversion Pedestrian"));
	return 0;
}
