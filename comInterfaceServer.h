#ifndef COMINTERFACESERVER_H
#define COMINTERFACESERVER_H

#include "gnublin-api/gnublin.h"

#include <vector>

#include <boost/python/list.hpp>

class RPiInterfaceServer
{
public:
    RPiInterfaceServer();
    int i2c_write(int sa, boost::python::list& ns);
    std::vector<unsigned char> i2c_read(int sa, int sz);
    void wait(int usec);

private:
    gnublin_i2c i2c;

    int errno_;
};

#endif
