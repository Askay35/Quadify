#pragma once
typedef unsigned int uint;
typedef unsigned char uint8;
typedef unsigned char byte;
typedef unsigned short uint16;
//typedef unsigned int uint32;
//typedef unsigned long long uint64;

uint16 u8to16(uint8 arr[2]) {
	return arr[1] | (arr[0] << 8);
}