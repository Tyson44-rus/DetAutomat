#include "Automat.h"

bool Automat::string_is_accepted(vector < string > buf) {
    cur_state_ = start_state_;
    for (auto c_it = buf.begin(); c_it != buf.end(); ++c_it) {
        if (!successfully_set_cur_state_for_symb(*c_it)) {
            return false;
        }
    }
    return cur_state_is_final();
}

void Automat::add_rule(T_state cur_state, string symb, T_state new_state) {
    state_transition_table_[T_state_and_symb(cur_state, symb)] = new_state;
}

void Automat::add_final_state(T_state state) {
    final_states_.insert(state);
}

bool Automat::successfully_set_cur_state_for_symb(string symb) {
    auto tr_it = state_transition_table_.find(T_state_and_symb(cur_state_, symb));

    bool bool_res = tr_it != state_transition_table_.end();

    if (bool_res) {
        cur_state_ = tr_it->second;
    }
    return bool_res;
}

bool Automat::cur_state_is_final() {
    return final_states_.count(cur_state_) != 0;
}

void Automat::Check() {
    if (Alphabet_v_.empty())
        throw exception("Алфавит пуст\n");
    if (states_v_.empty())
        throw exception("Список вершин пуст\n");
    if (start_state_.empty())
        throw exception("Начальная вершина пуста\n");
    if (final_states_v_.empty())
        throw exception("Список конечных вершин пуст\n");
    if (state_transition_table_v_.empty())
        throw exception("Переходы пусты\n");

    bool flag = false;

    for (auto s : states_v_)
        if (s == start_state_) {
            flag = true;
            break;
        }
    if (!flag)
        throw exception("Начальная вершина не состоит в списке\n");

    for (int i = 0; i < Alphabet_v_.size(); i++) {
        for (int j = i + 1; j < Alphabet_v_.size(); j++) {
            if (Alphabet_v_[i] == Alphabet_v_[j]) {
                throw exception("В алфавите повторяются символы\n");
            }
        }
    }

    Alphabet_.insert(Alphabet_v_.begin(), Alphabet_v_.end());

    for (int i = 0; i < states_v_.size(); i++) {
        for (int j = i + 1; j < states_v_.size(); j++) {
            if (states_v_[i] == states_v_[j]) {
                throw exception("В вершинах есть повторения\n");
            }
        }
    }

    states_.insert(states_v_.begin(), states_v_.end());

    for (int i = 0; i < final_states_v_.size(); i++) {
        bool Check = false;
        for (int j = 0; j < states_v_.size(); j++) {
            if (final_states_v_[i] == states_v_[j]) {
                Check = true;
            }
        }
        if (!Check) {
            throw exception("Конечное состояние не входит в список\n");
        }
    }

    final_states_.insert(final_states_v_.begin(), final_states_v_.end());

    for (auto s : state_transition_table_) {
        bool Check = false;
        for (int j = 0; j < states_v_.size(); j++) {
            if (states_v_[j] == s.first.first || states_v_[j] == s.second) {
                Check = true;
            }
        }
        if (!Check) {
            throw exception("В переходах есть несуществующие вершины\n");
        }
    }

    for (auto s : state_transition_table_) {
        bool Check = false;
        for (int j = 0; j < Alphabet_v_.size(); j++) {
            if (Alphabet_v_[j] == s.first.second) {
                Check = true;
            }
        }
        if (!Check) {
            throw exception("В переходах есть несуществующие символы\n");
        }
    }

    for (int i = 0; i < state_transition_table_v_.size(); i++) {
        for (int j = i + 1; j < state_transition_table_v_.size(); j++) {
            if (state_transition_table_v_[i].Left == state_transition_table_v_[j].Left && state_transition_table_v_[i].Center == state_transition_table_v_[j].Center) {
                throw exception("В переходах есть повторы\n");
            }
        }
    }

}

vector < string > Split(string s, char sep) {
    vector < string > r;
    int i = 0, start, end;
    while (i < s.size()) {
        while (i < s.size() && s[i] == sep)
            i++;
        start = i;
        while (i < s.size() && s[i] != sep)
            i++;
        end = i;
        if (start < end)
            r.push_back(s.substr(start, end - start));
    }
    return r;
}

string removeS(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            s.erase(i, 1);
            i--;
        }
    }
    return s;
}