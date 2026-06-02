#include "Column.h"

Column::Column(const std::string& name, DataType type): name(name), type(type){}

std::string Column::getName() const{
    return name;
}

DataType Column::getType() const {
    return type;
}