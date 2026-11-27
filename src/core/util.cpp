#include "util.h"
#include<iostream>
using namespace std;

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

static bool Space(char a) {
 return ( a == ' ' || a == '\t' || a == '\n' || a == '\r'); 
}

void trimWhitespace (char* str) {
 int start = 0;
 while ( Space(str[start]) ) {
  start++;
 }
 int end = start;
 while ( str[end] != '\0') {
  end++;
 }
 while (end > start && (Space(str[end - 1]))) {
  end--;
 }
 
 int i = 0;
 while (start < end) {
  str[i] = str[start];
  i++;
  start++;
 }
 str[i] = {'\0'};
}  

void printHeader(const char* title) {
 for (int i = 0; i < 35; i++) {
  cout << "-"; }
 cout << endl;
 cout << " " << title << endl;
 for (int i = 0; i < 35; i++) {
  cout << "-";}
 cout << endl;
}  

void clearScreen() {
 cout << "\033[2J\033[H";
 }
   
    
        
