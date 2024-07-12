obj-m += hello1.o hello2.o 

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

insmod:
	sudo insmod hello1.ko
	sudo insmod hello2.ko

rmmod:
	sudo rmmod hello2
	sudo rmmod hello1 
