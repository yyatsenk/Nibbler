#include <stdio.h>
#include <stdlib.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"
#include "Lib2.hpp"
#include <unistd.h>

int main(int argc, char* argv[])
{

    LibAbstract *test = new Lib1();

    test = new Lib2();

    sleep(5);
    test->Destroy();
    return 0;
}
