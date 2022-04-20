//
// Created by Daniel on 4/20/2022.
//

#ifndef DATA_STRUCTURES_234218_HIGHTECH_H
#define DATA_STRUCTURES_234218_HIGHTECH_H

#include "Map.h"

class Employee {
private:
    int salary;
    int grade;
    int company_id;
public:
    Employee(int salary, int grade, int company_id);
};

class Company {
private:
    int value;
public:
    Company(int);
};

class HighTech {
    Map<Employee> employees;
    Map<Company> companies;
public:
    HighTech();

    void AddEmployee(int employee_id, int company_id, int salary, int grade);

    void RemoveEmployee(int employee_id);

    void RemoveCompany(int company_id);

    void AddCompany(int company_id, int value);


};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
