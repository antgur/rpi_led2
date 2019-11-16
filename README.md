Project based on RaspPi for driving LCD matrix 

main.c - the main server working as system service. It waiting for clients
	TCP connection on port 4441.
client.c - client service which is activating when client is connected.
srvlog.c - log creation part. It writing logs to /var/log/Month/Year/Day.log
It creates necessary folders if such folder missing at the software start.
ipc.c - procedure dedicated to access variables located in IPC section

build - script for execution module creation.

Software action.
Software starting as system service which is waiting for the client side TCP
connection. If second client connects at the time of managing first client
then second client management informs via IPC variable correction LCD blinking
period.


