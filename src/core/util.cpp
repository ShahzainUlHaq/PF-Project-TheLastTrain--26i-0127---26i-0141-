#include "util.h"

// Primitive helper utilities, clamping, and screen control
int clampInt(int val, int minVal, int maxVal) {
 if (val < minVal) {
  val = minVal; }
 if (val > maxVal) {
  val = maxVal; }
 return val;
}   

bool stringEquals(const char* a, const char* b) {
 int i = 0;
 while ((a[i] == b[i]) && (a[i] != '\0') && (b[i] != '\0')) {
  i++; }
 return (a[i] == b[i]);
}   
