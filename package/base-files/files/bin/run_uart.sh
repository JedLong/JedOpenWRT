#!/bin/sh /etc/rc.common
START=59

start() {
        tt=
        LOG=/var/pupauart_f.log
	touch /var/lock_cgi.file; chmod 777 /var/lock_cgi.file
	ulimit -c unlimited
	echo 1 > /proc/sys/kernel/core_uses_pid
        while [ "$tt" = "" ]
        do
                echo "Start uart "/dev/ttyS1" "9600"" >> $LOG
                uart -f "/dev/ttyS1" "9600" &
                sleep 1;
                tt=`ps |  grep 'uart -f /dev/ttyS1 9600' | grep -v grep`
                while [ -n "$tt" ]
                do
                        tt=`ps |  grep 'uart -f /dev/ttyS1 9600' | grep -v grep`
                        sleep 1;
                done
        done
}
