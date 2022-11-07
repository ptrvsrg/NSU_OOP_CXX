#include <iostream>

#include "cl_parser.h"

int main(int argc,
         char ** argv)
{
    try
    {
        Options opts;
        GetOptions(argc,
                   argv,
                   opts);
    }
    catch ()
    {

    }

    return EXIT_SUCCESS;
}