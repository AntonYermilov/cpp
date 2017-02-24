#include <cstring>
#include <employees.h>

void load(EmployeesArray& array) {
    char filename[256];
    std::cin >> filename;
    std::ifstream in(filename);

    int size;
    in.read((char*) &size, 4);
    for (int i = 0; i < size; i++) {
        Employee* employee;
        in >> employee;
        array.add(employee);
    }
    
    in.close();
}

void list(const EmployeesArray& array) {
    std::cout << array;
}

void add(EmployeesArray& array) {
    Employee* employee = NULL;
    std::cin >> employee;
    array.add(employee);
}

void save(const EmployeesArray& array) {
    char filename[256];
    std::cin >> filename;
    std::ofstream out(filename);
    out << array;
    out.close();
}

int main() {
    char cmd[256];
    EmployeesArray array;

    while (true) {
        std::cin >> cmd;
        if (strcmp(cmd, "load") == 0)
            load(array);
        if (strcmp(cmd, "list") == 0)
            list(array);
        if (strcmp(cmd, "add") == 0)
            add(array);
        if (strcmp(cmd, "save") == 0)
            save(array);
        if (strcmp(cmd, "exit") == 0)
            break;
    }
    return 0;
}
