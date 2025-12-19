//_______________________________________
//обьявляем все наши функции в этом файле
#ifndef BAZA_NOUTOV_H
#define BAZA_NOUTOV_H

#define MAX_LEN 50


// Структура ноутбука ( одного элемента )
typedef struct Laptop {
    int id;
    char brand[MAX_LEN];
    char model[MAX_LEN];  // содержит данные о ноуте и указатель на следующий элемент
    int ram;
    int price;
    struct Laptop* next;
} Laptop;

// Основные функции
void init_db(Laptop** head);
void free_db(Laptop** head);
void add_laptop(Laptop** head, Laptop new_laptop);
void remove_laptop(Laptop** head, int id);
Laptop* find_by_id(Laptop* head, int id);
Laptop* find_by_brand(Laptop* head, char* brand);
Laptop* find_by_price(Laptop* head, int max_price);
void update_laptop(Laptop* laptop, Laptop new_data);
void show_laptop(Laptop* laptop);
void show_all(Laptop* head);

// Работа с файлом
void save_to_file(Laptop* head,const char* filename);
void load_from_file(Laptop** head,const char* filename);
int get_next_id(Laptop* head);
Laptop input_laptop(Laptop* head);


#endif
