Notes:
FIFO can be used among processes without any relations (i.e., no need to be parent and child)


Usages:

1 Start server

	root@ubuntu:/ipc/fifo# ./server 
	SERVER: Begin to make fifo 1...
	SERVER: Begin to make fifo 2...
	SERVER: Read & Write
	SERVER: read pathname from readfd
	root@ubuntu:/ipc/fifo# 


2 Start client

	root@ubuntu:/ipc/fifo# ./client 
	CLIENT: Pls input pathname to read
	
	/ipc/fifo/testfile [This is the input]
	
	This is a testfile.

