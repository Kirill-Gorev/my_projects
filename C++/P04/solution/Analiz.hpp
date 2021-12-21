#include <iostream>
#include <vector>

template <class T, int max_size > class Stack
{
    T s[max_size];
    int top;
public:
    Stack(){top = 0;}
    void reset() { top = 0; }
    void push(T i);
    T pop();
    bool is_empty();
    bool is_full();
};

enum type_of_lex
{
    LEX_NUM, // 0
    LEX_ID, // 1
    LEX_OP, // 2
    LEX_SCOB, // 3
    LEX_OP_SRAVN, // 4
    LEX_AP, // 5
    LEX_ZAP, // 6
    LEX_SLUG, // 7
    LEX_TYPE, // 8
    LEX_BOOL, // 9
    LEX_LOG, // 10
    LEX_NULL // 11
};


class Lex{
    type_of_lex T;
    std::string value;
public:
    Lex (type_of_lex t, std::string &v): T(t), value(v){}
    void print();
    type_of_lex get_type ();
    std::string get_value ();
};

void Lex::print(){
    std::cout << "Type: " << T << "; Val: " << value << ";" << std::endl;
}
type_of_lex Lex::get_type () { return T; }
std::string Lex::get_value () { return value; }

class Scanner{
    char sim;
    int num;
    std::string s_pars;
    type_of_lex t;
    bool fl_end;
    std::string val;
    std::vector <Lex> lexsems;
    std::vector<Lex>::iterator it;
    void clear_val();
    void clear();
    void gc();
    void ident();
    Lex get_lex();
    void S();
    void S_P();
    void I_P();
    void U_P();
    void D_P();
    void C_P();
    void DR_P();
    void LIST_P();
    void NAME_T();
    void NAME_P();
    void NAME();
    void F_VAL();
    void STR();
    void NUM();
    void LIST_O_P();
    void O_P();
    void TYPE_P();
    void WHERE_K();
    void WHERE_N();
    void LONG_LOG_SENT();
    void WHERE_DOP();
    void CONST_LIST();
    void LONG_LOG_T();
    void OP_ADD();
    void LONG_LOG_M();
    void OP_M();
    void LONG_VAL();
    void DOP();
    void OP_C();
    static void check_op();
    static void check_not();
    static void eq_type();
public:
    explicit Scanner(std::string &s);
    void SA();
    void parser();
    void print();
};