/*
 * Progarm Name: exlibCases.cpp
 * Created Time: 2016-12-21 10:05:59
 * Last modified: 2017-01-14 15:54:16
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exlibCases.hpp"
#include <iostream>
#include "mjson.hpp"

using std::cout;
using std::endl;

exlibCases::exlibCases()
{
}

exlibCases::~exlibCases()
{
}

int  exlibCases::exlibcases_main(int argc, char **argv)
{
    int ret = 0;

    {
#if 1
        mJson mjson;

        ret = mjson.mjson_main(argc, argv);
#endif
    }

    return ret;
}

