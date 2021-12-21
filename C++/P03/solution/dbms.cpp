#include "dbms.hpp"
extern "C" {
    #include "Table.h"
}

void My_Table::Fill_Struct(unsigned count, FieldDef* mas){
    struct_t->numOfFields = count;
    struct_t->fieldsDef = mas;
}

void My_Table::Create_Table(char* name){
    table_name = name;
    if(createTable(name, struct_t) != OK)
        throw "error Table, Create";
}

void My_Table::Open(){
    if(openTable(table_name, &data) != OK)
        throw "error Table, Open";
}

void My_Table::Drop(){
    if(closeTable(data) != OK)
        throw "error Table, Close";
}
    
void My_Table::Add(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas){
    if(createNew(data) != OK)
        throw "error Table, Add";
    for(unsigned i = 0; i < struct_t->numOfFields; i++){
        if(mas[i].first == Text)
            if(putTextNew(data, struct_t->fieldsDef[i].name, mas[i].second.second) != OK)
                throw "error Table, Add";
        if(mas[i].first == Long)
            if(putLongNew(data, struct_t->fieldsDef[i].name, mas[i].second.first) != OK)
                throw "error Table, Add";
    }
    if(insertNew(data) != OK)
        throw "error Table, Add";
}

void My_Table::Add_a(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas){
    if(createNew(data) != OK)
        throw "error Table, Add_a";
    for(unsigned i = 0; i < struct_t->numOfFields; i++){
        if(mas[i].first == Text)
            if(putTextNew(data, struct_t->fieldsDef[i].name, mas[i].second.second) != OK)
                throw "error Table, Add_a";
        if(mas[i].first == Long)
            if(putLongNew(data, struct_t->fieldsDef[i].name, mas[i].second.first) != OK)
                throw "error Table, Add_a";
    }
    if(insertaNew(data) != OK)
        throw "error Table, Add_a";
}

void My_Table::Add_z(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas){
    if(createNew(data) != OK)
        throw "error Table, Add_z";
    for(unsigned i = 0; i < struct_t->numOfFields; i++){
        if(mas[i].first == Text)
            if(putTextNew(data, struct_t->fieldsDef[i].name, mas[i].second.second) != OK)
                throw "error Table, Add_z";
        if(mas[i].first == Long)
            if(putLongNew(data, struct_t->fieldsDef[i].name, mas[i].second.first) != OK)
                throw "error Table, Add_z";
    }
    if(insertzNew(data) != OK)
        throw "error Table, Add_z";
}

void My_Table::Delete(){
    if(deleteRec(data) != OK)
        throw "error Table, Delete";
}

bool My_Table::ReadFirst(){
    if(moveFirst(data) != OK)
        throw "error Table, Read";
    return beforeFirst(data);
}

bool My_Table::ReadNext(){
    if(moveNext(data) != OK)
        throw "error Table, Read";
    return afterLast(data);
}

bool My_Table::ReadLast(){
    if(moveLast(data) != OK)
        throw "error Table, Read";
    return afterLast(data);
}

bool My_Table::ReadPrevios(){
    if(moveNext(data) != OK)
        throw "error Table, Read";
    return beforeFirst(data);
}

void My_Table::Update(char* name, char* val){
    if(startEdit(data) != OK)
        throw "error Table, Add_a";
    if(putText(data, name, val) != OK)
        throw "error Table, Add_a";
    if(finishEdit(data) != OK)
        throw "error Table, Add_a";
}

void My_Table::Update(char* name, long val){
    if(startEdit(data) != OK)
        throw "error Table, Add_a";
    if(putLong(data, name, val) != OK)
        throw "error Table, Add_a";
    if(finishEdit(data) != OK)
        throw "error Table, Add_a";
}

unsigned My_Table::FieldLen(char * name){
    unsigned len;
    if(getFieldLen(data, name, &len) != OK)
        throw "error Table, FieldLen";
    return len;
}

enum FieldType My_Table::FieldType(char * name){
    enum FieldType type;
    if(getFieldType(data, name, &type) != OK)
        throw "error Table, FieldType";
    return type;
}

unsigned My_Table::FieldNum(char * name){
    unsigned len;
    if(getFieldsNum(data, &len) != OK)
        throw "error Table, FieldNum";
    return len;
}

char* My_Table::FieldName(unsigned ind){
    char* name;
    if(getFieldName(data, ind, &name) != OK)
        throw "error Table, FieldName";
    return name;
}

My_Table::~My_Table(){
    Drop();
    delete struct_t;
}

char* My_Table::GetText(char* name){
    char* val;
    if(getText(data, name, &val) != OK)
        throw "error Table, FieldNum";
    return val;
}

long My_Table::GetLong(char* name){
    long len;
    if(getLong(data, name, &len) != OK)
        throw "error Table, FieldNum";
    return len;
}
