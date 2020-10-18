#pragma once

#include <fstream>

#include <iostream>

#include <map>

#include <set>

#include <string>

#include <utility>

#include <vector>

using namespace std;

struct jump {
    string Left;
    string Center;
    string Right;
};

class Automat {
public:
    typedef string T_state;
    typedef pair < T_state, string > T_state_and_symb;
    typedef map < T_state_and_symb, T_state > T_state_transition_table;
    typedef set < T_state > T_states;
    typedef vector < T_state > T_states_v;
    typedef vector < jump > T_state_transition_table_v;
    T_state cur_state_;
    T_state start_state_;
    T_state_transition_table state_transition_table_;
    T_state_transition_table_v state_transition_table_v_;
    T_states final_states_;
    T_states states_;
    T_states Alphabet_;
    T_states_v states_v_;
    T_states_v Alphabet_v_;
    T_states_v final_states_v_;
public:
    Automat() {}
    bool string_is_accepted(vector < string > buf);
    void add_rule(T_state cur_state, string symb, T_state new_state);
    void add_final_state(T_state state);
    bool successfully_set_cur_state_for_symb(string symb);
    bool cur_state_is_final();
    void Check();
    ~Automat() {}
};

vector < string > Split(string s, char sep);
void removeS(string& s);
