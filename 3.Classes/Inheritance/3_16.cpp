#include <iostream>
#include <string>

class Person {
public:
    Person(const std::string& name, const std::string& university_id)
        : name(name), university_id(university_id) {}

    virtual void display() const {
        std::cout << "Name: " << name << ", University ID: " << university_id << std::endl;
    }

protected:
    std::string name;
    std::string university_id;
};

class Faculty : public Person {
public:
    Faculty(const std::string& name, const std::string& university_id, const std::string& rank)
        : Person(name, university_id), rank(rank) {}

    void display() const override {
        Person::display();
        std::cout << "Rank: " << rank << std::endl;
    }

private:
    std::string rank;
};

class Student : public Person {
public:
    Student(const std::string& name, const std::string& university_id)
        : Person(name, university_id) {}

    void display() const override {
        Person::display();
    }
};

class UndergraduateStudent : public Student {
public:
    UndergraduateStudent(const std::string& name, const std::string& university_id, int year_of_study)
        : Student(name, university_id), year_of_study(year_of_study) {}

    void display() const override {
        Student::display();
        std::cout << "Year of Study: " << year_of_study << std::endl;
    }

private:
    int year_of_study;
};

class GraduateStudent : public Student {
public:
    GraduateStudent(const std::string& name, const std::string& university_id, const std::string& supervisor_id)
        : Student(name, university_id), supervisor_id(supervisor_id) {}

    void display() const override {
        Student::display();
        std::cout << "Supervisor ID: " << supervisor_id << std::endl;
    }

private:
    std::string supervisor_id;
};

int main() {
    Faculty faculty("Dr. Smith", "F123", "Associate Professor");
    UndergraduateStudent undergrad("Alice Johnson", "U456", 2);
    GraduateStudent grad("Bob Brown", "G789", "F123");

    std::cout << "Faculty Information:" << std::endl;
    faculty.display();
    std::cout << std::endl;

    std::cout << "Undergraduate Student Information:" << std::endl;
    undergrad.display();
    std::cout << std::endl;

    std::cout << "Graduate Student Information:" << std::endl;
    grad.display();
    std::cout << std::endl;

    return 0;
}