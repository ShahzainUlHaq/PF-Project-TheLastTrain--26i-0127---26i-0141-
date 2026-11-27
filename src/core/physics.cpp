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

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
 if (inventoryCount >= MAX_INVENTORY_CAPACITY) {
  return false;
 }
 inventory[inventoryCount] = itemSymbol;
 inventoryCount++;
 return true;
}

bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol) {
 for (int i = 0; i < inventoryCount; i++) {
  if (inventory[i] == itemSymbol) {
   for (int j = i; j < inventoryCount - 1; j++) {
    inventory[j] = inventory[j+1];
   }
   inventoryCount--;
   return true;
  }
 }
 return false;
}      

void applyScoreDelta(int& score, int deltaScore) {
 score += deltaScore;
}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime) {
 energy = clampInt(energy+deltaEnergy, 0, MAX_ENERGY);
 time = clampInt(time+deltaTime, 0 , MAX_TIME);
} 
 
   
  

