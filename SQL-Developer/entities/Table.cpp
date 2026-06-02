#include <iostream>
#include "Table.h"
#include "../utils/Utils.h"

Table::Table(std::string name, std::string fileName) : name(name), fileName(fileName) {}

void Table::showDetails() const {
    int len = cols.size();
    Utils::log("TABLE:");
    for (int i = 0; i < len; i++) {
        Utils::log(cols[i].getName() + " - " + Utils::getTypeAsString(cols[i].getType()));
    }
}

void Table::addColumn(const std::string& name, const std::string& type) {
    cols.push_back(Column(name, Utils::stringToDataType(type)));

    int len = rows.size();

    for(int i = 0; i < len; i++) {
        rows[i].push_back("NULL");
    }
    
    Utils::log("Column added successfully!", Utils::Color::GREEN);
}

//all rows should be the correct size
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

const std::string Table::getFileName() const {
    return fileName;
}

const std::vector<Column>& Table::getColumns() const {
    return cols;
}

const std::vector<std::vector<std::string>>& Table::constGetRows() const {
    return rows;
}

//ros have to be modified in some cases
std::vector<std::vector<std::string>>& Table::getRows() { 
    return rows; 
}