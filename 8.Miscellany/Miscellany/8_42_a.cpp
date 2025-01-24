#include <iostream>
#include <list>
#include <map>
#include <string>

namespace ra {

class Item {
public:
    Item(const std::string& id, const std::string& name, std::size_t quantity, double cost)
        : id(id), name(name), quantity(quantity), cost(cost) {}

    std::string id;
    std::string name;
    std::size_t quantity;
    double cost;
};

class Inventory {
public:
    using item_type = Item;
    using items_iterator = std::list<item_type>::iterator;
    using items_const_iterator = std::list<item_type>::const_iterator;

    using items_by_id_iterator = std::map<std::string, item_type*>::iterator;
    using items_by_id_const_iterator = std::map<std::string, item_type*>::const_iterator;

    using items_by_name_iterator = std::multimap<std::string, item_type*>::iterator;
    using items_by_name_const_iterator = std::multimap<std::string, item_type*>::const_iterator;

    Inventory() = default;
    ~Inventory() = default;

    items_iterator add_item(const std::string& id, const std::string& name, std::size_t quantity, double cost);
    items_iterator items_begin() { return items_.begin(); }
    items_iterator items_end() { return items_.end(); }
    items_by_id_iterator items_by_id_begin() { return items_by_id_.begin(); }
    items_by_id_iterator items_by_id_end() { return items_by_id_.end(); }
    items_by_name_iterator items_by_name_begin() { return items_by_name_.begin(); }
    items_by_name_iterator items_by_name_end() { return items_by_name_.end(); }

    item_type* find_by_id(const std::string& id);

private:
    std::list<item_type> items_;  // Store actual items
    std::map<std::string, item_type*> items_by_id_;  // Pointers to items sorted by ID
    std::multimap<std::string, item_type*> items_by_name_;  // Pointers to items grouped by name
};

// Add item to the inventory
Inventory::items_iterator Inventory::add_item(const std::string& id, const std::string& name, std::size_t quantity, double cost) {
    // Check if item with the same ID already exists
    if (items_by_id_.count(id) > 0) {
        return items_.end(); // ID must be unique
    }

    // Add the new item to the list
    items_.emplace_back(id, name, quantity, cost);
    auto it = --items_.end(); // Iterator to the newly added item

    // Add pointers to the map and multimap
    items_by_id_[id] = &(*it);
    items_by_name_.emplace(name, &(*it));

    return it;
}

// Find item by ID
Item* Inventory::find_by_id(const std::string& id) {
    auto it = items_by_id_.find(id);
    return (it != items_by_id_.end()) ? it->second : nullptr;
}

} // namespace ra

// Example usage
int main() {
    ra::Inventory inventory;

    inventory.add_item("842", "apple", 100, 0.25);
    inventory.add_item("843", "apple", 100, 0.32);
    inventory.add_item("000", "grape", 100, 0.50);

    std::cout << "Items in insertion order:\n";
    for (auto it = inventory.items_begin(); it != inventory.items_end(); ++it) {
        std::cout << it->id << " " << it->name << " " << it->quantity << " " << it->cost << "\n";
    }

    std::cout << "\nItems sorted by ID:\n";
    for (auto it = inventory.items_by_id_begin(); it != inventory.items_by_id_end(); ++it) {
        auto item = it->second;
        std::cout << item->id << " " << item->name << " " << item->quantity << " " << item->cost << "\n";
    }

    std::cout << "\nItems sorted by name:\n";
    for (auto it = inventory.items_by_name_begin(); it != inventory.items_by_name_end(); ++it) {
        auto item = it->second;
        std::cout << item->id << " " << item->name << " " << item->quantity << " " << item->cost << "\n";
    }

    std::cout << "\nFinding item by ID '842':\n";
    auto item = inventory.find_by_id("842");
    if (item) {
        std::cout << "Found: " << item->id << " " << item->name << " " << item->quantity << " " << item->cost << "\n";
    } else {
        std::cout << "Item not found\n";
    }

    return 0;
}
