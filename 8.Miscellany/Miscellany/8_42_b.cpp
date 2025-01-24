#include <iostream>
#include <string>
#include <list>
#include <map>
namespace ra{
class Item{
public:
    std::string id;
    std::string name;
    int quantity;
    float cost;

    Item(const std::string& _id, const std::string& _name, int _quantity, float _cost)
    : id(_id), name(_name), quantity(_quantity), cost(_cost){}
};

class Inventory{
public:
    using item_type = Item;

    using items_iterator = std::list<item_type>::iterator;
    using items_const_iterator = std::list<item_type>::const_iterator;

    using items_by_id_iterator = std::map<std::string, item_type*>::iterator;
    using items_by_id_const_iterator = std::map<std::string, item_type*>::const_iterator;

    using items_by_name_iterator = std::multimap<std::string, item_type*>::iterator;
    using items_by_name_const_iterator = std::multimap<std::string, item_type*>::const_iterator;

    Inventory()=default;
    ~Inventory()=default;

    Inventory(const Inventory&) = delete;
    Inventory& operator=(const Inventory&) = delete;

    Inventory(const Inventory&&) = delete;
    Inventory& operator=(const Inventory&&) = delete;

    items_iterator add_item(const std::string& id, const std::string& name, int quantity, float cost);

    items_iterator items_begin(){ return itemByInsertionOrder_.begin();}
    items_iterator items_end(){ return itemByInsertionOrder_.end();}
    items_const_iterator items_begin() const { return itemByInsertionOrder_.begin();}
    items_const_iterator items_end() const { return itemByInsertionOrder_.end();}

    items_by_id_iterator items_by_id_begin(){ return itemsById_.begin();}
    items_by_id_iterator items_by_id_end(){ return itemsById_.end();}
    items_by_id_const_iterator items_by_id_begin() const { return itemsById_.begin();}
    items_by_id_const_iterator items_by_id_end() const { return itemsById_.end();}

    items_by_name_iterator items_by_name_begin(){ return itemsByName_.begin();}
    items_by_name_iterator items_by_name_end(){ return itemsByName_.end();}
    items_by_name_const_iterator items_by_name_begin() const { return itemsByName_.begin();}
    items_by_name_const_iterator items_by_name_end() const { return itemsByName_.end();}

    item_type* find_by_id(const std::string& id);
    const item_type* find_by_id(const std::string& id) const;

private:
    std::list<item_type> itemByInsertionOrder_;
    std::map<std::string, item_type*> itemsById_;
    std::multimap<std::string, item_type*> itemsByName_;
};

Inventory::items_iterator Inventory::add_item(const std::string& id, const std::string& name, int quantity, float cost) {
    if (itemsById_.find(id) != itemsById_.end()) {
        return itemByInsertionOrder_.end(); // ID already exists
    }

    itemByInsertionOrder_.emplace_back(id, name, quantity, cost);
    auto it = std::prev(itemByInsertionOrder_.end()); // Iterator to the newly added item

    itemsById_[id] = &(*it);
    itemsByName_.emplace(name, &(*it));

    return it;
}

Inventory::item_type* Inventory::find_by_id(const std::string& id){
    auto it = itemsById_.find(id);
    return it == itemsById_.end() ? nullptr : it->second;
}
const Inventory::item_type* Inventory::find_by_id(const std::string& id) const {
    auto it = itemsById_.find(id);
    return it == itemsById_.end() ? nullptr : it->second;
}
} //namespace ra

int main() {
    ra::Inventory inventory;

    inventory.add_item("apple-0000", "apple", 10, 1000);
    inventory.add_item("grape-0001", "grape", 10, 0.10);
    inventory.add_item("grape-0002", "grape", 10, 0.10);

    // Example usage:
    std::cout << "Items in insertion order:\n";
    for (ra::Inventory::items_iterator it = inventory.items_begin(); it != inventory.items_end(); ++it) {
        const auto& item = *it;
        std::cout << item.id << " " << item.name << " " << item.quantity << " " << item.cost << std::endl;
    }

    std::cout << "\nItems sorted by ID:\n";
    for (ra::Inventory::items_by_id_iterator it = inventory.items_by_id_begin(); it != inventory.items_by_id_end(); ++it) {
        const auto& item_pair = *it;
        std::cout << item_pair.first << " " << item_pair.second->name << " "
                  << item_pair.second->quantity << " " << item_pair.second->cost << std::endl;
    }

    std::cout << "\nItems sorted by name:\n";
    for (ra::Inventory::items_by_name_iterator it = inventory.items_by_name_begin(); it != inventory.items_by_name_end(); ++it) {
        const auto& item_pair = *it;
        std::cout << item_pair.first << " " << item_pair.second->id << " "
                  << item_pair.second->quantity << " " << item_pair.second->cost << std::endl;
    }

    return 0;
}

