#include <stdio.h>
#include <stdlib.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"
#include "Lib2.hpp"
#include <unistd.h>
#include <dlfcn.h>

int main(int argc, char* argv[])
{

    void *handle;
    void (*hello_world)(void);
    char *error;

   /*handle = dlopen("libsecond.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&hello_world) = dlsym(handle, "hello");

   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    (*hello_world)();
    dlclose(handle);*/
    //exit(EXIT_SUCCESS);
    LibAbstract *test = new Lib1();
    //hello();
    test = new Lib2();

    sleep(5);
    test->Destroy();
    return 0;
}
