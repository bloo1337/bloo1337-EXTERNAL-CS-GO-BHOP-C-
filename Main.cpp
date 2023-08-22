#include <iostream>  //COMPILE IN X86
#include <Windows.h> //USE MULTIBYTE CHARACTER SET, IF YOU DONT KNOW HOW, YOU GOT THE INTERNET
#include "MemMan.h"

MemMan bloo;

struct offsets {
	DWORD lplayer; // PUT YOUR OFFSETS HERE
	DWORD fjump;   // PUT YOUR OFFSETS HERE
	DWORD flags;   // PUT YOUR OFFSETS HERE


}offsets;


struct {
	DWORD localplayer;
	DWORD process;
	DWORD gameModule;
	DWORD flag;

}val;


int main()
{
	val.process = bloo.getProcess("csgo.exe");
	val.gameModule = bloo.getModule(val.process, "client_dll");

	val.localplayer = bloo.readMem<DWORD>(val.gameModule + offsets.lplayer);

	if (val.localplayer == NULL)
	{
		while (val.gameModule == NULL) {
			val.localplayer = bloo.readMem<DWORD>(val.gameModule + offsets.lplayer);
		}
	}

	while (true)
	{
		val.flag = bloo.readMem<BYTE>(val.localplayer + offsets.flags);

		if (GetAsyncKeyState(VK_SPACE) && val.flag & (1 << 0)) {
			bloo.writeMem(val.gameModule + offsets.fjump, 6);

		}
		Sleep(1);
	}
	return 0;
}