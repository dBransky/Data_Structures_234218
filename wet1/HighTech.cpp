#include "HighTech.h"
#include <cmath>

void HighTech::UpdateInCompany(Employee *employee, Company *company) {
    if (company->GetAmountOfEmployees() == 1) {
        company->SetCompanyBestEmployee(employee);
        best_earning_employees.insert(EmployeeByCompanyId((employee)), employee);
        amount_of_companies_with_at_least_one_employee++;
    } else {
        Employee *best_emp = company->GetBestSalaryEmployee();
        int max_salary = best_emp->GetSalary();
        int max_id = best_emp->GetId();
        int current_salary = employee->GetSalary();
        int current_id = employee->GetId();
        if (max_salary < current_salary || (current_salary == max_salary && current_id < max_id)) {
            EmployeeByCompanyId compare = EmployeeByCompanyId((best_emp));
            best_earning_employees.remove(compare);
            best_earning_employees.insert(EmployeeByCompanyId((employee)), employee);
            company->SetCompanyBestEmployee(employee);
        }
    }
}


HighTech::HighTech() : employees_sorted_by_id(), companies(), employees_sorted_by_salary(), best_earning_employees() {
    employee_with_best_salary = NULL;
    total_amount_of_employees = 0;
    amount_of_companies_with_at_least_one_employee = 0;
    amount_of_companies = 0;
}

HighTech::~HighTech() {
    Pair<Company *, int> *companies_list = companies.GetFirstNum(amount_of_companies);
    Pair<Employee *, int> *employees = employees_sorted_by_id.GetFirstNum(total_amount_of_employees);
    for (int i = 0; i < amount_of_companies; i++) {
        delete (companies_list[i].element);
    }
    for (int i = 0; i < total_amount_of_employees; i++) {
        delete (employees[i].element);
    }
    delete[] companies_list;
    delete[] employees;
}


void HighTech::AddCompany(int CompanyId, int Value) {
    if (CompanyId <= 0 || Value <= 0) {
        throw InvalidInput();
    }
    auto *new_company = new Company(CompanyId, Value);
    try {
        companies.insert(CompanyId, new_company); // O(log k)
        amount_of_companies++;
    }
    catch (KeyAlreadyExists &k) {
        delete (new_company);
        throw Failure();
    }
}

void HighTech::AddEmployee(int EmployeeId, int CompanyID, int Salary, int Grade) {
    if (EmployeeId <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0) {
        throw InvalidInput();
    }
    Employee *new_employee;
    try {
        Company *company = companies.find(CompanyID); // O(log k)
        new_employee = new Employee(Salary, Grade, EmployeeId, company);
        employees_sorted_by_id.insert(EmployeeId, new_employee); // O(log n)
        employees_sorted_by_salary.insert(SalaryId(Salary, EmployeeId), new_employee); // O(log n)
        company->GetCompanyEmployees().insert(SalaryId(Salary, EmployeeId), new_employee); // O(log n)
        company->GetCompanyIDEmployees().insert(EmployeeId, new_employee);
        company->AddNewEmployee(); // O(1)
        UpdateInCompany(new_employee, new_employee->GetCompany());
        total_amount_of_employees++;
        employee_with_best_salary = employees_sorted_by_salary.GetMaxId();
    }
    catch (KeyDoesntExist &f) {
        throw Failure();
    }
    catch (KeyAlreadyExists &f) {
        delete (new_employee);
        throw Failure();
    }
}

void HighTech::RemoveEmployee(int employee_id) {
    if (employee_id <= 0) {
        throw InvalidInput();
    }
    try {
        Employee *employee = employees_sorted_by_id.find(employee_id);
        employees_sorted_by_id.remove(employee_id);
        employees_sorted_by_salary.remove(SalaryId(employee->GetSalary(), employee_id));
        employee->GetCompany()->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), employee_id));
        employee->GetCompany()->GetCompanyIDEmployees().remove(employee_id);
        employee->GetCompany()->RemoveEmployee();
        if (employee->GetCompany()->GetBestSalaryEmployee()->GetId() ==
            employee_id)  // if this employee is the best in his company...
        {
            best_earning_employees.remove(EmployeeByCompanyId(employee));
            Company *company = employee->GetCompany();
            if (company->GetAmountOfEmployees() > 0) {
                company->SetCompanyBestEmployee(company->GetCompanyEmployees().GetMaxId());
                best_earning_employees.insert(EmployeeByCompanyId(company->GetBestSalaryEmployee()),
                                              company->GetBestSalaryEmployee());
                employee_with_best_salary = (employees_sorted_by_salary.GetMaxId());
            }
        }
        total_amount_of_employees--;
        if (employee->GetCompany()->GetAmountOfEmployees() == 0) {
            amount_of_companies_with_at_least_one_employee--;
        }
        employee->SetCompany(NULL);
        delete (employee);
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::RemoveCompany(int company_id) {
    if (company_id <= 0) {
        throw InvalidInput();
    }
    try {
        Company *company = companies.find(company_id);
        if (company->GetAmountOfEmployees() > 0) {
            throw Failure();
        }
        companies.remove(company_id);
        amount_of_companies--;
        delete (company);
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::GetCompanyInfo(int company_id, int *Value, int *NumEmployees) {
    if (Value == NULL || NumEmployees == NULL || company_id <= 0) {
        throw InvalidInput();
    }
    try {
        Company *company = companies.find(company_id); // O(log k)
        *NumEmployees = company->GetAmountOfEmployees(); // O(1)
        *Value = company->GetCompanyValue(); // O(1)
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::GetEmployeeInfo(int EmployeeId, int *EmployerID, int *Salary, int *Grade) {
    if (EmployerID == NULL || Salary == NULL || Grade == NULL || EmployeeId <= 0) {
        throw InvalidInput();
    }
    try {
        Employee *employee = employees_sorted_by_id.find(EmployeeId); // O(log n)
        *EmployerID = employee->GetCompanyId(); // O(1)
        *Salary = employee->GetSalary(); // O(1)
        *Grade = employee->GetGrade(); // O(1)
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::IncreaseCompanyValue(int CompanyId, int ValueIncrease) {
    if (CompanyId <= 0 || ValueIncrease <= 0) {
        throw InvalidInput();
    }
    try {
        Company *company = companies.find(CompanyId); // O(log k)
        company->AddCompanyValue(ValueIncrease); // O(1)
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}


void HighTech::HireEmployee(int EmployeeID, int NewCompanyID) {
    if (EmployeeID <= 0 || NewCompanyID <= 0) {
        throw InvalidInput();
    }

    try {
        Employee *employee = employees_sorted_by_id.find(EmployeeID); // O(log n)
        int salary = employee->GetSalary();
        int grade = employee->GetGrade();
        Company *company = companies.find(NewCompanyID);
        if (company->GetCompanyIDEmployees().does_exist(EmployeeID)) {
            throw Failure();
        }
        RemoveEmployee(EmployeeID);
        AddEmployee(EmployeeID, NewCompanyID, salary, grade); // O(log k + log n)
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
    if (EmployeeID <= 0 || SalaryIncrease <= 0) {
        throw InvalidInput();
    }
    try {
        Employee *employee = employees_sorted_by_id.find(EmployeeID);
        Company *company = employee->GetCompany();
        company->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeID));
        employees_sorted_by_salary.remove(SalaryId(employee->GetSalary(), EmployeeID));
        best_earning_employees.remove(EmployeeByCompanyId(company->GetBestSalaryEmployee()));
        employee->IncreaseSalary(SalaryIncrease);
        if (BumpGrade > 0) {
            employee->IncreaseGrade();
        }
        company->GetCompanyEmployees().insert(SalaryId(employee->GetSalary(), employee->GetId()), employee);
        employees_sorted_by_salary.insert(SalaryId(employee->GetSalary(), employee->GetId()), employee);
        company->SetCompanyBestEmployee(company->GetCompanyEmployees().GetMaxId());
        best_earning_employees.insert(EmployeeByCompanyId(company->GetBestSalaryEmployee()),
                                      company->GetBestSalaryEmployee());
        employee_with_best_salary = employees_sorted_by_salary.GetMaxId();

    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::AcquireCompany(int AcquireID, int TargetID, double Factor) {
    if (AcquireID <= 0 || TargetID <= 0 || AcquireID == TargetID || Factor < 1.00) {
        throw InvalidInput();
    }
    try {
        Company *AcquireCompany = companies.find(AcquireID);
        Company *TargetCompany = companies.find(TargetID);
        int total_amount = AcquireCompany->GetAmountOfEmployees() + TargetCompany->GetAmountOfEmployees();
        int ac_value = AcquireCompany->GetCompanyValue();
        int tr_value = TargetCompany->GetCompanyValue();
        if (AcquireCompany->GetCompanyValue() >= TargetCompany->GetCompanyValue() * 10) {
            if (AcquireCompany->GetAmountOfEmployees() > 0) {
                best_earning_employees.remove(
                        EmployeeByCompanyId((AcquireCompany->GetBestSalaryEmployee())));
            }
            if (TargetCompany->GetAmountOfEmployees() > 0) {
                best_earning_employees.remove(
                        EmployeeByCompanyId((TargetCompany->GetBestSalaryEmployee())));
            }
            if (TargetCompany->GetAmountOfEmployees() > 0) {
                amount_of_companies_with_at_least_one_employee--;
            }
            if (AcquireCompany->GetAmountOfEmployees() == 0 && TargetCompany->GetAmountOfEmployees() > 0) {
                amount_of_companies_with_at_least_one_employee++;
            }
            AcquireCompany->GetCompanyEmployees().merge(TargetCompany->GetCompanyEmployees());
            AcquireCompany->GetCompanyIDEmployees().merge(TargetCompany->GetCompanyIDEmployees());
            int new_value = floor((tr_value + ac_value) * (Factor));
            AcquireCompany->SetCompanyValue(new_value);
            AcquireCompany->SetCompanyAmountOfEmployees(total_amount);
            companies.remove(TargetCompany->GetCompanyId());
            amount_of_companies--;
            Pair<Employee *, SalaryId> *pair_list = AcquireCompany->GetCompanyEmployees().GetFirstNum(
                    AcquireCompany->GetAmountOfEmployees());
            for (int i = 0; i < AcquireCompany->GetAmountOfEmployees(); i++) {
                pair_list[i].element->SetCompany(AcquireCompany);
                pair_list[i].element = NULL;
            }
            delete[] pair_list;
            if (AcquireCompany->GetAmountOfEmployees() > 0) {
                Employee *best_emp = AcquireCompany->GetCompanyEmployees().GetMaxId();
                AcquireCompany->SetCompanyBestEmployee(best_emp);
                best_earning_employees.insert(EmployeeByCompanyId((best_emp)), best_emp);
            }
            delete (TargetCompany);
        } else {
            throw Failure();
        }
    }
    catch (KeyDoesntExist &k) {
        throw Failure();
    }
}

void HighTech::GetHighestEarner(int CompanyID, int *EmployeeID) {
    if (CompanyID == 0 || EmployeeID == NULL) {
        throw InvalidInput();
    }
    if (CompanyID < 0) {
        if (total_amount_of_employees == 0) {
            throw Failure();
        } else {
            *EmployeeID = employee_with_best_salary->GetId();
        }
    } else {
        try {
            Company *company = companies.find(CompanyID);
            if (company->GetAmountOfEmployees() == 0) {
                throw Failure();
            } else {
                *EmployeeID = company->GetBestSalaryEmployee()->GetId();
            }

        }
        catch (KeyDoesntExist &k) {
            throw Failure();
        }
    }
}

void HighTech::GetAllEmployeesBySalary(int companyID, int **Employees, int *NumOfEmployees) {
    if (Employees == NULL || NumOfEmployees == NULL || companyID == 0) {
        throw InvalidInput();
    }
    if (companyID < 0 && employee_with_best_salary == NULL) {
        throw Failure();
    }
    if (companyID < 0) {
        int *emp = (int *) malloc(total_amount_of_employees * sizeof(int));
        Pair<Employee *, SalaryId> *pair_list = employees_sorted_by_salary.GetFirstNum(total_amount_of_employees);
        for (int i = 0; i < total_amount_of_employees; i++) {
            emp[total_amount_of_employees - 1 - i] = pair_list[i].element->GetId();
            pair_list[i].element = NULL;
        }
        delete[] pair_list;
        *Employees = emp;
        *NumOfEmployees = total_amount_of_employees;
    } else {
        try {
            Company *company = companies.find(companyID);
            if (company->GetAmountOfEmployees()==0) {
                throw Failure();
            }
            int *emp = (int *) malloc(company->GetAmountOfEmployees() * sizeof(int));
            Pair<Employee *, SalaryId> *pair_list = company->GetCompanyEmployees().GetFirstNum(
                    company->GetAmountOfEmployees());
            for (int i = 0; i < company->GetAmountOfEmployees(); i++) {
                emp[company->GetAmountOfEmployees() - 1 - i] = pair_list[i].element->GetId();
                pair_list[i].element = NULL;
            }
            delete[] pair_list;
            *Employees = emp;
            *NumOfEmployees = company->GetAmountOfEmployees();
        }
        catch (KeyDoesntExist &k) {
            throw Failure();
        }
    }
}

void HighTech::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees) {
    if (Employees == NULL || NumOfCompanies < 1) {
        throw InvalidInput();
    }
    if (NumOfCompanies > amount_of_companies_with_at_least_one_employee) {
        throw Failure();
    }
    int *emp = (int *) malloc(NumOfCompanies * sizeof(int));
    Pair<Employee *, EmployeeByCompanyId> *pair_list = best_earning_employees.GetFirstNum(NumOfCompanies);
    for (int i = 0; i < NumOfCompanies; i++) {
        emp[i] = pair_list[i].element->GetId();
        pair_list[i].element = NULL;
    }
    delete[]pair_list;
    *Employees = emp;
}

void HighTech::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID, int MinSalary, int MinGrade,
                                       int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (TotalNumOfEmployees == NULL || NumOfEmployees == NULL || CompanyID == 0 || MinEmployeeID < 0 ||
        MaxEmployeeID < 0 || MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeID) {
        throw InvalidInput();
    }
    Pair<Employee *, int> *pair_list = NULL;
    if (CompanyID < 0) {
        if (total_amount_of_employees == 0) {
            throw Failure();
        } else {
            pair_list = employees_sorted_by_id.GetObjectsFromKey(MinEmployeeID, MaxEmployeeID, TotalNumOfEmployees);
        }
    } else {
        try {
            Company *company = companies.find(CompanyID);
            if (company->GetAmountOfEmployees() == 0) {
                throw Failure();
            }
            pair_list = company->GetCompanyIDEmployees().GetObjectsFromKey(MinEmployeeID, MaxEmployeeID,
                                                                           TotalNumOfEmployees);
        }
        catch (KeyDoesntExist &k) {
            throw Failure();
        }
    }
    int my_total = *TotalNumOfEmployees;
    *TotalNumOfEmployees = my_total;
    int count = 0;
    for (int i = 0; i < my_total; i++) {
        if (pair_list[i].element->GetSalary() >= MinSalary && pair_list[i].element->GetGrade() >= MinGrade) {
            pair_list[i].element = NULL;
            count++;
        }
    }
    delete[] pair_list;
    *NumOfEmployees = count;
}


Company::Company(int id, int value) : value(value), amount_of_employees(0), best_salary_employee(NULL),
                                      company_employees(), employees_id(), id(id) {}

void Company::AddCompanyValue(int valueIncrease) {
    value = value + valueIncrease;
}

int Company::GetCompanyValue() const {
    return value;
}

Employee *Company::GetBestSalaryEmployee() {
    return best_salary_employee;
}


int Company::GetAmountOfEmployees() const {
    return amount_of_employees;
}

void Company::AddNewEmployee() {
    amount_of_employees++;
}

void Company::RemoveEmployee() {
    amount_of_employees--;
}

Map<Employee *, int> &Company::GetCompanyIDEmployees() {
    return employees_id;
}


Map<Employee *, SalaryId> &Company::GetCompanyEmployees() {
    return company_employees;
}

int Company::GetEmployeeIdWithBestSalary() {
    return best_salary_employee->GetId();
}

void Company::SetCompanyEmployees(const Map<Employee *, SalaryId> &new_company_employees) {
    company_employees = new_company_employees;
}

void Company::SetCompanyValue(int new_value) {
    value = new_value;
}

void Company::SetCompanyBestEmployee(Employee *new_employee) {
    best_salary_employee = new_employee;
}

int Company::GetCompanyId() const {
    return id;
}

int Company::GetCompanyAmountOfEmployees() const {
    return amount_of_employees;
}

void Company::SetCompanyAmountOfEmployees(int new_amount) {
    amount_of_employees = new_amount;
}


// Employee


Employee::Employee(int salary, int grade, int employee_id, Company *company) : salary(salary), grade(grade),
                                                                               company(company), id(employee_id) {

}

int Employee::GetSalary() const {
    return salary;
}

void Employee::IncreaseSalary(int valueIncrease) {
    salary = salary + valueIncrease;
}

void Employee::IncreaseGrade() {
    grade = grade + 1;
}

int Employee::GetGrade() const {
    return grade;
}

int Employee::GetCompanyId() {
    return company->GetCompanyId();
}

Company *Employee::GetCompany() {
    return company;
}

int Employee::GetId() const {
    return id;
}

void Employee::SetCompany(Company *new_company) {
    company = new_company;
}
