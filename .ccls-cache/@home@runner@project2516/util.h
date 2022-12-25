//
// STARTER CODE: util.h
//
// Name : Lakshmi K
// NetID: 672897625
// Email: lkris2@uic.edu

#pragma once
#include "hashmap.h"
#include "mainprog.h"
#include <cctype>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>

typedef hashmap hashmapF;
typedef unordered_map<int, string> hashmapE;

struct HuffmanNode {
  int character;
  int count;
  HuffmanNode *zero;
  HuffmanNode *one;
};

struct compare {
  bool operator()(const HuffmanNode *lhs, const HuffmanNode *rhs) {
    return lhs->count > rhs->count;
  }
};

//
// *This method frees the memory allocated for the Huffman tree.
// post order for clearing the tree
void freeTree(HuffmanNode *node) {
  if (node == nullptr) {
    return;
    // if node is null return nothing
  } else {
    freeTree(node->zero);
    freeTree(node->one);
    // do post order traversal to free the memory
    delete node;
  }
  // TO DO:  Write this function here.
}

//
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
  char charKey;

  if (isFile == true) {
    // open file if exists
    ifstream inFile;
    inFile.open(filename);

    while (inFile.get(charKey)) {
      //
      if (map.containsKey(charKey)) {
        // if already found key increment the count by 1
        map.put(charKey, map.get(charKey) + 1);
      } else {
        map.put(charKey, 1);
        // otherwise count is 1
      }
    }
  } else {
    for (auto s : filename) {
      // if key is a string do the same process
      if (map.containsKey(charKey)) {

        map.put(charKey, map.get(charKey) + 1);
      } else {
        map.put(charKey, 1);
      }
    }
  }
  map.put(PSEUDO_EOF, 1); // if end of file is reached, add it
}

//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode *buildEncodingTree(hashmapF &map) {
  priority_queue<HuffmanNode *, vector<HuffmanNode *>, compare> pq;

  vector<int> keyVector = map.keys();

  for (auto m : keyVector) {

    HuffmanNode *huffNode = new HuffmanNode();
    // creating a new node and initializing the parameters
    huffNode->character = m;
    huffNode->count = map.get(m);
    huffNode->one = nullptr;
    huffNode->zero = nullptr;

    pq.push(huffNode);
  }

  while (pq.size() > 1) {
    HuffmanNode *firstNode = nullptr;
    HuffmanNode *secondNode = nullptr;
    // initialize the first and second node according to the priority queue
    // order
    firstNode = pq.top();
    pq.pop();
    secondNode = pq.top();
    pq.pop();

    HuffmanNode *huffNode = new HuffmanNode();
    huffNode->character = 257;
    // sets the count to sum of the charater frequency of both elements in the
    // priority queue
    huffNode->count = (firstNode->count) + (secondNode->count);
    huffNode->zero = firstNode;
    huffNode->one = secondNode;
    pq.push(huffNode);
  }

  return pq.top();
}

//
// *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode *node, hashmapE &encodingMap, string str,
                       HuffmanNode *prev) {
  if (node == nullptr) {
    return;
  } else {
    // if its a leaf node, insert into mymapmap
    if (node->character != NOT_A_CHAR) {
      encodingMap.insert(pair<int, string>(node->character, str));
    }

    _buildEncodingMap(node->zero, encodingMap, str + '0', prev);

    str = str + '1';
    _buildEncodingMap(node->one, encodingMap, str, prev);
  }
}

//
// *This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode *tree) {
  hashmapE encodingMap;

  HuffmanNode *prev = nullptr;
  string str = "";
  _buildEncodingMap(tree, encodingMap, str, prev);

  return encodingMap;
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream &input, hashmapE &encodingMap, ofbitstream &output,
              int &size, bool makeFile) {
  string outputStr;
  char character;
  while (input.get(character)) {
    outputStr += encodingMap[character];
  }
  outputStr += encodingMap[PSEUDO_EOF];

  if (makeFile) {
    for (unsigned int z = 0; z < outputStr.size(); z++) {
      if (outputStr[z] == '0') {
        output.writeBit(0);
      } else {
        output.writeBit(1);
      }
    }
  }
  size = outputStr.size();

  return outputStr;
}

//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode *encodingTree, ofstream &output) {
  HuffmanNode *currNode = encodingTree;
  string outputString;
  while (!input.eof()) {
    int bit = input.readBit();

    if (bit == 0) {
      currNode = currNode->zero;

    }

    else {
      currNode = currNode->one;
    }

    if (currNode->character == PSEUDO_EOF) {
      currNode = encodingTree;
      break;

    } else {
      if (currNode->character != NOT_A_CHAR) {

        outputString += currNode->character;
        output.put(currNode->character);
        currNode = encodingTree;
      }
    }
  }

  return outputString; // TO DO: update this return
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
  hashmap FrequencyMap;
  hashmapE Map;
  string EncodeTree;
  ifstream isFile(filename);
  int size;
  string hufFilename = filename;
  hufFilename += ".huf";

  ofbitstream output(hufFilename);
  buildFrequencyMap(filename, true, FrequencyMap);

  HuffmanNode *HuffTree = buildEncodingTree(FrequencyMap);

  Map = buildEncodingMap(HuffTree);

  output << FrequencyMap;

  EncodeTree = encode(isFile, Map, output, size, true);
  cout << EncodeTree << endl;
  cout << FrequencyMap << endl;
  // freeing the EncodedTree
  freeTree(HuffTree);

  return EncodeTree;
}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) {
  hashmapF FrequencyMap;

  string DecodeTree = "";

  ifbitstream input(filename);

  string uncFilename = filename;
  int pos = filename.find(".");
  uncFilename = filename.substr(0, pos);
  uncFilename += "_unc.txt";

  ofstream output(uncFilename);

  input >> FrequencyMap;
  HuffmanNode *HuffTreeDecode = buildEncodingTree(FrequencyMap);


  DecodeTree = decode(input, HuffTreeDecode, output);

  // freeing the EncodedTree
  freeTree(HuffTreeDecode);
  return DecodeTree;
}
