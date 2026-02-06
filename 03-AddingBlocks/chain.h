/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * chain.h: Header file containing definition of block_chain for blockchain demo.
 */

#ifndef chain_h
#define chain_h
 
#include "block.h" 
#include <vector>
#include <chrono>

using namespace std;

struct block_chain {
    vector<block> chain;

    // Constructor
    block_chain () {
        chain = {};
        chain.push_back(create_genesis_block());
    }

    // Create a genesis block for the block chain.
    block create_genesis_block() {
        return block(0, chrono::system_clock::to_time_t(chrono::system_clock::now()), "Basic Data", "0000000000000000000000000000000000000000000000000000000000000000");
    }

    // Return the newest block to the chain
    // Required to get hash for new blocks
    block get_last_block() {
        return chain[chain.size()-1];
    }

    // Add a block to the chain
    void add_block(string data, time_t timestamp) {
        block new_block = block(chain.size(), timestamp, data, get_last_block().this_hash);
        chain.push_back(new_block);
    }

    // Return a printable string of the chain
    string to_string(){
        string output_string = "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
        output_string += chain[0].to_string().c_str();

        for (int i = 1; i < chain.size(); i++) {
            output_string += ",\n";
            output_string += chain[i].to_string().c_str();
        }
        output_string += "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
        return output_string;
    }
};

#endif