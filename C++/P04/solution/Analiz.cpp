#include "Analiz.hpp"

template <class T, int max_size >
void Stack <T, max_size >::push(T i){
    if(!is_full()) {
        s[top] = i;
        ++top;
    } else throw "Stack_is_full";
}

template <class T, int max_size >
bool Stack <T, max_size >::is_empty(){ return top == 0; }

template <class T, int max_size >
bool Stack <T, max_size >::is_full() { return top == max_size; }

template <class T, int max_size >
T Stack <T, max_size >::pop(){
    if(!is_empty()) {
        --top;
        return s[top];
    } else throw "Stack_is_empty";
}

Stack <type_of_lex, 100> Stack_lex;

void Scanner::check_op () {
    type_of_lex t1, t2, op, t3 = LEX_NUM, r = LEX_BOOL;
    t2 = Stack_lex.pop();
    op = Stack_lex.pop();
    t1 = Stack_lex.pop();
    if ( op==LEX_OP ) {
        r = LEX_NUM;
        if ( t1 == t2 && t1 == t3 )
            Stack_lex.push(r);
        else throw "wrong types are in operation";
    }
    if (op == LEX_LOG) {
        t3 = LEX_BOOL;
        if ( t1 == t2 && t1 == t3 )
            Stack_lex.push(r);
        else throw "wrong types are in operation";
    }
    if (op == LEX_OP_SRAVN) {
        r = LEX_BOOL;
        if (t1 == t2) Stack_lex.push(r);
        else throw "wrong types are in operation";
    }
}

void Scanner::check_not (){
    if (Stack_lex.pop() != LEX_BOOL) throw "wrong type is in not";
    else Stack_lex.push (LEX_BOOL);
}

void Scanner::eq_type ()
{
    if ( Stack_lex.pop() != Stack_lex.pop() ) throw "wrong types are in :=";
}

Scanner::Scanner(std::string &s){
    sim = ' ';
    s_pars = s;
    fl_end = false;
    num = 0;
    t = LEX_NULL;
}
void Scanner::clear_val(){
    val.clear();
}
void Scanner::clear(){
    lexsems.clear();
    s_pars.clear();
    fl_end = false;
    num = 0;
}
void Scanner::gc(){
    if(num == 0) {
        sim = s_pars[0];
        num = 1;
    } else {
        num++;
        sim = s_pars[num - 1];
    }
    if(sim == '\0') fl_end = true;
}
void Scanner::ident(){
    if((sim != '_') && !isalpha(sim)) throw "error LA, error code 3";
    else val += sim;
    size_t i = 0;
    gc();
    while((sim == '_') || isalpha(sim) || isdigit(sim)){
        i++;
        if((sim == '+') || (sim == '-') || (sim == '*') || (sim == '(') || (sim == ')')){
            break;
        }
        val += sim;
        gc();
    }
    if((sim != ' ') && !fl_end) throw "error LA, code 1";
    else t = LEX_ID;
}
Lex Scanner::get_lex(){
    while (sim == ' '){
        gc();
    }
    if (fl_end) {
        Lex lex(LEX_NULL, val);
        return lex;
    }
    switch (sim) {
        case ',':
            val += sim;
            t = LEX_ZAP;
            gc();
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            val += sim;
            t = LEX_OP;
            gc();
            break;
        case '=':
            val += sim;
            t = LEX_OP_SRAVN;
            gc();
            break;
        case '>':
        case '<':
            val += sim;
            t = LEX_OP_SRAVN;
            gc();
            if(sim == '='){
                val += sim;
                gc();
            }
            break;
        case '!':
            val += sim;
            t = LEX_OP_SRAVN;
            gc();
            if(sim == '='){
                val += sim;
                gc();
            } else throw "error LA, error code 4";
            break;
        case '(':
        case ')':
        case '[':
        case ']':
            val += sim;
            t = LEX_SCOB;
            gc();
            break;
        case '\'':
            val += sim;
            t = LEX_AP;
            gc();
            while(sim != '\''){
                if(fl_end || (sim == ' ')) throw "error apostrof";
                val += sim;
                gc();
            }
            val += sim;
            gc();
            break;
        case '0':
            val += sim;
            t = LEX_NUM;
            gc();
            if(!fl_end && (sim != ' ')) throw "error LA, error code 5";
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':{
            bool fl = false;
            val += sim;
            t = LEX_NUM;
            gc();
            while (!fl_end && (sim != ' ')) {
                if((sim == '+') || (sim == '-') || (sim == '*') || (sim == '(') || (sim == ')')
                || (sim == '[') || (sim == ']') || (sim == '=') || (sim == '<') || (sim == '>') || (sim == '!')){
                    fl = true;
                    break;
                }
                if ((sim < '0') || (sim > '9')) throw "error LA, code 2";
                val += sim;
                gc();
            }
            if(!fl_end && (sim != ' ') && !fl) throw "error LA, code 2";
            break;
        }
        case 'S':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'E') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'T') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        break;
                    }
                    ident();
                } else if(sim == 'L'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'E') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'C') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                t = LEX_ID;
                                break;
                            }
                            if (sim == 'T') {
                                val += sim;
                                gc();
                                if (fl_end || (sim == ' ')) {
                                    break;
                                } else ident();
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'I':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'N') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    break;
                }
                if(sim == 'T') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        break;
                    }
                    if (sim == 'O') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            break;
                        }
                        ident();
                    } else ident();
                } else if(sim == 'S'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'E') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'R') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                t = LEX_ID;
                                break;
                            }
                            if (sim == 'T') {
                                val += sim;
                                gc();
                                if (fl_end || (sim == ' ')) {
                                    break;
                                }
                                ident();
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'U':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'P') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'D'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'A') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'T') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                t = LEX_ID;
                                break;
                            }
                            if (sim == 'E') {
                                val += sim;
                                gc();
                                if (fl_end || (sim == ' ')) {
                                    break;
                                } else ident();
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'D':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'E') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'L'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'E') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'T') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                t = LEX_ID;
                                break;
                            }
                            if (sim == 'E') {
                                val += sim;
                                gc();
                                if (fl_end || (sim == ' ')) {
                                    break;
                                } else ident();
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else if(sim == 'R') {
                val += sim;
                gc();
                if (fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if (sim == 'O') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if (sim == 'P') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            break;
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'C':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'R') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'E'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'A') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'T') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                t = LEX_ID;
                                break;
                            }
                            if (sim == 'E') {
                                val += sim;
                                gc();
                                if (fl_end || (sim == ' ')) {
                                    break;
                                } else ident();
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'F':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'R') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'O'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'M') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            break;
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'T':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'A') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'B'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'L') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'E') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                break;
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else if(sim == 'E') {
                val += sim;
                gc();
                if (fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if (sim == 'X') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if (sim == 'T') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_TYPE;
                            break;
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'L':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'I') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'K'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'E') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            break;
                        } else ident();
                    } else ident();
                } else ident();
            } else if(sim == 'O') {
                val += sim;
                gc();
                if (fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if (sim == 'N') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if (sim == 'G') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_TYPE;
                            break;
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'N':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'O') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'T'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        break;
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'W':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'H') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'E'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_ID;
                        break;
                    }
                    if(sim == 'R') {
                        val += sim;
                        gc();
                        if (fl_end || (sim == ' ')) {
                            t = LEX_ID;
                            break;
                        }
                        if (sim == 'E') {
                            val += sim;
                            gc();
                            if (fl_end || (sim == ' ')) {
                                break;
                            } else ident();
                        } else ident();
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'A':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'N') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if(sim == 'D'){
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        t = LEX_LOG;
                        break;
                    } else ident();
                } else ident();
            } else if(sim == 'L') {
                val += sim;
                gc();
                if (fl_end || (sim == ' ')) {
                    t = LEX_ID;
                    break;
                }
                if (sim == 'L') {
                    val += sim;
                    gc();
                    if (fl_end || (sim == ' ')) {
                        break;
                    } else ident();
                } else ident();
            } else ident();
            break;
        case 'O':
            t = LEX_SLUG;
            val += sim;
            gc();
            if(fl_end || (sim == ' ')) {
                t = LEX_ID;
                break;
            }
            if(sim == 'R') {
                val += sim;
                gc();
                if(fl_end || (sim == ' ')) {
                    t = LEX_LOG;
                    break;
                } else ident();
            } else ident();
            break;
        default: ident();
    }
    Lex lex(t, val);
    clear_val();
    return lex;
}

void Scanner::OP_C() {
    std::cout << "OP_C" << std::endl;
    Stack_lex.push(LEX_OP_SRAVN);
    if((it->get_value() != ">") && (it->get_value() != "<") && (it->get_value() != "=") &&
       (it->get_value() != ">=") && (it->get_value() != "<=") && (it->get_value() != "!="))
        throw "error SA, code 23";
    it++;
}

void Scanner::LONG_VAL() {
    std::cout << "LONG_VAL" << std::endl;
    if(it->get_type() == LEX_NUM){
        Stack_lex.push(LEX_NUM);
        NUM();
    } else if(it->get_type() == LEX_AP){
        Stack_lex.push(LEX_AP);
        STR();
    } else if(it->get_type() == LEX_ID){
        Stack_lex.push(LEX_ID);
        it++;
    } else throw "error SA, code 22";
}

void Scanner::DOP(){
    std::cout << "DOP" << std::endl;
    if(it->get_type() == LEX_SCOB){
        it++;
    } else{
        OP_C();
        LONG_LOG_SENT();
        check_op();
        if(it->get_type() != LEX_SCOB) throw "error SA, code 21";
        it++;
    }
}

void Scanner::LONG_LOG_M() {
    std::cout << "LONG_LOG_M" << std::endl;
    if(it->get_value() == "NOT"){
        Stack_lex.push(LEX_BOOL);
        it++;
        LONG_LOG_M();
        check_not();
    } else if(it->get_type() == LEX_SCOB){
        it++;
        LONG_LOG_SENT();
        DOP();
    } else{
        LONG_VAL();
    }
}

void Scanner::OP_M() {
    std::cout << "OP_M" << std::endl;
    if((it->get_value() == "*") || (it->get_value() == "/") || (it->get_value() == "%")) Stack_lex.push(LEX_OP);
    if(it->get_value() == "AND") Stack_lex.push(LEX_BOOL);
    if((it->get_value() != "*") && (it->get_value() != "/") && (it->get_value() != "%") &&
        (it->get_value() != "AND")) throw "error SA, code 20";
    it++;
}

void Scanner::LONG_LOG_T() {
    std::cout << "LONG_LOG_T" << std::endl;
    LONG_LOG_M();
    if(it != lexsems.end()) {
        while ((it->get_value() == "*") || (it->get_value() == "/") || (it->get_value() == "%") ||
               (it->get_value() == "AND")) {
            OP_M();
            LONG_LOG_M();
            check_op();
            if (it == lexsems.end()) break;
        }
    }
}

void Scanner::OP_ADD() {
    std::cout << "OP_ADD" << std::endl;
    if((it->get_value() == "+") || (it->get_value() == "-")) Stack_lex.push(LEX_OP);
    if(it->get_value() == "OR") Stack_lex.push(LEX_BOOL);
    if((it->get_value() != "+") && (it->get_value() != "-") && (it->get_value() != "OR"))
        throw "error SA, code 19";
    it++;
}

void Scanner::LONG_LOG_SENT() {
    std::cout << "LONG_LOG_SENT" << std::endl;
    LONG_LOG_T();
    if(it != lexsems.end()) {
        while ((it->get_value() == "+") || (it->get_value() == "-") || (it->get_value() == "OR")) {
            OP_ADD();
            LONG_LOG_T();
            check_op();
            if (it == lexsems.end()) break;
        }
    }
}

void Scanner::CONST_LIST() {
    std::cout << "CONST_LIST" << std::endl;
    if(it->get_type() == LEX_AP){
        STR();
        while (it->get_type() == LEX_ZAP) {
            it++;
            STR();
        }
    } else if(it->get_type() == LEX_NUM){
        NUM();
        while (it->get_type() == LEX_ZAP) {
            it++;
            NUM();
        }
    } else throw "error SA, code 18";
}

void Scanner::WHERE_DOP() {
    std::cout << "WHERE_DOP" << std::endl;
    if (it->get_value() == "NOT") it++;
    if (it->get_value() == "LIKE") {
        it++;
        STR();
    } else if (it->get_value() == "IN") {
        it++;
        if (it->get_type() != LEX_SCOB) throw "error SA, code 17";
        it++;
        CONST_LIST();
        if (it->get_type() != LEX_SCOB) throw "error SA, code 17";
        it++;
    }
}

void Scanner::WHERE_N() {
    std::cout << "WHERE_N" << std::endl;
    if(it->get_value() == "ALL"){
        it++;
    } else {
        std::cout << it->get_value() << std::endl;
        LONG_LOG_SENT();
        std::cout << it->get_value() << std::endl;
        if(it != lexsems.end()) WHERE_DOP();
    }
}

void Scanner::WHERE_K() {
    std::cout << "WHERE_K" << std::endl;
    if(it->get_value() != "WHERE") throw "error SA, code 16";
    it++;
    WHERE_N();
}

void Scanner::DR_P() {
    if(it->get_value() != "TABLE") throw "error SA, code 15";
    it++;
    NAME_T();
}

void Scanner::TYPE_P() {
    std::cout << "TYPE_P" << std::endl;
    if(it->get_value() == "TEXT"){
        it++;
        if(it->get_type() != LEX_SCOB) throw "error SA, code 13";
        it++;
        NUM();
        if(it->get_type() != LEX_SCOB) throw "error SA, code 13";
        it++;
    } else if(it->get_value() == "LONG") it++;
    else throw "error SA, code 14";
}

void Scanner::O_P() {
    std::cout << "O_P" << std::endl;
    NAME_P();
    TYPE_P();
}

void Scanner::LIST_O_P() {
    std::cout << "LIST_O_P" << std::endl;
    O_P();
    while (it->get_type() == LEX_ZAP) {
        it++;
        O_P();
    }
}

void Scanner::C_P() {
    if(it->get_value() != "TABLE") throw "error SA, code 12";
    it++;
    NAME_T();
    if(it->get_type() != LEX_SCOB) throw "error SA, code 13";
    it++;
    LIST_O_P();
    if(it->get_type() != LEX_SCOB) throw "error SA, code 13";
    it++;
}

void Scanner::D_P() {
    if(it->get_value() != "FROM") throw "error SA, code 11";
    it++;
    NAME_T();
    WHERE_K();
}

void Scanner::U_P() {
    NAME_T();
    if(it->get_value() != "SET") throw "error SA, code 9";
    it++;
    NAME_P();
    if(it->get_value() != "=") throw "error SA, code 10";
    it++;
    LONG_LOG_SENT();
    WHERE_K();
}

void Scanner::NUM() {
    std::cout << "NUM" << std::endl;
    if(it->get_type() != LEX_NUM) throw "error SA, code 8";
    it++;
}

void Scanner::STR() {
    std::cout << "STR" << std::endl;
    if(it->get_type() != LEX_AP) throw "error SA, code 7";
    it++;
}

void Scanner::F_VAL() {
    if(it->get_type() == LEX_AP) STR();
    else if (it->get_type() == LEX_NUM) NUM();
    else throw "error SA, code 6";
}

void Scanner::I_P() {
    if(it->get_value() != "INTO") throw "error SA, code 4";
    it++;
    NAME_T();
    if(it->get_type() != LEX_SCOB) throw "error SA, code 5";
    it++;
    F_VAL();
    while (it->get_type() == LEX_ZAP) {
        it++;
        F_VAL();
    }
    if(it->get_type() != LEX_SCOB) throw "error SA, code 5";
    it++;
}

void Scanner::NAME() {
    std::cout << "NAME" << std::endl;
    if(it->get_type() != LEX_ID) throw "error SA, code 3";
    it++;
}

void Scanner::NAME_P() {
    NAME();
}

void Scanner::NAME_T() {
    NAME();
}

void Scanner::LIST_P() {
    std::cout << "LIST_P" << std::endl;
    if(it->get_value() == "*"){
        it++;
    } else {
        NAME_P();
        while (it->get_type() == LEX_ZAP) {
            it++;
            NAME_P();
        }
    }
}

void Scanner::S_P() {
    std::cout << "S_P" << std::endl;
    LIST_P();
    if(it->get_value() != "FROM") throw "error SA, code 2";
    it++;
    NAME_T();
    WHERE_K();
}

void Scanner::S(){
    std::cout << "S" << std::endl;
    if(it->get_value() == "SELECT") {
        it++;
        S_P();
    } else if(it->get_value() == "INSERT") {
        it++;
        I_P();
    } else if(it->get_value() == "UPDATE") {
        it++;
        U_P();
    } else if(it->get_value() == "DELETE") {
        it++;
        D_P();
    } else if(it->get_value() == "CREATE") {
        it++;
        C_P();
    } else if(it->get_value() == "DROP") {
        it++;
        DR_P();
    } else throw "error first word";
    if(it != lexsems.end()) throw "error SA, code 1";
}

void Scanner::SA(){
    it = lexsems.begin();
    S();
}

void Scanner::parser(){
    while(!fl_end){
        Lex lex = get_lex();
        if(lex.get_type() != 11) lexsems.push_back(lex);
    }
}

void Scanner::print(){
    auto it_p = lexsems.begin();
    for(int i = 1; it_p != lexsems.end(); i++, it_p++)
        it_p->print();
}