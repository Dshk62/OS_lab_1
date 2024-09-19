﻿#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

struct employee {
    int num;        // Идентификационный номер сотрудника
    char name[10];  // Имя сотрудника
    double hours;   // Количество отработанных часов
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <binary file> <report file> <hourly rate>" << std::endl;
        return 1;
    }
    
    const char* binaryFile = argv[1];
    const char* reportFile = argv[2];
    double hourlyRate = std::stod(argv[3]);

    std::ifstream inFile(binaryFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening binary file!" << std::endl;
        return 1;
    }

    std::ofstream outFile(reportFile);
    if (!outFile) {
        std::cerr << "Error opening report file!" << std::endl;
        return 1;
    }

    outFile << "File report \"" << binaryFile << "\"\n";
    outFile << "Employee number\tEmployee name\ttimepiece\tSalary\n";

    employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        double salary = emp.hours * hourlyRate;
        outFile << emp.num << "\t\t" << emp.name << "\t\t" << emp.hours << "\t\t" << salary << "\n";
    }

    inFile.close();
    outFile.close();
    std::cout << "Report generated successfully." << std::endl;
    return 0;
}