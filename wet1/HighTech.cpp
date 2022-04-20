//
// Created by Daniel on 4/20/2022.
//

#include "HighTech.h"

HighTech::HighTech() : employees(), companies() {

}

void HighTech::AddEmployee(int employee_id, int company_id, int salary, int grade) {
    employees.insert(employee_id, Employee(company_id, salary, grade));

}

void HighTech::AddCompany(int company_id, int value) {
    companies.insert(company_id, Company(value));

}

void HighTech::RemoveEmployee(int employee_id) {
    employees.remove(employee_id);

}

void HighTech::RemoveCompany(int company_id) {
    companies.remove(company_id);

}

Company::Company(int value) : value(value) {

}

Employee::Employee(int salary, int grade, int company_id) : salary(salary), grade(grade), company_id(company_id) {

}
