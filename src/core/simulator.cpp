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
