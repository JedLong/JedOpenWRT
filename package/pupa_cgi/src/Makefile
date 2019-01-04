CC=/home/ljd/jedOpenWRT/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/bin/mipsel-openwrt-linux-gcc
#CC=gcc
#(CC) -o $@ $^  -lm -g -gdwarf-2 -g3 -std=c99
#objects=log.c cJSON.c common.c protocol.c cgi_devices.c cgi_displays.c cgi_motor_fan.c cgi_temp_sensor.c  #temp_sensor.o display.c motor_fan.o
CFLAGS  =      -g -gdwarf-2 -g2
LDFLAGS =   -lm
OBJS =log.o cJSON.o common.o protocol.o cgi_devices.o cgi_displays.o cgi_motor_fan.o cgi_temp_sensor.o main.o  #temp_sensor.o display.c motor_fan.o
#protocol.cgp: $(objects) main.c
#	$(CC) -o $@ $^  -lm -g  

#..c.o:
#	$(CC)-c -g $< 
.c.o:
	$(CC) -c $*.c $(CFLAGS) $(IFLAGS)

protocol.cgp: $(OBJS)
	$(CC) -o protocol.cgp $(OBJS) $(LINK) $(LDFLAGS) $(LIBS)

clean:
	-rm protocol.cgp *.o *.swp
