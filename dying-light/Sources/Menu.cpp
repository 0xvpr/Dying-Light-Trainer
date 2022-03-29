#include "Menu.hpp"
#include <cstring>

Menu* Menu::instance = nullptr;

Menu* Menu::Instance() {

    if (instance == nullptr) {
        instance = new Menu();
    } 

    return instance;

}

Menu::Menu()
    : items(nullptr)
    , n_items(3)
    , title("Daylight Savings")
    , pos({30, 30})
    , size({200, 15 + static_cast<float>(n_items) * 30})
{
    items = new HackItem[n_items]{
        {false, "Godmode\0"},
        {false, "Oneshot\0"},
        {false, "Infinite Stamina\0"},
    };
}

Menu::~Menu() {
    delete[] items;
    delete instance;
}

HackItem& Menu::operator [] (unsigned idx) {
    return items[idx];
}

const char* Menu::Title() const {
    return title;
}

Position Menu::Pos() const {
    return pos;
}

Size Menu::Size() const {
    return size;
}

size_t Menu::NumberOfItems() const {
    return n_items;
}

void Menu::MovePosLeft() {
    if (pos.x > 20) {
        pos.x -= 5;
    }
}

void Menu::MovePosRight() {
    if (pos.x < 1368 - size.x) {
        pos.x += 5;
    }
}

void Menu::MovePosUp() {
    if (pos.y > 20) {
        pos.y -= 5;
    }
}

void Menu::MovePosDown() {
    if (pos.y < 762 - size.y) {
        pos.y += 5;
    }
}
