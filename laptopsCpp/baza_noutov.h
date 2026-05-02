#ifndef BAZA_NOUTOV_H
#define BAZA_NOUTOV_H

#include <string>
#include <list>
#include <optional>

struct Laptop {
    int id;
    std::string brand;
    std::string model;
    int ram;
    int price;
};
class LaptopDatabase {
private:
    std::list<Laptop> laptops;
    std::string filename;
    int get_next_id() const;
public:
    explicit LaptopDatabase(const std::string& file);
    ~LaptopDatabase();
    void add_laptop(const Laptop& laptop);
    void remove_laptop(int id);
    std::optional<std::reference_wrapper<const Laptop>> find_by_id(int id) const;
    void find_by_brand(const std::string& brand) const;
    void find_by_price(int max_price) const;
    void update_laptop(int id, const Laptop& new_data);
    void show_all() const;
    void load_from_file();
    void save_to_file() const;
};

Laptop input_laptop();
#endif
