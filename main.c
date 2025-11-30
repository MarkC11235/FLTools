#include <stdio.h>

#include "dfa.h"

// accepts a*b+c+
DFA* create_M1_dfa(){
    DFA* dfa = create_dfa("M1");
    print_dfa(dfa);

    add_state(dfa, 'A');
    add_state(dfa, 'B');
    add_state(dfa, 'C');
   
    add_alphabet(dfa, 'a');
    add_alphabet(dfa, 'b');
    add_alphabet(dfa, 'c');

    add_transition(dfa, 'A', 'a', 'A');   
    add_transition(dfa, 'A', 'b', 'B');   
    add_transition(dfa, 'B', 'b', 'B');   
    add_transition(dfa, 'B', 'c', 'C');   
    add_transition(dfa, 'C', 'c', 'C');   

    set_start_state(dfa, 'A'); 

    add_final_state(dfa, 'C'); 
    
    print_dfa(dfa);
    
    return dfa;
}

int main(){
    DFA* dfa = create_M1_dfa();

//    string input = screate(10);
//    sappend(input, "aaabccc"); 

    string input;
    sfromfile(input, "input.txt");
    sprint(input);
    lprint(input, ctostr);

    bool res = run_dfa(dfa, input, true);
    printf("Result: %d\n", res);

    destroy_dfa(dfa);
    return 0;
}
