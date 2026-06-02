#include <iostream>
#include <vector>

#include "App.h"
#include "../utils/Utils.h"
#include "../fileManager/FileManager.h"

App::App() : currFile(""), isFileOpened(false) {
    db = Database(); 
}

void App::openFile(const std::string& fileName) {
    if(isFileOpened) {
        Utils::log("A file is already open", Utils::Color::RED);
        return;
    }

    currFile = fileName;
    Utils::log("Successfully opened file.", Utils::Color::GREEN);
    isFileOpened = true;
}

void App::closeFile(){
    if(!isFileOpened) {
        Utils::log("No file is open", Utils::Color::RED);
        return;
    }

    Utils::log("Successfully closed " + currFile, Utils::Color::GREEN);
    currFile = "";
    isFileOpened = false;
}

void App::save() {
    if(!isFileOpened){
        Utils::log("No file is open.", Utils::Color::RED);
        return;
    }

    Utils::log("Successfully saved file!", Utils::Color::GREEN);
}

void App::saveAs(const std::string& fileName) {
    if(!isFileOpened) {
        Utils::log("No file is open.", Utils::Color::RED);
        return;
    }

    Utils::log("Successfully saved file", Utils::Color::GREEN);
}

void App::help() const {
    std::cout << "\nCommands:\n"
              << "open <file>\t\topens <file>\n"
              << "close\t\t\tcloses currently opened file\n"
              << "save\t\t\tsaves the currently open file\n"
              << "saveas <file>\t\tsaves the currently open file in <file>\n"
              << "help\t\t\tprints this information\n"
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

    std::string action = data[0];

    if(action == "open") {
        if(data.size() >= 2) {
            openFile(data[1]);
        }

        return;

    }else if(action == "help") {
        help();
        return;

    } else if(action == "close") {
        closeFile();
        return;

    } else if(action == "save") {
        save();

    } else if(action == "saveas") {
        if(data.size() >= 2) {
            saveAs(data[1]);
        }

    } else if(action == "import") {
        if(data.size() >= 3) {
            db.importTable(data[1], data[2]);
        }

    } else if(action == "showtables") {
        db.showTables();

    } else if(action == "describe") {
        if(data.size() >= 2) {
            db.describe(data[1]);
        }

    } else if(action == "print") {
        if(data.size() >= 2) {
            db.printTable(data[1]);
        }

    } else if(action == "export"){
        if(data.size() >= 3) {
            db.exportTable(data[1], data[2]);
        }

    } else if(action == "select") {
        if(data.size() >= 4) {
            db.select(std::stoul(data[1]), data[2], data[3]);
        }

    } else if(action == "addcolumn") {
        if(data.size() >= 4) {
            db.addColumn(data[1], data[2], data[3]);
        }

    } else if(action == "update") {
        if(data.size() >= 6) {
            db.updateRow(data[1], std::stoul(data[2]), data[3], std::stoul(data[4]), data[5]);
        }

    } else if(action == "delete"){
        if(data.size() >= 4) {
            db.deleteRows(data[1], std::stoul(data[2]), data[3]);
        }

    } else if(action == "insert") {
        if(data.size() >= 3) {
            std::vector<std::string> values;
            int argCount = data.size();

            for(int i = 2; i < argCount; i++) {
                values.push_back(data[i]);
            }

            db.insertRow(data[1], values);
        }
    } else if(action == "innerjoin") {
        if(data.size() >= 5) {
            db.innerJoin(data[1], std::stoul(data[2]), data[3], std::stoul(data[4]));
        }

    } else if(action == "rename") {
        if(data.size() >= 3) {
            db.renameTable(data[1], data[2]);
        }

    } else if(action == "count") {
        if(data.size() >= 4) {
            db.count(data[1], std::stoul(data[2]), data[3]);
        }

    } else if(action == "aggregate") {
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