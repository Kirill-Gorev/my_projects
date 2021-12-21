#include <vector>
#include <iostream>
#include <string>
#include <string.h>
extern "C" {
    #include "Table.h"
}

Class My_Table{
    struct Table * table;
    TableStruct * struct_t;
    THandle data;
    char* table_name;
public:
    My_Table(): table(new Table), struct_t(new TableStruct){}
    void Fill_Struct(int count, FieldDef* mas);
    void Create_Table(char* name); // Struct_t
    void Open();
    void Drop();
    
    void Add();
    void Delete();
    bool ReadFirst();
    bool ReadNext();
    bool ReadLast();
    bool ReadPrevios();
    void Update();
    void FieldLen(char* name);
    void FieldType(char* name);
    void FieldNum(char* name);
    void FieldName(char* name);
    
    ~My_Table();
};
