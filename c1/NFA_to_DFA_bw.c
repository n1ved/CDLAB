#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define PREDEF_SYM 2

typedef struct {
    int states[MAX_SIZE];
    int count;
} StateSet ;



int n_states = 0;
int n_symbol = PREDEF_SYM;
int n_nfa_tr = 0;

int from,sym,to;

StateSet nfa_trans[MAX_SIZE][PREDEF_SYM];
StateSet dfa_map[MAX_SIZE];
int dfa_map_ptr = 1;
StateSet dfa_trans[MAX_SIZE][PREDEF_SYM];

int pending_queue[MAX_SIZE*3] = {0};
int pq_front = 0;
int pq_rear = 0;

void enqueue(int state){
    pending_queue[pq_rear++] = state;
}
int dequeue(){
    return pending_queue[pq_front++];
}

void init_nfa(){
    for(int state=0 ; state<n_states ; state++){
        for(int sym=0 ; sym<n_symbol ; sym++){
            nfa_trans[state][sym].count = 0;
        }
    }
}

void sort_nfa(){
    for(int st =0 ; st<n_states ; st++){
        for(int sy=0 ; sy<n_symbol ; sy++){
            int count = nfa_trans[st][sy].count;
            if(count){
                for(int i=0 ; i<count ; i++){
                    for(int j=0 ; j < count - i - 1 ; j++){
                        if(nfa_trans[st][sy].states[j] > nfa_trans[st][sy].states[j+1]){
                            int temp = nfa_trans[st][sy].states[j];
                            nfa_trans[st][sy].states[j] = nfa_trans[st][sy].states[j+1];
                            nfa_trans[st][sy].states[j+1] = temp;
                        }
                    }
                }
            }
        }
    }
}

void bubble_sort(int size , int array[size]){
    for(int i=0 ; i<size ; i++){
        for(int j=0 ; j < size - i - 1 ; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}


bool dup_dfa_state(int st , int sy){
    int count = nfa_trans[st][sy].count;
    for(int dfa =0 ; dfa<dfa_map_ptr ; dfa++){
        if(dfa_map[dfa].count != count)
            continue;
        bool broke = false;
        for(int i=0 ; i<count ; i++){
            if(dfa_map[dfa].states[i] != nfa_trans[st][sy].states[i]){
                broke = true;
                break;
            }
        }
        if(!broke){
            return true;
        }
    }
    return false;
}

void map_dfa_states(){
    dfa_map[0].states[0] = 0;
    dfa_map[0].count = 1;
    dfa_map_ptr = 1;
    enqueue(0);
    for(int st=0 ; st<n_states ; st++){
        for(int sy=0 ; sy<n_symbol ; sy++){
            if(nfa_trans[st][sy].count || !dup_dfa_state(st, sy)){
                dfa_map[dfa_map_ptr].count = 0;
                for(int ct=0 ; ct<nfa_trans[st][sy].count ; ct++){
                    dfa_map[dfa_map_ptr].states[dfa_map[dfa_map_ptr].count++] = nfa_trans[st][sy].states[ct];
                }
                enqueue(dfa_map_ptr++);
                printf("Generated new set : ");
                for(int i=0 ; i<dfa_map[dfa_map_ptr-1].count ; i++){
                    printf("%d,",dfa_map[dfa_map_ptr-1].states[i]);
                }
                printf("\b\n");
            }

        }
    }
}

void print_nfa(){
    for(int state=0 ; state<n_states ; state++){
        for(int sym=0 ; sym<n_symbol ; sym++){
            if(nfa_trans[state][sym].count){
                printf("q%d\t%d\t{",state,sym);
                for(int to_i = 0 ; to_i <nfa_trans[state][sym].count ; to_i++){
                    printf("%d,",nfa_trans[state][sym].states[to_i]);
                }
                printf("\b}\n");
            }
        }
    }
}

void print_dfa(){
    for(int state=0 ; state<dfa_map_ptr ; state++){
        for(int sym=0 ; sym<n_symbol ; sym++){
            if(dfa_trans[state][sym].count){
                printf("q{");
                for(int to_i = 0 ; to_i<dfa_map[state].count ; to_i++){
                    printf("%d,",dfa_map[state].states[to_i]);
                }
                printf("\b}\t\t%d\t\t{",sym);
                for(int to_i = 0 ; to_i <dfa_trans[state][sym].count ; to_i++){
                    printf("%d,",dfa_trans[state][sym].states[to_i]);
                }
                printf("\b}\n");
            }
        }
    }
}

bool dup_in_dfa_map(int size , int array[size]){
    for(int i=0 ; i<dfa_map_ptr ; i++){
        if(dfa_map[i].count != size)
            continue;
        bool broke = false;
        for(int j=0 ; j<size ; j++){
            if(dfa_map[i].states[j] != array[j]){
                broke = true;
                break;
            }
        }
        if(!broke)
            return true;
    }
    return false;
}

void print_map(){
    for(int dfa =0 ; dfa<dfa_map_ptr ; dfa++){
        printf("DFA STATE %d : {",dfa);
        for(int i=0 ; i<dfa_map[dfa].count ; i++){
            printf("%d,",dfa_map[dfa].states[i]);
        }
        printf("\b}\n");
    }
}

bool in_array_duplicate_found(int size , int array[size] , int element){
    for(int i=0 ; i<size ; i++){
        if(array[i] == element)
            return true;
    }
    return false;
}

void nfa_to_dfa_resolver(){
    while(pq_rear >= pq_front){
        printf("Processing QUEUE : ");
        for(int i = pq_front ; i<pq_rear ; i++)
            printf(" %d" , pending_queue[i]);
        printf("\n");
        print_map();
        int current_dfa_state = dequeue();
        StateSet current_set = dfa_map[current_dfa_state];
        for(int sy = 0 ; sy<n_symbol ; sy++){
            int new_state[MAX_SIZE] = {0};
            int new_state_count = 0;
            for(int dst = 0 ; dst < current_set.count ; dst++){
                int state_in_nfa = current_set.states[dst];
                if(nfa_trans[state_in_nfa][sy].count){
                    for(int nst = 0 ; nst<nfa_trans[state_in_nfa][sy].count ; nst++){
                        if(!in_array_duplicate_found(new_state_count, new_state , nfa_trans[state_in_nfa][sy].states[nst]))
                            new_state[new_state_count++] = nfa_trans[state_in_nfa][sy].states[nst];
                    }
                }
            }
            bubble_sort(new_state_count, new_state);
            if(new_state_count && !dup_in_dfa_map(new_state_count, new_state)){
                printf("Current new state : q{");
                for(int i=0 ; i<new_state_count ; i++)
                    printf("%d,",new_state[i]);
                printf("\b}\n");
                dfa_trans[current_dfa_state][sy].count = new_state_count;
                dfa_map[dfa_map_ptr++].count = new_state_count;
                for(int i=0 ; i<new_state_count ; i++){
                    dfa_trans[current_dfa_state][sy].states[i] = new_state[i];
                    dfa_map[dfa_map_ptr].states[i] = new_state[i];
                }
                enqueue(dfa_map_ptr++);
                print_map();
            }
        }
    }
}

int main(){

    printf("Enter number of states : ");
    scanf("%d",&n_states);

    printf("Enter number of transitions : ");
    scanf("%d",&n_nfa_tr);

    init_nfa();

    printf("Enter transitions\n");
    for(int s_idx = 0 ; s_idx < n_nfa_tr ; s_idx++){
        printf("TRANSITION %d [from , sym , to] : ",s_idx+1 );
        scanf("%d%d%d",&from,&sym,&to);
        nfa_trans[from][sym].states[nfa_trans[from][sym].count] = to;
        nfa_trans[from][sym].count++;
    }

    print_nfa();
    sort_nfa();
    map_dfa_states();
    nfa_to_dfa_resolver();
    print_dfa();
    return 0;
}
