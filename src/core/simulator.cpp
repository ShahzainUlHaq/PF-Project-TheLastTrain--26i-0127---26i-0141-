#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"
#include<iostream>
using namespace std;

// Modular simulation loop using primitive variables

bool handleMoveCommand(int targetFloor, int targetRoom,int& currentFloor, int& currentRoom, int& energy, int& time, const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1], const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int& emergencyTripsLeft, bool lift2Operational) {
 char connType = ' ';
 if (!isDirectlyConnected(currentFloor, currentRoom, targetFloor, targetRoom, horizontalConn, connType)) {
  cout << "Movement to that area is not allowed from current position" << endl;
  return false;
 } 
 if (!canTraverse(targetFloor, targetRoom, connType, inventory, inventoryCount, emergencyTripsLeft, lift2Operational)) {
  cout << "Route is Blocked. Cannot traverse" << endl;
  return false;
 }
 int deltaE = COST_MOVE_ORDINARY_ENERGY;
 int deltaT = COST_MOVE_ORDINARY_TIME;
 if (connType == CONN_WINDOW) {
  deltaE = COST_MOVE_WINDOW_ENERGY;
  deltaT = COST_MOVE_WINDOW_TIME;
 }
 else if (connType == CONN_LIFT1 || connType == CONN_LIFT2) {
  deltaE = COST_MOVE_LIFT_ENERGY;
  deltaT = COST_MOVE_LIFT_TIME;
 }
 applyResourceDelta(energy, time, deltaE, deltaT);
 if (connType == CONN_LIFT2 && !lift2Operational) {
  emergencyTripsLeft--;
 }
 currentFloor = targetFloor;
 currentRoom = targetRoom;
 cout << "You moved to F" << currentFloor + 1 << "-R" << currentRoom + 1 << "." << endl;
 return true;
}     

bool handleCollectCommand(char itemSymbol, int currentFloor, int currentRoom, int& energy, int& time, int& score, char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int& entityCount, char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, bool objectives[NUM_OBJECTIVES]) {
 if (currentFloor < 0 || currentFloor >= NUM_FLOORS || currentRoom < 0 || currentRoom >= ROOMS_PER_FLOOR) {
  return false;
 }
 if (!hasItem(roomEntities[currentFloor][currentRoom], entityCount, itemSymbol)) {
  cout << "Item is not present in this room" << endl;
  return false;
 }
 bool consumable = (itemSymbol == ENT_ENERGY_PACK || itemSymbol == ENT_EMERGENCY_TOOLKIT || itemSymbol == ENT_OBSERVATION_TOKEN);
 bool carryable = (itemSymbol == ENT_MASTER_KEY || itemSymbol == ENT_FUSE || itemSymbol == ENT_LIFT_PASS || itemSymbol == ENT_MEDICAL_KIT || itemSymbol == ENT_EMERGENCY_CARD || itemSymbol == ENT_CAT_CARRIER);
 if (!consumable && !carryable) {  
  cout << "You can't pick that up." << endl;
  return false;
 }
 if (carryable && !addItem(inventory, inventoryCount, itemSymbol)) {
  cout << "Your inventory is full" << endl;
  return false;
 }
 removeItem(roomEntities[currentFloor][currentRoom], entityCount, itemSymbol);
 applyResourceDelta(energy, time, COST_ITEM_PICKUP_ENERGY, COST_ITEM_PICKUP_TIME);
 if (itemSymbol == ENT_ENERGY_PACK) {
  applyResourceDelta(energy, time, BONUS_ENERGY_PACK, 0);
 }
 if (itemSymbol == ENT_EMERGENCY_TOOLKIT) {
  applyResourceDelta(energy, time, BONUS_EMERGENCY_TOOLKIT, 0); }
 if (itemSymbol == ENT_OBSERVATION_TOKEN) {
  applyResourceDelta(energy, time, 0, BONUS_OBSERVATION_TOKEN); }
 if (itemSymbol == ENT_MASTER_KEY && !objectives[OBJ_MASTER_KEY]) {
  objectives[OBJ_MASTER_KEY] = true;
  applyScoreDelta(score, SCORE_KEY_COLLECT);
 }
 if (itemSymbol == ENT_FUSE) {
  objectives[OBJ_FUSE_COLLECTED] = true;
 }
 if (itemSymbol == ENT_LIFT_PASS && !objectives[OBJ_LIFT_PASS]) {
  objectives[OBJ_LIFT_PASS]= true;
  applyScoreDelta(score, SCORE_LIFT_PASS);
 }
 if (itemSymbol == ENT_CAT_CARRIER) {
  objectives[OBJ_CAT_CARRIER] = true;
 }
 cout << "An Item was Collected" << endl;
 return true;
}       

