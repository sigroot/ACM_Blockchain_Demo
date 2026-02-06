# ACM_Blockchain_Demo
This is a demonstration of blockchain that encourages learners to follow along. 

Each step is contained in its own folder (descriptions below) so anyone can use and modify the examples.

Based on a tutorial by Dr. Ernesto Lee for details on how blockchain works, visit his tutorial with the following link:
https://drlee.io/building-your-own-blockchain-in-python-a-step-by-step-guide-ec10ea6c976d

## Requirements
 - g++ (to compile c++ code)
    - **Important note: to correctly compile with the openssl library, the g++ command must include the flag '-lcrypto' (e.g. g++ test.cpp -o test -lcrypto)**
 - openssl (for hashing)
 - a desire to learn (for maximal mental gain)

## Units
### 01-Blocks

This unit defines the "block" struct. Each block contains a section of data and two cryptographic hashes. The first hash is of the block itself while the second is of the previous block in the chain (establishing a verifiable link between the blocks as the chain grows).

### 02-Chains

This unit adds a "chain" struct to hold blocks. It also defines the "genesis block", or the first block in a chain. Each block will be connected to this genesis block. 

### 03-AddingBlocks

This unit starts adding blocks to the chain. Now blocks can each be seen to relate to the last block in the chain. If a block in the middle is modified, then that block's hash would need to change. Because the each block's **prev_hash** is factored into its **this_hash**, each block following the modified block would also need to be modified for the chain's hashes to become consistent again.

### 04-ChainValidation

This unit allows the chain to validate its own hashes. The chain now technically works and could create an agreed upon series of events between a network of devices (though that would several other mechanisms to prevent individuals from confusing the others. This will not delve into those mechanisms.). However, this is not sufficient for blockchain's most well known usecase: cryptocurrency. Currently blocks are nearly free to create.

### 05-Mining

This units now permits mining for blocks. Each block now has the additional requirement that its hash starts with four '0's. Because hashes are, intentionally, one-way functions, the only what to correctly change a block's hash is to change the block information and recalculate the hash. Eventually, a valid hash will be randomly discovered (the block is now "mined"). In order to not change any existing variables in the block, a new variable called "nonce" is introduced specifically to change the hash. After each failed mining attempt, nonce is incremented by 1. This process of mining increases the computational work required to create a single event and makes blocks harder to alter the older they are (because more blocks ahead of it would also need to be recalculated). 

### 06-Transactions

This unit modifies the current blockchain structure to better act as a currency. The "transaction" struct is added to represent a tranfer of currency betweeen users. The **index** variable in the block struct is removed amd **data** is replacedd by the transaction. Each block mined now provides a reward to an address (so that the total sum of currency can be above 0) and the block chain can be scanned, based on what a given user has lost and gained, to determine their balance.

