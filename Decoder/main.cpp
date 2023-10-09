#include "DecoderPR.h"
#include <iostream>

int main(int argc, char** argv) {
    Decoder program;
    if (argc > 2) {
        program.run(argv[1], argv[2]);
    }
    else if (argc == 2) {
        std::cout << "Please provide key file" << std::endl;
    }
    else {
        program.run();
    }
    return 0;
}