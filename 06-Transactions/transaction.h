/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * transaction.h: Header file containing definition of transaction for blockchain demo.
 */

#ifndef transaction_h
#define transaction_h

#include <string>

using namespace std;

struct transaction {
    string from_addr;
    string to_addr;
    double amount;
    
    // Constructor
    transaction (string _from_addr, string _to_addr, double _amount) {
        from_addr = _from_addr;
        to_addr = _to_addr;
        amount = _amount;
    }

    transaction clone() {
        return transaction(from_addr, to_addr, amount);
    }
    // Return a printable string of the block
    string to_string() {
        string output = "Transaction: \"";

        output += from_addr;

        output += "\" to \"";

        output += to_addr;

        output += "\" the amount ";

        char buffer[20] = {};
        snprintf(buffer, 20, "%lld", (unsigned long long) amount);
        output += buffer;

        return output;
    }
};

#endif