#include "baza_noutov.h"
#include <iostream>
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
        cin >> choice;
        cin.ignore();
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
            cin >> price;
            cin.ignore();
            db.find_by_price(price);
            break;
        }
        case 5: {
            int id;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            db.update_laptop(id, input_laptop());
            break;
        }
        case 6: {
            int id;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            db.remove_laptop(id);
            break;
        }
        case 7:
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный ввод\n";
        }
    } while (choice != 7);
    return 0;
}
