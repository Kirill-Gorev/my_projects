#include <vector>
#include <iostream>
#include <string>
#include <string.h>
extern "C" {
    #include "Table.h"
}

class My_Table{
    TableStruct * struct_t;
    THandle data;
    char* table_name;
public:
    My_Table(): struct_t(new TableStruct){}
    void Fill_Struct(unsigned count, FieldDef* mas);
    void Create_Table(char* name); // Struct_t
    void Open();
    void Drop();
    void Add(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas);
    void Add_a(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas);
    void Add_z(std::vector<std::pair<enum FieldType, std::pair<long, char*>>>& mas);
    void Delete();
    bool ReadFirst();
    bool ReadNext();
    bool ReadLast();
    bool ReadPrevios();
    char* GetText(char* name);
    long GetLong(char* name);
    void Update(char* name, long val);
    void Update(char* name, char* val);
    unsigned FieldLen(char* name);
    enum FieldType FieldType(char* name);
    unsigned FieldNum(char* name);
    char* FieldName(unsigned ind);
    ~My_Table();
};
