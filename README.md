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

This section defines the "block" struct. Each block contains a section of data and two cryptographic hashes. The first hash is of the block itself while the second is of the previous block in the chain (establishing a verifiable link between the blocks as the chain grows).

### 02-Chains

This section adds a "chain" struct to hold blocks. It also defines the "genesis block", or the first block in a chain.