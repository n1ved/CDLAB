#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100
#define PREDEF_SYMBOLS 2

int n_states = 0;
int n_dfa_states = 0;
int n_pending_states = 1;
int n_closes = 0;
int n_sym    = PREDEF_SYMBOLS;
int n_trans  = 0;

int nfa[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
int dfa[MAX_SIZE][MAX_SIZE] = {0};
int current_state[MAX_SIZE] = {0};
int next_state_set[MAX_SIZE] = {0};
int nfa_dfa_map [MAX_SIZE] = {-1};
int nfa_dfa_map_x [MAX_SIZE] = {1};
int unproc_queue[MAX_SIZE];
int top_unproc_queue = 0;
int bottom_unproc_queue = 0;

int start_state = 0;

int next_state_built = 0;
int current_dfa_state = 0;

int from,symbol,to;

void enqueue(int data){
    top_unproc_queue++;
    unproc_queue[top_unproc_queue] = data;
}

void dequeue(){
    bottom_unproc_queue++;
}

void reset_array(int array[MAX_SIZE]){
    for(int i =0 ; i < n_states ; i++)
        array[i] = 0;
}

bool is_empty_state(int state[MAX_SIZE]){
    for(int j=0 ; j<n_states ; j++){
        if(state[j]) return false;
    }
    return true;
}

void proc_next_state(int p_current_state[MAX_SIZE] , int proc_sym , int p_next_state_set[MAX_SIZE]){
    for(int i=0 ; i<n_states ; i++){
        if(p_current_state[i]){
            for(int j=0 ; j<n_states ; j++){
                if(nfa[i][proc_sym][j]){
                    p_next_state_set[j] = 1;
                }
            }
        }
    }
}

bool check_state_matches(){
    for(int i=0 ; i<n_dfa_states ; i++){
        bool local_valid = true;
        for(int j=0 ; j<n_states ; j++){
            if(dfa[i][j] != next_state_set[j])
                local_valid = false;
        }
        if(local_valid)
            return true;
    }
    return false;
}

int main(){
    printf("Enter number of states : ");
    scanf("%d",&n_states);

    printf("Enter start state : ");
    scanf("%d", &start_state);

    printf("Enter number of transitions : ");
    scanf("%d",&n_trans);
    printf("Enter transitions \n");


    for(int i=0 ; i<n_trans ; i++){
        printf("Transition %d ( from , symbol , to ) : ",i+1);
        scanf("%d%d%d",&from,&symbol,&to);
        nfa[from][symbol][to] = 1;
    }

    reset_array(current_state);
    current_state[start_state] = 1;
    for(int j=0 ; j<n_states ; j++){
        dfa[0][j] = current_state[j];
    }
    n_dfa_states = 1;
    enqueue(0);

    while(top_unproc_queue > bottom_unproc_queue){
        int dfa_state_idx = unproc_queue[bottom_unproc_queue + 1];
        dequeue();

        for(int sym=0 ; sym<n_sym ; sym++){
            reset_array(next_state_set);
            proc_next_state(dfa[dfa_state_idx], sym, next_state_set);

            bool found=false;
            int found_idx = -1;

            for(int i=0 ; i<n_dfa_states ; i++){
                bool same = true;
                for(int j=0 ; j<n_states ; j++){
                    if(dfa[i][j] != next_state_set[j]){
                        same = false;
                        break;
                    }
                }
                if(same){
                    found = true;
                    found_idx = i;
                    break;
                }
            }

            if(!is_empty_state(next_state_set) && !found){
                for(int j=0 ; j<n_states ; j++){
                    dfa[n_dfa_states][j] = next_state_set[j];
                }
                enqueue(n_dfa_states);
                n_dfa_states++;
            }
        }
    }

    for(int i=0 ; i<n_dfa_states ; i++){
        bool empty = true;
        for(int j=0 ; j<n_states ;j++){
            if(dfa[i][j]){
                empty = false;
                break;
            }
        }

        if (empty) continue;

        printf("q");
        for(int j=0 ; j<n_states ; j++){
            if(dfa[i][j]){
                printf("%d",j);
            }
        }
        printf("\n");
    }


    return 0;
}
