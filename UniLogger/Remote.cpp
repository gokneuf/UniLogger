//#include "stdafx.h"
#include "Remote.h"
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

#define BUFSIZE MAX_PATH
//#define UNICODE 
#define FILENAME "sdrsharptrunking.log"
// sdrsharptrunking.log can be used with Trunking Recorder
//#define FILENAME "remote_trunking.log"
char   FullLogFileName[MAX_PATH] = {0};
//WCHAR   DllPath[MAX_PATH] = {0};

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
	switch ( ul_reason_for_call )
	{
		case 1: /* DLL_PROCESS_ATTACH */
			char path[MAX_PATH];
			HMODULE hm = NULL;
			unsigned int i;
			int base_path_end = 0;

			if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
				GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
					(LPCSTR) &Park, &hm))
			{
				int ret = GetLastError();
				fprintf(stderr, "GetModuleHandle returned %d\n", ret);
			}
			GetModuleFileNameA(hm, path, sizeof(path));
			for(i=0;i<strlen(path);i++) {
				if(path[i] == '\\')
					base_path_end=i;
			}
			path[base_path_end+1] = '\0';
			strcpy_s(FullLogFileName,path);
			strcat_s(FullLogFileName,FILENAME);
			//MessageBox( NULL, TEXT("Hello World"), 
			//path, MB_OK);
  
		break;
		//case DLL_THREAD_ATTACHED:
		// A process is creating a new thread.
		//break;
		//case DLL_THREAD_DETACH:
		// A thread exits normally.
		//break;
		//case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		//break;
	}
	return TRUE;
}
/*
Called when a voice role receiver is idle.
The arguments are guaranteed to remain stable for the duration of the function call.
However, the called function should return ASAP to prevent blocking the application.
rx - receiver to park on a voice channel.
ch - conventional voice channel (_site is likely NULL).
*/
void Park(const RX *rx, const Channel *ch)
{
	Log("Park", rx, ch, NULL, NULL);
}

/*
Called when a signal role receiver follows a control channel.
The arguments are guaranteed to remain stable for the duration of the function call.
However, the called function should return ASAP to prevent blocking the application.
rx - receiver chasing a control channel.
ch - control channel
*/
void Control(const RX *rx, const Channel *ch)
{
	Log("Control", rx, ch, NULL, NULL);
}

/*
Called when a voice role receiver follows a voice channel.
The arguments are guaranteed to remain stable for the duration of the function call.
However, the called function should return ASAP to prevent blocking the application.
rx - receiver chasing a voice channel.
ch - voice channel
src - speaking party with radio ID.
tgt - audience party (may be a talkgroup or radio).
*/
void Listen(const RX *rx, const Channel *ch, const Address *src, const Address *tgt)
{
	Log("Listen", rx, ch, src, tgt);
}

void Log(char* action, const RX *rx, const Channel *ch, const Address *src, const Address *tgt)
{
	ofstream logfile;
	logfile.open(FullLogFileName);
	logfile << "action\treceiver\tfrequency\ttargetid\ttargetlabel\tsourceid\tsourcelabel\tlcn\tvoiceservice\tsystemid\tsystemlabel\n";
	logfile << action << "\t" << rx->_label << "\t" << ch->_Hz;

	//Add target info if set
	if (tgt != NULL) {
		//Verify source ID is set
		if (tgt->_ID != NULL)
		{
			logfile << "\t" << tgt->_ID;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
		//Verify source label is set
		if (tgt->_label != NULL)
		{
			logfile << "\t" << tgt->_label;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
	}
	else
	{
		//Add blanks to keep file consistent
		logfile << "\t\t";
	}

	//Add source info if set
	if (src != NULL) {
		//Verify source ID is set
		if (src->_ID != NULL)
		{
			logfile << "\t" << src->_ID;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
		//Verify source label is set
		if (src->_label != NULL)
		{
			logfile << "\t" << src->_label;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
	}
	else
	{
		//Add blanks to keep file consistent
		logfile << "\t\t";
	}

	//Add LCN if set
	if (ch != NULL) {
		//Verify LCN is set
		if (ch->_ID != NULL)
		{
			logfile << "\t" << ch->_ID;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
	}
	else
	{
		//Add blanks to keep file consistent
		logfile << "\t";
	}

	//Add Voice service if set
	if (ch != NULL) {
		//Verify LCN is set
		if (ch->_service != NULL)
		{
			logfile << "\t" << ch->_service;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
	}
	else
	{
		//Add blanks to keep file consistent
		logfile << "\t";
	}

	//Add System info if set
	if (ch->_site != NULL && ch->_site->_system != NULL){
		//Verify system ID is set
		if (ch->_site->_system->_ID != NULL)
		{
			logfile << "\t" << ch->_site->_system->_ID;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
		//Verify system label is set
		if (ch->_site->_system->_label != NULL)
		{
			logfile << "\t" << ch->_site->_system->_label;
		}
		else
		{
			//Add a blank to keep file consistent
			logfile << "\t";
		}
	}
	else
	{
		//Add blanks to keep file consistent
		logfile << "\t\t";
	}

	logfile << "\n";
	logfile.close();
}
