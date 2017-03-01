/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 22:15:06
 * Last modified: 2017-03-01 14:05:19
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"
#include "dic-parser.hpp"
#include "exlibCases.hpp"
#include <cassert>
#include "key-bind-main.hpp"
#include "bit.hpp"

using std::cout;
using std::endl;

Cases::Cases()
{
}

Cases::~Cases()
{
}

int Cases::cases_main(int argc, char **argv)
{
    int ret = 0;

    /* 
     * exlib-cases
     * */
    {
#if 1
        exlibCases exlibcases;

        ret = exlibcases.exlibcases_main(argc, argv); assert(-1 != ret);
#endif
    }

    /* 
     * cases 001, 002 ,,,
     * */
    {
#if 0
        /* case001 entry */
        test_main();
#endif
    }
    {
#if 1
        /* 
         * case002
         * */
        DicParser dp;

        ret = dp.dicparser_main(argc, argv); assert(-1 != ret);
#endif
    }
    {
#if 0
        /* 
         * case003
         * */
        KeyBind kbind;

        ret = kbind.keybind_main(argc, argv); assert(-1 != ret);
#endif
    }
    {
#if 0
        /* 
         * case004
         * */
        Bit bit;

        ret = bit.bit_main(argc, argv); assert(-1 != ret);
#endif
    }

    return ret;
}

