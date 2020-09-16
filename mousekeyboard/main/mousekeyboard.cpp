#include "pch.h"
#include <iostream>
#include <algorithm> 
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono> 
#include "SerialPort.h"


using namespace std::chrono;
using namespace std;

char output[MAX_DATA_LENGTH];
char incoming[MAX_DATA_LENGTH];
int sensitivity_level = 1;
int function_page = 0;

//--- array to store activation values of buttons 
bool activate[20] = { true };


void delay(int number_of_seconds);
int return_btn_val(string button_name);
int return_x_joystick();
int return_y_joystick();
void mouse_move(int sensitivity_level);
void scroll();
void scroll_arrow();
void command_activate(string button_name, string command);
void key_list(string command);


int main()
{	
	//--- search for ports
	bool connection_established = false;
	int portnum = 0;
	char portname[20];
	const char *port = portname;
	

	//arduino object
	SerialPort arduino;
	SerialPort *ptr_arduino = &arduino;

	cout << "Keyboard by Maciej Zajaczkowski" << endl;

	int search_method = 1;
	cout << "Choose COM port search method" << endl;
	cout << "0 - Manual" << endl;
	cout << "1 - Automatic" << endl;
	cin >> search_method;

	if (search_method == 1)
	{
		//brute force automatic port search
		while (connection_established == false)
		{
			sprintf_s(portname, "\\\\.\\COM%d", portnum);
			ptr_arduino->setSerialPort((char*)port);
			if (arduino.isConnected())
			{
				cout << "Connection established at COM";
				cout << portnum << endl;
				connection_established = true;
			}
			portnum++;

			//emergency loop break (if no device connected)
			if (portnum > 256)
			{
				cout << "ERROR, No Device Detected" << endl;
				return 0;
			}
		}
	}
	else if (search_method == 0)
	{
		//--- manual port search
		while (connection_established == false)
		{
			cout << "Insert COM port number (-1 for Quit Program)" << endl;
			cout << "COM";
			cin >> portnum;
			if (portnum < 0) { return 0; }
			sprintf_s(portname, "\\\\.\\COM%d", portnum);
			ptr_arduino->setSerialPort((char*)port);
			if (arduino.isConnected())
			{
				cout << "Connection is established" << endl;
				connection_established = true;
			}
			else
			{
				cout << "Not connected, try again" <<endl;
			}
		}
	}
	
	
	while (arduino.isConnected())
	{
		//auto start = high_resolution_clock::now();
		
		
		//---write
		
		//string command;
		//command = "hi";
		////cin >> command;
		//char *charArray = new char[command.size() + 1];
		//copy(command.begin(), command.end(), charArray);
		//charArray[command.size()] = '\n';
		//arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);								

		//---read
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		cout << output;
		//cout << return_btn_val("BJ") <<endl;
		//cout << return_x_joystick() << endl;
		//cout << return_y_joystick() << endl;

		
	    //cout << return_btn_val("B3") <<endl;
		//mouse_move(sensitivity_level);

		//change function page
		if (return_btn_val("B9") == 1)
		{
			function_page++;
			if (function_page > 1)
			{
				function_page = 0;
			}
		}				
		

		if (function_page == 0)
		{
				scroll();
				command_activate("B1", "reopen_window");
				command_activate("B2", "change_colours");
				command_activate("B3", "open_chrome");
				command_activate("B4", "open_win_explorer");
				command_activate("B5", "open_calc");				
				command_activate("B6", "window_down");
				command_activate("B7", "close_window");				
				command_activate("B8", "find");	
		}
		else if (function_page == 1)
		{
				scroll_arrow();
				command_activate("B1", "go_back");
				command_activate("B2", "copy");
				command_activate("B3", "paste");
				command_activate("B4", "delete_word");
		}		

		

		//auto stop = high_resolution_clock::now();
		//auto duration = duration_cast<microseconds>(stop - start);
		//cout << duration.count() << endl;				

		//delete [] charArray;

		delay(62.5);
	}

	return 0;
}



void key_list(string command)
{
	if (command == "change_colours")
	{
		//ctrl + window + c
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x5B, 0, 0x0000, 0);
		keybd_event(0x43, 0, 0x0000, 0);
		keybd_event(0x43, 0, 0x0002, 0);
		keybd_event(0x5B, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "reopen_window")
	{
		//ctrl + shift + T
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x10, 0, 0x0000, 0);
		keybd_event(0x54, 0, 0x0000, 0);
		keybd_event(0x54, 0, 0x0002, 0);
		keybd_event(0x10, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "copy")
	{
		//ctrl + C
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x43, 0, 0x0000, 0);
		keybd_event(0x43, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "paste")
	{
		//ctrl + V
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x56, 0, 0x0000, 0);
		keybd_event(0x56, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "window_down")
	{
		//win + D
		keybd_event(0x5B, 0, 0x0000, 0);
		keybd_event(0x44, 0, 0x0000, 0);
		keybd_event(0x44, 0, 0x0002, 0);
		keybd_event(0x5B, 0, 0x0002, 0);
	}
	else if (command == "close_window")
	{
		//ctrl + W
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x57, 0, 0x0000, 0);
		keybd_event(0x57, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "delete_word")
	{
		//ctrl + backspace
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x08, 0, 0x0000, 0);
		keybd_event(0x08, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "find")
	{
		//ctrl + F
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x46, 0, 0x0000, 0);
		keybd_event(0x46, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "go_back")
	{
		//ctrl + Z
		keybd_event(0x11, 0, 0x0000, 0);
		keybd_event(0x5A, 0, 0x0000, 0);
		keybd_event(0x5A, 0, 0x0002, 0);
		keybd_event(0x11, 0, 0x0002, 0);
	}
	else if (command == "open_chrome")
	{
		system("start chrome");	
	}
	else if (command == "open_calc")
	{
		system("start calc");
	}
	else if (command == "open_win_explorer")
	{
		system("start explorer");
	}
}

void command_activate(string button_name, string command)
{
	char transfer = button_name[1];

	if (activate[atoi(&transfer) - 1] == true)
	{
		if (return_btn_val(button_name) == 1)
		{
			key_list(command);
		}
		activate[atoi(&transfer) - 1] = false;
	}

	if (return_btn_val(button_name) == false)
	{
		activate[atoi(&transfer) - 1] = true;
	}
}

void scroll_arrow()
{
	double x_joystick = return_x_joystick();
	double y_joystick = return_y_joystick();
	x_joystick /= 5.5;
	y_joystick /= 5.5;

	//vertical scroll
	if (x_joystick < 0)
	{
		keybd_event(0x25, 0, 0x0000, 0);
		keybd_event(0x25, 0, 0x0002, 0);
	}
	if (x_joystick > 0)
	{
		keybd_event(0x27, 0, 0x0000, 0);
		keybd_event(0x27, 0, 0x0002, 0);
	}


	//horizontal scroll
	if (y_joystick < 0)
	{
		keybd_event(0x28, 0, 0x0000, 0);		
		keybd_event(0x28, 0, 0x0002, 0);
	}
	if (y_joystick > 0)
	{
		keybd_event(0x26, 0, 0x0000, 0);
		keybd_event(0x26, 0, 0x0002, 0);
	}

}

void scroll()
{
	double x_joystick = return_x_joystick();
	double y_joystick = return_y_joystick();
	x_joystick /= 5.5;
	y_joystick /= 5.5;

	y_joystick *= (-1);

	//senstivity adjust		
	if (return_btn_val("BJ") == 1)
	{
		sensitivity_level += 3;
	}
	if (sensitivity_level > 4)
	{
		sensitivity_level = 1;
	}
	//cout << sensitivity_level << endl;

	//vertical scroll
	if (x_joystick < 0)
	{
		mouse_event(0x0800, 0, 0, (int)x_joystick*sensitivity_level, 0);
	}
	if (x_joystick > 0)
	{
		mouse_event(0x0800, 0, 0, (int)x_joystick*sensitivity_level, 0);
	}
	if (x_joystick == 0)
	{
		mouse_event(0x0800, 0, 0, 0, 0);
	}

	//horizontal scroll
	if (y_joystick > 0)
	{
		keybd_event(0x10, 0, 0x0000, 0);
		mouse_event(0x0800, 0, 0, (int)y_joystick*sensitivity_level, 0);
		keybd_event(0x10, 0, 0x0002, 0);
	}
	if (y_joystick < 0)
	{
		keybd_event(0x10, 0, 0x0000, 0);
		mouse_event(0x0800, 0, 0, (int)y_joystick*sensitivity_level, 0);
		keybd_event(0x10, 0, 0x0002, 0);
	}
	if (y_joystick == 0)
	{
		keybd_event(0x10, 0, 0x0000, 0);
		mouse_event(0x0800, 0, 0, 0, 0);
		keybd_event(0x10, 0, 0x0002, 0);
	}
}

void mouse_move(int sensitivity_level)
{
	//mouse move
	POINT point;
	GetCursorPos(&point);
	int mouse_sensitivity = pow(10, sensitivity_level);
	int x_joystick = return_x_joystick();
	int y_joystick = return_y_joystick();
	double new_x = point.x;
	double new_y = point.y;
	new_x /= 1535;
	new_y /= 863;
	new_x *= 65535;
	new_y *= 65535;

	if (x_joystick > 0)
	{
		new_x += mouse_sensitivity;
		mouse_event(0x8000 | 0x0001, new_x, new_y, 0, 0);
	}
	if (x_joystick < 0)
	{
		new_x -= mouse_sensitivity;
		mouse_event(0x8000 | 0x0001, new_x, new_y, 0, 0);
	}
	if (y_joystick > 0)
	{
		new_y += mouse_sensitivity;
		mouse_event(0x8000 | 0x0001, new_x, new_y, 0, 0);
	}
	if (y_joystick < 0)
	{
		new_y -= mouse_sensitivity;
		mouse_event(0x8000 | 0x0001, new_x, new_y, 0, 0);
	}
}

void delay(int milli_seconds)
{

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds);
}

int return_btn_val(string button_name)
{
	char B[2];
	int pos = 0;
	int value = 0;
	int n = 0;

	B[0] = button_name[0];
	B[1] = button_name[1];

	for (n = 0; n < sizeof(output) - 1; n++)
	{
		if (output[n] == B[0] && output[n + 1] == B[1])
		{
			pos = n;
		}
	}
	//adjust to value position (general format BX:'val')
	pos += 3;

	value = output[pos];

	if (output[pos] == '1')
		value = 1;
	else
		value = 0;

	return value;
}

int return_x_joystick()
{
	int n = 0;
	int pos = 0;
	int value;
	for (n = 0; n < sizeof(output) - 1; n++)
	{
		if (output[n] == 'X' && output[n + 1] == 'J')
		{
			pos = n;
		}
	}
	pos += 3;

	value = atoi(&output[pos + 1]);
	if (output[pos] == '-')
	{
		value *= -1;
	}
	return value;
}

int return_y_joystick()
{
	int n = 0;
	int pos = 0;
	int value;
	for (n = 0; n < sizeof(output) - 1; n++)
	{
		if (output[n] == 'Y' && output[n + 1] == 'J')
		{
			pos = n;
		}
	}
	pos += 3;

	value = atoi(&output[pos + 1]);
	if (output[pos] == '-')
	{
		value *= -1;
	}
	return value;
}

