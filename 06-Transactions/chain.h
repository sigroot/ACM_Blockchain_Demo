/* Written by Samuel Armstrong
 * Based on tutorial by Dr. Ernesto Lee
 * https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d
 *
 * chain.h: Header file containing definition of block_chain for blockchain demo.
 */

#ifndef chain_h
#define chain_h
 
#include "block.h" 
#include "transaction.h"
#include <vector>
#include <chrono>

using namespace std;

struct block_chain {
    vector<block> chain;
    short difficulty;
    vector<transaction> pending_transactions;
    double mining_reward;

    // Constructor
    block_chain (short _difficulty) {
        difficulty = _difficulty;
        chain = {};
        chain.push_back(create_genesis_block());
        pending_transactions = vector<transaction>();
        mining_reward = 10.0;
    }

    // Create a genesis block for the block_chain.
    // Now with mined hash
    block create_genesis_block() {
        block genesis = block(chrono::system_clock::to_time_t(chrono::system_clock::now()), vector<transaction>(), "0000000000000000000000000000000000000000000000000000000000000000");
        genesis.mine_block(difficulty);
        return genesis;
    }

    // Return the newest block to the chain
    // Required to get hash for new blocks
    block get_last_block() {
        return chain[chain.size()-1];
    }

    // Mine a block representing the current pending transactions
    void mine_pending_transactions(string mining_reward_address) {
        // Mine a new block
        block new_block = block(chrono::system_clock::to_time_t(chrono::system_clock::now()), pending_transactions, get_last_block().this_hash); 
        
        new_block.mine_block(difficulty);

        // Append to block chain
        chain.push_back(new_block);

        // Reset transactions
        pending_transactions.clear();
        pending_transactions.push_back(transaction("", mining_reward_address, mining_reward));
    }

    // Append to pending trans
    void create_transaction(transaction _transaction) {
        pending_transactions.push_back(_transaction);
    }

    // Check a given address's current balance (by iterating over the history
    // contained in the block chain)
    double get_balance_of_address(string address) {
        double balance = 0;

        for (int i = 0; i < chain.size(); i++) {
            block current_block = chain[i];
            for (int j = 0; chain[i].transactions.size(); j++) {
                transaction current_transaction = current_block.transactions[j];
                if (current_transaction.from_addr == address) {
                    balance -= current_transaction.amount;
                }
                if (current_transaction.to_addr == address) {
                    balance += current_transaction.amount;
                }
            }
        }

        return balance;
    }

    // REMOVED 'add_block()'
    // Add a block to the chain
    // Now with mined hash
    /*void add_block(string data, time_t timestamp) {
        block new_block = block(chain.size(), timestamp, data, get_last_block().this_hash);
        new_block.mine_block(difficulty);
        chain.push_back(new_block);
    }*/

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

#endif