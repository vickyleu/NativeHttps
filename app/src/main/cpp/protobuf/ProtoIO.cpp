//
// Created by vicky on 2017.08.03.
//

#include <iostream>
#include "sample.pb.h"
#include "ProtoIO.h"

using namespace std;

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int read(User user) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    char *argv = (char *) malloc(4);
    // Read the existing address book.
    CodedInputStream input((const uint8 *) argv, ios::in | ios::binary);
    if (!user.ParseFromCodedStream(&input)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }
    // Optional:  Delete all global objects allocated by libprotobuf.
    ShutdownProtobufLibrary();
    return 0;
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int white(User user) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    char *argv = (char *) malloc(4);
    // Read the existing address book.
    CodedInputStream input((const uint8 *) argv,
                           ios::in | ios::binary);
    if (!input.ExpectAtEnd()) {
        cout << argv << ": File not found.  Creating a new file." << endl;
    } else if (!user.ParseFromCodedStream(&input)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }
    ZeroCopyOutputStream *zout;
    // Write the new address book back to disk.
    CodedOutputStream output(zout, ios::out | ios::trunc | ios::binary);
    if (!user.SerializeToCodedStream(&output)) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }
    // Optional:  Delete all global objects allocated by libprotobuf.
    ShutdownProtobufLibrary();
    return 0;
}