#include "baza_noutov.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

LaptopDatabase::LaptopDatabase(const string& file)
    : head(nullptr), filename(file) {
    load_from_file();
}

LaptopDatabase::~LaptopDatabase() {
    save_to_file();
    clear();
}

void LaptopDatabase::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int LaptopDatabase::get_next_id() const {
    int max_id = 0;
    Node* current = head;

    while (current) {
        if (current->data.id > max_id)
            max_id = current->data.id;
        current = current->next;
    }

    return max_id + 1;
}

void LaptopDatabase::add_laptop(const Laptop& laptop) {
    Laptop copy = laptop;
    copy.id = get_next_id();

    Node* new_node = new Node(copy);

    if (!head) {
        head = new_node;
        return;
    }

    Node* current = head;
    while (current->next)
        current = current->next;

    current->next = new_node;
}

void LaptopDatabase::remove_laptop(int id) {
    if (!head) return;

    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next && current->next->data.id != id)
        current = current->next;

    if (current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }
}

optional<reference_wrapper<const Laptop>>
LaptopDatabase::find_by_id(int id) const {

    Node* current = head;

    while (current) {
        if (current->data.id == id)
            return current->data;
        current = current->next;
    }

    return nullopt;
}

void LaptopDatabase::find_by_brand(const string& brand) const {
    Node* current = head;
    bool found = false;

    while (current) {
        if (current->data.brand == brand) {
            const Laptop& l = current->data;
            cout << l.id << " | "
                 << l.brand << " | "
                 << l.model << " | "
                 << l.ram << "GB | "
                 << l.price << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
        cout << "Не найдено\n";
}

void LaptopDatabase::find_by_price(int max_price) const {
    Node* current = head;
    bool found = false;

    while (current) {
        if (current->data.price <= max_price) {
            const Laptop& l = current->data;
            cout << l.id << " | "
                 << l.brand << " | "
                 << l.model << " | "
                 << l.ram << "GB | "
                 << l.price << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found)
        cout << "Не найдено\n";
}

void LaptopDatabase::update_laptop(int id, const Laptop& new_data) {
    Node* current = head;

    while (current) {
        if (current->data.id == id) {
            current->data.brand = new_data.brand;
            current->data.model = new_data.model;
            current->data.ram = new_data.ram;
            current->data.price = new_data.price;
            return;
        }
        current = current->next;
    }
}

void LaptopDatabase::show_all() const {
    if (!head) {
        cout << "База пуста\n";
        return;
    }

    Node* current = head;

    while (current) {
        const Laptop& l = current->data;
        cout << l.id << " | "
             << l.brand << " | "
             << l.model << " | "
             << l.ram << "GB | "
             << l.price << endl;
        current = current->next;
    }
}

void LaptopDatabase::save_to_file() const {
    ofstream file(filename);

    Node* current = head;

    while (current) {
        const Laptop& l = current->data;
        file << l.id << "|"
             << l.brand << "|"
             << l.model << "|"
             << l.ram << "|"
             << l.price << "\n";
        current = current->next;
    }
}

void LaptopDatabase::load_from_file() {
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;

    while (getline(file, line)) {
        Laptop l;
        string token;
        istringstream ss(line);

        getline(ss, token, '|'); l.id = stoi(token);
        getline(ss, l.brand, '|');
        getline(ss, l.model, '|');
        getline(ss, token, '|'); l.ram = stoi(token);
        getline(ss, token, '|'); l.price = stoi(token);

        Node* new_node = new Node(l);

        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next)
                current = current->next;
            current->next = new_node;
        }
    }
}

Laptop input_laptop() {
    Laptop l;

    cout << "Бренд: ";
    getline(cin, l.brand);

    cout << "Модель: ";
    getline(cin, l.model);

    cout << "ОЗУ: ";
    while (!(cin >> l.ram)) {
        cout << "Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Цена: ";
    while (!(cin >> l.price)) {
        cout << "Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return l;
}
