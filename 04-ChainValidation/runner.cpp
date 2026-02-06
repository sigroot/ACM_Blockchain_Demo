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
    
    // Create valid chain
    my_chain.add_block("Sent $1337", chrono::system_clock::to_time_t(chrono::system_clock::now()));
    my_chain.add_block("Recieved $42", chrono::system_clock::to_time_t(chrono::system_clock::now()));
    my_chain.add_block("Lost EVERYTHING", chrono::system_clock::to_time_t(chrono::system_clock::now()));
    my_chain.add_block("Account 0", chrono::system_clock::to_time_t(chrono::system_clock::now()));

    bool valid_before = my_chain.is_valid();

    // Modify chain
    my_chain.chain[3] = block(3, chrono::system_clock::to_time_t(chrono::system_clock::now()), "Lost nothing?", my_chain.chain[3].prev_hash);

    bool valid_after = my_chain.is_valid();

    printf("%s\n", my_chain.to_string().c_str());

    printf("Is chain valid before modification? %s\n", valid_before ? "True" : "False");
    printf("Is chain valid after modification? %s\n", valid_after ? "True" : "False");
    return 0;
}