#include "util.h"

// Primitive helper utilities, clamping, and screen control
int clampInt(int val, int minVal, int maxVal) {
 if (val < minVal) {
  val = minVal; }
 if (val > maxVal) {
  val = maxVal; }
 return val;
}   
