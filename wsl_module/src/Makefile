# Makefile
TARGETNAME = test
OBJ        = $(TARGETNAME).o
MODULE     = $(TARGETNAME).ko
obj-m += $(OBJ)

all:
	make -j $(nproc) -C ~/WSL2-Linux-Kernel M=$(PWD) modules

install:
	@modprobe -r $(TARGETNAME)
	@install $(MODULE) ~/WSL2-Linux-Kernel/kernel/drivers/hid
	@depmod
	@modprobe $(TARGETNAME)
clean:
	make -C ~/WSL2-Linux-Kernel M=$(PWD) clean
