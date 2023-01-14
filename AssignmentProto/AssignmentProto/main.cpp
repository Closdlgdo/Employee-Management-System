#include <iostream>
#include <string>
#include <map>

using namespace std;

// Base class for employee
class Employee {
private:
    string name;
    int id;
public:
    Employee(string name, int id) : name(name), id(id) {}

    string getName() { return name; }
    int getId() { return id; }
};

// Derived class for Human Resources employee
class HR : public Employee {
private:
    map<int, Employee*> employees; // map to store employee records
public:
    HR(string name, int id) : Employee(name, id) {}

    // Add an employee to the map
    void addEmployee(Employee* e) {
        employees[e->getId()] = e;
    }

    // Search for an employee by ID
    Employee* searchEmployee(int id) {
        if (employees.count(id) > 0)
            return employees[id];
        else
            return nullptr;
    }

    // Modify an employee's record
    void modifyEmployee(int id, Employee* e) {
        if (employees.count(id) > 0)
            employees[id] = e;
        else
            cout << "Employee not found!" << endl;
    }

    // Delete an employee's record
    void deleteEmployee(int id) {
        if (employees.count(id) > 0)
            employees.erase(id);
        else
            cout << "Employee not found!" << endl;
    }

    // View all employee records
    void viewAll() {
        for (auto it = employees.begin(); it != employees.end(); it++) {
            cout << "ID: " << it->first << " Name: " << it->second->getName() << endl;
        }
    }
};

// Derived class for Management employee
class Management : public Employee {
private:
    HR* hr; // pointer to HR object to access employee records
public:
    Management(string name, int id, HR* hr) : Employee(name, id), hr(hr) {}

    // Search for an employee by ID
    void searchEmployee(int id) {
        Employee* e = hr->searchEmployee(id);
        if (e != nullptr)
            cout << "ID: " << e->getId() << " Name: " << e->getName() << endl;
        else
            cout << "Employee not found!" << endl;
    }

    // View all employee records
    void viewAll() { hr->viewAll(); }
};

// Derived class for General Employee
class General : public Employee {
public:
    General(string name, int id) : Employee(name, id) {}

    // View own employee record
    void view() {
        cout << "ID: " << getId() << " Name: " << getName() << endl;
    }
};

// Function to prompt user for login credentials and return employee object
Employee* login() {
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
        cout << "Enter password: ";
    cin >> password;

    // Check login credentials
    if (username == "hr" && password == "hr123") {
        return new HR("HR", 123);
    } else if (username == "mgmt" && password == "mgmt123") {
        HR* hr = new HR("HR", 123);
        return new Management("Management", 234, hr);
    } else if (username == "employee" && password == "emp123") {
        return new General("Employee", 345);
    } else {
        cout << "Invalid login credentials!" << endl;
        return nullptr;
    }
}

int main() {
    Employee* user = login();

    if (user == nullptr)
        return 0;

    // Show menu options based on user type
    if (static_cast<HR*>(user) != nullptr) {
        cout << "Welcome HR!" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Search employee" << endl;
        cout << "3. Modify employee" << endl;
        cout << "4. Delete employee" << endl;
        cout << "5. View all employees" << endl;
        cout << "6. Logout" << endl;

        int choice;
        cin >> choice;

        HR* hr = static_cast<HR*>(user);

        while (choice != 6) {
            if (choice == 1) {
                string name;
                int id;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter ID: ";
                cin >> id;
                hr->addEmployee(new Employee(name, id));
            } else if (choice == 2) {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                hr->searchEmployee(id);
            } else if (choice == 3) {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                string name;
                cout << "Enter name: ";
                cin >> name;
                hr->modifyEmployee(id, new Employee(name, id));
            } else if (choice == 4) {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                hr->deleteEmployee(id);
            } else if (choice == 5) {
                hr->viewAll();
            }
            cout << "Enter choice: ";
            cin >> choice;
        }
    } else if (static_cast<Management*>(user) != nullptr) {
        cout << "Welcome Management!" << endl;
        cout << "1. Search employee" << endl;
        cout << "2. View all employees" << endl;
        cout << "3. Logout" << endl;

        int choice;
        cin >> choice;

        Management* mgmt = static_cast<Management*>(user);

        while (choice != 3) {
            if (choice == 1) {
                int id;
                cout << "Enter ID: ";
                cin >> id;
                mgmt->searchEmployee(id);
            } else if (choice == 2) {
                mgmt->viewAll();
            }
            cout << "Enter choice: ";
            cin >> choice;
        }
    } else if (static_cast<General*>(user) != nullptr) {
        cout << "Welcome Employee!" << endl;
        cout << "1. View employee record" << endl;
        cout << "2. Logout" << endl;

        int choice;
        cin >> choice;

        General* emp = static_cast<General*>(user);

        while (choice != 2) {
            if (choice == 1) {
                emp->view();
            }
            cout << "Enter choice: ";
            cin >> choice;
        }
    }

    return 0;
}
                
