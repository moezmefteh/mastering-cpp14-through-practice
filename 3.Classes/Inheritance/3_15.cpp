#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base\n";
    }
};

class Derived1 : public Base {
public:
    void display() override {
        std::cout << "Derived1\n";
    }
};

class Derived2 : public Base {
public:
    void display() override {
        std::cout << "Derived2\n";
    }
};

int main() {
    // Stack allocation
    Base baseObj;
    Derived1 derived1Obj;
    Derived2 derived2Obj;

    // Calling display on stack-allocated objects
    baseObj.display();       // Output: Base
    derived1Obj.display();   // Output: Derived1
    derived2Obj.display();   // Output: Derived2

    // Creating pointers to stack-allocated objects
    Base* basePtr = &baseObj;
    Base* derived1Ptr = &derived1Obj;
    Base* derived2Ptr = &derived2Obj;

    // Calling display through pointers
    basePtr->display();      // Output: Base
    derived1Ptr->display();  // Output: Derived1
    derived2Ptr->display();  // Output: Derived2

    // Heap allocation
    Base* ptr1 = new Base();
    Base* ptr2 = new Derived1();
    Base* ptr3 = new Derived2();

    // Calling display on heap-allocated objects
    ptr1->display(); // Output: Base
    ptr2->display(); // Output: Derived1
    ptr3->display(); // Output: Derived2

    // Clean up heap memory
    delete ptr3;
    delete ptr2;
    delete ptr1;

    return 0;
}