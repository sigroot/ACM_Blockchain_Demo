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
    
    my_chain.add_block("Sent $1337", chrono::system_clock::to_time_t(chrono::system_clock::now()));
    my_chain.add_block("Recieved $42", chrono::system_clock::to_time_t(chrono::system_clock::now()));
    my_chain.add_block("Lost EVERYTHING", chrono::system_clock::to_time_t(chrono::system_clock::now()));

    printf("%s\n", my_chain.to_string().c_str());
    return 0;
}