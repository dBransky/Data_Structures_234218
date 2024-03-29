//
// Created by Daniel on 4/20/2022.
//

#ifndef DATA_STRUCTURES_234218_HIGHTECH_H
#define DATA_STRUCTURES_234218_HIGHTECH_H

#include "MyMap.h"

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
        return ((id1.salary == id2.salary && id1.id < id2.id) || id1.salary > id2.salary);
    }

    friend bool operator<(SalaryId id1, SalaryId id2) {
        return !(id1 > id2) && !(id1 == id2);
    }

    friend bool operator==(SalaryId id1, SalaryId id2) {
        return (id1.salary == id2.salary) && (id1.id == id2.id);
    }

    friend bool operator>=(SalaryId id1, SalaryId id2) {
        return ((id1.salary == id2.salary && id1.id <= id2.id) || (id1.salary > id2.salary));
    }

public:
    SalaryId()=default;

    SalaryId(double salary, int id) : salary(salary), id(id) {}
};


class Employee;

class Company {
private:
    int value;
    int amount_of_employees;
    Employee *best_salary_employee;
    Map<Employee *, SalaryId> company_employees;
    Map<Employee *, int> employees_id;
public:
    int id;
    Company(int id, int value);

    void AddCompanyValue(int valueIncrease);

    void AddNewEmployee();

    void RemoveEmployee();

    int GetCompanyValue() const;

    int GetCompanyAmountOfEmployees() const;

    void SetCompanyAmountOfEmployees(int add_amount);

    Employee *GetBestSalaryEmployee();

    int GetCompanyId() const;

    int GetAmountOfEmployees() const;

    Map<Employee *, SalaryId> &GetCompanyEmployees();

    Map<Employee *, int> &GetCompanyIDEmployees();

    int GetEmployeeIdWithBestSalary();

    void SetCompanyEmployees(const Map<Employee *, SalaryId>& new_company_employees);

    void SetCompanyValue(int new_value);

    void SetCompanyBestEmployee(Employee *new_employee);
};

class Employee {
private:
    int salary;
    int grade;
    Company *company;
public:
    int id;
    Employee()=default;

    Employee(int salary, int grade, int employee_id, Company *company);

    int GetSalary() const;

    int GetGrade() const;

    int GetCompanyId();

    int GetId() const;

    Company *GetCompany();

    void IncreaseSalary(int valueIncrease);

    void IncreaseGrade();

    void SetCompany(Company* new_company);

};

class EmployeeByCompanyId {
    Employee* employee{};
public:
    EmployeeByCompanyId() = default;;

    explicit EmployeeByCompanyId(Employee* employee) :
            employee(employee) {
    }

    friend bool operator>(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return employee1.employee->GetCompanyId() > employee2.employee->GetCompanyId();
    }

    friend bool operator>=(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return (employee1 > employee2) || (employee1 == employee2);
    }

    friend bool operator<(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return !(employee1 >= employee2);
    }

    friend bool operator==(EmployeeByCompanyId &employee1, EmployeeByCompanyId &employee2) {
        return employee1.employee->GetCompanyId() == employee2.employee->GetCompanyId();
    }
};


class HighTech {
    Map<Employee *, int> employees_sorted_by_id;
    Map<Company *, int> companies;
    Map<Employee *, SalaryId> employees_sorted_by_salary;
    Map<Employee *, EmployeeByCompanyId> best_earning_employees;
    int total_amount_of_employees;
    int amount_of_companies_with_at_least_one_employee;
    int amount_of_companies;
    Employee *employee_with_best_salary;

public:
    HighTech();

    ~HighTech();

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

};

#endif //DATA_STRUCTURES_234218_HIGHTECH_H
