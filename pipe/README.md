Usage:

root@ubuntu:/ipc/pipe# ./pipe
PARENT: Begin to fork child...
PARENT: Call client...
CLIENT: Pls input pathname to read
CHILD: Call server...
SERVER: read pathname from readfd

/ipc/pipe/testfile [This is the input]

This is a testfile.
root@ubuntu:/ipc/pipe# ./pipe
PARENT: Begin to fork child...
PARENT: Call client...
CLIENT: Pls input pathname to read
CHILD: Call server...
SERVER: read pathname from readfd

file [This is the input]

file: can't open No such file or directory

