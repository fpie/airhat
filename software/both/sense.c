/* sense - serial air quality sensors reader
 * Copyright (C) 2016 Frederic Pierson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char **argv) {
	char SerialPort0[]="/dev/ttySC0";
	char SerialPort1[]="/dev/ttySC1";
	char mhz14_read_cmd[]="\377\001\206\000\000\000\000\000\171";
	int port0, port1,i;
	char buffer[10];
	float ppm2dot5, ppm10, co2;
	
	if (!(port0=open(SerialPort0, O_RDWR))) {
		printf("Error opening %s, exit.", SerialPort0);
		exit(1);
	}
	else if (!(port1=open(SerialPort1, O_RDWR))) {
		printf("Error opening %s, exit.", SerialPort1);
		close(port0);
		exit(1);
	}
	else {
		do {
			/* Blank ternminal */
			printf("\033c");
			
			/* Trigger a mzh14 sensor read command */
			write(port0,mhz14_read_cmd,sizeof(mhz14_read_cmd));
			read(port0,buffer,9);
			printf("%s : ",SerialPort0); 
			for(i=0;i<9;i++) {
				printf("%2.2X ",buffer[i]);
			}
			printf("\n");
			co2=(float)(((int)buffer[2]*256)+(int)buffer[3]);
			printf("CO2 = %4.1f ppm\n",co2);
			printf("\n");
			
			
			/* Synchonise SDS021 buffer */
			do {
				read(port1,buffer,1);
			}while(buffer[0]!=0xAA);
			read(port1,buffer+1,9);

			printf("%s : ",SerialPort1); 
			for(i=0;i<10;i++) {
				printf("%2.2X ",buffer[i]);
			}
			printf("\n");
						
			ppm2dot5=(float)(((int)buffer[3]*256)+(int)buffer[2])/10.0;
			ppm10=(float)(((int)buffer[5]*256)+(int)buffer[4])/10.0;
			
			printf("ppm2.5 = %3.1f µg/m3\n",ppm2dot5);
			printf("ppm10  = %3.1f µg/m3\n",ppm10);
			sleep(1);
		}while(!read(0,NULL,0));
	}
	close(port0);
	close(port1);
	return 0;
}
