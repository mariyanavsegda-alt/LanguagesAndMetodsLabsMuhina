// подключаем всё что надо
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "baza_noutov.h"

using namespace std;

// расписываем функции для работы с базой
//_______________________________________

// Инициализируем базу данных
void init_db(Laptop** head) {
    *head = nullptr; // создаем пустой список
}

// чистим память
void free_db(Laptop** head) {
    Laptop* current = *head; // начинаем с первого элемента и идем до конца
    while (current != nullptr) {
        Laptop* next = current->next; // делаем указатель на следующий элемент
        delete current; // чистим текущий
        current = next;  // переходим на следующий
    }
    *head = nullptr;
}

// добавляем ноутбук
void add_laptop(Laptop** head, Laptop new_laptop) {
    Laptop* new_node = new Laptop; // выделяем память для нового узла списка
    *new_node = new_laptop;        // копируем структуру
    new_node->next = nullptr;      // делаем указатель в пустоту

    if (*head == nullptr) {
        *head = new_node; // если список был пустой, то новый узел становится первым
    } else {
        Laptop* current = *head;
        while (current->next != nullptr) { // если не пустой, то идем до последнего
            current = current->next;
        }
        current->next = new_node;
    }
}

// удаляем ноутбук
void remove_laptop(Laptop** head, int id) {
    if (*head == nullptr) return;

    // если удаляем первый элемент
    if ((*head)->id == id) {
        Laptop* temp = *head;        // сохраняем текущий первый
        *head = (*head)->next;       // делаем второй первым
        delete temp;                 // текущий удаляем
        return;
    }

    // и если не первый
    Laptop* current = *head;
    while (current->next != nullptr && current->next->id != id) { // ищем элемент перед тем, который удаляем
        current = current->next;
    }

    if (current->next != nullptr) {
        Laptop* temp = current->next;            // нужный нам элемент запоминаем
        current->next = current->next->next;     // меняем указатель
        delete temp;                             // удаляем
    }
}

// ищем по ID
Laptop* find_by_id(Laptop* head, int id) {
    Laptop* current = head;
    while (current != nullptr) { // проходимся циклом по списку
        if (current->id == id) {
            return current; // нашли — возвращаем указатель
        }
        current = current->next;
    }
    return nullptr;
}

// ищем по бренду
Laptop* find_by_brand(Laptop* head, const string& brand) {
    Laptop* current = head;    // указатель на первый элемент
    Laptop* result = nullptr;  // указатель на первый найденный элемент

    cout << "\nНоутбуки " << brand << ":" << endl;
    int found = 0; // флаг, нужен если ничего не найдём

    while (current != nullptr) {
        if (current->brand == brand) { // сравниваем строку с брендом
            show_laptop(current);
            if (!result) result = current; // запоминаем первый найденный ноут
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Не найдено" << endl;
    }

    return result;
}

// ищем по цене
Laptop* find_by_price(Laptop* head, int max_price) {
    Laptop* current = head;
    Laptop* result = nullptr;

    cout << "\nНоутбуки до " << max_price << " руб.:" << endl;
    int found = 0;

    while (current != nullptr) {
        if (current->price <= max_price) { // ищем ноут, цена которого не превышает заданную
            show_laptop(current);
            if (!result) result = current;
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Не найдено" << endl;
    }

    return result;
}

// обновляем данные
void update_laptop(Laptop* laptop, Laptop new_data) {
    *laptop = new_data;
}

// показываем один конкретный ноутбук
void show_laptop(Laptop* laptop) {
    cout << "\nID: " << laptop->id << endl;
    cout << "Бренд: " << laptop->brand << endl;   // получаем доступ к полям структуры через указатель
    cout << "Модель: " << laptop->model << endl;
    cout << "ОЗУ: " << laptop->ram << " ГБ" << endl;
    cout << "Цена: " << laptop->price << " руб." << endl;
    cout << "--------------------" << endl;
}

// Показываем все ноутбуки
void show_all(Laptop* head) {
    if (head == nullptr) {
        cout << "\nБаза данных пуста" << endl;
        return;
    }

    cout << "\n=== Все ноутбуки ===" << endl;
    Laptop* current = head;
    while (current != nullptr) { // с помощью предыдущей функции выводим данные всех имеющихся ноутов
        show_laptop(current);
        current = current->next;
    }
}

// сохраняем в файл
void save_to_file(Laptop* head) {
    ofstream file(FILE_NAME); // открываем файл на запись
    if (!file.is_open()) {
        cout << "Ошибка" << endl;
        return;
    }

    Laptop* current = head;
    while (current != nullptr) {
        file << current->id << "|"      // в нужном нам формате записываем
             << current->brand << "|"    // все поля структуры в файл
             << current->model << "|"
             << current->ram << "|"
             << current->price << endl;
        current = current->next; // записали — идем дальше
    }

    file.close(); // обязательно закрываем
    cout << "Данные сохранены, милорд" << endl;
}

// загружаем из файла
void load_from_file(Laptop** head) {
    ifstream file(FILE_NAME); // открываем, но уже на чтение
    if (!file.is_open()) {
        cout << "Файл не найден, делаем новый" << endl;
        return;
    }

    string line; // строка-буфер
    while (getline(file, line)) {
        Laptop laptop;
        istringstream ss(line);
        string token;

        // разбиваем строку на части по разделителю '|'
        if (getline(ss, token, '|')) laptop.id = stoi(token);
        if (getline(ss, token, '|')) laptop.brand = token;
        if (getline(ss, token, '|')) laptop.model = token;    // и записываем в конкретные поля элемента
        if (getline(ss, token, '|')) laptop.ram = stoi(token);
        if (getline(ss, token, '|')) laptop.price = stoi(token);

        laptop.next = nullptr;
        add_laptop(head, laptop);
    }

    file.close();
}

// делаем следующий ID
int get_next_id(Laptop* head) {
    int max_id = 0;
    Laptop* current = head;
    // тут просто обходим список, ищем максимальный айди
    while (current != nullptr) { // и возвращаем этот айди +1
        if (current->id > max_id) {
            max_id = current->id;
        }
        current = current->next;
    }
    return max_id + 1;
}

// вводим данные
Laptop input_laptop(Laptop* head) {
    Laptop laptop;                       // создаём новую переменную
    laptop.id = get_next_id(head);       // для нового ноута делаем айди

    cout << "\nДобавление ноутбука:" << endl;

    cout << "Бренд: ";
    getline(cin, laptop.brand);

    cout << "Модель: ";
    getline(cin, laptop.model);

    cout << "ОЗУ (ГБ): ";
    cin >> laptop.ram;

    cout << "Цена (в конях): ";
    cin >> laptop.price;
    cin.ignore(); // очищаем буфер после cin >>

    laptop.next = nullptr;
    return laptop;
}