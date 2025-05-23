#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <compare>  // std::strong_ordering
#include <ostream>  // std::ostream
#include <string>   // std::string

struct Employee {
    std::string id;
    std::string name;
    int birth_year;
    double salary;

    std::strong_ordering operator<=>(const Employee& rhs) const noexcept
    {
        std::strong_ordering result = name <=> rhs.name;
        if (result != 0) {
            return result;
        }
        result = birth_year <=> rhs.birth_year;
        if (result != 0) {
            return result;
        }
        return id <=> rhs.id;
    }

    bool operator==(const Employee& rhs) const noexcept
    {
        return name == rhs.name && birth_year == rhs.birth_year &&
               id == rhs.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& emp)
    {
        os << "Employee{" << emp.id << ", " << emp.name << ", " << emp.id
           << ", " << emp.salary << "}";
        return os;
    }
};

#endif // EMPLOYEE_H
