#include <stdio.h>
#include <stdlib.h>
#include "LibAbstract.hpp"
#include "Lib1.hpp"
#include "Lib2.hpp"
#include <unistd.h>
#include <dlfcn.h>

int lib_num = 0;

static char *libs[2] = {
    "/home/yyatsenko/unit/Nibbler/build/lib1/libfirst.so",
    "/home/yyatsenko/unit/Nibbler/build/lib2/libsecond.so"
};

LibAbstract *changeLibrary(void *handle, LibAbstract *(*createLIB)(void))
{
    dlclose(handle);
    if (lib_num == 2)
        lib_num = 0;
    handle = dlopen(libs[lib_num], RTLD_LAZY);
    lib_num++;
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&createLIB) = dlsym(handle, "createLib");
    return (*createLIB)();
}

void gameLoop(LibAbstract *test, void *handle, LibAbstract *(*createLIB)(void))
{
    test->WindowCreate();
    while (1)
    {
        int code = test->GetEvents();
        printf("%d\n", code);
        if (code == 1)
        {
            test->WindowDestroy();
            test = changeLibrary(handle, createLIB);
            test->WindowCreate();
        }
        if (code == 0)
            break;
    }
    //sleep(5);
    test->WindowDestroy();
}

int main(int argc, char* argv[])
{

    void *handle;
    void (*hello_world)(void);
    char *error;
    LibAbstract *(*createLIB)(void);

   handle = dlopen("/home/yyatsenko/unit/Nibbler/build/lib2/libsecond.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&createLIB) = dlsym(handle, "createLib");

   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    LibAbstract *test = (*createLIB)();
    gameLoop(test, handle, createLIB);
    dlclose(handle);
    return 0;
}
