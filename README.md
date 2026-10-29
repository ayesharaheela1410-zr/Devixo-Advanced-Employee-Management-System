# Devixo-Advanced-Employee-Management-System
An advanced C++ Employee Management System featuring OOP, inheritance, polymorphism, employee records, payroll calculations, salary statements, sorting, searching, exception handling, and file persistence — Devixo Solutions Internship Task 04.

# 👥 Advanced Employee Management System with Payroll

### Devixo Solutions Internship — Task 04 | C++

An advanced console-based **Employee Management System with Payroll** developed in C++ as part of the Devixo Solutions internship. The project demonstrates object-oriented programming, encapsulation, inheritance, polymorphism, exception handling, STL vectors, searching, sorting, input validation, and file handling.

The application manages employee records, supports full-time and part-time employee types, calculates payroll, generates salary statements, maintains payroll history, and saves employee information for future use.

---

## 📌 Table of Contents

- [Project Overview](#-project-overview)
- [Objectives](#-objectives)
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Programming Concepts](#-programming-concepts)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [How to Use](#-how-to-use)
- [Payroll Calculation](#-payroll-calculation)
- [Data Storage and File Handling](#-data-storage-and-file-handling)
- [Input Validation and Exception Handling](#-input-validation-and-exception-handling)
- [Testing](#-testing)
- [Limitations](#-limitations)
- [Future Improvements](#-future-improvements)
- [Internship Information](#-internship-information)
- [Author](#-author)

---
## 📖 Project Overview

The Advanced Employee Management System provides a structured way to manage employee information and payroll through an interactive command-line interface.

The application supports two employee categories: full-time and part-time employees. It allows users to add, display, search, update, and delete employee records. It also supports sorting employee records, calculating payroll, displaying payroll summaries, generating individual salary statements, and maintaining a payroll history.

Employee information is stored in a text file so that records can be loaded when the application starts. Payroll transactions and salary statements are also written to text files when the corresponding operations are completed successfully.

This project applies object-oriented programming and practical C++ techniques to an employee administration and payroll management scenario.

## 🎯 Objectives

The main objectives of this project are to:

- Apply classes and objects to represent employees and manage employee records.
- Implement encapsulation to organize employee data and related operations.
- Use inheritance to represent different employee categories.
- Demonstrate polymorphism through a common employee interface.
- Use constructors to initialize employee objects.
- Manage employee records through STL vectors.
- Implement searching and sorting operations.
- Calculate employee salaries, bonuses, deductions, and net pay.
- Generate salary statements and maintain payroll history.
- Apply input validation and exception handling.
- Use file handling to save and retrieve employee records.
- Develop a modular, menu-driven console application.

## ✨ Features

| Feature | Description |
|---|---|
| Add Employee | Adds a new full-time or part-time employee. |
| Display Employees | Displays stored employee information. |
| Search Employee | Searches for an employee using an ID or name. |
| Update Employee | Updates the details of an existing employee. |
| Delete Employee | Removes an employee record. |
| Full-Time Employees | Supports monthly salary, bonus, and deductions. |
| Part-Time Employees | Supports hourly rates, hours worked, bonus, and deductions. |
| Payroll Calculation | Calculates gross pay and net pay. |
| Sorting | Sorts employee records by name or net salary. |
| Payroll Summary | Displays a summary of employee payroll information. |
| Salary Statement | Generates an individual employee salary statement. |
| Payroll History | Records payroll processing details in a text file. |
| File Persistence | Saves and loads employee records. |
| Input Validation | Handles invalid input according to the implemented validation rules. |

### ⭐ Bonus Features

The project includes payroll history and individual salary statement generation.

When payroll is processed, the application can record the payroll transaction and generate a salary statement for the selected employee, provided the relevant file operations succeed.

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Standard Library:** `iostream`, `string`, `vector`, `fstream`, `memory`, `algorithm`, and other required standard headers
- **Data Structure:** `vector<shared_ptr<Employee>>`
- **Object-Oriented Design:** Abstract base class and derived employee classes
- **Data Storage:** Text files
- **Development Environment:** Code Utility Online C++ Compiler

## 🧠 Programming Concepts

### 1. Classes and Objects

The program uses classes to represent employees and organize employee management and payroll operations.

- **`Employee`** — the common abstract base class for employee information and payroll behaviour.
- **`FullTimeEmployee`** — represents employees paid using a monthly salary structure.
- **`PartTimeEmployee`** — represents employees paid according to an hourly rate and hours worked.
- **`EmployeeManager`** — manages employee records and provides operations such as adding, searching, updating, deleting, sorting, saving, and loading records.

### 2. Encapsulation

Employee information and related behaviour are organized within classes. Member functions provide structured access to employee data and payroll operations.

### 3. Inheritance

The `FullTimeEmployee` and `PartTimeEmployee` classes inherit from the `Employee` base class. This allows common employee functionality to be shared while supporting different salary structures.

### 4. Polymorphism

Virtual functions allow the application to work with different employee types through the common `Employee` interface. Derived classes provide employee-specific payroll calculations.

### 5. Constructors

Constructors initialize employee objects with the information required for their respective employee categories.

### 6. STL Vectors

The program uses `vector<shared_ptr<Employee>>` to maintain a dynamically sized collection of employee objects.

### 7. Searching

Searching operations allow the user to locate employees using supported identifiers, such as employee ID or employee name.

### 8. Sorting

Sorting operations organize employee records by supported fields, such as employee name or net salary.

### 9. Functions and Modular Programming

Separate member functions organize employee management, payroll processing, data storage, searching, sorting, and reporting operations into manageable sections.

### 10. File Handling

File streams save and retrieve employee records, append payroll history, and generate individual salary statements.

### 11. Exception Handling and Input Validation

The application uses input validation and error-handling techniques to deal with invalid entries and supported exceptional conditions.

### 12. Payroll Calculations

The system calculates gross pay and net pay using the salary information associated with each employee category.

## 📁 Project Structure

The intended repository structure is:

```text
Devixo-Advanced-Employee-Management-System/
│
├── main.cpp
├── employees.txt
├── payroll_history.txt
├── salary_statement_101.txt
├── README.md
├── screenshots/
│   ├── libraries
│   ├── classes
│   ├── main menu loop
└── Devixo_Employee_Management_System_Report.pdf
```
## 🚀 Getting Started

### Prerequisites

You need a C++ compiler that supports the standard library and C++11 or later.

Examples include:

- GCC / G++
- Code::Blocks
- Visual Studio with C++ support
- A compatible online C++ compiler

### Installation

1. Clone or download the repository.
2. Open the project directory.
3. Open `main.cpp` in a compatible C++ editor or compiler.
4. Compile and execute the program.
5. Follow the interactive menu to manage employees and process payroll.

### Compile Using G++

If G++ is installed, open a terminal in the project directory and run:

```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o employee_management
```

On Windows, execute:

```bash
employee_management.exe
```

On Linux or macOS, execute:

```bash
./employee_management
```

Alternatively, run the source code in the Code Utility Online C++ Compiler or another compatible environment.

## 🖥️ How to Use

After launching the application, follow the on-screen menu to select an employee management or payroll operation.

The general workflow is:

1. **Add an employee:** Select the relevant employee category and enter the requested details.
2. **Display employees:** View the stored employee records.
3. **Search:** Find an employee using the supported search options.
4. **Update:** Modify an existing employee's details.
5. **Delete:** Remove an employee record when required.
6. **Sort records:** Organize employees using the available sorting options.
7. **View payroll summary:** Review the payroll information calculated by the application.
8. **Process payroll:** Calculate the selected employee's payroll and generate the corresponding statement.
9. **Review files:** Inspect the employee data, payroll history, and salary statement files.
10. **Save Records:** Inspect the employee data, payroll history, and save it in .txt files.
11. **Exit:** Close the application using the exit option.

## 💰 Payroll Calculation

The application uses different pay structures for full-time and part-time employees.

### Full-Time Employee

The general calculation is:

```text
Gross Pay = Monthly Salary + Bonus
Net Pay   = Gross Pay - Deductions
```

**Example:**

| Component | Amount |
|---|---:|
| Monthly salary | PKR 50,000 |
| Bonus | PKR 5,000 |
| Gross pay | PKR 55,000 |
| Deductions | PKR 2,000 |
| Net pay | PKR 53,000 |

### Part-Time Employee

The general calculation is:

```text
Base Pay  = Hourly Rate × Hours Worked
Gross Pay = Base Pay + Bonus
Net Pay   = Gross Pay - Deductions
```

The actual calculation depends on the salary fields and formulas implemented in the source code. Any sample values above are illustrative and should not be presented as actual program output unless verified.

## 💾 Data Storage and File Handling

The application uses text files to store employee information and payroll records.

### `employees.txt`

Stores employee records so that the application can retrieve previously saved employee information when it starts.

The file uses a pipe-separated record format.

A full-time employee record may follow this structure:

```text
F|101|Sara Khan|Human Resources|50000|5000|2000
```

A part-time employee record may follow this structure:

```text
P|102|Ali Ahmed|Sales|500|80|3000|1000
```

These examples illustrate the intended field structure:

- Employee category
- Employee ID
- Employee name
- Department
- Salary-related information
- Bonus and deductions

The exact field order must match the final source code.

### `payroll_history.txt`

Stores payroll processing history when a payroll transaction is recorded successfully.

### `salary_statement_101.txt`

An example of an individual salary statement file. The actual filename depends on the selected employee ID.

The application accesses these files relative to its working directory. In online compiler environments, file persistence between separate executions depends on the environment's storage behaviour.

## 🛡️ Input Validation and Exception Handling

The application should be tested for appropriate handling of invalid input, including:

- Invalid menu selections.
- Non-numeric input where a number is required.
- Duplicate employee IDs.
- Invalid or nonexistent employee IDs.
- Empty or invalid employee names and department values.
- Negative salary, bonus, deduction, or hourly-rate values.
- Invalid hours-worked values.
- Attempts to update or delete nonexistent employees.
- File-opening or file-writing failures, where handled by the implementation.

## 🧪 Testing

The following test cases can be used to evaluate the application.

| Test | Expected Behaviour |
|---|---|
| Add a full-time employee | A full-time employee record is created. |
| Add a part-time employee | A part-time employee record is created. |
| Display employees | Stored employee records are displayed. |
| Search by ID | The matching employee is found when the ID exists. |
| Search by name | Matching employees are found using the supported name search. |
| Update employee | The selected employee's details are updated. |
| Delete employee | The selected employee record is removed. |
| Sort by name | Employee records are ordered by name. |
| Sort by net salary | Employee records are ordered using the implemented net-salary sorting logic. |
| Payroll summary | Payroll information is calculated and displayed. |
| Process payroll | The selected employee's payroll is calculated. |
| Generate salary statement | A salary statement is written when the operation succeeds. |
| Payroll history | Payroll transactions are recorded in the history file. |
| Invalid input | Invalid entries are handled according to the implemented validation rules. |
| Duplicate employee ID | A duplicate ID is rejected if duplicate checking is implemented. |
| Save and reload | Previously saved employee records are restored when the application runs again in a persistent environment. |

## ⚠️ Limitations

- The application uses a console-based interface rather than a graphical interface.
- Records are stored in text files instead of a database.
- The application does not provide a full authentication or role-based access system.
- File persistence depends on the working directory and execution environment.
- Payroll calculations are limited to the salary components implemented in the current version.
- The application is intended as an educational project and is not a replacement for a production payroll platform.

## 🔮 Future Improvements

Potential improvements include:

- A graphical user interface.
- Database integration using SQLite or MySQL.
- Employee attendance and leave management.
- Tax calculations and additional payroll deductions.
- Monthly payroll reports and historical salary comparisons.
- Exporting salary statements to PDF.
- User authentication and role-based access control.
- Improved data validation and recovery from corrupted files.
- Department-wise employee and payroll reports.

## 🎓 Internship Information

- **Organization:** Devixo Solutions
- **Program:** C++ Programming Internship
- **Task Number:** Task 04
- **Project:** Advanced Employee Management System with Payroll
- **Language:** C++
- **Development Environment:** Code Utility Online C++ Compiler

This project was developed to demonstrate practical C++ programming skills, object-oriented design, employee record management, payroll calculations, data structures, and file handling.

## 👩‍💻 Author

**Ayesha Raheela**  
BS Computer Science Student

GitHub: [Ayesha Raheela]((https://github.com/ayesharaheela1410-zr/Devixo-Advanced-Employee-Management-System))
