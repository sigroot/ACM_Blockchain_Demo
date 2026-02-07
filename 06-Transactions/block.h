/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * block.h: Header file containing definition of block for blockchain demo.
 */

#ifndef block_h
#define block_h

#include <ctime>
#include <openssl/sha.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>
#include "transaction.h"

using namespace std;

struct block {
    time_t timestamp;                   // The time of the block event
    vector<transaction> transactions;   // The transactions represented by this block
    string prev_hash;                   // The hash of the last block in the chain
    string this_hash;                   // The hash of this block
    unsigned long long nonce;           // Additional data to change the block hash

    // Constructor
    block (time_t _timestamp, vector<transaction> _transactions, string _prev_hash) {
        timestamp = _timestamp;
        transactions = vector<transaction>(_transactions);
        prev_hash = _prev_hash;
        nonce = 0;      // Define starting value of nonce before mining
        this_hash = create_hash();        
    }

    // Return this block's hash
    // Now includes nonce
    string create_hash() {
        // Generate block string without own hash. Otherwise, the change to the 
        // block would change the blocks hash and force recalculation. Nigh 
        // impossible to correctly calculate.

        string concatBlock;

        // Build string

        // Add previous hash
        concatBlock += prev_hash;
        // Add timestamp
        concatBlock += asctime(gmtime(&timestamp));
        concatBlock.pop_back(); // Remove newline from timestamp
        // Add transactions
        for (int i = 0; i < transactions.size(); i++) {
            concatBlock += transactions[i].to_string();
        }
        // Add nonce
        char buffer[20] = {};
        snprintf(buffer, 20, "%llu", nonce);
        concatBlock += buffer;
        
        // Calculate and return hash
        unsigned char* raw_hash = SHA256((const unsigned char *) concatBlock.c_str(), strlen(concatBlock.c_str()), NULL);
        char return_hash[64] = {};
        for (int i = 0; i < 32; i++) {
            snprintf((return_hash+(2*i)), 3, "%2.2X", *(raw_hash+i));
        }
        return return_hash;
    }

    // Change nonce until block hash is 'valid'. A 'valid' block is arbitrarily 
    // defined to be any block with *difficulty* 0's at the beginning of the 
    // hash.
    void mine_block(short difficulty) {
        bool mining = true;
        while (mining) {
            // if the first *difficulty* characters in this hash are 0, then
            // stop mining. Otherwise, increase nonce and recalcutate hash
            for (short i = 0; i < difficulty; i++) {
                // The current character in this_hash is not 0
                if (this_hash[i] == '0') {
                    // Difficulty requirement met, break while loop
                    if (i+1 == difficulty) {
                        mining = false;
                    }
                } else {
                    break;
                }
            }
            // Difficulty requirement met, break while loop
            if (mining == false) break;

            // Recalculate hash
            nonce++;
            this_hash = create_hash();
        }
    }

    // Return a printable string of the block
    string to_string() {
        string output;

        // Build string
        output += "{";

        output += "\n\tTimestamp: \"";

        // Add timestamp
        output += asctime(gmtime(&timestamp));
        output.pop_back();

        output += "\"\n\tPrevious Hash: \"";

        // Add previous hash
        output += prev_hash;

        output += "\"\n\tThis Block's Hash:\"";
        
        // Add this hash
        output += this_hash;

        output += "\"";

        output += "\n\tNonce: ";
        char buffer[20] = {};
        snprintf(buffer, 20, "%llu", nonce);
        output += buffer;

        output += "\n\tTransactions:";
        for (int i = 0; i < transactions.size(); i++) {
            output += "\n\t\t" + transactions[i].to_string() + ",";
        }

        output += "\n}";

        return output;
    }
};

#endif
