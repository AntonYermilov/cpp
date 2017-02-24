#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>

class Employee {
public:
    Employee();
    virtual ~Employee();

    virtual int salary() const = 0;

    friend std::istream& operator>>(std::istream& input, Employee*& employee);
    friend std::ostream& operator<<(std::ostream& output, const Employee& employee);
    friend std::ifstream& operator>>(std::ifstream& input, Employee*& employee);
    friend std::ofstream& operator<<(std::ofstream& output, const Employee& employee);

private:
    Employee(const Employee &other);
    Employee& operator=(const Employee &other);

protected:
    virtual void read_txt(std::istream& input) = 0;
    virtual void print_txt(std::ostream& output) const = 0;
    virtual void read_bin(std::ifstream& input) = 0;
    virtual void print_bin(std::ofstream& output) const = 0;

    char* _name;
    int _base_salary;
};

class Developer : public Employee {
public:
    int salary() const;
private:
    void read_txt(std::istream& input);
    void print_txt(std::ostream& output) const;
    void read_bin(std::ifstream& input);
    void print_bin(std::ofstream& output) const;
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    int salary() const;
private:
    void read_txt(std::istream& input);
    void print_txt(std::ostream& output) const;
    void read_bin(std::ifstream& input);
    void print_bin(std::ofstream& output) const;
    int _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();

    void add(Employee *employee);
    int total_salary() const;

    friend std::ifstream& operator>>(std::ifstream& input, EmployeesArray& array);
    friend std::ostream& operator<<(std::ostream& output, const EmployeesArray& array);
    friend std::ofstream& operator<<(std::ofstream& output, const EmployeesArray& array);
private:
    EmployeesArray(const EmployeesArray& array);
    EmployeesArray& operator=(const EmployeesArray& array);

    int _size, _capacity;
    Employee **_employees;
    int _total_salary;
};

#endif
