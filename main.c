#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

int main(void) {

	DDRE = 0xFF;
	DDRB = 0xFF;
	PORTE = 0xFF;
	PORTB = 0xFF;
	
	char* p1Type = "square"; // TYPE (sin, square, triangle)
	char* p2Type = "triangle"; // TYPE
	
	int p1 = 0;
	int p2 = 0;
	
	int counter = 0;
	
	int p1realfreq = 50000; // FREQ
	int p2realfreq = 2; // FREQ (5000)
	
	int p1freq = (101 - p1realfreq) / 10;
	int p2freq = (101 - p2realfreq) / 10;
	
	int p1angle = 0; // OFFSET
	int p1ampl = 2; // AMPL
	int p1i = 0;
	
	int p2angle = 0; // OFFSET (147)
	int p2ampl = 3; // AMPL
	int p2i = 0;
	
	while(1) {
		if (counter % p1freq >= 0 && counter % p1freq < 0.00005) {
			if (p1Type == "sin") {
				if (p1i == (51*p1ampl)) p1i = 0;
				else p1i++;
				
				p1 = 50*sin(p1angle*3.141/180);
				p1 = (51*p1ampl)/2 -p1;
				p1angle += 7;
			}
			if (p1Type == "square") {
				if (p1 == 0) p1 = p1ampl*51;
				else p1 = 0;
			}
			if (p1Type == "triangle") {
				if (p1 == 255) p1 = 0;
				else p1++;
			}
		}
		
		if (counter % p2freq >= 0 && counter % p2freq < 0.00005) {
			if (p2Type == "sin") {
				if (p2i == (51*p2ampl)) p2i = 0;
				else p2i++;
				
				p2 = 50*sin(p2angle*3.141/180);
				p2 = (51*p2ampl)/2 -p2;
				p2angle += 7;
			}
			if (p2Type == "square") {
				if (p2 == 0) p2 = p2ampl*51;
				else p2 = 0;
			}
			if (p2Type == "triangle") {
				if (p2 == 255) p2 = 0;
				else p2++;
			}
		}
	
		
		generate(p1, p2);
		_delay_us(1);
		counter++;
	}

}

void generateSquare(int channel, int freq, int ampl) {
	if (channel == 2) PORTB = 0;
	if (channel == 1) PORTE = 0;
	_delay_ms(freq/2);
	PORTB = 51*ampl;
	if (channel == 2) PORTB = 51*ampl;
	if (channel == 1) PORTE = 51*ampl;
	_delay_ms(freq/2);
}

void generateSin(int channel, int freq, int ampl) {

	int angle = 0;
	for (int i = 0; i < (51*ampl); i++) {
	
		int y = 50*sin(angle*3.141/180);
		y = (51*ampl)/2 -y;
		generate(y, 0);
		_delay_ms(1/freq);
		angle += 7;
	
	}

}

void generate(int p1, int p2) {
	PORTE = p1;
	PORTB = p2;
}