#include <iostream>
#include <vector>

#include "App.h"
#include "../utils/Utils.h"
#include "../fileManager/FileManager.h"

App::App() {
    db = Database(); 
}

void App::save() {
    db.saveAllTables();
}

void App::help() const {
    std::cout << "\nCommands:\n"
              << "save\t\t\tsaves all tables and their changes\n"
              << "help\t\t\tprints commands\n"
              << "exit\t\t\texits the program\n\n"
              << "import <file name> <table name>\n"
              << "showtables\n"
              << "describe <table name>\n"
              << "print <table name>\n"
              << "export <table name> <file name>\n"
              << "select <column-n> <value> <table name>\n"
              << "addcolumn <table name> <column name> <column type>\n"
              << "update <table name> <search col> <search val> <target col> <target val>\n"
              << "delete <table name> <search col> <search val>\n"
              << "insert <table name> <val1> ... <valN>\n"
              << "innerjoin <table1> <col1> <table2> <col2>\n"
              << "rename <old name> <new name>\n"
              << "count <table name> <search col> <search val>\n"
              << "aggregate <table name> <search col> <search val> <target col> <operation>\n\n";
}

void App::executeCommand(const std::string& cmd) {
    std::vector<std::string> data = Utils::splitRow(cmd, ' ');

    int len = data.size();

    for(int i = 0; i < len; i++) {
        if(data[i].empty()) {
            data.erase(data.begin() + i);
            i--;
            len--;
        }
    }

    if(data.empty()) return;

    if(data[0] == "help"){
        help();

    } else if(data[0] == "save") {
        save();

    } else if(data[0] == "import") {
        if(data.size() >= 3) {
            db.importTable(data[1], data[2]);
        }

    } else if(data[0] == "showtables"){
        db.showTables();

    } else if(data[0] == "describe") {
        if(data.size() >= 2) {
            db.describe(data[1]);
        }

    } else if(data[0] == "print") {
        if(data.size() >= 2) {
            db.printTable(data[1]);
        }

    } else if(data[0] == "export"){
        if(data.size() >= 3) {
            db.exportTable(data[1], data[2]);
        }

    } else if(data[0] == "select") {
        if(data.size() >= 4) {
            db.select(std::stoul(data[1]), data[2], data[3]);
        }

    } else if(data[0] == "addcolumn") {
        if(data.size() >= 4) {
            db.addColumn(data[1], data[2], data[3]);
        }

    } else if(data[0] == "update") {
        if(data.size() >= 6) {
            db.updateRow(data[1], std::stoul(data[2]), data[3], std::stoul(data[4]), data[5]);
        }

    } else if(data[0] == "delete"){
        if(data.size() >= 4) {
            db.deleteRows(data[1], std::stoul(data[2]), data[3]);
        }

    } else if(data[0] == "insert") {
        if(data.size() >= 3) {
            std::vector<std::string> values;
            int argCount = data.size();

            for(int i = 2; i < argCount; i++) {
                values.push_back(data[i]);
            }

            db.insertRow(data[1], values);
        }
    } else if(data[0] == "innerjoin") {
        if(data.size() >= 5) {
            db.innerJoin(data[1], std::stoi(data[2]), data[3], std::stoi(data[4]));
        }

    } else if(data[0] == "rename") {
        if(data.size() >= 3) {
            db.renameTable(data[1], data[2]);
        }

    } else if(data[0] == "count") {
        if(data.size() >= 4) {
            db.count(data[1], std::stoul(data[2]), data[3]);
        }

    } else if(data[0] == "aggregate") {
        if(data.size() >= 6) {
            db.aggregate(data[1], std::stoul(data[2]), data[3], std::stoul(data[4]), data[5]);
        }
    }
}

void App::run() {
    Utils::log("Type commands:", Utils::Color::GREEN);
    std::string input;

    while(true) {
        std::cout << "> ";

        if(!std::getline(std::cin, input)) {
            break; 
        }

        if(input == "exit") {
            Utils::log("Exiting the program.");
            break;
        }

        executeCommand(input);
    }
}