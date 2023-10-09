#include "Encoder.h"
#include <iostream>

int main(int argc, char** argv) {
    Encoder program;
    if (argc > 1) {
        program.run(argv[1]);
    }
    else {
        program.run();
    }
    return 0;
}