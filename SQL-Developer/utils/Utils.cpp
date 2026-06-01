#include <iostream>
#include "Utils.h"

std::string Utils::getColorCode(Color col) {
    switch (col) {
        case Color::RED:
            return "\033[31m";

        case Color::GREEN:
            return "\033[32m";

        case Color::YELLOW:
            return "\033[33m";

        case Color::DEFAULT:
        default:
            return "\033[0m";
    }
}

std::string Utils::getTypeAsString(DataType type){
    switch (type) {
        case DataType::INT:
            return "INT";
        case DataType::DOUBLE:
            return "DOUBLE";
        case DataType::STRING:
            return "STRING";
        case DataType::NULL_TYPE:
            return "NULL_TYPE";
        default:
            return "NOT_FOUND";
    }
}

Utils::DataType Utils::stringToDataType(const std::string& type) {
    if(type.empty() || type == "NULL"){
        return DataType::NULL_TYPE;

    } else if(type == "INT") {
        return DataType::INT;

    } else if(type == "DOUBLE") {
        return DataType::DOUBLE;

    } else if(type == "STRING") {
        return DataType::STRING;
        
    } else {
        return DataType::NULL_TYPE;
    }
}

void Utils::log(const std::string& text, Color col) {
    std::cout << getColorCode(col) << text << getColorCode(Color::DEFAULT) << std::endl;
}