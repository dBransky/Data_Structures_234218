//
// Created by Daniel on 4/20/2022.
//

#include "HighTech.h"


HighTech::HighTech() : employees(), companies() {

}

void HighTech::AddEmployee(int employee_id, int company_id, int salary, int grade){
    employees.insert(employee_id, Employee(company_id, salary, grade));
    companies.find(company_id).AddNewEmployee();
}

void HighTech::AddCompany(int company_id, int value) {
    companies.insert(company_id, Company(value));

}

void HighTech::RemoveEmployee(int employee_id) {
    employees.remove(employee_id);
    // something wrong here...

}

void HighTech::RemoveCompany(int company_id) {
    companies.remove(company_id);

}

void HighTech::GetCompanyInfo(int company_id, int *Value, int *NumEmployees)
{
    Company& company = companies.find(company_id);
    *NumEmployees = company.GetAmountOfEmployees();
    *Value = company.GetCompanyValue();
}

void HighTech::GetEmployeeInfo(int EmployeeId, int *EmployerID, int *Salary, int *Grade)
{
    Employee& employee = employees.find(EmployeeId);
    *EmployerID = employee.GetCompanyId();
    *Salary = employee.GetSalary();
    *Grade = employee.GetGrade();
}

void HighTech::IncreaseCompanyValue(int CompanyId, int ValueIncrease)
{
    Company& company = companies.find(CompanyId);
    company.AddCompanyValue(ValueIncrease);
}

void HighTech::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    Employee& employee = employees.find(EmployeeID);
    employee.IncreaseSalary(SalaryIncrease);
    if (BumpGrade > 0)
    {
        employee.IncreaseGrade();
    }
}

void HighTech::HireEmployee(int EmployeeID, int NewCompanyID)
{
    
}







Company::Company(int value, int amount_of_employees) : value(value), amount_of_employees(amount_of_employees) {

}

void Company::AddCompanyValue(int valueIncrease)
{
    value = value + valueIncrease;
}

int Company::GetCompanyValue()
{
    return value;
}

int Company::GetAmountOfEmployees()
{
    return amount_of_employees;
}

void Company::AddNewEmployee() {
    amount_of_employees++;
}

void Company::RemoveEmployee() {
    amount_of_employees--;
}

Employee::Employee(int salary, int grade, int company_id) : salary(salary), grade(grade), company_id(company_id) {

}

int Employee::GetSalary()
{
    return salary;
}

void Employee::IncreaseSalary(int valueIncrease)
{
    salary = salary + valueIncrease;
}

void Employee::IncreaseGrade()
{
    grade = grade + 1;
}

int Employee::GetGrade()
{
    return grade;
}

int Employee::GetCompanyId()
{
    return company_id;
}