#ifndef UNTITLED4_CLASS_H
#define UNTITLED4_CLASS_H

#include <iostream>
#include <vector>
#include <string>

class ISchoolMember { //интерфейсный класс
public:
    virtual void ShowInfo() const = 0; //виртуальные методы
    virtual void PerformAction() const = 0; //совершить действие
    virtual ~ISchoolMember() = default;
};


class Person : virtual public ISchoolMember { //виртуальные классы
protected: //инкапсуляция private/public
    std::string name;
    int age;
    //статическое поле для подсчёта
    static int TotalObjects;
public:
    Person(const std::string& n, int a): name (n), age(a) {
        TotalObjects++;
    }
    virtual ~Person() {
        TotalObjects--;
    }
    std::string GetName() const {
        return name;
    }
    int GetAge() const {
        return age;
    }
    virtual void ShowInfo() const { //полиморфизм, переопределение методов
        std::cout << "Person: " << name << ", age " << age;
    }
    virtual void PerformAction() const { //полиморфизм, переопределение методов
        std::cout << name << " выполняет действие человека.";
    }
    static int GetTotalObjects() { //статическая функция
        return TotalObjects;
    } // перегрузка оператора
    bool operator==(const Person& other) const {
        return (name == other.name && age == other.age);
    } // перегрузка оператора
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

int Person::TotalObjects = 0;

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person{name=" << p.name << ", age=" << p.age << "}";
    return os;
}


class Student : virtual public Person {
protected:
    int grade;
public:
    Student(const std::string& n, int a, int g) : Person(n, a), grade(g) {}
    void ShowInfo() const override {
        std::cout << "Student: " << GetName() << ", age " << GetAge() << ", grade " << grade;
    }
    void PerformAction() const override {
        std::cout << GetName() << " учится, делает домашнее задание и семестровые.";
    }
    int GetGrade() const {
        return grade;
    }
    bool operator==(const Student& other) const {
        return Person::operator==(other) && grade == other.grade;
    }
};


class Teacher: virtual public Person {
protected:
    std::string subject;
public:
    Teacher(const std::string& n, int a, const std::string& subj) : Person(n, a), subject(subj) {}
    void ShowInfo() const override {
        std::cout << "Teacher: " << GetName() << ", age " << GetAge() << ", subject " << subject;
    }
    void PerformAction() const override {
        std::cout << GetName() << " преподает предмет " << subject;
    }
    std::string GetSubject() const {
        return subject;
    }
    bool operator==(const Teacher& other) const {
        return Person::operator==(other) && subject == other.subject;
    }
};


template<typename T>
class SchoolGroup {
protected:
    std::vector<T*> members;
public:
    void add(T* member) {
        members.push_back(member);
    }
    void remove(T* member) {
        for (int i = 0; i < members.size(); ) {
            if (members[i] == member) {
                members.erase(members.begin() + i);
                break;
            }
        }
    }
    int GetSize() const {
        return members.size();
    }
    template<typename Func>
    void ForEach(Func func) const {
        for (T* m : members) {
            func(m);
        }
    }
    void ShowAll() const {
        for (T* m : members) {
            m->ShowInfo();
            std::cout << std::endl;
        }
    }
};

#endif