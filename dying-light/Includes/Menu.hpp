#ifndef MENU_HEADER
#define MENU_HEADER

enum item {
    godmode,
    oneshot,
    infinite_stamina
};

typedef struct HackItem
{
    bool bEnabled;
    char name[64];
} HackItem;

typedef struct Position
{
    float x;
    float y;
} Position;

typedef struct Size
{
    float x;
    float y;
} Size;

struct
[[nodiscard]]
Menu {
private: // Private variables
    HackItem*       items;
    size_t          n_items;
    static Menu*    instance;
    const char*     title;
    Position        pos;
    Size            size;
private: // Private Constructors
    Menu();
    ~Menu();
public: // Public Constructor
    static Menu* Instance();
public: // Overloads
    Menu(const Menu&) = delete;
    Menu& operator = (const Menu&) = delete;
    HackItem& operator [] (unsigned);
public: // Constant
    const char* Title() const;
    Position Pos() const;
    Size Size() const;
    size_t NumberOfItems() const;
public: // Non-Constant
    void MovePosLeft();
    void MovePosRight();
    void MovePosUp();
    void MovePosDown();
};

#endif // MENU_HEADER
