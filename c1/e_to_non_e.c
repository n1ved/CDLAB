#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int result[MAX_SIZE];
int visited[MAX_SIZE];
int eclose[MAX_SIZE][2];

int transitions[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
int new_trans[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int e_closure[MAX_SIZE];
int e_close_ptr = 0;

int stateindex[MAX_SIZE];


int startstate;
int n_finalstate = 0;
int finalstates[MAX_SIZE];

int is_already_created[MAX_SIZE];

int writeptr = 0;
int n_states = 0;
int n_symbol = 0;
int n_closes = 0;

int n_trans  = 0;

int from , symbol , to;


void add(int state){
 visited[writeptr] = state;
  result[writeptr++] = state;
}

bool isvisited(int state){
  for(int i=-1 ; i<writeptr ; i++){
    if(visited[i] == state)
        return true;
  }
  return false;
}



void find_closure(int state){
  add(state);
  e_closure[e_close_ptr++] = state;
  for(int i=0 ; i<n_closes ; i++){
    if(eclose[i][0] == state){
      if(!isvisited(eclose[i][1])){
        find_closure(eclose[i][1]);
      }
    }
  }
}
void return_state_close(int state){
  writeptr = 0;
  e_close_ptr = 0; 
  find_closure(state);
}
int main(){
  printf("Enter  number of states : ");
  scanf("%d" , &n_states);
  printf("Enter number of non-epsilion symbols : ");
  scanf("%d" , &n_symbol);

  printf("Enter number of epsilion transitions : ");
  scanf("%d" , &n_closes);
  printf("Enter each epsilion transitions [from , to]\n");
  for(int i=0 ; i<n_closes ; i++){
    scanf("%d%d",&eclose[i][0] , &eclose[i][1]);
  }

  printf("Enter number of regular transitions : ");
  scanf("%d" , &n_trans);

  printf("Enter each regular transitions [from ,symbol, to]\n");
  for(int i=0 ; i<n_trans ; i++){
    scanf("%d%d%d", &from , &symbol , &to);
    transitions[from][symbol][to] = 1;
  }

  printf("Enter Start State : ");
  scanf("%d", &startstate);
  
  printf("Enter number of accepting states : ");
  scanf("%d", &n_finalstate);

  printf("Enter final states : ");
  for(int i=0 ; i<n_finalstate ; i++){
    scanf("%d" , &finalstates[i]);
  }

  printf("New Start States : ");
  return_state_close(startstate);

  for(int i=0 ; i<e_close_ptr ; i++){
    printf("q%d ",e_closure[i]);
  }

  printf("\n");

  bool new_state_generated = true;
  while(new_state_generated){
    for(int i=0 ; i<n_states ; i++){
      new_state_generated = false;
      return_state_close(i);
      if(!is_already_created[i]){
        stateindex[i] = e_close_ptr;
        new_state_generated = true;
      }else if(stateindex[i] != e_close_ptr){
        stateindex[i] = e_close_ptr;
        new_state_generated = true;
      }else{
        continue;
      }
      is_already_created[i] = 1;
      for(int j=0 ; j<e_close_ptr ; j++){
        for(int k=0 ; k <n_symbol ; k++){
          for(int l=0 ; l<n_states ; l++){
            if(transitions[e_closure[j]][k][l]){
              //return_state_close(l);
              //for(int m = 0 ; m<e_close_ptr ; m++){
                new_trans[i][k][l] = 1;
                printf("q%d [%d] -> q%d\n", i , k , l);
              //}
            }
          }
        }
      }
      writeptr = 0;
      e_close_ptr = 0;
    }
  }

}
