//
// Created by User on 2022/9/11.
// Basic pattern matching
#include <cstdio>
#include <cstring>
#include <cstdlib>
int basicPatternMatching(char *,char *);
/*int main() {
    //char *master,*slave;
    char master[256],slave[256];
    printf("Please input two respective words on the screen:\n");
//    scanf("%s",master);
//    fflush(stdin);
//    scanf("%s",slave);
//    fflush(stdin);
    gets(master);
    gets(slave);
    int sonIndex = basicPatternMatching(master,slave);
    printf("The son string local in %d", sonIndex);
    return 0;
}*/
//It finds the son string in master string.
int basicPatternMatching(char *master,char *slave){
    int i=0,j=0,sonIndex=0;
    while(sonIndex <= strlen(master) - strlen(slave)){
        if(master[i]==slave[j]){
            i++;
            j++;
            if(j==strlen(slave)) return sonIndex; //Success
        }else{
            //If not found,it will move index one step right.
            sonIndex++;
            i = sonIndex;
            j = 0;
        }
    }
    return -1; //Failure
}
