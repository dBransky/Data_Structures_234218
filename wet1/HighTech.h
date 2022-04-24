//
// Created by Daniel on 4/20/2022.
//

#ifndef DATA_STRUCTURES_234218_HIGHTECH_H
#define DATA_STRUCTURES_234218_HIGHTECH_H

#include "Map.h"

class SalaryId {
    double salary;
    int id;;

    friend bool operator>(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id > id2.id) || id1.salary > id2.salary);
    }

    friend bool operator<(SalaryId id1, SalaryId id2) {
        return !(id1 > id2);
    }

    friend bool operator==(SalaryId id1, SalaryId id2) {
        return (!(id1 > id2)) && (!(id1 < id2));
    }

public:
    SalaryId(double salary, int id) : salary(salary), id(id) {}
};


class Employee;

class Company {
private:
    int value;
    int amount_of_employees;
    Map<Employee, SalaryId> company_employees;
public:
    explicit Company(int value, int amount_of_employees = 0);

    void AddCompanyValue(int valueIncrease);

    void AddNewEmployee();

    void RemoveEmployee();

    int GetCompanyValue();

    int GetAmountOfEmployees();

    Map<Employee, SalaryId> GetCompanyEmployees();

    int GetEmployeeIdWithBestSalary();
};

class Employee {
private:
    int salary;
    int grade;
    int company_id;
    Company *company;
public:
    Employee(int salary, int grade, int company_id, Company *company);

    int GetSalary();

    int GetGrade();

    int GetCompanyId();

    Company *GetCompany();

    void IncreaseSalary(int valueIncrease);

    void IncreaseGrade();

};

class EmployeeByCompanyId {
    std::shared_ptr<Employee> employee;
    EmployeeByCompanyId(std::shared_ptr<Employee> employee):
        employee(employee){
    }
    friend bool operator>(EmployeeByCompanyId& employee1,EmployeeByCompanyId& employee2){
        return employee1.employee->GetCompany()>employee2.employee->GetCompany();
    }
    friend bool operator<(EmployeeByCompanyId& employee1,EmployeeByCompanyId& employee2){
        return !(employee1>employee2);
    }

};


class HighTech {
    Map<Employee, int> employees_sorted_by_id;
    Map<Employee, SalaryId> employees_sorted_by_salary;
    Employee *employee_with_best_salary;
    int employee_id_with_best_salary;
    Map<Company, int> companies;
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

    void GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

    void GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID, int MinSalary, int MinGrade,
                                 int *TotalNumOfEmployees, int *NumOfEmployees);

    void Quit();
};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
