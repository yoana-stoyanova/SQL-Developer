#include "Column.h"
#include "../utils/Utils.h"

Column::Column(const std::string& name, Utils::DataType type): name(name), type(type){}

std::string Column::getName() const{
    return name;
}

Utils::DataType Column::getType() const {
    return type;
}