//
// Created by User on 2022/9/12.
//KMP Pattern Matching
#include <cstdio>
#include <cstring>
#include <cstdlib>

void getNext(const char *, int *);

int kmpPatternMatching(const char *master, const char *slave);

int *kmpPatternMatchingMultiple(const char *master, const char *slave);

int main() {
//    const char *slave = "aabaafaab";
//    int next[strlen(slave)];
//    getNext(slave,next);
//    printf("The array of next is:");
//    for(int i = 0;i < strlen(slave);i++){
//        printf("%d",next[i]);
//    }
//    int index = kmpPatternMatching("abxabcabcaby", "a");
//    printf("%d", index);
    int *substring;
    substring = kmpPatternMatchingMultiple("aabxxfadfawsfas", "a");
    printf("matching substring:\n");
    while(*substring!=-1) { //substring will not reach the null.
        printf("%d\t", *substring);
        substring++;
    }
    return 0;
}

//It generates prefix list.
void getNext(const char *slave, int *next) {
    //1.initialization
    int i, j;
    next[0] = 0; //whenever,the next[0] is always zero.
    j = 0; //j is last of prefix index,which is used to backtracking and add in next[].
    //2.judge
    for (i = 1; i < strlen(slave); i++) { // variable i is last of suffix index,which moves step by step.
        //the different situation
        while (j > 0 && slave[i] != slave[j]) {
            j = next[j - 1]; //keep backtracking until j is 0
        }
        //the same situation
        if (slave[i] == slave[j]) {
            j++;
        }
        //3. change contents of array of next
        next[i] = j;
    }
}

//Let's start to use KMP.
int kmpPatternMatching(const char *master, const char *slave) {
    int next[strlen(slave)];
    //First,get the next[];
    getNext(slave, next);
    int i, j;
    i = 0;
    j = next[0];
    //the index of i moves step by step
    while (i < strlen(master)) {
        if (j == next[0] && master[i] != slave[j]) i++;
        else if (j > next[0] && master[i] != slave[j]) j = next[j - 1];
        else {
            i++;
            j++;
            if (j == strlen(slave)) return i - strlen(slave);
        }
    }
    return -1;
}

//KMP finds multiple substrings.
int *kmpPatternMatchingMultiple(const char *master, const char *slave) {
    int next[strlen(slave)];
    getNext(slave, next);
    int i, j;
    //int substring[4];
    int *substring = (int *) malloc(sizeof(int));
    //solution: add a new variable to save the initial address of substring.
    int *newSubstring = substring;
    j = next[0];
    while (i < strlen(master)) {
        if (j == next[0] && master[i] != slave[j]) i++;
        else if (j > next[0] && master[i] != slave[j]) j = next[j - 1];
        else {
            i++;
            j++;
            if (j == strlen(slave)) {
                /**
                 *  There is a trouble that *substring can't acquire value of i-strlen(slave).
                 *  analysis: The new address of substring replaced the old so that the data of old address lost.
                 */
                *substring = i - strlen(slave);
                //Searching more substrings.
                substring++; //In essence,substring++ equals substring=substring+1 so that the address was changed.
                j = next[0];
            }
        }
    }
    /**
     * I want to make the address of last substring to null,but the newSubstring++ wouldn't reach the null.
     */
    //substring = nullptr;
    //return substring; //The address of substring is the last.
    *substring = -1;
    return newSubstring;
}