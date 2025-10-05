### 1. P1 : Finding epsilon closures
```algorithm
main:
    1. Start.
    2. Declare and initialize necessary headers and variables:
        a. Arrays for result[], visited[], and eclose[][].
        b. Integer variables for write pointer, number of states, and number of epsilon transitions.
    3. Read the number of states 'n_states'.
    4. Read the number of epsilon transitions 'n_closes'.
    5. For each epsilon transition:
        a. Read 'from' and 'to' states, and store them as a pair in eclose[].
    6. For each state in states[]:
        a. Call the function find_closure(i) to compute the epsilon closure for state i.
        b. Print the transition
        c. Reset writeptr to 0 for next iteration.
    7. Stop.

add(int state)
    1. Add the given 'state' to visited[] and result[] at position writeptr.
    2. Increment writeptr.

isvisited(int state)
    1. For each index j from 0 to writeptr - 1:
        a. If visited[j] equals the given 'state':
            i. Return true.
    2. If not found, return false.

find_closure(int state)
    1. Add the current 'state' to visited[] and result[] using add(state).
    2. Print the current state.
    3. For each epsilon transition in eclose[]:
        a. If the transition 'from' matches the current 'state':
            i. If 'to' state is not already visited (isvisited(eclose[i][1]) == false):
                - Recursively call find_closure(eclose[i][1]) to add reachable states.
    4. Return after processing all transitions.
```

### 2. P2 : Converting NFA to DFA
```algorithm
main:
    1. Start.
    2. Declare and initialize necessary headers and variables:
        a. Arrays for result[], visited[], eclose[][], transitions[][][], new_trans[][][], e_closure[].
        b. Integer variables for pointers, counts, stateindex[], startstate, finalstates[], etc.
    3. Read the number of states 'n_states'.
    4. Read the number of non-epsilon symbols 'n_symbol'.
    5. Read the number of epsilon transitions 'n_closes'.
    6. For each epsilon transition:
        a. Read 'from' and 'to' states, and store them in eclose[].
    7. Read the number of regular transitions 'n_trans'.
    8. For each regular transition:
        a. Read 'from', 'symbol', 'to' and mark transitions[from][symbol][to] = 1.
    9. Read the start state 'startstate'.
    10. Read the number of accepting states 'n_finalstate'.
    11. Read the accepting states into finalstates[].
    12. Print new start states by computing their epsilon closure via return_state_close(startstate).
    13. For each state, perform the following until no new state is generated:
        a. Compute epsilon closure for the state using return_state_close(i).
        b. If the state’s closure is not already created or has changed, update stateindex[i] and set is_already_created[i].
        c. For each state in its epsilon closure, for each symbol, for each possible destination:
            i. If transitions[e_closure[j]][k][l] exists, update new_trans[i][k][l] = 1.
            ii. Print the transition (q<i> [<symbol>] -> q<l>).
        d. Reset writeptr and e_close_ptr for next iteration.
    14. Stop.

add(int state)
    1. Add the given 'state' to visited[] and result[] at position writeptr.
    2. Increment writeptr.

isvisited(int state)
    1. For each index j from 0 to writeptr - 1:
        a. If visited[j] equals the given 'state':
            i. Return true.
    2. If not found, return false.

find_closure(int state)
    1. Add the current 'state' to visited[] and result[] using add(state).
    2. Add the current 'state' to e_closure[] at position e_close_ptr.
    3. For each epsilon transition in eclose[]:
        a. If the transition 'from' matches the current 'state':
            i. If 'to' state is not already visited (isvisited(eclose[i][1]) == false):
                - Recursively call find_closure(eclose[i][1]) to add reachable states.
    4. Return after processing all transitions.

return_state_close(int state)
    1. Reset writeptr and e_close_ptr to 0.
    2. Call find_closure(state) to compute the epsilon closure for the given state.
```

### 3. P3 : NFA to DFA conversion
```algorithm
main:
    1. Start.
    2. Declare and initialize necessary headers, variables, and structures:
        a. StateSet structures for transitions, DFA maps, and queues.
        b. Integer variables for state and symbol counts, transition counts, pointers.
    3. Read the number of NFA states 'n_states'.
    4. Read the number of transitions 'n_nfa_tr'.
    5. Call init() to reset transition counts and DFA mapping arrays.
    6. For each NFA transition:
        a. Read 'from', 'sym', 'to'.
        b. Store 'to' in nfa_trans[from][sym].states and increment its count.
    7. Print the NFA transition table using print_nfa().
    8. Sort each NFA transition state's destinations via sort_nfa().
    9. Map the initial DFA state and all reachable states using map_dfa_states().
    10. Resolve DFA transitions using nfa_to_dfa_resolver().
    11. Print the DFA transition table using print_dfa().
    12. Print information about dead states.
    13. Stop.

init():
    1. For each state and symbol, set nfa_trans[state][sym].count to 0.
    2. For each index in dfa_map, set count to 0.

sort_nfa():
    1. For each NFA state and symbol:
        a. If there are transitions, call bubble_sort on its states.

dup_dfa_state(int st, int sy):
    1. For each DFA state in dfa_map:
        a. If the count matches, compare all state elements.
        b. If all elements match, return true.
    2. If no match found, return false.

map_dfa_states():
    1. Set dfa_map[0] as the initial DFA state containing state 0.
    2. Enqueue initial DFA state index.
    3. For each NFA state and symbol:
        a. If transition exists and not a duplicate, create new DFA state in dfa_map and enqueue it.

dup_in_dfa_map(int size, int array[size]):
    1. For each DFA state in dfa_map:
        a. If size matches, compare each state.
        b. If all match, return true.
    2. Return false if not found.

in_array_duplicate_found(int size, int array[size], int element):
    1. For each element in array, check if it matches 'element'.
    2. Return true if found, false otherwise.

nfa_to_dfa_resolver():
    1. While the DFA pending queue is not empty:
        a. Dequeue the current DFA state.
        b. For each symbol:
            i. For each NFA state in current DFA set:
                - Gather all possible destination states for this symbol.
                - Avoid duplicates using in_array_duplicate_found.
            ii. Sort the new state set using bubble_sort.
            iii. If new state set is not a duplicate, add to dfa_map, enqueue, and update dfa_trans.
            iv. Set transitions for current DFA state.

print_nfa():
    1. For each NFA state and symbol:
        a. If transition exists, print state, symbol, and destination set.

print_dfa():
    1. For each DFA state and symbol:
        a. Print the DFA state set, symbol, and destination set.
        b. Print '-' for dead state.

```

### 4. P4 : Minimizing DFA
```algorithm
main:
    1. Start.
    2. Declare and initialize necessary headers and variables:
        a. Arrays for dfa[][], final_states[], reachable_states[], reachability_finding_queue[], partition_map[], final_partions[].
        b. Integer variables for state count, symbol count, transition count, final state count, and others.
    3. Read the number of states 'n_states'.
    4. Compute total transitions as n_states * n_symbol.
    5. Read the number of final states 'n_final_states'.
    6. Read and store the final states in final_states[] and set partition_map for each as 1.
    7. Set initial final_partions[0] to 1.
    8. Read all transitions and store in dfa[from][sym] = to; set reachable_states[from] to -1.
    9. Call process_reachable_states() to mark all reachable states.
    10. Print the DFA transition table using print_dfa().
    11. Call process_partitioning() to partition states based on final/non-final and transition behavior.
    12. Call merge_similear_partitions() to merge equivalent partitions.
    13. Print the minimized DFA transitions using print_minimized_dfa().
    14. Print note that * indicates final state.
    15. Stop.

is_empty(int rear, int front)
    1. Return true if rear < front, false otherwise.

print_dfa()
    1. For each state:
        a. If reachable_states[state] is -1, continue.
        b. For each symbol print the transition or '-' if none.

process_reachable_states()
    1. Enqueue state 0 and mark reachable_states[0] = 0.
    2. While queue is not empty:
        a. Dequeue current_state.
        b. For each symbol:
            i. Get next_state from dfa[current_state][sym].
            ii. If next state exist and is not marked as reachable:
                - Mark reachable_states[next_state] = next_state.
                - Enqueue next_state.

process_partitioning()
    1. Repeat until no change:
        a. For each pair of distinct states i, j:
            i. If either is unreachable or already in different partitions, skip.
            ii. For each symbol:
                - set 'same' to false if both transitions does not lead to same partition.
            iii. If not same:
                - For each final partition, if partition_map[i] == final_partions[k]:
                    - Add new partition to final_partions.
                - Set partition_map[j] to new partition and mark changed.

merge_similear_partitions()
    1. For each pair of distinct states i, j:
        a. If either is unreachable or already in same partition, skip.
        b. For each symbol:
            i. set 'same' to true if both transitions lead to same partition.
        c. If same, set partition_map[j] = partition_map[i].

print_minimized_dfa()
    1. For each partition:
        a. For each state s:
            i. If partition_map[s] == p and s is reachable:
                - For each symbol:
                    - Print * if p is a final partition, otherwise print space.
                    - If dfa[s][sym] != -1, print the transition
                - Break after first such state in partition.
```
