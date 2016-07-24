#py2c#
###A simple i2c compatible library for python that just works.#

##Other libraries#
Other libraries like smbus or connect2wire feel the need to make the i2c interface more 'pythonic' or more 'intuitive.' But in their attempt to make the process simple for new users, they make an extremely simple protocol far too complicated.

##This library#
Should make it easy for someone who understands i2c to   simply use the library the way one would a C library, with no bullshit.

##History#
This code was written for a Raspberry Pi. It can be used in multiple ways, but its intended purpose was to recieve commands from a web socket, and the Pi had no other running processes.

##Requirements#
*This library has only been run on a Raspberry Pi, but may run on other platforms.
* Gnublin Api should be installed in the home directory
* Boost++ is necessary to compile the library.
* The Pi should be configured for i2c.

##Installation#
Once everything is set up, all you need to do is import py2c from a directory containing y2c.so.

##Use#
To use py2c in your python shell or script, first `import py2c`.
Then create a Bus object, using something like `bus = py2c.Bus()`.
The Bus() object has three member functions: `i2c_read()`, `i2c_write()`, and `wait()`.

####i2c_read()#
This function takes two arguments, the target i2c address and the number of bytes to read from that address. It returns a python list in which the first item is the error code, followed by the data read (each byte in integer form). An error code of 0 means the read appeared to be successful.

Format: `bus.i2c_read(address, numbytes)`.

####i2c_write()#
This function takes two arguments, the target i2c address and a python list of bytes to write to that address (in integer form). It returns an errorcode of 0 if the write appears successful.

Format: `bus.i2c_write(address, byteArray)`.

####wait()#
This function takes one argument, a number of microseconds to wait before sending the next i2c command. It does not return anything.

Format: `bus.wait(uSeconds)`.

