CC = /opt/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc
LD = /opt/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-ld
LIB = /opt/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/arm-fsl-linux-gnueabi/multi-libs/lib
EXEC = main
OBJS = main.o
SRC  = main.c
 
CFLAGS += 
LDFLAGS += 
all:deploy
deploy:$(EXEC)
	@scp $(EXEC) root@192.168.0.3:/tmp 

$(EXEC):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lm
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -vf $(EXEC) *.o *~