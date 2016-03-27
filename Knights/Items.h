#ifndef ITEMS_H
#define ITEMS_H

#include "Item.h"

class Items{
    
public:
    static ItemPtr fishItem;
    static ItemPtr swordItem;
    static ItemPtr potionItem;
    
    static void setItems();
};

#endif