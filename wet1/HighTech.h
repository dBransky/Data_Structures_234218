//
// Created by Daniel on 4/20/2022.
//

#ifndef DATA_STRUCTURES_234218_HIGHTECH_H
#define DATA_STRUCTURES_234218_HIGHTECH_H

#include "Map.h"

class Exceptions : public std::exception {
};

class Failure : public Exceptions {
};

class InvalidInput : public Exceptions {
};


class SalaryId {
    double salary;
    int id;

    friend bool operator>(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id > id2.id) || id1.salary > id2.salary);
    }

    friend bool operator<(SalaryId id1, SalaryId id2) {
        return !(id1 > id2) && !(id1 == id2);
    }

    friend bool operator==(SalaryId id1, SalaryId id2) {
        return (id1.salary == id2.salary) && (id1.id == id2.id);
    }

    friend bool operator>=(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id >= id2.id) || id1.salary >= id2.salary);
    }

public:
    SalaryId() {}

    SalaryId(double salary, int id) : salary(salary), id(id) {}
};


class Employee;

class Company {
private:
    int id;
    int value;
    int amount_of_employees;
    Employee *best_salary_employee;
    Map<Employee *, SalaryId> company_employees;
    Map<Employee *, int> employees_id;
public:
    Company(int id, int value);

    void AddCompanyValue(int valueIncrease);

    void AddNewEmployee();

    void RemoveEmployee();

    int GetCompanyValue();

    int GetCompanyAmountOfEmployees();

    void SetCompanyAmountOfEmployees(int add_amount);

    Employee *GetBestSalaryEmployee();

    int GetCompanyId();

    int GetAmountOfEmployees();

    Map<Employee *, SalaryId> &GetCompanyEmployees();

    Map<Employee *, int> &GetCompanyIDEmployees();

    int GetEmployeeIdWithBestSalary();

    void SetCompanyEmployees(Map<Employee *, SalaryId> new_company_employees);

    void SetCompanyValue(int new_value);

    void SetCompanyBestEmployee(Employee *new_employee);
};

class Employee {
private:
    int id;
    int salary;
    int grade;
    Company *company;
public:
    Employee();

    Employee(int salary, int grade, int employee_id, Company *company);

    int GetSalary();

    int GetGrade();

    int GetCompanyId();

    int GetId();

    Company *GetCompany();

    void IncreaseSalary(int valueIncrease);

    void IncreaseGrade();

};

class EmployeeByCompanyId {
    std::shared_ptr<Employee> employee;
public:
    EmployeeByCompanyId() {};

    EmployeeByCompanyId(std::shared_ptr<Employee> employee) :
            employee(employee) {
    }

    friend bool operator>(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return employee1.employee->GetCompany() > employee2.employee->GetCompany();
    }

    friend bool operator<(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return !(employee1 > employee2);
    }

    friend bool operator==(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return !(employee1 > employee2) && !(employee1 < employee2);
    }
};


class HighTech {
    int total_amount_of_employees;
    int amount_of_companies_with_at_least_one_employee;
    Map<Employee *, int> employees_sorted_by_id;
    Map<Employee *, SalaryId> employees_sorted_by_salary;
    Map<Employee *, EmployeeByCompanyId> best_earning_employees;
    Employee *employee_with_best_salary;
    Map<Company *, int> companies;

public:
    HighTech();

    ~HighTech() = default;

    void AddCompany(int CompanyId, int Value); // v

    void AddEmployee(int EmployeeId, int CompanyID, int Salary, int Grade); // v



    void RemoveEmployee(int employee_id); // v

    void RemoveCompany(int company_id); // v


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

    void UpdateInCompany(Employee *employee, Company *company);

    void UpdateInHighTech(Employee *employee);
};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
