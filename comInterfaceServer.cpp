#include "comInterfaceServer.h"
#include <ctime>

#include <Python.h>
#include <boost/python.hpp>

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

RPiInterfaceServer::RPiInterfaceServer() : i2c()
{
}

void printCom(int err, int sa,  char buf[], int sz, char type, int i )
{

    FILE * out = stdout;
    if(err) 
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];
        time (&rawtime);
        timeinfo = localtime (&rawtime);

        strftime(buffer,80,"%F %X ",timeinfo);
        out = stderr;
        fprintf(out, buffer);
    }
    fprintf(out,"%c: %02x i: %d err:%d val:",type,sa,i,err);
    for(int j =0; j < sz; j++)
    {
        if(err) buf[j] = 0x00;
        fprintf(out,"%02x ", buf[j]);
    }
    fprintf(out,"\n");

    fflush(out);
}

int RPiInterfaceServer::i2c_write(int sa, boost::python::list& ns)
{
    const int size = boost::python::len(ns);
    
    char* buf = new char[size];

    for(int j = 0; j < size; ++j) buf[j] = boost::python::extract<unsigned char>(ns[j]);

    int i = 0;
    do
    {
        i2c.setAddress(sa);
        i2c.send((unsigned char *)buf, size);
        errno_ = i2c.fail();
    } while ((errno_) && ++i < 19 && !usleep((i < 10)?1000:10000));

    printCom(errno_,sa, buf,size,'w', i);

    return errno_;
}

std::vector<unsigned char> RPiInterfaceServer::i2c_read(int sa, int sz)
{
    char* buf = new char[sz+1];

    int i = 0;
    do
    {
        i2c.setAddress(sa);
        i2c.receive((unsigned char *)buf, sz);

        errno_ = i2c.fail();
    } while (errno_ && ++i < 19 && !usleep((i < 10)?1000:10000));

    printCom(errno_,sa, buf,sz,'r', i);

    std::vector<unsigned char> retval;

    for(int i = 0; i < sz; ++i) retval.push_back(static_cast<unsigned char>(buf[i]));

    delete [] buf;

    return retval;
}

void RPiInterfaceServer::wait(int usec)
{
    usleep(usec);
}

BOOST_PYTHON_MODULE(RPiInterfaceServer)
{
    using namespace boost::python;

    class_<std::vector<unsigned char>>("CharList").def(vector_indexing_suite<std::vector<unsigned char>>() );

    class_<RPiInterfaceServer>("RPiInterfaceServer").def("i2c_write", &RPiInterfaceServer::i2c_write).def("i2c_read", &RPiInterfaceServer::i2c_read).def("wiite", &RPiInterfaceServer::wait);
}
