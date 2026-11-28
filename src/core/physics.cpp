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
 
bool isDirectlyConnected(int fromF, int fromR, int toF, int toR, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR -1], char& outConnType) {
 int index;
 if (fromF < 0 || fromF >= NUM_FLOORS || toF < 0 || toF >= NUM_FLOORS || fromR < 0 || fromR >= ROOMS_PER_FLOOR || toR < 0 || toR >= ROOMS_PER_FLOOR ) {
  return false; 
 }
 if (fromF == toF) {
  int diff = fromR - toR;
   if (diff == 1 || diff == -1) {
    if (fromR < toR) {
     index = fromR; }
    else { 
     index = toR; } 
    char conn = horizontalConn[fromF][index];
    if (conn == CONN_NONE || conn == CONN_SOLID_WALL) {
     return false; }
    outConnType = conn;
    return true;
   }
   return false;
  }
 int floorDiff = fromF - toF;
 if (floorDiff < 0) {
  floorDiff = -floorDiff;
 }
 int lowF = fromF;
 if (toF < fromF) {
  lowF = toF;
 }
 if (fromR == 0 && toR == 0 && floorDiff == 1 && (lowF == 0 || lowF == 1 || lowF == 3)) { 
  outConnType = CONN_STAIRS;
  return true;
 }
 if (fromF <= 1 && toF <= 1 && fromR >= 1 && fromR <= 2 && toR >= 1 && toR <= 2) {
  outConnType = CONN_LIFT1;
  return true;
 }
 if (fromR == 3 && toR == 3 && (fromF == 1 || fromF == 3 || fromF == 4) && (toF == 1 || toF == 3 || toF == 4)) {
  outConnType = CONN_LIFT2;
  return true;     
 }      
 return false;   
  }

bool canTraverse(int targetFloor, int targetRoom, char connType, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft, bool lift2Operational) {
 if (targetFloor < 0 || targetFloor >= NUM_FLOORS || targetRoom < 0 || targetRoom >= ROOMS_PER_FLOOR) {
  return false;
 }
 if (connType == CONN_DOOR || connType == CONN_WINDOW || connType == CONN_STAIRS || connType == CONN_LIFT1) {
  return true;
 }
 if (connType == CONN_LOCKED_DOOR) {
  return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
 }
 if (connType == CONN_LIFT2) {
  return lift2Operational || (hasItem(inventory, inventoryCount, ENT_EMERGENCY_CARD) && emergencyTripsLeft > 0);
 }
 return false;
}     
