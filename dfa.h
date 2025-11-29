#ifndef DFA_H
#define DFA_H

#include "helpers.h"

def_list(char);

typedef struct {
    char from;
    char input;
    char to;
} transition;
def_list(transition);

#define transition_to_str(buf, transition) snprintf(buf, sizeof(char) * ITEM_TO_STR_BUF_LEN, "(%c, %c -> %c)", transition.from, transition.input, transition.to)


typedef struct {
    char* name;
    list(char) states;
    list(char) alphabet;
    list(transition) transitions;
    char start_state;
    list(char) final_states;
} DFA;

DFA* create_dfa(char* name){
    DFA* dfa = malloc(sizeof(DFA));
    
    dfa->name = name;
    dfa->states = lcreate(char, 10);
    dfa->alphabet = lcreate(char, 10);
    dfa->transitions = lcreate(transition, 10);
    dfa->final_states = lcreate(char, 10);

    INFO("CREATED DFA");
    return dfa;
}

void destroy_dfa(DFA* dfa){
    ldestroy(dfa->states);
    ldestroy(dfa->alphabet);
    ldestroy(dfa->transitions);
    ldestroy(dfa->final_states);
    free(dfa);
    INFO("DESTROYED DFA");
}

void print_dfa(DFA* dfa){
    printf("DFA %s = (\n", dfa->name);
   
    printf("\tStates (%d) = ", dfa->states.count);
    lprint(dfa->states, ctostr);

    printf("\tAlphabet (%d) = ", dfa->alphabet.count);
    lprint(dfa->alphabet, ctostr);
    
    printf("\ttransitions (%d) = ", dfa->transitions.count);
    lprint(dfa->transitions, transition_to_str);
    
    printf("\tStart State = %c\n", dfa->start_state);

    printf("\tFinal States (%d) = ", dfa->final_states.count);
    lprint(dfa->final_states, ctostr);

    printf(")\n");
}

void add_state(DFA* dfa, char state){
    lpush(dfa->states, state); 
}

void add_alphabet(DFA* dfa, char a){
    lpush(dfa->alphabet, a); 
}

void add_transition(DFA* dfa, char from, char input, char to){
    transition t = {.from = from, .input = input, .to = to};
    lpush(dfa->transitions, t);
}

void set_start_state(DFA* dfa, char state){
    dfa->start_state = state; 
}

void add_final_state(DFA* dfa, char state){
    lpush(dfa->final_states, state); 
}










#endif // DFA_H
