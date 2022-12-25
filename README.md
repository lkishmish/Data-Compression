# Data-Compression
For this project, you will build a file compression algorithm that uses binary trees and priority queues. Your program will allow the user to compress and decompress files using the standard Huffman algorithm for encoding and decoding. You will also use a provided custom hashmap class.
   
Huffman encoding is an example of a lossless compression algorithm that works particularly well on text but can, in fact, be applied to any type of file. Using Huffman encoding to compress a file can reduce the storage it requires by a third, half, or even more, in some situations. You’ll be impressed with the compression algorithm, and you’ll be equally impressed that you’re outfitted to implement the core of a tool that imitates one you’re already very familiar with. 

count frequencies: Examine a source file’s contents and count the number of occurrences of each character, and store them in a map using the hashmap class you are provided. 
build encoding tree: Build a binary tree with a particular structure, where each node represents a character and its count of occurrences in the file. A priority queue is used to help build the tree along the way. 
build encoding map: Traverse the binary tree to discover the binary encodings of each character. 
encode data: Re-examine the source file’s contents, and for each character, output the encoded binary version of that character to the destination file. 

