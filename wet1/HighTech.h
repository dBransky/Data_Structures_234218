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
    explicit Company(int);
};

class SalaryId {
    double salary;
    int id;

    friend bool operator>(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id > id2.id) || id1.salary > id2.salary);
    }

    friend bool operator<(SalaryId id1, SalaryId id2) {
        return !(id1 > id2);
    }
};

class HighTech {
    Map<Employee, int> employees;
    Map<Company, int> companies;
public:
    HighTech();

    void AddEmployee(int employee_id, int company_id, int salary, int grade);

    void RemoveEmployee(int employee_id);

    void RemoveCompany(int company_id);

    void AddCompany(int company_id, int value);


};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
