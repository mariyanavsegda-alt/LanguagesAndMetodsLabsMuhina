#include "baza_noutov.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

LaptopDatabase::LaptopDatabase(const string& file) : filename(file) {
    load_from_file();
}

LaptopDatabase::~LaptopDatabase() {
    save_to_file();
}

int LaptopDatabase::get_next_id() const {
    int max_id = 0;
    for (const auto& l : laptops)
        if (l.id > max_id)
            max_id = l.id;
    return max_id + 1;
}

void LaptopDatabase::add_laptop(const Laptop& laptop) {
    Laptop copy = laptop;
    copy.id = get_next_id();
    laptops.push_back(copy);
}

void LaptopDatabase::remove_laptop(int id) {
    laptops.remove_if([id](const Laptop& l) { return l.id == id; });
}

optional<reference_wrapper<const Laptop>>
LaptopDatabase::find_by_id(int id) const {
    for (const auto& l : laptops)
        if (l.id == id)
            return l;
    return nullopt;
}

void LaptopDatabase::find_by_brand(const string& brand) const {
    bool found = false;
    for (const auto& l : laptops)
        if (l.brand == brand) {
            cout << l.id << " | " << l.brand << " | "
                 << l.model << " | "
                 << l.ram << "GB | "
                 << l.price << endl;
            found = true;
        }
    if (!found)
        cout << "Не найдено\n";
}

void LaptopDatabase::find_by_price(int max_price) const {
    bool found = false;
    for (const auto& l : laptops)
        if (l.price <= max_price) {
            cout << l.id << " | " << l.brand << " | "
                 << l.model << " | "
                 << l.ram << "GB | "
                 << l.price << endl;
            found = true;
        }
    if (!found)
        cout << "Не найдено\n";
}

void LaptopDatabase::update_laptop(int id, const Laptop& new_data) {
    for (auto& l : laptops)
        if (l.id == id) {
            l.brand = new_data.brand;
            l.model = new_data.model;
            l.ram = new_data.ram;
            l.price = new_data.price;
            return;
        }
}

void LaptopDatabase::show_all() const {
    if (laptops.empty()) {
        cout << "База пуста\n";
        return;
    }
    for (const auto& l : laptops)
        cout << l.id << " | " << l.brand << " | "
             << l.model << " | "
             << l.ram << "GB | "
             << l.price << endl;
}

void LaptopDatabase::save_to_file() const {
    ofstream file(filename);
    for (const auto& l : laptops)
        file << l.id << "|"
             << l.brand << "|"
             << l.model << "|"
             << l.ram << "|"
             << l.price << "\n";
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

        laptops.push_back(l);
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
