#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char laneName[24];
	int prio;
	int seconds;
}Lane;

Lane newLane(char *lname, int prio, int sec){
	Lane l;
	
	strcpy(l.laneName, lname);
	l.prio = prio;
	l.seconds = sec;
	
	return l;
}


int main(){
	Lane list[10];
	list[0] = newLane("Main Straight", 1, 80);
	list[1] = newLane("Diversion Straight", 2, 70);
	list[2] = newLane("Main Left", 3, 60);
	list[3] = newLane("Diversion Left", 4, 50);
	list[4] = newLane("Main Right", 5, 40);
	list[5] = newLane("Diversion Right", 6, 30);
	list[6] = newLane("Main Pedestrian", 7, 20);
	list[7] = newLane("Diversion Pedestrian", 8, 10);
	
	FILE *fp;
	
	fp = fopen("traffic.dat", "w+");
	
	if(fp!=NULL){
		fwrite(list, sizeof(Lane), 8, fp);
	}
	fclose(fp);
	return 0;
}
