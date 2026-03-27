// подключаем необходимые файлы
//__________________
#include <iostream>
#include <string>
#include "baza_noutov.h"
#include <windows.h>

using namespace std;

// отдельная функция для меню действий
//____________________________________________
void show_menu() {
    cout << "\n___ Магазин ноутбуков ____" << endl;
    cout << "1. Показать все" << endl;
    cout << "2. Добавить" << endl;
    cout << "3. Найти по бренду" << endl;
    cout << "4. Найти по цене" << endl;
    cout << "5. Редактировать" << endl;
    cout << "6. Удалить" << endl;
    cout << "7. Сохранить" << endl;
    cout << "8. Выход" << endl;
    cout << "Выбирай: ";
}

//_____________________________________________
// основная программа
//_____________________________________________
int main() {
    SetConsoleCP(65001);        
    SetConsoleOutputCP(65001);
    // делаем список
    Laptop* db = nullptr; // указываем на начало списка
    int choice;           // переменная, где мы будем запоминать выбор

    init_db(&db);          // инициализируем базу данных
    load_from_file(&db);   // загружаем данные из файла

    // главный цикл, показываем меню, и считываем выбор
    do {
        show_menu();
        cin >> choice;
        cin.ignore(); // очищаем буфер

        // в зависимости от значения choice делаем что-то
        switch (choice) {
            case 1: // Показываем все
                show_all(db);
                break;

            case 2: // Добавляем
            {
                Laptop new_laptop = input_laptop(db); // запрашиваем данные отдельной функцией
                add_laptop(&db, new_laptop);           // добавляем в список
                cout << "Добавлено, милорд!" << endl;
            }
            break;

            case 3: // ищем по бренду
            {
                string brand;
                cout << "Бренд: "; // ну тут просто запрашиваем, и вызываем функцию
                getline(cin, brand);
                find_by_brand(db, brand);
            }
            break;

            case 4: // ищем по цене
            {
                int price;
                cout << "Макс. цена: ";
                cin >> price; // аналогично как и с брендом
                find_by_price(db, price);
            }
            break;

            case 5: // редактируем
            {
                int id;
                cout << "ID для редактирования: "; // запрашиваем номер ноута
                cin >> id;
                cin.ignore();

                Laptop* laptop = find_by_id(db, id); // отдельной функцией ищем по айди
                if (laptop) {
                    cout << "Текущие данные:" << endl;
                    show_laptop(laptop);              // нашли — показываем то, что есть сейчас
                    Laptop new_data = input_laptop(db); // и собственно меняем
                    new_data.id = id;                    // id сохраняем
                    update_laptop(laptop, new_data);     // копируем новые данные
                    cout << "Обновлено, милорд!" << endl;
                } else {
                    cout << "нет такого" << endl;
                }
            }
            break;

            case 6: // Удалить
            {
                int id;
                cout << "ID для удаления: ";
                cin >> id; // по айди ищем и удаляем
                remove_laptop(&db, id);
                cout << "Удалено!" << endl;
            }
            break;

            case 7: // Сохранить
                save_to_file(db);
                break;

            // ну тут все и так ясно
            case 8: // Выход
                save_to_file(db);
                cout << "Данные сохранены, милорд. Выход." << endl;
                break;

            default:
                cout << "Неверный выбор" << endl;
        }

    } while (choice != 8);

    free_db(&db); // освобождаем всю выделенную память
    return 0;
}