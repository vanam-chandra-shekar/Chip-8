#include "app.hpp"

int main()  {

    Application app{"chip-8" , 20};

    app.run("test_opcode.ch8");

    return 0;
}