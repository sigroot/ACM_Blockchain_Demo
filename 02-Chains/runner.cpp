/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * runner.cpp: Driver for blockchain files
 */

#include "block.h"
#include "chain.h"
#include <stdio.h>

using namespace std;

int main() { 
    block_chain my_chain = block_chain();
    printf("%s\n", my_chain.to_string().c_str());
    return 0;
}