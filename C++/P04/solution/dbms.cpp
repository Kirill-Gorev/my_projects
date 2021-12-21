void My_Table::Fill_Struct(unsigned count, FieldDef* mas){
    struct_t->numOfFields = count;
    struct_t->fieldsDef = mas;
}

void My_Table::Create_Table(char* name){
    if(createTable(name, struct_t) != OK)
        throw "error Table, Create";
}

void My_Table::Open(){
    if(openTable(name, &data) != OK)
        throw "error Table, Open";
}

void My_Table::Drop(){
    if(closeTable(data) != OK)
        throw "error Table, Close";
}
    
void My_Table::Add(){

}

void My_Table::Delete(){

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

void My_Table::Update(){
    
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
    if(getFieldNum(data, &len) != OK)
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
    if(deleteTable(table_name) != OK)
        throw "error Table, ~My_Table";
}
