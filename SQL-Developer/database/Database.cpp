#include "Database.h"
#include "../utils/Utils.h"
#include "../fileManager/FileManager.h"
#include <iostream>
#include "../utils/DataType.h"

Database::Database() {}

Table* Database::findTableByName(const std::string& name){
    int len = tables.size();

    for(int i = 0; i < len; i++){
        if (tables[i].getName() == name) {
            return &tables[i];
        }
    }

    return nullptr;
}

const Table* Database::findTableByName(const std::string& name) const {
    int len = tables.size();

    for(int i = 0; i < len; i++){
        if (tables[i].getName() == name) {
            return &tables[i];
        }
    }

    return nullptr;
}

void Database::importTable(const std::string& fileName, const std::string& tableName) {
    if(findTableByName(tableName) != nullptr) {
        Utils::log("Table with name " + tableName + " already exists!", Utils::Color::RED);
        return;
    }
    
    Table newTable = Table(tableName, fileName);
    
    if(FileManager::loadTable(fileName, newTable)) {
        tables.push_back(newTable);

        FileManager::addToCatalog(tableName, fileName, catalogFileName);

        Utils::log("Table successfully imported!", Utils::Color::GREEN);

    } else {
        Utils::log("Couldn't import table.", Utils::Color::RED);
    }
}

void Database::showTables() const{
    if(tables.empty()) {
        Utils::log("No tables found in the DB.", Utils::Color::YELLOW);
        return;
    }

    Utils::log("Loaded tables:");

    int len = tables.size();

    for(int i = 0; i < len; i++){
        Utils::log(tables[i].getName());
    }
}

void Database::describe(const std::string& tableName) const{
    const Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }
    
    t->showDetails();
}

void Database::printTable(const std::string& tableName) const{
    const Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    int len = t->getColumns().size();
    std::string headers = "";
    std::string divider = "";

    for(int i = 0; i < len; i++){
        headers += t->getColumns()[i].getName();
        divider += "---------------------------";

        if(i < len - 1){
            headers += " \t| ";
        }
    }
    
    Utils::log(headers);
    Utils::log(divider);

    const std::vector<std::vector<std::string>>& rows = t->constGetRows();

    int len2 = rows.size();

    if(len2 == 0){
        Utils::log("Table is empty", Utils::Color::YELLOW);
        return;
    }

    for(int i = 0; i < len2; i++){

        std::string output = "";
        int len3 = rows[i].size();

        for(int j = 0; j < len3; j++){
            output += rows[i][j];
            if(j < len3 - 1){
                output += " \t| ";
            }
        }

        Utils::log(output);
    }
}

void Database::exportTable(const std::string& tableName, const std::string& fileName) {
    const Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    if(FileManager::saveTable(fileName, *t)){
        FileManager::addToCatalog(tableName, fileName, catalogFileName);
        Utils::log("Table successfully exported!", Utils::Color::GREEN);

    } else {
        Utils::log("Couldn't export table.", Utils::Color::RED);
    }
}

void Database::select(size_t colIdx, const std::string& value, const std::string& tableName) const {
    const Table* t = findTableByName(tableName);

    if (t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }
    
    if(colIdx >= t->getColumns().size()){
        Utils::log("Out of bounds.", Utils::Color::RED);
        return;
    }

    const std::vector<std::vector<std::string>>& rows = t->constGetRows();

    int len = rows.size();
    int count = 0;

    for(int i = 0; i < len; i++){
        if(colIdx < rows[i].size()){
            if(rows[i][colIdx] == value){
                count++;
                
                std::string output = "";
                int len2 = rows[i].size();
                
                for(int j = 0; j < len2; j++){
                    output += rows[i][j];
                    if(j < len2 - 1){
                        output += " \t| ";
                    }
                }
                Utils::log(output);
            }
        }
    }

    if(count > 0){
        Utils::log("Found " + std::to_string(count) + " matching rows.", Utils::Color::GREEN);
    } else {
        Utils::log("No matching rows found.", Utils::Color::YELLOW);
    }
}

void Database::addColumn(const std::string& tableName, const std::string& col, const std::string& type) {
    Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    t->addColumn(col, type);

    Utils::log("Column added successfully to table!", Utils::Color::GREEN);
}

void Database::updateRow(const std::string& tableName, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& targetValue) {
    Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    std::vector<std::vector<std::string>>& rows = t->getRows();

    int count = 0;
    int len = rows.size();

    for(int i = 0; i < len; i++) {
        if(searchCol >= rows[i].size() || targetCol >= rows[i].size()){
            continue;
        }

        if(rows[i][searchCol] == searchValue){
            rows[i][targetCol] = targetValue;
            count++;
        }
    }

    if(count > 0) {
        Utils::log("Successfully updated " + std::to_string(count) + " rows!", Utils::Color::GREEN);
    } else {
        Utils::log("No matching rows.", Utils::Color::YELLOW);
    }
}

void Database::deleteRows(const std::string& table, size_t col, const std::string& value){
    Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    std::vector<std::vector<std::string>>& rows = t->getRows();
    size_t count = 0;

    for(int i = 0; i < rows.size(); i++) {
        if(col < rows[i].size() && rows[i][col] == value) {
            rows.erase(rows.begin() + i);
            count++;
            
            i--;
        }
    }

    if(count > 0) {
        Utils::log("Successfully deleted " + std::to_string(count) + " rows!", Utils::Color::GREEN);
    } else {
        Utils::log("No matching rows.", Utils::Color::YELLOW);
    }
}

void Database::insertRow(const std::string& table, const std::vector<std::string>& row) {
    Table* t = findTableByName(table);

    if(t == nullptr){
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }

    t->addRow(row);
}

void Database::innerJoin(const std::string& t1, size_t col1, const std::string& t2, size_t col2){
    const Table* table1 = findTableByName(t1);
    const Table* table2 = findTableByName(t2);
    
    if(!table1 || !table2){
        Utils::log("Not all tables exist.", Utils::Color::RED);
        return;
    }

    int len1 = table1->getColumns().size();
    int len2 = table2->getColumns().size();

    if(col1 >= len1 || col2 >= len2) {
        Utils::log("Out of bounds.", Utils::Color::RED);
        return;
    }

    if(table1->getColumns()[col1].getType() != table2->getColumns()[col2].getType()) {
        Utils::log("Column types don't match.", Utils::Color::RED);
        return;
    }

    std::string newName = t1 + '.' + t2;

    if(findTableByName(newName) != nullptr) {
        Utils::log("Joined table " + newName + " already exists!", Utils::Color::RED);
        return;
    }

    Table newTable = Table(newName, "{JOIN_TABLE}");

    for(int i = 0; i < len1; i++){
        newTable.addColumn(table1->getColumns()[i].getName(), Utils::getTypeAsString(table1->getColumns()[i].getType()));
    }

    for(int i = 0; i < len2; i++) {
        newTable.addColumn(table2->getColumns()[i].getName(), Utils::getTypeAsString(table1->getColumns()[i].getType()));
    }

    const std::vector<std::vector<std::string>>& rows1 = table1->constGetRows();
    const std::vector<std::vector<std::string>>& rows2 = table2->constGetRows();

    size_t count = 0;

    int len11 = rows1.size();
    for(int i = 0; i < len11; i++){
        if(col1 >= rows1[i].size()) {
            continue;
        }

        int len22 = rows2.size();

        for(int j = 0; j < len22; j++){
            if(col2 >= rows2[j].size()) {
                continue;
            }
            
            if(rows1[i][col1] == rows2[j][col2]){
                std::vector<std::string> newRow;

                int rlen1 = rows1[i].size();
                for(int a = 0; a < rlen1; a++){
                    newRow.push_back(rows1[i][a]);
                }

                int rlen2 = rows2[j].size();
                for(int b = 0; b < rows2[j].size(); b++){
                    newRow.push_back(rows2[j][b]);
                }

                newTable.addRow(newRow);
                count++;
            }
        }
    }

    tables.push_back(newTable);

    if(count > 0) {
        Utils::log("Inner join successful! Created table " + newName + " with " + std::to_string(count) + " rows.", Utils::Color::GREEN);
    } else {
        Utils::log("Inner join successful, but 0 matching rows found.", Utils::Color::YELLOW);
    }
}

void Database::renameTable(const std::string& oldName, const std::string& newName){
    Table* t = findTableByName(oldName);

    if(t == nullptr) {
        Utils::log("Table " + oldName+ " not found.", Utils::Color::RED);
        return;
    }

    if(findTableByName(newName) != nullptr){
        Utils::log("The name " + newName + " is taken.", Utils::Color::RED);
        return;
    }
    
    t->setName(newName);

    Utils::log("Table successfully renamed!", Utils::Color::GREEN);
}

int Database::count(const std::string& tableName, size_t searchCol, const std::string& searchValue) const {
    const Table* t = findTableByName(tableName);

    if(t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return -1;
    }

    int count = 0;

    const std::vector<std::vector<std::string>>& rows = t->constGetRows();
    int len = rows.size();

    for(int i = 0; i < len; i++){
        if(searchCol < rows[i].size()){
            if(rows[i][searchCol] == searchValue){
                count++;
            }
        }
    }

    return count;
}

void Database::aggregate(const std::string& tableName, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& operation) {
    Table* t = findTableByName(tableName);

    if (t == nullptr) {
        Utils::log("Table not found.", Utils::Color::RED);
        return;
    }
    
    if(searchCol >= t->getColumns().size() || targetCol >= t->getColumns().size()) {
        Utils::log("Out of bounds.", Utils::Color::RED);
        return;
    }

    DataType type = t->getColumns()[targetCol].getType();

    if(type != DataType::INT && type != DataType::DOUBLE) {
        Utils::log("Column isn't INT or DOUBLE.", Utils::Color::RED);
        return;
    }

    const std::vector<std::vector<std::string>>& rows = t->constGetRows();

    int len = rows.size();
    
    int count = 0;
    double res = 0.0;

    if(operation == "product"){
        res = 1.0;

    } else if(operation == "maximum"){
        res = -__DBL_MAX__;

    } else if(operation == "minimum"){
        res = __DBL_MAX__;
    }

    for(int i = 0; i < len; i++) {
        if(searchCol >= rows[i].size() || targetCol >= rows[i].size()) {
            continue;
        }

        if(rows[i][searchCol] == searchValue) {
            count++;
            
            double curr = 0.0;

            if(!rows[i][targetCol].empty()){
                curr = std::stod(rows[i][targetCol]);
            }

            if(operation == "sum"){
                res += curr;

            } else if(operation == "product"){
                res *= curr;

            } else if(operation == "maximum"){
                if(curr > res) {
                    res = curr;
                }

            } else if(operation == "minimum"){
                if(curr < res) {
                    res = curr;
                }

            } else {
                Utils::log("Operation not found.", Utils::Color::RED);
                return;
            }
        }
    }

    if(count == 0) {
        Utils::log("No matching rows.", Utils::Color::YELLOW);
        return;
    }

    if((operation == "maximum" && res == -__DBL_MAX__) || (operation == "minimum" && res == __DBL_MAX__)){
         Utils::log("Result: no MIN or MAX.", Utils::Color::GREEN);
         return;
    }

    std::string str;
    if(type == DataType::INT) {
        str = std::to_string(static_cast<long long>(res));

    } else {
        str = std::to_string(res);
    }

    Utils::log("Result: " + str, Utils::Color::GREEN);
}