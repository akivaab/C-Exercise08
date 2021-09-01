#include <stdlib.h>
#include "miniz.h"
#include "Unzip.h"

int main(size_t argc, char *argv[])
{
    unzip("puppies.zip", argv[1]);
}
