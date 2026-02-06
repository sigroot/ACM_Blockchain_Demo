/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * runner.cpp: Driver for blockchain files
 */

#include "block.h"
#include <stdio.h>
#include <chrono>

using namespace std;

int main() { 
    block my_block = block(0, chrono::system_clock::to_time_t(chrono::system_clock::now()), "Data", "No Previous Hash");
    printf("Basic block:\n%s\n", my_block.to_string().c_str());
    return 0;
}