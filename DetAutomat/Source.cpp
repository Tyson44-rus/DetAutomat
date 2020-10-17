#include <iostream>

#include <vector>

#include <string>

#include <fstream>

#include <utility>

#include <random>

#include <set>

#include "Automat.h"

using namespace std;

int main() 
{
    locale::global(locale(""));
    try {
        char start;
        ifstream file;
        cout << "Здравствуйте, желаете загрузить автомат? Y/N\n";
        cin >> start;
        do {
            switch (start) {
            case 'Y': {
                while (start == 'Y') {
                    string f, s;
                    cout << "Введите путь к файлу: ";
                    cin >> f;
                    file.open(f);
                    if (!file)
                        throw exception("Ошибка при открытии файла\n");
                    string FileLine;
                    int LCount = 0;
                    while (!file.eof())
                    {
                        getline(file, FileLine);
                        if (!FileLine.empty())
                            LCount++;
                    }
                    if (LCount < 5)
                        throw exception("Недостаточно условий\n");
                    file.close();
                    file.open(f);
                    if (!file)
                        throw exception("Ошибка при открытии файла\n");
                    Automat t;
                    getline(file, s);
                    t.Alphabet_v_ = Split(s, ' ');
                    getline(file, s);
                    t.states_v_ = Split(s, ' ');
                    getline(file, s);
                    t.start_state_ = s;
                    getline(file, s);
                    t.final_states_v_ = Split(s, ' ');
                    while (!file.eof()) {
                        getline(file, s);
                        jump j;
                        vector < string > buf = Split(s, ' ');
                        if (buf.size() != 3)
                            throw exception("Некорректный переход\n");
                        j.Left = buf[0];
                        j.Center = buf[1];
                        j.Right = buf[2];
                        t.state_transition_table_v_.push_back(j);
                        t.add_rule(j.Left, j.Center, j.Right);
                    }
                    file.close();
                    t.Check();
                    vector < string > buf;
                    cout << "Введите символы: ";
                    cin.get();
                    getline(cin, s);
                    removeS(s);
                    for (auto str : s) {
                        string temp;
                        temp.push_back(str);
                        buf.push_back(temp);
                    }
                    set < string > sBuf(buf.begin(), buf.end());
                    for (auto a : sBuf) {
                        bool Check = false;
                        for (auto b : t.Alphabet_) {
                            if (a == b)
                            {
                                Check = true;
                                break;
                            }
                        }
                        if (!Check)
                            throw exception("Строка состоит из неалфавитных символов\n");
                    }
                    cout << endl << (t.string_is_accepted(buf) ? "Строка допускается\n" : "Строка НЕ допускается\n");
                    cout << endl;
                    cout << "Желаете загрузить снова автомат? Y/N\n";
                    cin >> start;
                }
            }
                    break;
            case 'N': {
                file.close();
                exit(0);
                break;
            }
            default:
                cout << "Неправильный символ, повторите\n";
                cout << "Желаете загрузить автомат? Y/N\n";
                cin >> start;
                break;
            }
        } while (true);
        file.close();
    }
    catch (exception e) {
        cout << "Ошибка: " << e.what();
    }
    system("pause");
    return 0;
}