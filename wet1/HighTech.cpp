//
// Created by Daniel on 4/20/2022.
//

#include "HighTech.h"


HighTech::HighTech()
        : employees_sorted_by_id(), companies(), employees_sorted_by_salary(), employee_with_best_salary(NULL) {
    employee_id_with_best_salary = 0;

}

void HighTech::AddEmployee(int employee_id, int company_id, int salary, int grade) {
    Company *company = &(companies.find(company_id));
    Employee new_employee = Employee(salary, grade, company_id, company);
    employees_sorted_by_id.insert(employee_id, new_employee);
    company->AddNewEmployee();
    company->GetCompanyEmployees().insert(SalaryId(salary, employee_id), new_employee);
    employees_sorted_by_salary.insert(SalaryId(salary, employee_id), new_employee);
    if (salary > employee_with_best_salary->GetSalary() ||
        (salary == employee_with_best_salary->GetSalary() && employee_id < employee_id_with_best_salary)) {
        employee_with_best_salary = &(new_employee);
        employee_id_with_best_salary = employee_id;
    }
}

void HighTech::AddCompany(int company_id, int value) {
    companies.insert(company_id, Company(value));

}

void HighTech::RemoveEmployee(int employee_id) {
    Employee &employee = employees_sorted_by_id.find(employee_id);
    employees_sorted_by_id.remove(employee_id);
    employee.GetCompany()->RemoveEmployee();
}

void HighTech::RemoveCompany(int company_id) {
    Company &company = companies.find(company_id);
    if (company.GetAmountOfEmployees() == 0) {
        companies.remove(company_id);
    }
}

void HighTech::GetCompanyInfo(int company_id, int *Value, int *NumEmployees) {
    Company &company = companies.find(company_id);
    *NumEmployees = company.GetAmountOfEmployees();
    *Value = company.GetCompanyValue();
}

void HighTech::GetEmployeeInfo(int EmployeeId, int *EmployerID, int *Salary, int *Grade) {
    Employee &employee = employees_sorted_by_id.find(EmployeeId);
    *EmployerID = employee.GetCompanyId();
    *Salary = employee.GetSalary();
    *Grade = employee.GetGrade();
}

void HighTech::IncreaseCompanyValue(int CompanyId, int ValueIncrease) {
    if (ValueIncrease > 0 && CompanyId > 0) {
        Company &company = companies.find(CompanyId);
        company.AddCompanyValue(ValueIncrease);
    }
}

void HighTech::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
    Employee &employee = employees_sorted_by_id.find(EmployeeID);
    employee.IncreaseSalary(SalaryIncrease);
    if (BumpGrade > 0) {
        employee.IncreaseGrade();
    }
}

void HighTech::HireEmployee(int EmployeeID, int NewCompanyID) {
    Employee &employee = employees_sorted_by_id.find(EmployeeID);
    RemoveEmployee(EmployeeID);
    AddEmployee(EmployeeID, NewCompanyID, employee.GetSalary(), employee.GetGrade());
}

void HighTech::GetHighestEarner(int CompanyID, int *EmployeeID) {
    if (CompanyID < 0) {
        *EmployeeID = employee_id_with_best_salary;
    } else {
        Company company = companies.find(CompanyID);
        *EmployeeID = company.GetEmployeeIdWithBestSalary();
    }
}

void HighTech::AcquireCompany(int AcquireID, int TargetID, double Factor) {
    if (AcquireID <= 0 || TargetID <= 0)
    {
        // throw InvalidInput();
    }
    else {
        Company &AcquireCompany = companies.find(AcquireID);
        Company &TargetCompany = companies.find(TargetID);
        if (AcquireCompany.GetCompanyValue() >= TargetCompany.GetCompanyValue() * 10)
        {
            //AcquireCompany.SetCompanyEmployees(Map(AcquireCompany.GetCompanyEmployees(),TargetCompany.GetCompanyEmployees()));
            AcquireCompany.SetCompanyValue((int)(Factor * (AcquireCompany.GetCompanyValue() + TargetCompany.GetCompanyValue())));

        }
    }
}


Company::Company(int value, int amount_of_employees) : value(value), amount_of_employees(amount_of_employees) {

}

void Company::AddCompanyValue(int valueIncrease) {
    value = value + valueIncrease;
}

int Company::GetCompanyValue() {
    return value;
}

int Company::GetAmountOfEmployees() {
    return amount_of_employees;
}

void Company::AddNewEmployee() {
    amount_of_employees++;
}

void Company::RemoveEmployee() {
    amount_of_employees--;
}

Map<Employee, SalaryId> Company::GetCompanyEmployees() {
    return company_employees;
}

int Company::GetEmployeeIdWithBestSalary() {
    return 1;
}


Employee::Employee(int salary, int grade, int company_id, Company *company) : salary(salary), grade(grade),
                                                                              company_id(company_id), company(company) {

}

int Employee::GetSalary() {
    return salary;
}

void Employee::IncreaseSalary(int valueIncrease) {
    salary = salary + valueIncrease;
}

void Employee::IncreaseGrade() {
    grade = grade + 1;
}

int Employee::GetGrade() {
    return grade;
}

int Employee::GetCompanyId() {
    return company_id;
}

Company *Employee::GetCompany() {
    return company;
}
