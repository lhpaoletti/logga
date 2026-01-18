#include <stdio.h>

#define NO_LOGGA_PREFIX
#include "logga.h"


void foo(void)
{
    trace("foo()");
    warn("no-op");
}

int main(int argc, char *argv[])
{
    logga_set_level(TRACE);
    logga_set_outfile(stderr);
    trace("main()");
    info("hello, world!");
    foo();
    return 0;
}
