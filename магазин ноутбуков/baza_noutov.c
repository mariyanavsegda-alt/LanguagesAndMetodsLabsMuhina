// подключаем всё что надо
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza_noutov.h"
// расписываем функции для работы с базой
//_______________________________________


// Инициализируем базу данных
void init_db(Laptop** head) {
    *head = NULL;              // создаем пустой список
}

// чистим память
void free_db(Laptop** head) {
    Laptop* current = *head;          // начинаем с первого элемента и идем до конца
    while (current != NULL) {
        Laptop* next = current->next;// делаем указатель на слкедующий элемент 
        free(current); // чистим текущий
        current = next;//переходим на следующий
    }
    *head = NULL;
}

// добавляем ноутбук
void add_laptop(Laptop** head, Laptop new_laptop) {
    Laptop* new_node = (Laptop*)malloc(sizeof(Laptop));//выделяем память для нового как бы узла списка
    *new_node = new_laptop; //копируем структуру
    new_node->next = NULL; //делаем указатель в пустоту, потому что куда-то указывать надо
    
    if (*head == NULL) {
        *head = new_node;         //если список бвл пустой, то новый узел становиться первым
    } else {
        Laptop* current = *head;
        while (current->next != NULL) { //если не пустой то идем до последнегоои добавляем в конец
            current = current->next;
        }
        current->next = new_node;
    }
}

// удаляем ноутбук
void remove_laptop(Laptop** head, int id) {
    if (*head == NULL) return;
    // если удаляем первый элемент
    if ((*head)->id == id) {
        Laptop* temp = *head;  // сохраняем текущий первый
        *head = (*head)->next;// делаем второй первым
        free(temp);//текущий удаляем
        return;
    }
    // и если не первый
    Laptop* current = *head;
    while (current->next != NULL && current->next->id != id) {//ищем элемент перед тем который удаляем
        current = current->next; 
    }
    
    if (current->next != NULL) {
        Laptop* temp = current->next;          //нужный наи элемент запоминаем
        current->next = current->next->next;//меняем в предыдущем указатель на наш элемент на указатель на следующий элемент
        free(temp);//удаляем
    }
}

// ищем по ID
Laptop* find_by_id(Laptop* head, int id) {
    Laptop* current = head;
    while (current != NULL) {        // проходимся циклом по списку
        if (current->id == id) {
            return current;        // нашли - возвращаем указатель
        }
        current = current->next;
    }
    return NULL;
}

// ищем по бренду
Laptop* find_by_brand(Laptop* head, char* brand) {
    Laptop* current = head; // указатель на первый элемент
    Laptop* result = NULL; // указатель на первый найденный элемент
    
    printf("\nНоутбуки %s:\n", brand);
    int found = 0; // флаг, нужен если ничего не найдем
    
    while (current != NULL) {
        if (strcmp(current->brand, brand) == 0) { // сравниваем строку с брендом и текущую строку
            show_laptop(current);
            if (!result) result = current;    //запоминаем первый найденый ноут и выводим инфу о нем
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Не найдено\n");
    }
    
    return result;
}

// ищем по цене
Laptop* find_by_price(Laptop* head, int max_price) {
    Laptop* current = head;
    Laptop* result = NULL;
    
    printf("\nНоутбуки до %d коней:\n", max_price);
    int found = 0;
    
    while (current != NULL) {
        if (current->price <= max_price) {   //точно так же, как и с брендом, ищем ноут цена которого не превышает заданную
            show_laptop(current);
            if (!result) result = current;
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Не найдено\n");
    }
    
    return result;
}

// обновляем данные
void update_laptop(Laptop* laptop, Laptop new_data) {
    *laptop = new_data;
}

// показываем один конкретный ноутбук
void show_laptop(Laptop* laptop) {
    printf("\nID: %d\n", laptop->id);
    printf("Бренд: %s\n", laptop->brand);    // получаем доступ к полям структуры через указатель
    printf("Модель: %s\n", laptop->model);
    printf("ОЗУ: %d ГБ\n", laptop->ram);
    printf("Цена: %d коней\n", laptop->price);
    printf("--------------------\n");
}

// Ппоказываем все ноутбуки
void show_all(Laptop* head) {
    if (head == NULL) {
        printf("\nБаза данных пуста\n");
        return;
    }
    
    printf("\n=== Все ноутбуки ===\n");
    Laptop* current = head;
    while (current != NULL) {   //с помощью предыдущей функции выводим данные всех имеющихся ноутов
        show_laptop(current);
        current = current->next;
    }
}

// сохраняем в файл
void save_to_file(Laptop* head,const char* filename) {
    FILE* file = fopen(filename, "w"); // открываем файл на запись
    if (!file) {
        printf("Ошибка\n");
        return;
    }
    Laptop* current = head;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%d|%d\n",//в нужном нам формате записывает все поля структуры в файл
                current->id,
                current->brand,
                current->model,
                current->ram,
                current->price);
        current = current->next;// записали - идем дальше
    }
    
    fclose(file);//обязательно закрываем
    printf("Данные сохранены, милорд\n");
}

// загружаем из файла
void load_from_file(Laptop** head,const char* filename) {
    FILE* file = fopen(filename, "r");// открываем, но уже на чтение
    if (!file) {
        printf("Файл не найден, делаем новый\n");
        return;
    }
    
    char line[256];// делаем буфер для строки
    while (fgets(line, sizeof(line), file)) {
        Laptop laptop;
        line[strcspn(line, "\n")] = 0;
        
        char* token = strtok(line, "|");
        if (token) laptop.id = atoi(token);  
        
        token = strtok(NULL, "|");
        if (token) strcpy(laptop.brand, token);
                                                // разбиваем строки на части по разделителю
        token = strtok(NULL, "|");              // и записываем в конкретные поля элемента
        if (token) strcpy(laptop.model, token);
        
        token = strtok(NULL, "|");
        if (token) laptop.ram = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) laptop.price = atoi(token);
        
        laptop.next = NULL;
        add_laptop(head, laptop);
    }
    
    fclose(file);
}

// делаем следующий ID
int get_next_id(Laptop* head) {
    int max_id = 0;
    Laptop* current = head;
                                  // тут просто обходим список, ищем максимальный айди
    while (current != NULL) {     // и возвращаем этот айди +1
        if (current->id > max_id) {
            max_id = current->id;
        }
        current = current->next;
    }
    
    return max_id + 1;
}

// вводим данные
Laptop input_laptop(Laptop* head) {
    Laptop laptop;                     // создаем новыу переменную
    laptop.id = get_next_id(head);   // для нового ноута делаем айди
    
    printf("\nДобавление ноутбука:\n");   
                                        
    printf("Бренд: ");
    scanf(" %[^\n]", laptop.brand);
    
    printf("Модель: ");
    scanf(" %[^\n]", laptop.model);
    
    printf("ОЗУ (ГБ): ");
    scanf("%d", &laptop.ram);
    
    printf("Цена (в конях): ");
    scanf("%d", &laptop.price);
    
    laptop.next = NULL;
    return laptop;

}

