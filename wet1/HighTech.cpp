#include "HighTech.h"

void HighTech::UpdateInCompany(Employee *employee, Company *company) {
    if (company->GetAmountOfEmployees() == NULL) {
        company->SetCompanyBestEmployee(employee);
        best_earning_employees.insert(EmployeeByCompanyId(shared_ptr<Employee>(employee)), employee);
    } else {
        if (company->GetBestSalaryEmployee() != NULL) {
            Employee *best_emp = company->GetBestSalaryEmployee();
            int max_salary = best_emp->GetSalary();
            int max_id = best_emp->GetId();
            int current_salary = employee->GetSalary();
            int current_id = employee->GetId();
            if (max_salary < current_salary || (current_salary == max_salary && current_id < max_id)) {
                EmployeeByCompanyId compare = EmployeeByCompanyId(shared_ptr<Employee>(best_emp));
                best_earning_employees.remove(compare);
                best_earning_employees.insert(EmployeeByCompanyId(shared_ptr<Employee>(employee)), employee);
                company->SetCompanyBestEmployee(employee);
            }
        }
        else
        {
            best_earning_employees.insert(EmployeeByCompanyId(shared_ptr<Employee>(employee)), employee);
            company->SetCompanyBestEmployee(employee);
        }
    }
}

void HighTech::UpdateInHighTech(Employee *employee) {
    if (employee_with_best_salary == NULL) {
        employee_with_best_salary = employee;
    } else {
        if (employee_with_best_salary != NULL) {
            Employee *best_emp = employee_with_best_salary;
            int max_salary = best_emp->GetSalary();
            int max_id = best_emp->GetId();
            int current_salary = employee->GetSalary();
            int current_id = employee->GetId();
            if (max_salary < current_salary || (current_salary == max_salary && current_id < max_id)) {
                employee_with_best_salary = employee;
            }
        }
        else
        {
            employee_with_best_salary = employee;
        }

    }

}


HighTech::HighTech() : employees_sorted_by_id(), companies(), employees_sorted_by_salary(), best_earning_employees() {
    employee_with_best_salary = NULL;
    total_amount_of_employees = 0;
}

void HighTech::AddCompany(int CompanyId, int Value) {
    if (CompanyId <= 0 || Value <= 0) {
        throw InvalidInput();
    }
    auto *new_company = new Company(CompanyId, Value);
    try {
        companies.insert(CompanyId, new_company); // O(log k)
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
        UpdateInHighTech(new_employee);
        total_amount_of_employees++;
        if (company->GetAmountOfEmployees() == 1) {
            amount_of_companies_with_at_least_one_employee++;
        }
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
        if (employee->GetCompany()->GetBestSalaryEmployee()->GetId() == employee_id) {
            employee->GetCompany()->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), employee_id));
            employee->GetCompany()->GetCompanyIDEmployees().remove(employee_id);
            employee->GetCompany()->SetCompanyBestEmployee(
                    reinterpret_cast<Employee *>((employee->GetCompany()->GetCompanyEmployees().GetMaxId()).get()));
            best_earning_employees.remove(EmployeeByCompanyId(shared_ptr<Employee>(employee)));
            best_earning_employees.insert(
                    EmployeeByCompanyId(shared_ptr<Employee>(employee->GetCompany()->GetBestSalaryEmployee())),
                    employee);
            employee_with_best_salary = reinterpret_cast<Employee *>(best_earning_employees.GetMaxId().get());
        } else {
            employee->GetCompany()->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), employee_id));
        }
        employee->GetCompany()->RemoveEmployee();
        total_amount_of_employees--;
        if (employee->GetCompany()->GetAmountOfEmployees() == 0) {
            amount_of_companies_with_at_least_one_employee--;
        }
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
        RemoveEmployee(EmployeeID); // O(log k)
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
        employee->IncreaseSalary(SalaryIncrease);
        if (BumpGrade > 0) {
            employee->IncreaseGrade();
        }
        Company *company = employee->GetCompany();
        company->GetCompanyEmployees().remove(SalaryId(employee->GetSalary()-SalaryIncrease, EmployeeID));
        company->GetCompanyEmployees().insert(SalaryId(employee->GetSalary(), employee->GetId()), employee);
        employees_sorted_by_salary.remove(SalaryId(employee->GetSalary()-SalaryIncrease, EmployeeID));
        employees_sorted_by_salary.insert(SalaryId(employee->GetSalary(), employee->GetId()), employee);
        Employee *best_emp = company->GetBestSalaryEmployee();
        if (best_emp->GetSalary() < employee->GetSalary() ||
            (best_emp->GetSalary() == employee->GetSalary() && best_emp->GetId() > employee->GetId())) {
            employee->GetCompany()->GetCompanyEmployees().remove(SalaryId(employee->GetSalary(), EmployeeID));
            employee->GetCompany()->SetCompanyBestEmployee(
                    reinterpret_cast<Employee *>((employee->GetCompany()->GetCompanyEmployees().GetMaxId()).get()));
        }
        if (employee_with_best_salary->GetSalary() < employee->GetSalary() ||
            (employee_with_best_salary->GetSalary() == employee->GetSalary() &&
             employee_with_best_salary->GetId() > employee->GetId())) {
            best_earning_employees.remove(EmployeeByCompanyId(shared_ptr<Employee>(employee)));
            best_earning_employees.insert(
                    EmployeeByCompanyId(shared_ptr<Employee>(employee->GetCompany()->GetBestSalaryEmployee())),
                    employee);
            employee_with_best_salary = reinterpret_cast<Employee *>(best_earning_employees.GetMaxId().get());
        }
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
        if (AcquireCompany->GetCompanyValue() >= TargetCompany->GetCompanyValue() * 10) {
            if (TargetCompany->GetAmountOfEmployees() > 0) {
                amount_of_companies_with_at_least_one_employee--;
            }
            AcquireCompany->SetCompanyEmployees(Map<Employee *, SalaryId>(AcquireCompany->GetCompanyEmployees(),
                                                                          TargetCompany->GetCompanyEmployees()));
            AcquireCompany->SetCompanyValue(
                    (int) (Factor * (AcquireCompany->GetCompanyValue() + TargetCompany->GetCompanyValue())));
            companies.remove(TargetCompany->GetCompanyId());
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
    if (CompanyID < 0 && employee_with_best_salary == NULL) {
        throw Failure();
    }
    if (CompanyID < 0) {
        *EmployeeID = employee_with_best_salary->GetId();
    } else {
        try {
            Company *company = companies.find(CompanyID);
            if ((company->GetEmployeeIdWithBestSalary()) == NULL) {
                throw Failure();
            }
            *EmployeeID = company->GetEmployeeIdWithBestSalary();
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
        int amount = 0;
        int *emp = new int[total_amount_of_employees];
        Pair<Employee *, SalaryId> *pair_list = employees_sorted_by_salary.GetFirstNum(total_amount_of_employees);
        for (int i = 0; i < total_amount_of_employees; i++) {
            emp[i] = pair_list[i].element->GetId();
        }
        *Employees = emp;
        *NumOfEmployees = total_amount_of_employees;
    } else {
        try {
            Company *company = companies.find(companyID);
            if (company->GetEmployeeIdWithBestSalary() == NULL) {
                throw Failure();
            }
            int *emp = new int[company->GetAmountOfEmployees()];
            Pair<Employee *, SalaryId> *pair_list = company->GetCompanyEmployees().GetFirstNum(
                    company->GetAmountOfEmployees());
            for (int i = 0; i < company->GetAmountOfEmployees(); i++) {
                emp[i] = pair_list[i].element->GetId();
            }
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
    int *emp = new int[NumOfCompanies];
    Pair<Employee *, EmployeeByCompanyId> *pair_list = best_earning_employees.GetFirstNum(NumOfCompanies);
    for (int i = 0; i < NumOfCompanies; i++) {
        emp[i] = pair_list[i].element->GetId();
    }
    *Employees = emp;
}

void HighTech::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeID, int MinSalary, int MinGrade,
                                       int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (TotalNumOfEmployees == NULL || NumOfEmployees == NULL || CompanyID == 0 || MinEmployeeID < 0 ||
        MaxEmployeeID < 0 || MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeID) {
        throw InvalidInput();
    }
    if (CompanyID < 0 && employee_with_best_salary == NULL) {
        throw Failure();
    }
    if (CompanyID < 0) {
        Pair<Employee *, int> *pair_list = employees_sorted_by_id.GetObjectsFromKey(MinEmployeeID, MaxEmployeeID,
                                                                                    TotalNumOfEmployees);
        int count = 0;
        for (int i = 0; i < *TotalNumOfEmployees; i++) {
            if (pair_list->element->GetSalary() >= MinSalary && pair_list->element->GetGrade() >= MinGrade) {
                count++;
            }
        }
        *NumOfEmployees = count;
    } else {
        try {
            Company *company = companies.find(CompanyID);
            Pair<Employee *, int> *pair_list = company->GetCompanyIDEmployees().GetObjectsFromKey(MinEmployeeID,
                                                                                                  MaxEmployeeID,
                                                                                                  TotalNumOfEmployees);
            int count = 0;
            for (int i = 0; i < *TotalNumOfEmployees; i++) {
                if (pair_list->element->GetSalary() >= MinSalary && pair_list->element->GetGrade() >= MinGrade) {
                    count++;
                }
            }
            *NumOfEmployees = count;
        }
        catch (KeyDoesntExist &k) {
            throw Failure();
        }
    }

}











// Compnay

Company::Company(int id, int value) : id(id), value(value), amount_of_employees(0), company_employees(), employees_id(),
                                      best_salary_employee(NULL) {}

void Company::AddCompanyValue(int valueIncrease) {
    value = value + valueIncrease;
}

int Company::GetCompanyValue() {
    return value;
}

Employee *Company::GetBestSalaryEmployee() {
    return best_salary_employee;
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

Map<Employee *, int> &Company::GetCompanyIDEmployees() {
    return employees_id;
}

Map<Employee *, SalaryId> &Company::GetCompanyEmployees() {
    return company_employees;
}

int Company::GetEmployeeIdWithBestSalary() {
    return best_salary_employee->GetId();
}

void Company::SetCompanyEmployees(Map<Employee *, SalaryId> new_company_employees) {
    company_employees = new_company_employees;
}

void Company::SetCompanyValue(int new_value) {
    value = new_value;
}

void Company::SetCompanyBestEmployee(Employee *new_employee) {
    best_salary_employee = new_employee;
}

int Company::GetCompanyId() {
    return id;
}



// Employee

Employee::Employee() {

}

Employee::Employee(int salary, int grade, int employee_id, Company *company) : salary(salary), grade(grade),
                                                                               company(company), id(employee_id) {

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
    return company->GetCompanyId();
}

Company *Employee::GetCompany() {
    return company;
}

int Employee::GetId() {
    return id;
}
