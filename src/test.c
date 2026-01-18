#include <stdio.h>

#define NO_LOGGA_PREFIX
#include "logga.h"


static logga_t logga;

void foo(void)
{
    trace(&logga, "foo()");
    warn(&logga, "no-op");
}

int main(int argc, char *argv[])
{
    logga_init(&logga);
    trace(&logga, "main()");
    info(&logga, "hello, world!");
    foo();
    return 0;
}
