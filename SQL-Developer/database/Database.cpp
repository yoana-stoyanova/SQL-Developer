#include "Database.h"
#include "../utils/Utils.h"
#include <iostream>

Database::Database() {}

//TODO: const?
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

void Database::importTable(const std::string& fileName, const std::string& table) {
    if(findTableByName(table) != nullptr) {
        Utils::log("Table with name " + table + " already exists!", Utils::Color::RED);
        return;
    }
    
    //TODO: file stuff

    Utils::log("Table " + table + " successfully imported!", Utils::Color::GREEN);
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

void Database::describe(const std::string& table) const{
    const Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }
    
    t->showDetails();
}

void Database::printTable(const std::string& table) const{
    const Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }

    //TODO: paging with get rows??
}

void Database::exportTable(const std::string& table, const std::string& fileName) {
    const Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }

    //TODO: file stuff

    Utils::log("Table '" + table + "' successfully exported to " + fileName, Utils::Color::GREEN);
}

void Database::select(size_t colIdx, const std::string& value, const std::string& table) const {
    const Table* t = findTableByName(table);

    if (t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }
    //TODO: get the rows, paginations???
}

void Database::addColumn(const std::string& table, const std::string& col, const std::string& type) {
    Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }

    t->addColumn(col, type);

    Utils::log("Column " + col + " added successfully to table " + table + "!", Utils::Color::GREEN);
}

void Database::updateRow(const std::string& table, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& targetValue) {
    Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }
    // TODO: get the rows
}

void Database::deleteRows(const std::string& table, size_t col, const std::string& value){
    Table* t = findTableByName(table);

    if(t == nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return;
    }

    //TODO: delete rows
}

void Database::insertRow(const std::string& table, const std::vector<std::string>& row) {
    Table* t = findTableByName(table);

    if(t == nullptr){
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
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

    // TODO: join
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

int Database::count(const std::string& table, size_t searchCol, const std::string& searchValue) const {
    const Table* t = findTableByName(table);

    if(t = nullptr) {
        Utils::log("Table " + table + " not found.", Utils::Color::RED);
        return -1;
    }
    
    int count = 0;

    // TODO: count rows
    return count;
}

void Database::aggregate(const std::string& table, size_t searchCol, const std::string& searchValue, size_t targetCol, const std::string& operation) {
    Table* t = findTableByName(table);

    if (t == nullptr) {
        Utils::log("Table '" + table + " not found.", Utils::Color::RED);
        return;
    }
    //TODO: stuff
}