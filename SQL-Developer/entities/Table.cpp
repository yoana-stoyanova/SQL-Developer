#include <iostream>
#include "Table.h"
#include "../utils/Utils.h"

//TODO: error handling?
//TODO: add comments

Table::Table(std::string name, std::string fileName) : name(name), fileName(fileName){}

//SHOWCASES TABLE NAME, COLUMNS AND THEIR TYPES
void Table::showDetails() const {
    int len = cols.size();

    for (int i = 0; i < len; i++) {
        Utils::log("TABLE:");
        Utils::log(cols[i].getName() + " - " + Utils::getTypeAsString(cols[i].getType()));
    }
}

//INSERT INTO
void Table::addColumn(const std::string& name, const std::string& type) {
    cols.push_back(Column(name, Utils::stringToDataType(type)));

    int len = rows.size();

    for(int i = 0; i < len; i++) {
        rows[i].push_back("NULL");
    }
    
    Utils::log("Column added successfully!", Utils::Color::GREEN);
}

//INSERT INTO [TABLE NAME] VALUES (SPLIT BY , - CORRESPOND TO COL VALS)
void Table::addRow(const std::vector<std::string>& row) {
    if (row.size() != cols.size()) {
        Utils::log("Invalid number of values!", Utils::Color::RED);
        return;
    }

    rows.push_back(row);
}

std::string Table::getName() const {
    return name; 
}

void Table::setName(const std::string& newName){
    name = newName; 
}

const std::vector<Column>& Table::getColumns() const {
    return cols;
}

const std::vector<std::vector<std::string>>& Table::getRows() const {
    return rows;
}