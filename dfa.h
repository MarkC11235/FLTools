#ifndef DFA_H
#define DFA_H

#include "helpers.h"

// DFA CREATION ===============================================

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

bool is_state_accepting(DFA* dfa, char state){
    foreach(final_state, dfa->final_states, 
        if(state == final_state) return true;
    );
    return false;
}

// DFA RUN ===============================================

typedef struct {
    char code;
    char next_state;
} DFA_Step;

bool is_valid_step(DFA* dfa, char current_state, char input){
    foreach(transition, dfa->transitions,
        if(transition.from == current_state && transition.input == input) return true;
    );
    return false;
}

char get_next_state(DFA* dfa, char current_state, char input){
    foreach(transition, dfa->transitions,
        if(transition.from == current_state && transition.input == input) return transition.to;
    );
    ERROR("State: %c does to have a transition for input: %c", current_state, input);
    return 'x';
}

DFA_Step step_dfa(DFA* dfa, char current_state, char input){
    bool valid_step = is_valid_step(dfa, current_state, input);
    if (!valid_step) return (DFA_Step){.code = 'T', .next_state = 'x'};
    char next_state = get_next_state(dfa, current_state, input);
    bool accept = is_state_accepting(dfa, next_state);
    char code = 'R';
    if(accept) code = 'A';
    return (DFA_Step){.code = code, .next_state = next_state};
}

bool run_dfa(DFA* dfa, list(char) input_tape, bool verbose){
    if(verbose){
        printf("Running %s on input: ", dfa->name);
        lprint(input_tape, ctostr);
    }

    char current_state = dfa->start_state; 
    bool accept = is_state_accepting(dfa, dfa->start_state); // if start state is accepting make it true 
    foreach(c, input_tape,
        if(verbose){
            printf("State: %c\n", current_state);
            printf("Input: %c\n\n", c);
        }

        DFA_Step dfa_step = step_dfa(dfa, current_state, c);
        char code = dfa_step.code;
        switch(code){
            case 'T': // Trap
                if(verbose) printf("Entered Trap State\n");
                return false; // do not accept
                break;
            case 'A': // Accept
                accept = true;
                break;
            case 'R': // Reject
                accept = false;
                break;
            default:
                ERROR("UNKNOWN STATE CODE");
                break;
        }
        current_state = dfa_step.next_state;
    );


    printf("Final State: %c\n\n", current_state);
    return accept;
}










#endif // DFA_H
