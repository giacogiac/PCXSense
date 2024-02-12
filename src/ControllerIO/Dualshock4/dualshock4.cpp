#include "dualshock4.h"
#include <tchar.h>
#include "User Settings/Adaptive Triggers/Adaptive Triggers.h"
#include "User Settings/Game Profiles/gameProfile.h"

extern bool gameProfileSet;

extern "C" int returnSmaller(int x); //Assembly Function in src/Assembly Functions/assemblyFunctions.s
constexpr DWORD TITLE_SIZE = 1024;

void inline static setButtons(controller& x360Controller) {
	//std::cout << (short)(((x360Controller.inputBuffer[39] & 0x0f) << 8) | x360Controller.inputBuffer[38]) << '\n'; //X
	//std::cout << x360Controller.inputBuffer[40] << '\n'; //Y

	// Normal Order
	x360Controller.ControllerState.Gamepad.wButtons = (bool)(x360Controller.inputBuffer[7] & (1 << 4)) ? XINPUT_GAMEPAD_X : 0; //Square

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 5)) ? XINPUT_GAMEPAD_A : 0; //Cross

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 6)) ? XINPUT_GAMEPAD_B : 0; //Circle

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 7)) ? XINPUT_GAMEPAD_Y : 0; //Triangle

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 0)) ? XINPUT_GAMEPAD_LEFT_SHOULDER : 0; //Left Shoulder

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 1)) ? XINPUT_GAMEPAD_RIGHT_SHOULDER : 0; //Right Shoulder

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 4)) ? XINPUT_GAMEPAD_BACK : 0; //Select

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 5)) ? XINPUT_GAMEPAD_START : 0; //Start

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 6)) ? XINPUT_GAMEPAD_LEFT_THUMB : 0; //Left Thumb

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 7)) ? XINPUT_GAMEPAD_RIGHT_THUMB : 0; //Right thumb
	//ControllerState.Gamepad.wButtons += joystick.rgbButtons[12] ? 0x0400 : 0; //Sony Button

	switch ((int)(x360Controller.inputBuffer[7] & 0x0F)) {
	case 0: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP; break;

	case 1: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP + XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 2: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 3: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN + XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 4: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN; break;

	case 5: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN + XINPUT_GAMEPAD_DPAD_LEFT; break;

	case 6: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_LEFT; break;

	case 7: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP + XINPUT_GAMEPAD_DPAD_LEFT; break;

	}

}


void inline static setButtonsGameProfile(controller& x360Controller) {
	extern int buttonMapping[12];

	// Normal Order
	x360Controller.ControllerState.Gamepad.wButtons = (bool)(x360Controller.inputBuffer[7] & (1 << 4)) ? buttonMapping[0] : 0; //Square

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 5)) ? buttonMapping[1] : 0; //Cross

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 6)) ? buttonMapping[2] : 0; //Circle

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[7] & (1 << 7)) ? buttonMapping[3] : 0; //Triangle

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 0)) ? buttonMapping[4] : 0; //Left Shoulder

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 1)) ? buttonMapping[5] : 0; //Right Shoulder

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 4)) ? buttonMapping[6] : 0; //Select

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 5)) ? buttonMapping[7] : 0; //Start

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 6)) ? buttonMapping[8] : 0; //Left Thumb

	x360Controller.ControllerState.Gamepad.wButtons += (bool)(x360Controller.inputBuffer[8] & (1 << 7)) ? buttonMapping[9] : 0; //Right thumb
	//ControllerState.Gamepad.wButtons += joystick.rgbButtons[12] ? 0x0400 : 0; //Sony Button

	if (buttonMapping[10] == 1) {

		switch ((int)(x360Controller.inputBuffer[7] & 0x0f)) {

		case 0: x360Controller.ControllerState.Gamepad.sThumbLY = 32767; break; //Up

		case 1: x360Controller.ControllerState.Gamepad.sThumbLY = 29727; x360Controller.ControllerState.Gamepad.sThumbLX = 19403; break; //Up Right

		case 2: x360Controller.ControllerState.Gamepad.sThumbLX = 32767; break; //Right

		case 3: x360Controller.ControllerState.Gamepad.sThumbLY = -29727; x360Controller.ControllerState.Gamepad.sThumbLX = 19403; break; //Down Right

		case 4: x360Controller.ControllerState.Gamepad.sThumbLY = -32768; break; //Down

		case 5: x360Controller.ControllerState.Gamepad.sThumbLY = -29727; x360Controller.ControllerState.Gamepad.sThumbLX = -22223; break; //Down Left

		case 6: x360Controller.ControllerState.Gamepad.sThumbLX = -32768; break; //Left

		case 7: x360Controller.ControllerState.Gamepad.sThumbLY = 29727; x360Controller.ControllerState.Gamepad.sThumbLX = -22223; break; //Up Left
		}
		return;
	}

	switch ((int)(x360Controller.inputBuffer[7] & 0x0F)) {
	case 0: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP; break;

	case 1: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP + XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 2: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 3: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN + XINPUT_GAMEPAD_DPAD_RIGHT; break;

	case 4: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN; break;

	case 5: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_DOWN + XINPUT_GAMEPAD_DPAD_LEFT; break;

	case 6: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_LEFT; break;

	case 7: x360Controller.ControllerState.Gamepad.wButtons += XINPUT_GAMEPAD_DPAD_UP + XINPUT_GAMEPAD_DPAD_LEFT; break;

	}
}

void inline getDualShock4Input(controller& x360Controller) {

	bool readSuccess = ReadFile(x360Controller.deviceHandle, x360Controller.inputBuffer, x360Controller.bufferSize, NULL, NULL);

	if (!readSuccess) {
		CloseHandle(x360Controller.deviceHandle);
		while (!isControllerConnected(x360Controller)) {}
		return;
	}

	/*for (int i = 0; i < 78; i++)
		std::cout << i << ": " << (uint32_t)x360Controller.inputBuffer[i] << '\n';
	system("cls");
	Sleep(5);*/

	x360Controller.batteryLevel = (x360Controller.inputBuffer[32] & 15) * 12.5; /* Hex 0x35 (USB) to get Battery / Hex 0x36 (Bluetooth) to get Battery
																											  because if bluetooth == true then bluetooth == 1 so we can just add bluetooth
																											  to the hex value of USB to get the battery reading
																										   */

																										   //Because of a bug on the Dualsense HID this needs to be implemented or else battery might display higher than 100 %
	x360Controller.batteryLevel = returnSmaller(x360Controller.batteryLevel);

	x360Controller.ControllerState.Gamepad.sThumbLX = ((x360Controller.inputBuffer[3] * 257) - 32768);
	x360Controller.ControllerState.Gamepad.sThumbLY = (32767 - (x360Controller.inputBuffer[4] * 257));
	x360Controller.ControllerState.Gamepad.sThumbRX = ((x360Controller.inputBuffer[5] * 257) - 32768);
	x360Controller.ControllerState.Gamepad.sThumbRY = (32767 - (x360Controller.inputBuffer[6] * 257));

	x360Controller.ControllerState.Gamepad.bLeftTrigger = x360Controller.inputBuffer[10];
	x360Controller.ControllerState.Gamepad.bRightTrigger = x360Controller.inputBuffer[11];

	if (gameProfileSet) {
		setButtonsGameProfile(x360Controller);
		return;
	}

	setButtons(x360Controller);

}
void sendDualShock4OutputReport(controller& x360Controller) {

	unsigned char outputHID[574]{};
	extern bool profileOpen;
	extern bool lightbarOpen;
	extern bool profileEdit;

	while (true) {
		Sleep(1);

		ZeroMemory(outputHID, 0);

		outputHID[0] = 0x11;
		outputHID[1] = (byte)(0xC0);
		
		outputHID[3] = 0x07;
		outputHID[4] = 0x04;

		outputHID[6] = rumble[0]; //Low Rumble
		outputHID[7] = rumble[1]; //High Rumble

		switch (x360Controller.batteryLevel + lightbarOpen + gameProfileSet + profileEdit) { //Chooses Lightbar Profile, if any of those editors are open then it breaks and sets itself to the currently being edited profile
		case 0: x360Controller.RGB[0].Index = 1; break;
		case 12: x360Controller.RGB[0].Index = 2; break;
		case 25: x360Controller.RGB[0].Index = 3; break;
		case 37: x360Controller.RGB[0].Index = 4; break;
		case 50: x360Controller.RGB[0].Index = 5; break;
		case 62: x360Controller.RGB[0].Index = 6; break;
		case 75: x360Controller.RGB[0].Index = 7; break;
		case 87: x360Controller.RGB[0].Index = 8; break;
		case 100: x360Controller.RGB[0].Index = 9; break;
		default: break;
		}

		//LightEditorOpened:

		//	outputHID[9 + x360Controller.bluetooth] = x360Controller.RGB[x360Controller.RGB[0].Index].microhponeLed;
		//	outputHID[39 + x360Controller.bluetooth] = 0x02;
		//	outputHID[42 + x360Controller.bluetooth] = 0x02;
		//	outputHID[43 + x360Controller.bluetooth] = 0x02;


		for (int i = 0; i < 3; i++) {
			outputHID[8 + i] = x360Controller.RGB[x360Controller.RGB[0].Index].colors[i] * 255;
			x360Controller.RGB[0].colors[i] = x360Controller.RGB[x360Controller.RGB[0].Index].colors[i];
		}

		//Send Output Report

		const UINT32 crc = computeCRC32(outputHID, 74);

		outputHID[74] = (crc & 0x000000FF);
		outputHID[75] = ((crc & 0x0000FF00) >> 8UL);
		outputHID[76] = ((crc & 0x00FF0000) >> 16UL);
		outputHID[77] = ((crc & 0xFF000000) >> 24UL);

		WriteFile(x360Controller.deviceHandle, outputHID, 334, NULL, NULL);
			

	}
}