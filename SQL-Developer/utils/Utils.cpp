#include <iostream>
#include <vector>
#include <string>
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

DataType Utils::stringToDataType(const std::string& type) {
    if(type.empty() || type == "NULL"){
        return DataType::NULL_TYPE;

    } else if(type == "INT"){
        return DataType::INT;

    } else if(type == "DOUBLE"){
        return DataType::DOUBLE;

    } else if(type == "STRING"){
        return DataType::STRING;

    } else{
        return DataType::NULL_TYPE;
    }
}

std::vector<std::string> Utils::splitRow(const std::string& row, char sep) {
    std::vector<std::string>  data;

    size_t start = 0;
    size_t end = row.find(sep);

    while(end != std::string::npos) {
        data.push_back(row.substr(start, end - start));
        start = end + 1;
        end = row.find(sep, start);
    }

    data.push_back(row.substr(start));

    return data;
}

std::string Utils::concatRow(const std::vector<std::string>& data, char sep){
    int len = data.size();

    std::string row = "";

    for(int i = 0; i < len - 1; i++){
        row += data[i];
        row += sep;
    }

    row += data[len - 1];
    row += "\n";

    return row;
}

std::vector<Column> Utils::splitHeader(const std::string& header, char sep){
    std::vector<Column> columns;

    std::vector<std::string> data = Utils::splitRow(header, sep);

    int len = data.size();

    for(int i = 0; i < len; i++){
        if(data[i].empty()) continue;

        size_t b1 = data[i].find('[');
        size_t b2 = data[i].find(']');

        if(b1 != std::string::npos && b2 != std::string::npos && b2 > b1) {
            std::string name = data[i].substr(0, b1);
            std::string colType = data[i].substr(b1 + 1, b2 - b1 - 1);
            
            DataType type = stringToDataType(toUpperCase(colType));

            columns.push_back(Column(name, type));
        }
    }

    return columns;
}

std::string Utils::concatHeader(const std::vector<Column>& columns, char sep) {
    int len = columns.size();
    std::string row = "";

    for (int i = 0; i < len - 1; i++) {
        row += columns[i].getName();
        row += "[";
        row += Utils::getTypeAsString(columns[i].getType());
        row += "]";
        row += sep;
    }

    row += columns[len - 1].getName();
    row += "[";
    row += Utils::getTypeAsString(columns[len - 1].getType());
    row += "]\n";

    return row;
}

void Utils::log(const std::string& text, Color col) {
    std::cout << getColorCode(col) << text << getColorCode(Color::DEFAULT) << std::endl;
}

std::string Utils::toUpperCase(std::string s) {
    int len = s.length();

    for(int i = 0; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= ('a' - 'A');
        }
    }

    return s;
}

std::string Utils::fileTableName(const std::string& fileName) {
    size_t start = 0;

    if(fileName.rfind(FILE_PATH, 0) == 0){
        start = FILE_PATH.length();
    }

    size_t end = fileName.length();
    if (fileName.length() >= FILE_TYPE.length() && fileName.substr(fileName.length() - FILE_TYPE.length()) == FILE_TYPE) {
        end = fileName.length() - FILE_TYPE.length();
    }

    return fileName.substr(start, end - start);
}