/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-20 17:37:08
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db-caller.hpp"
#include "cases.hpp"
#include "algorithm_main.h"
#include "linux_main.h"
#include <cassert>
#include "container.hpp"

using namespace std;

int main(int argc, char **argv)
{
    int ret = 0;

    {
        Primer  primer;

        ret = primer.primer_main(argc, argv);
    }
    {
#if 0 
        Container container;

        assert(-1 != ret);
        ret = container.container_main(argc, argv);
#endif
    }
    {
#if 0
        dbCaller dbcaller;

        assert(-1 != ret);
        ret = dbcaller.dbcaller_main(argc, argv);

        assert(-1 != ret);
        //ret = linux_main(argc, argv);
#endif
    }
    {
#if 1
        Cases cases;

        assert(-1 != ret);
        ret = cases.cases_main(argc, argv);
#endif
    }
    {
#if 0
        mAlgorithm  malgo;

        assert(-1 != ret);
        ret = malgo.malgo_main(argc, argv);
#endif
    }
    return ret;
}


