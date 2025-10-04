#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10
#define PREDEF_SYM 2


int n_states = 0;
int n_symbol = PREDEF_SYM;
int n_transitions = 0;
int n_final_states = 0;

int from, sym, to;

int dfa[MAX_SIZE][PREDEF_SYM] = { {-1} };
int final_states[MAX_SIZE] = {0};
int reachable_states[MAX_SIZE] = {-1};

int reachability_finding_queue[MAX_SIZE] = {-1};
int reachability_front = 0;
int reachability_rear = 0;

int partition_map[MAX_SIZE] = {0};
int final_partions[MAX_SIZE] = {0};
int n_partitions = 2;
int n_final_partitions = 1;

int dequeue(int q[MAX_SIZE] , int front){
    return q[front++];
}
void enqueue(int q[MAX_SIZE] , int rear , int state){
    q[rear++] = state;
}

bool is_empty(int rear , int front){
    return rear < front;
}

void print_dfa(){
    for(int state=0 ; state<n_states ; state++){
        if(reachable_states[state] == -1)
            continue;
        for(int sym=0 ; sym<n_symbol ; sym++){
            printf("q%d ==%d==> q%d\n", state, sym, dfa[state][sym]);
        }
    }
}

void process_reachable_states(){
    enqueue(reachability_finding_queue , reachability_rear , 0);
    reachability_rear++;
    reachable_states[0] = 0;

    while(!is_empty(reachability_rear , reachability_front)){
        int current_state = dequeue(reachability_finding_queue , reachability_front);
        reachability_front++;
        for(int sym=0 ; sym<n_symbol ; sym++){
            int next_state = dfa[current_state][sym];
            if(next_state != -1 && reachable_states[next_state] == -1){
                reachable_states[next_state] = next_state;
                enqueue(reachability_finding_queue , reachability_rear , next_state);
                reachability_rear++;
            }
        }
    }
}

void process_partitioning(){
    bool changed = false;
    do{
        changed = false;
        for(int i=0 ; i<n_states ; i++){
            if(reachable_states[i] == -1)
                continue;
            for(int j=0 ; j<n_states ; j++){
               if (reachable_states[j] == -1 || i == j || partition_map[i] != partition_map[j])
                   continue;
               bool same = true;
               for(int sym = 0 ; sym<n_symbol ; sym++){
                   if(partition_map[dfa[i][sym]] != partition_map[dfa[j][sym]]){
                       same = false;
                       break;
                   }
               }
                if(!same){
                     for(int k=0 ; k<n_final_partitions ; k++){
                         if(partition_map[i] == final_partions[k]){
                             final_partions[n_final_partitions++] = n_partitions;
                             break;
                         }
                     }
                     partition_map[j] = n_partitions++;
                     changed = true;
                }
            }
        }
    }while(changed);
}

void merge_similear_partitions(){
    for(int i=0 ; i<n_states ; i++){
        if(reachable_states[i] == -1)
            continue;
        for(int j=0 ; j<n_states ; j++){
           if (reachable_states[j] == -1 || i == j || partition_map[i] == partition_map[j])
               continue;
           bool same = true;
           for(int sym = 0 ; sym<n_symbol ; sym++){
                if(partition_map[dfa[i][sym]] != partition_map[dfa[j][sym]]){
                     same = false;
                     break;
                }
            }
            if(same){
                partition_map[j] = partition_map[i];
            }
        }
    }

}

void print_minimized_dfa(){
    for(int p = 0 ; p<n_partitions ; p++){
        for(int s = 0 ; s<n_states ; s++){
            if(partition_map[s] == p && reachable_states[s] != -1){
                bool is_final = false;
                for(int sym = 0 ; sym<n_symbol ; sym++){
                    int to_state = dfa[s][sym];
                    for(int i=0 ; i<n_final_partitions ; i++){
                        if(p == final_partions[i]){
                            printf("*");
                            is_final = true;
                            break;
                        }
                    }
                    if(!is_final){
                        printf(" ");
                    }
                    if(to_state != -1)
                        printf("q%d==%d==>q%d \n", p, sym, partition_map[to_state]);
                }
                break;
            }
        }
    }
}

int main(){

    printf("Enter number of states: ");
    scanf("%d", &n_states);
    n_transitions = n_states * n_symbol;
    printf("Enter number of final states: ");
    scanf("%d", &n_final_states);
    printf("Enter final states: ");
    for(int i=0 ; i<n_final_states ; i++){
        scanf("%d",&final_states[i]);
        partition_map[final_states[i]] = 1;
    }
    final_partions[0] = 1;
    printf("Enter transitions (from, sym, to):\n");
    for(int i=0 ; i<n_transitions ; i++){
        printf("Transition %d: ", i+1);
        scanf("%d %d %d", &from, &sym, &to);
        dfa[from][sym] = to;
        reachable_states[from] = -1;
    }
    process_reachable_states();
    printf("\nDFA Transition Table:\n");
    print_dfa();
    process_partitioning();
    merge_similear_partitions();
    printf("\nMinimized DFA Transitions:\n");
    print_minimized_dfa();
    printf("* is finals state\n");
    return 0;
}
