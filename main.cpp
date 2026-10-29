#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <ctime>
#include <cctype>

using namespace std;

// ============================================================
// INPUT VALIDATION FUNCTIONS
// ============================================================

string readText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (value.find_first_not_of(" \t\r\n") != string::npos &&
            value.find('|') == string::npos) {
            return value;
        }

        cout << "Invalid input. Enter a non-empty value without '|'.\n";
    }
}

double readNonNegative(const string& prompt) {
    string input;
    double value;

    while (true) {
        cout << prompt;
        getline(cin, input);

        try {
            size_t pos = 0;
            value = stod(input, &pos);

            if (pos != input.size() || value < 0 ||
                value != value || value > 1e12) {
                throw invalid_argument("Invalid number");
            }

            return value;
        } catch (...) {
            cout << "Invalid input. Enter a non-negative number.\n";
        }
    }
}

int readInt(const string& prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(cin, input);

        try {
            size_t pos = 0;
            value = stoi(input, &pos);

            if (pos != input.size()) {
                throw invalid_argument("Invalid integer");
            }

            return value;
        } catch (...) {
            cout << "Invalid input. Enter a whole number.\n";
        }
    }
}

int readPositiveInt(const string& prompt) {
    int value;

    while (true) {
        value = readInt(prompt);

        if (value > 0) {
            return value;
        }

        cout << "ID must be greater than zero.\n";
    }
}

string toLowerCase(string value) {
    transform(value.begin(), value.end(), value.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    return value;
}

string currentDateTime() {
    time_t now = time(NULL);
    tm* local = localtime(&now);

    if (local == NULL) {
        return "Date unavailable";
    }

    ostringstream output;
    output << put_time(local, "%Y-%m-%d %H:%M:%S");
    return output.str();
}

// ============================================================
// ABSTRACT BASE CLASS: EMPLOYEE
// ============================================================

class Employee {
private:
    int id;
    string name;
    string department;

protected:
    void editCommonDetails() {
        name = readText("Enter employee name: ");
        department = readText("Enter department: ");
    }

public:
    Employee(int employeeID, const string& employeeName,
             const string& employeeDepartment)
        : id(employeeID), name(employeeName),
          department(employeeDepartment) {}

    virtual ~Employee() {}

    int getID() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getDepartment() const {
        return department;
    }

    virtual string getType() const = 0;
    virtual double getGrossPay() const = 0;
    virtual double getDeductions() const = 0;
    virtual void editDetails() = 0;
    virtual void save(ofstream& file) const = 0;

    double getNetPay() const {
        return getGrossPay() - getDeductions();
    }

    virtual void display() const {
        cout << fixed << setprecision(2);
        cout << "\nEmployee ID : " << id
             << "\nName        : " << name
             << "\nDepartment  : " << department
             << "\nType        : " << getType()
             << "\nGross Pay   : PKR " << getGrossPay()
             << "\nDeductions  : PKR " << getDeductions()
             << "\nNet Pay     : PKR " << getNetPay() << "\n";
    }

    virtual void salaryDetails(ostream& out) const = 0;
};

// ============================================================
// DERIVED CLASS: FULL-TIME EMPLOYEE
// ============================================================

class FullTimeEmployee : public Employee {
private:
    double monthlySalary;
    double bonus;
    double deductions;

public:
    FullTimeEmployee(int id, const string& name,
                     const string& department,
                     double salary, double extraBonus,
                     double salaryDeductions)
        : Employee(id, name, department),
          monthlySalary(salary), bonus(extraBonus),
          deductions(salaryDeductions) {
        validatePayroll();
    }

    void validatePayroll() const {
        if (monthlySalary < 0 || bonus < 0 || deductions < 0 ||
            monthlySalary + bonus < deductions) {
            throw invalid_argument("Invalid full-time payroll values.");
        }
    }

    string getType() const {
        return "Full-Time";
    }

    double getGrossPay() const {
        return monthlySalary + bonus;
    }

    double getDeductions() const {
        return deductions;
    }

    void editDetails() {
        editCommonDetails();
        monthlySalary = readNonNegative("Enter monthly basic salary (PKR): ");
        bonus = readNonNegative("Enter bonus (PKR): ");

        while (true) {
            deductions = readNonNegative("Enter deductions (PKR): ");

            if (deductions <= monthlySalary + bonus) {
                break;
            }

            cout << "Deductions cannot exceed gross pay.\n";
        }
    }

    void display() const {
        Employee::display();
        cout << "Basic Salary: PKR " << monthlySalary
             << "\nBonus       : PKR " << bonus << "\n";
    }

    void salaryDetails(ostream& out) const {
        out << "Employment Type : Full-Time\n"
            << "Monthly Salary  : PKR " << fixed << setprecision(2)
            << monthlySalary << "\n"
            << "Bonus           : PKR " << bonus << "\n"
            << "Gross Pay       : PKR " << getGrossPay() << "\n"
            << "Deductions      : PKR " << deductions << "\n"
            << "Net Pay         : PKR " << getNetPay() << "\n";
    }

    void save(ofstream& file) const {
        file << "F|" << getID() << "|" << getName() << "|"
             << getDepartment() << "|" << monthlySalary << "|"
             << bonus << "|" << deductions << "\n";
    }
};

// ============================================================
// DERIVED CLASS: PART-TIME EMPLOYEE
// ============================================================

class PartTimeEmployee : public Employee {
private:
    double hourlyRate;
    double hoursWorked;
    double bonus;
    double deductions;

public:
    PartTimeEmployee(int id, const string& name,
                     const string& department,
                     double rate, double hours,
                     double extraBonus, double salaryDeductions)
        : Employee(id, name, department),
          hourlyRate(rate), hoursWorked(hours),
          bonus(extraBonus), deductions(salaryDeductions) {
        validatePayroll();
    }

    void validatePayroll() const {
        if (hourlyRate < 0 || hoursWorked < 0 ||
            bonus < 0 || deductions < 0 ||
            hourlyRate * hoursWorked + bonus < deductions) {
            throw invalid_argument("Invalid part-time payroll values.");
        }
    }

    string getType() const {
        return "Part-Time";
    }

    double getGrossPay() const {
        return hourlyRate * hoursWorked + bonus;
    }

    double getDeductions() const {
        return deductions;
    }

    void editDetails() {
        editCommonDetails();
        hourlyRate = readNonNegative("Enter hourly rate (PKR): ");
        hoursWorked = readNonNegative("Enter hours worked: ");
        bonus = readNonNegative("Enter bonus (PKR): ");

        while (true) {
            deductions = readNonNegative("Enter deductions (PKR): ");

            if (deductions <= hourlyRate * hoursWorked + bonus) {
                break;
            }

            cout << "Deductions cannot exceed gross pay.\n";
        }
    }

    void display() const {
        Employee::display();
        cout << "Hourly Rate : PKR " << hourlyRate
             << "\nHours Worked: " << hoursWorked
             << "\nBonus       : PKR " << bonus << "\n";
    }

    void salaryDetails(ostream& out) const {
        out << "Employment Type : Part-Time\n"
            << "Hourly Rate     : PKR " << fixed << setprecision(2)
            << hourlyRate << "\n"
            << "Hours Worked    : " << hoursWorked << "\n"
            << "Bonus           : PKR " << bonus << "\n"
            << "Gross Pay       : PKR " << getGrossPay() << "\n"
            << "Deductions      : PKR " << deductions << "\n"
            << "Net Pay         : PKR " << getNetPay() << "\n";
    }

    void save(ofstream& file) const {
        file << "P|" << getID() << "|" << getName() << "|"
             << getDepartment() << "|" << hourlyRate << "|"
             << hoursWorked << "|" << bonus << "|"
             << deductions << "\n";
    }
};

// ============================================================
// EMPLOYEE MANAGEMENT SYSTEM
// ============================================================

class EmployeeManager {
private:
    vector<shared_ptr<Employee> > employees;

    const string employeeFile;
    const string payrollFile;

    shared_ptr<Employee> findByID(int id) const {
        for (size_t i = 0; i < employees.size(); ++i) {
            if (employees[i]->getID() == id) {
                return employees[i];
            }
        }

        return shared_ptr<Employee>();
    }

    void saveEmployees() const {
        ofstream file(employeeFile.c_str());

        if (!file) {
            throw runtime_error("Unable to open employee data file for saving.");
        }

        file << setprecision(15);

        for (size_t i = 0; i < employees.size(); ++i) {
            employees[i]->save(file);
        }

        if (!file) {
            throw runtime_error("Error while saving employee records.");
        }
    }

    void recordPayroll(const Employee& employee) const {
        ofstream file(payrollFile.c_str(), ios::app);

        if (!file) {
            throw runtime_error("Unable to open payroll history file.");
        }

        file << fixed << setprecision(2);
        file << "Date: " << currentDateTime() << "\n"
             << "Employee ID: " << employee.getID() << "\n"
             << "Name: " << employee.getName() << "\n"
             << "Department: " << employee.getDepartment() << "\n";

        employee.salaryDetails(file);
        file << "----------------------------------------\n";

        if (!file) {
            throw runtime_error("Error writing payroll history.");
        }
    }

    void generateSalaryStatement(const Employee& employee) const {
        ostringstream filename;
        filename << "salary_statement_" << employee.getID() << ".txt";

        ofstream file(filename.str().c_str());

        if (!file) {
            throw runtime_error("Unable to create salary statement.");
        }

        file << "========================================\n"
             << "       EMPLOYEE SALARY STATEMENT\n"
             << "========================================\n"
             << "Generated: " << currentDateTime() << "\n\n"
             << "Employee ID : " << employee.getID() << "\n"
             << "Name        : " << employee.getName() << "\n"
             << "Department  : " << employee.getDepartment() << "\n";

        employee.salaryDetails(file);

        file << "\n========================================\n"
             << "This statement was generated by the\n"
             << "Employee Management System.\n";

        if (!file) {
            throw runtime_error("Error writing salary statement.");
        }

        cout << "Salary statement saved as "
             << filename.str() << "\n";
    }

public:
    EmployeeManager()
        : employeeFile("employees.txt"),
          payrollFile("payroll_history.txt") {}

    void loadEmployees() {
        ifstream file(employeeFile.c_str());

        // The file may not exist on the first run.
        if (!file) {
            cout << "No existing employee file found. "
                 << "A new file will be created when records are saved.\n";
            return;
        }

        string line;
        int loaded = 0;
        int skipped = 0;

        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            try {
                vector<string> fields;
                string field;
                stringstream stream(line);

                while (getline(stream, field, '|')) {
                    fields.push_back(field);
                }

                if (fields.size() < 7) {
                    throw invalid_argument("Incomplete record.");
                }

                int id = stoi(fields[1]);

                if (id <= 0 || findByID(id)) {
                    throw invalid_argument("Invalid or duplicate ID.");
                }

                shared_ptr<Employee> employee;

                if (fields[0] == "F" && fields.size() == 7) {
                    employee = make_shared<FullTimeEmployee>(
                        id, fields[2], fields[3],
                        stod(fields[4]), stod(fields[5]),
                        stod(fields[6]));
                } else if (fields[0] == "P" && fields.size() == 8) {
                    employee = make_shared<PartTimeEmployee>(
                        id, fields[2], fields[3],
                        stod(fields[4]), stod(fields[5]),
                        stod(fields[6]), stod(fields[7]));
                } else {
                    throw invalid_argument("Unknown employee type.");
                }

                employees.push_back(employee);
                ++loaded;
            } catch (...) {
                ++skipped;
            }
        }

        cout << loaded << " employee record(s) loaded.\n";

        if (skipped > 0) {
            cout << skipped
                 << " invalid record(s) were skipped.\n";
        }
    }

    void addEmployee() {
        cout << "\n--- Add Employee ---\n";

        int id = readPositiveInt("Enter employee ID: ");

        if (findByID(id)) {
            cout << "An employee with this ID already exists.\n";
            return;
        }

        string name = readText("Enter employee name: ");
        string department = readText("Enter department: ");

        cout << "\n1. Full-Time Employee\n"
             << "2. Part-Time Employee\n";

        int type = readInt("Choose employee type: ");
        shared_ptr<Employee> employee;

        try {
            if (type == 1) {
                double salary = readNonNegative(
                    "Enter monthly basic salary (PKR): ");
                double bonus = readNonNegative(
                    "Enter bonus (PKR): ");

                double deductions;

                while (true) {
                    deductions = readNonNegative(
                        "Enter deductions (PKR): ");

                    if (deductions <= salary + bonus) {
                        break;
                    }

                    cout << "Deductions cannot exceed gross pay.\n";
                }

                employee = make_shared<FullTimeEmployee>(
                    id, name, department, salary, bonus, deductions);
            } else if (type == 2) {
                double rate = readNonNegative(
                    "Enter hourly rate (PKR): ");
                double hours = readNonNegative(
                    "Enter hours worked: ");
                double bonus = readNonNegative(
                    "Enter bonus (PKR): ");

                double deductions;

                while (true) {
                    deductions = readNonNegative(
                        "Enter deductions (PKR): ");

                    if (deductions <= rate * hours + bonus) {
                        break;
                    }

                    cout << "Deductions cannot exceed gross pay.\n";
                }

                employee = make_shared<PartTimeEmployee>(
                    id, name, department, rate, hours,
                    bonus, deductions);
            } else {
                cout << "Invalid employee type.\n";
                return;
            }

            employees.push_back(employee);
            saveEmployees();

            cout << "Employee added and saved successfully.\n";
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    void displayEmployees() const {
        cout << "\n--- Employee Records ---\n";

        if (employees.empty()) {
            cout << "No employee records available.\n";
            return;
        }

        for (size_t i = 0; i < employees.size(); ++i) {
            employees[i]->display();
            cout << "----------------------------------------\n";
        }
    }

    void searchEmployee() const {
        cout << "\n--- Search Employee ---\n"
             << "1. Search by ID\n"
             << "2. Search by name\n";

        int option = readInt("Choose search method: ");

        if (option == 1) {
            int id = readPositiveInt("Enter employee ID: ");
            shared_ptr<Employee> employee = findByID(id);

            if (employee) {
                employee->display();
            } else {
                cout << "Employee not found.\n";
            }
        } else if (option == 2) {
            string name = toLowerCase(
                readText("Enter full or partial name: "));

            bool found = false;

            for (size_t i = 0; i < employees.size(); ++i) {
                if (toLowerCase(employees[i]->getName()).find(name)
                    != string::npos) {
                    employees[i]->display();
                    found = true;
                }
            }

            if (!found) {
                cout << "No matching employee found.\n";
            }
        } else {
            cout << "Invalid search option.\n";
        }
    }

    void updateEmployee() {
        cout << "\n--- Update Employee ---\n";

        int id = readPositiveInt("Enter employee ID: ");
        shared_ptr<Employee> employee = findByID(id);

        if (!employee) {
            cout << "Employee not found.\n";
            return;
        }

        cout << "Current record:\n";
        employee->display();

        cout << "\nEnter the updated details:\n";

        try {
            employee->editDetails();
            saveEmployees();

            cout << "Employee updated successfully.\n";
        } catch (const exception& e) {
            cout << "Error updating employee: " << e.what() << "\n";
        }
    }

    void deleteEmployee() {
        cout << "\n--- Delete Employee ---\n";

        int id = readPositiveInt("Enter employee ID: ");

        for (vector<shared_ptr<Employee> >::iterator it = employees.begin();
             it != employees.end(); ++it) {
            if ((*it)->getID() == id) {
                cout << "Employee: " << (*it)->getName() << "\n";

                string confirmation = toLowerCase(
                    readText("Type YES to confirm deletion: "));

                if (confirmation != "yes") {
                    cout << "Deletion cancelled.\n";
                    return;
                }

                shared_ptr<Employee> backup = *it;
                size_t index = static_cast<size_t>(
                    distance(employees.begin(), it));

                employees.erase(it);

                try {
                    saveEmployees();
                    cout << "Employee deleted successfully.\n";
                } catch (const exception& e) {
                    employees.insert(employees.begin() + index, backup);
                    cout << "Deletion could not be saved: "
                         << e.what() << "\n";
                }

                return;
            }
        }

        cout << "Employee not found.\n";
    }

    void sortEmployees() {
        if (employees.empty()) {
            cout << "No employee records to sort.\n";
            return;
        }

        cout << "\n--- Sort Employees ---\n"
             << "1. By name (A-Z)\n"
             << "2. By net salary (highest first)\n";

        int option = readInt("Choose sorting method: ");

        if (option == 1) {
            sort(employees.begin(), employees.end(),
                [](const shared_ptr<Employee>& a,
                   const shared_ptr<Employee>& b) {
                    return toLowerCase(a->getName()) <
                           toLowerCase(b->getName());
                });
        } else if (option == 2) {
            sort(employees.begin(), employees.end(),
                [](const shared_ptr<Employee>& a,
                   const shared_ptr<Employee>& b) {
                    return a->getNetPay() > b->getNetPay();
                });
        } else {
            cout << "Invalid sorting option.\n";
            return;
        }

        cout << "Employees sorted successfully.\n";
        displayEmployees();
    }

    void payrollReport() const {
        cout << "\n--- Payroll Summary Report ---\n";

        if (employees.empty()) {
            cout << "No employee records available.\n";
            return;
        }

        double totalGross = 0;
        double totalDeductions = 0;
        double totalNet = 0;
        int fullTimeCount = 0;
        int partTimeCount = 0;

        for (size_t i = 0; i < employees.size(); ++i) {
            totalGross += employees[i]->getGrossPay();
            totalDeductions += employees[i]->getDeductions();
            totalNet += employees[i]->getNetPay();

            if (employees[i]->getType() == "Full-Time") {
                ++fullTimeCount;
            } else {
                ++partTimeCount;
            }
        }

        cout << fixed << setprecision(2);
        cout << "Total Employees     : " << employees.size() << "\n"
             << "Full-Time Employees : " << fullTimeCount << "\n"
             << "Part-Time Employees : " << partTimeCount << "\n"
             << "Total Gross Payroll : PKR " << totalGross << "\n"
             << "Total Deductions    : PKR " << totalDeductions << "\n"
             << "Total Net Payroll   : PKR " << totalNet << "\n";
    }

    void processPayroll() {
        cout << "\n--- Process Payroll ---\n";

        int id = readPositiveInt("Enter employee ID: ");
        shared_ptr<Employee> employee = findByID(id);

        if (!employee) {
            cout << "Employee not found.\n";
            return;
        }

        employee->display();

        string confirmation = toLowerCase(
            readText("Type YES to record this payroll: "));

        if (confirmation != "yes") {
            cout << "Payroll cancelled.\n";
            return;
        }

        try {
            recordPayroll(*employee);
            generateSalaryStatement(*employee);

            cout << "Payroll recorded successfully.\n";
        } catch (const exception& e) {
            cout << "Payroll error: " << e.what() << "\n";
        }
    }

    void viewPayrollHistory() const {
        cout << "\n--- Payroll History ---\n";

        ifstream file(payrollFile.c_str());

        if (!file) {
            cout << "No payroll history is available yet.\n";
            return;
        }

        string line;
        bool hasContent = false;

        while (getline(file, line)) {
            cout << line << "\n";
            hasContent = true;
        }

        if (!hasContent) {
            cout << "Payroll history is empty.\n";
        }
    }

    void run() {
        loadEmployees();

        while (true) {
            cout << "\n========================================\n"
                 << "    ADVANCED EMPLOYEE MANAGEMENT SYSTEM\n"
                 << "========================================\n"
                 << "1.  Add Employee\n"
                 << "2.  Display All Employees\n"
                 << "3.  Search Employee\n"
                 << "4.  Update Employee\n"
                 << "5.  Delete Employee\n"
                 << "6.  Sort Employees\n"
                 << "7.  Payroll Summary Report\n"
                 << "8.  Process Payroll & Generate Statement\n"
                 << "9.  View Payroll History\n"
                 << "10. Save Records\n"
                 << "0.  Save and Exit\n"
                 << "----------------------------------------\n";

            int choice = readInt("Enter your choice: ");

            try {
                switch (choice) {
                    case 1:
                        addEmployee();
                        break;

                    case 2:
                        displayEmployees();
                        break;

                    case 3:
                        searchEmployee();
                        break;

                    case 4:
                        updateEmployee();
                        break;

                    case 5:
                        deleteEmployee();
                        break;

                    case 6:
                        sortEmployees();
                        break;

                    case 7:
                        payrollReport();
                        break;

                    case 8:
                        processPayroll();
                        break;

                    case 9:
                        viewPayrollHistory();
                        break;

                    case 10:
                        saveEmployees();
                        cout << "Employee records saved successfully.\n";
                        break;

                    case 0:
                        saveEmployees();
                        cout << "Records saved. Exiting program. Goodbye!\n";
                        return;

                    default:
                        cout << "Invalid menu option. Try again.\n";
                }
            } catch (const exception& e) {
                cout << "Operation failed: " << e.what() << "\n";
            }
        }
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    try {
        EmployeeManager manager;
        manager.run();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}