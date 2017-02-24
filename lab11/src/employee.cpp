#include <cassert>
#include <cstring>
#include <employees.h>

static char employee_name[256];

std::istream& operator>>(std::istream& input, Employee*& employee) {
    int type;
    input >> type;
    
    if (type == 1)
        employee = new Developer();
    if (type == 2)
        employee = new SalesManager();

    employee->read_txt(input);
    return input;
}

std::ostream& operator<<(std::ostream& output, const Employee& employee) {
    employee.print_txt(output);
    return output;
}

std::ifstream& operator>>(std::ifstream& input, Employee*& employee) {
    int type;
    input.read((char*) &type, 4);
    
    if (type == 1)
        employee = new Developer();
    if (type == 2)
        employee = new SalesManager();

    employee->read_bin(input);
    return input;
}

std::ofstream& operator<<(std::ofstream& output, const Employee& employee) {
    employee.print_bin(output);
    return output;
}

std::ifstream& operator>>(std::ifstream& input, EmployeesArray& array) {
    int size;
    input.read((char*) &size, 4);
    for (int i = 0; i < size; i++) {
        Employee* employee;
        input >> employee;
        array.add(employee);
    }
    return input;
}

std::ostream& operator<<(std::ostream& output, const EmployeesArray& array) {
    for (int i = 0; i < array._size; i++)
        output << i + 1 << ". " << *array._employees[i];
    output << "== Total salary: " << array.total_salary() << std::endl << std::endl;
    return output;
}

std::ofstream& operator<<(std::ofstream& output, const EmployeesArray& array) {
    output.write((char*)(&array._size), 4);
    for (int i = 0; i < array._size; i++)
        output << *array._employees[i];
    return output;
}

Employee::Employee() {
    _name = NULL;
}

Employee::~Employee() {
    if (_name)
        delete []_name;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus)
        salary += 1000;
    return salary;
}

void Developer::read_txt(std::istream& input) {
    assert(_name == NULL);

    input >> employee_name >> _base_salary >> _has_bonus;
    int len = strlen(employee_name);
    _name = new char[len + 1];
    strcpy(_name, employee_name);
}

void Developer::print_txt(std::ostream& output) const {
    output << "Developer" << std::endl;
    output << "Name: " << _name << std::endl;
    output << "Base Salary: " << _base_salary << std::endl;
    output << "Has bonus: " << (_has_bonus ? "+" : "-") << std::endl;
}

void Developer::read_bin(std::ifstream& input) {
    assert(_name == NULL);

    int len = 0;
    while (input >> employee_name[len]) {
        if (employee_name[len] == 0)
            break;
        len++;
    }
    _name = new char[len + 1];
    strcpy(_name, employee_name);

    input.read((char*) &_base_salary, 4);
    input.read((char*) &_has_bonus, 1);
}

void Developer::print_bin(std::ofstream& output) const {
    int type = 1;
    output.write((char*) &type, 4);
    output.write(_name, strlen(_name) + 1);
    output.write((char*) &_base_salary, 4);
    output.write((char*) &_has_bonus, 1);
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

void SalesManager::read_txt(std::istream& input) {
    assert(_name == NULL);

    input >> employee_name >> _base_salary >> _sold_nm >> _price;
    int len = strlen(employee_name);
    _name = new char[len + 1];
    strcpy(_name, employee_name);   
}

void SalesManager::print_txt(std::ostream& output) const {
    output << "Sales Manager" << std::endl;
    output << "Name: " << _name << std::endl;
    output << "Base Salary: " << _base_salary << std::endl;
    output << "Sold items: " << _sold_nm << std::endl;
    output << "Item price: " << _price << std::endl;
}

void SalesManager::read_bin(std::ifstream& input) {
    assert(_name == NULL);

    int len = 0;
    while (input >> employee_name[len]) {
        if (employee_name[len] == 0)
            break;
        len++;
    }
    _name = new char[len + 1];
    strcpy(_name, employee_name);

    input.read((char*) &_base_salary, 4);
    input.read((char*) &_sold_nm, 4);
    input.read((char*) &_price, 4);
}

void SalesManager::print_bin(std::ofstream& output) const {
    int type = 2;
    output.write((char*) &type, 4);
    output.write(_name, strlen(_name) + 1);
    output.write((char*) &_base_salary, 4);
    output.write((char*) &_sold_nm, 4);
    output.write((char*) &_price, 4);
}

EmployeesArray::EmployeesArray() {
    _capacity = 2;
    _size = 0;
    _total_salary = 0;
    _employees = new Employee*[_capacity];
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++)
        delete _employees[i];
    delete []_employees;
}

void EmployeesArray::add(Employee* employee) {
    if (_size == _capacity) {
        _capacity *= 2;
        Employee** new_array = new Employee*[_capacity];
        memcpy(new_array, _employees, _size * sizeof(Employee*));
        delete []_employees;
        _employees = new_array;
    }
    _employees[_size++] = employee;
    _total_salary += employee->salary();
}

int EmployeesArray::total_salary() const {
    return _total_salary;
}
