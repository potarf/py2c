
all:
	g++ -fPIC -shared -Wl,-soname,py2c.so -o py2c.so --std=c++0x -I.. -I/usr/include/python2.7/ -L ../gnublin-api/ -lpython2.7 -lboost_python -lgnublin comInterfaceServer.cpp