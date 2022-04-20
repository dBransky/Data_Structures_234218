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
    int GetSalary();
    int GetGrade();
    int GetCompanyId();
    void IncreaseSalary(int valueIncrease);
    void IncreaseGrade();
};

class Company {
private:
    int value;
    int amount_of_employees;
public:
    Company(int value, int amount_of_employees = 0);
    void AddCompanyValue(int valueIncrease);
    void AddNewEmployee();
    void RemoveEmployee();
    int GetCompanyValue();
    int GetAmountOfEmployees();
};

class HighTech {
    Map<Employee> employees;
    Map<Company> companies;
public:
    HighTech();

    void AddEmployee(int employee_id, int company_id, int salary, int grade); // v

    void RemoveEmployee(int employee_id); // v

    void RemoveCompany(int company_id); // v

    void AddCompany(int company_id, int value); // v

    void GetCompanyInfo(int company_id, int *Value, int *NumEmployees); // v

    void GetEmployeeInfo(int EmployeeId, int *EmployerID, int *Salary, int *Grade); // v

    void IncreaseCompanyValue(int CompanyId, int ValueIncrease); // v

    void PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade); // v

    void HireEmployee(int EmployeeID, int NewCompanyID);

    void AcquireCompany(int AcquireID, int TargetID, double Factor);

    void GetHighestEarner(int CompanyID, int *EmployeeID);

    void GetAllEmployeesBySalary(int companyID, int **Employees, int *NumOfEmployees);

    void GetHighestEarnerInEachCompany(int NumOfCompanies,int **Employees);

    void GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

    void Quit();
};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
