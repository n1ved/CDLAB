#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int result[MAX_SIZE];
int visited[MAX_SIZE];
int eclose[MAX_SIZE][2];
int writeptr = 0;
int n_states = 0;
int n_closes = 0;

void add(int state){
    visited[writeptr]  = state;
    result[writeptr++] = state;
}

bool isvisited(int state){
    for(int i=0 ; i<writeptr ; i++){
        if(visited[i] == state)
          return true;
    }
    return false;
}

void find_closure(int state){
    add(state);
    printf("q%d, ",state);
    for(int i = 0 ; i<n_closes ; i++){
        if(eclose[i][0] == state){
            if(!isvisited(eclose[i][1])){
                find_closure(eclose[i][1]);
            }
        }
    }
}

int main(){
    printf("Enter number of states : ");
    scanf("%d",&n_states);
    printf("Enter number of epsilion transitions : ");
    scanf("%d",&n_closes);
    printf("Enter each epsilion transitions [from , to] \n");
    for(int i=0 ; i<n_closes ; i++){
        scanf("%d%d",&eclose[i][0],&eclose[i][1]);
    }

     for(int i=0 ; i<n_states ; i++){
        printf("q%d : { ",i);
        find_closure(i);
        printf("\b\b }\n");
        writeptr=0;
    }
}
