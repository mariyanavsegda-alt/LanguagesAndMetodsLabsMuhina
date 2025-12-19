//подключаем необходимые файлы
//__________________
#include <stdio.h>
#include <stdlib.h>
#include "baza_noutov.h"
#define DEFAULT_FILE "laptops.txt"
//отдельная функция для меню действий
//____________________________________________
void show_menu() {
    printf("\n___ Магазин ноутбуков ____\n");
    printf("1. Показать все\n");
    printf("2. Добавить\n");
    printf("3. Найти по бренду\n");
    printf("4. Найти по цене\n");
    printf("5. Редактировать\n");
    printf("6. Удалить\n");
    printf("7. Сохранить\n");
    printf("8. Выход\n");
    printf("Выбирай: ");
}
//_____________________________________________
//основная программа
//_____________________________________________
int main() {
    //делаем список
    Laptop* db = NULL; // указываем на начало списка
    int choice;        // переменная, где мы бкдем запоминать выбор
    char* filename = DEFAULT_FILE;
    if (argc > 1) {
        filename = argv[1];}
    init_db(&db);         // инициализируем базу данных
    load_from_file(&db,filename); // загружаем данные из файла 
 // главный цикл, показываем меню, и считываем выбор
    do {
        show_menu();
        scanf("%d", &choice);
        getchar(); 
//  в зависимомти от значения choise делаем что то          
        switch(choice) {
            case 1: // Показываем все
                show_all(db);
                break;
                
            case 2: // Добавляем
                {
                    Laptop new_laptop = input_laptop(db);//запрашиваем данные отдельной функцией
                    add_laptop(&db, new_laptop);//добавляем в список
                    printf("Добавлено, милорд!\n");
                }
                break;
                
            case 3: // ищем по бренду
                {
                    char brand[MAX_LEN];
                    printf("Бренд: ");       // ну тут просто запрашиваем, и вызываем функцию, которая будет искать
                    scanf(" %[^\n]", brand);
                    find_by_brand(db, brand);
                }
                break;
                
            case 4: // ищем по цене
                {
                    int price;
                    printf("Макс. цена: ");
                    scanf("%d", &price);          // аналогично как и с брендом
                    find_by_price(db, price);
                }
                break;
                
            case 5: // редактируем
                {
                    int id;
                    printf("ID для редактирования: "); // запрашиваем номер ноута, который будем редактировать
                    scanf("%d", &id);
                    
                    Laptop* laptop = find_by_id(db, id); // отдельой функцией ищем по айди(возвращяет указатель на ноутбук)
                    if (laptop) {
                        printf("Текущие данные:\n");
                        show_laptop(laptop);                 // нашли - показываем то, что есть сейчас
                        Laptop new_data = input_laptop(db);  // и собственно меняем
                        new_data.id = id; // id сохраняем
                        update_laptop(laptop, new_data);// копируем новые данные в найденный элемент списка
                        printf("Обновлено, милорд!\n");
                    } else {
                        printf("нет такого\n");
                    }
                }
                break;
                
            case 6: // Удалить
                {
                    int id;
                    printf("ID для удаления: ");
                    scanf("%d", &id);            // по айди ищем и удаляем
                    remove_laptop(&db, id);
                    printf("Удалено!\n");
                }
                break;
                
            case 7: // Сохранить
                save_to_file(db,filename);
                break;
                                            // ну тут все и так ясно
            case 8: // Выход
                save_to_file(db,filename);
                printf("Данные сохранены, милорд. Выход.\n");
                break;
                
            default:
                printf("Неверный выбор\n");
        }
        
    } while(choice != 8);
    
    free_db(&db);//освобождаем всю выделенную память
    return 0;
}

//__________________________________________________________
