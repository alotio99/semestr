#include "class.h"

int main() {
    Student* s1 = new Student("Дудошников Илья", 18, 11);
    Student* s2 = new Student("Буров Егор", 17, 10);
    Teacher* t1 = new Teacher("Петров Алексей", 40, "Математика");
    Teacher* t2 = new Teacher("Мальков Иван", 45, "Русский язык");

    std::cout << "Общее количество созданных объектов Person: " << Person::GetTotalObjects() << std::endl;

    std::vector<ISchoolMember*> members = {s1, s2, t1, t2}; //компилятор не знает на какой объект указывает m
    for (ISchoolMember* m : members) {
        m->ShowInfo(); //позднее связывание
        std::cout << " -> ";
        m->PerformAction(); //позднее связывание
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << *s1 << std::endl; //раннее связывание
    std::cout << *t1 << std::endl; //раннее связывание
    std::cout << "Имя студента: " << s1->GetName() << std::endl; //раннее связывание
    std::cout << std::endl;

    Student s3("Дудошников Илья", 18, 11);
    Student s4("Буров Егор", 17, 10);
    std::cout << "s1 == s3 : " << (*s1 == s3) << std::endl; //раннее связывание
    std::cout << "s2 == s4 : " << (*s2 == s4) << std::endl;
    std::cout << "s1 == s2 : " << (*s1 == *s2) << std::endl << std::endl;

    SchoolGroup<Student> stud_group;
    stud_group.add(s1);
    stud_group.add(s2);
    std::cout << "Студенты в группе (" << stud_group.GetSize() << "):" << std::endl;
    stud_group.ShowAll();

    stud_group.ForEach([](Student* s) {
        s->PerformAction();
        std::cout << std::endl;
    });

    delete s1;
    delete s2;
    delete t1;
    delete t2;

    std::cout << "Оставшееся количество объектов Person: " << Person::GetTotalObjects() << std::endl;
    return 0;
}