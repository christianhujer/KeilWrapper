#include <err.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    errno = ENOTSUP;
    err(EXIT_FAILURE, "Not yet implemented.");
}
