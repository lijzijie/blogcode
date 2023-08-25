# Makefile
TARGETNAME = test
OBJ        = $(TARGETNAME).o
MODULE     = $(TARGETNAME).ko
obj-m += $(OBJ)

all:
	make -j $(nproc) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	@modprobe -r $(TARGETNAME)
	@install $(MODULE) /lib/modules/$(shell uname -r)/kernel/drivers/hid
	@depmod
	@modprobe $(TARGETNAME)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

