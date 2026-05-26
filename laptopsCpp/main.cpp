#include "baza_noutov.h"
#include <iostream>
#include <limits>

using namespace std;

void show_menu() {
    cout << "\n1. Показать все\n"
         << "2. Добавить\n"
         << "3. Найти по бренду\n"
         << "4. Найти по цене\n"
         << "5. Редактировать\n"
         << "6. Удалить\n"
         << "7. Выход\n"
         << "Выбор: ";
}

int main(int argc, char* argv[]) {

    string filename = (argc > 1) ? argv[1] : "laptops.txt";

    LaptopDatabase db(filename);

    int choice;

    do {
        show_menu();

        while (!(cin >> choice)) {
            cout << "Введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

        case 1:
            db.show_all();
            break;

        case 2:
            db.add_laptop(input_laptop());
            break;

        case 3: {
            string brand;
            cout << "Бренд: ";
            getline(cin, brand);
            db.find_by_brand(brand);
            break;
        }

        case 4: {
            int price;
            cout << "Макс. цена: ";
            while (!(cin >> price)) {
                cout << "Введите число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            db.find_by_price(price);
            break;
        }

        case 5: {
            int id;
            cout << "ID: ";
            while (!(cin >> id)) {
                cout << "Введите число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            db.update_laptop(id, input_laptop());
            break;
        }

        case 6: {
            int id;
            cout << "ID: ";
            while (!(cin >> id)) {
                cout << "Введите число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            db.remove_laptop(id);
            break;
        }

        case 7:
            cout << "Выход\n";
            break;

        default:
            cout << "Неверный ввод\n";
        }

    } while (choice != 7);

    return 0;
}
