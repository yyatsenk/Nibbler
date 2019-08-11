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
    LibAbstract *(*createLIB2)(void);

   handle = dlopen("/home/yyatsenk/Desktop/Nibbler/build/lib2/libsecond.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    *(void **) (&createLIB2) = dlsym(handle, "createLib2");

   if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    LibAbstract *test = (*createLIB2)();
    test->WindowCreate();
    while (1)
    {
        int code = test->GetEvents();
        printf("%d\n", code);
        if (code == 1)
            break;
    }
    //sleep(5);
    test->WindowDestroy();
    dlclose(handle);
    return 0;
}
