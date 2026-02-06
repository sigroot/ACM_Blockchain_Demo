/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * chain.h: Header file containing definition of chain for blockchain demo.
 */

#include "block.h" 
#include <vector>
#include <chrono>

using namespace std;

struct block_chain {
    vector<block> chain;
    short difficulty;

    // Constructor
    block_chain (short _difficulty) {
        difficulty = _difficulty;
        chain = {};
        chain.push_back(create_genesis_block());
    }

    // Create a genesis block for the block_chain.
    // Now with mined hash
    block create_genesis_block() {
        block genesis = block(0, chrono::system_clock::to_time_t(chrono::system_clock::now()), "Basic Data", "0000000000000000000000000000000000000000000000000000000000000000");
        genesis.mine_block(difficulty);
        return genesis;
    }

    // Return the newest block to the chain
    // Required to get hash for new blocks
    block get_last_block() {
        return chain[chain.size()-1];
    }

    // Add a block to the chain
    // Now with mined hash
    void add_block(string data, time_t timestamp) {
        block new_block = block(chain.size(), timestamp, data, get_last_block().this_hash);
        new_block.mine_block(difficulty);
        chain.push_back(new_block);
    }

    // Check the hashes of the block_chain
    bool is_valid() {
        // Verify the first block is valid
        if (chain[0].this_hash != chain[0].create_hash()) return false;

        // Verify each block is valid and that the hashes between blocks are valid
        for (int i = 1; i < chain.size(); i++) {
            block current_block = chain[i];
            block previous_block = chain[i-1];
            if (current_block.this_hash != current_block.create_hash()) return false;
            if (current_block.prev_hash != previous_block.this_hash) return false;
        }

        return true;
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