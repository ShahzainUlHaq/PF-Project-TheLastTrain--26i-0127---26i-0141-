#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol) {
 for (int i = 0; i < inventoryCount; i++ ) {
  if (inventory[i] == itemSymbol) {
   return true;}
  }
 return false;
}   
   
  

