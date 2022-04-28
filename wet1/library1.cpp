//
// Created by Daniel on 4/26/2022.
//
#include"library1.h"
#include "HighTech.h"

void *Init() {
    HighTech *DS = new HighTech();
    return (void *) DS;
}

StatusType AddCompany(void *DS, int CompanyID, int Value) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AddCompany(CompanyID, Value);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType RemoveCompany(void *DS, int CompanyID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->RemoveCompany(CompanyID);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType RemoveEmployee(void *DS, int EmployeeID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->RemoveEmployee(EmployeeID);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->HireEmployee(EmployeeID, NewCompanyID);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->AcquireCompany(AcquirerID, TargetID, Factor);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetHighestEarner(CompanyID, EmployeeID);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (DS == NULL) return INVALID_INPUT;
    try {
        ((HighTech *) DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade,
                                                   TotalNumOfEmployees, NumOfEmployees);
    }
    catch (InvalidInput) {
        return INVALID_INPUT;
    }
    catch (Failure) {
        return FAILURE;
    }
    catch (std::bad_alloc) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void **DS) {
    *DS = NULL;
}