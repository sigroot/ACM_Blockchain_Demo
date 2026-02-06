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
    block_chain my_chain = block_chain(4);
    
    // Create chain, now with work involved
    // I am M3MY53LF1
    printf("M3MY53LF1 Balance: %f\n", my_chain.get_balance_of_address("M3MY53LF1"));
    printf("Sent 1337 BC\n");
    my_chain.create_transaction(transaction("M3MY53LF1", "Other", 1337.0));
    printf("Mining transactions...\n");
    my_chain.mine_pending_transactions("M3MY53LF1");
    printf("M3MY53LF1 Balance: %f\n", my_chain.get_balance_of_address("M3MY53LF1"));
    printf("Recieved 42 BC\n");
    my_chain.create_transaction(transaction("Other", "M3MY53LF1", 42.0));
    printf("Lost 9999 BC\n");
    my_chain.create_transaction(transaction("M3MY53LF1", "Other", 9999999999.0));
    printf("Mining transactions...\n");
    my_chain.mine_pending_transactions("M3MY53LF1");
    printf("M3MY53LF1 Balance: %f", my_chain.get_balance_of_address("M3MY53LF1"));

    printf("%s\n", my_chain.to_string().c_str());
    return 0;
}