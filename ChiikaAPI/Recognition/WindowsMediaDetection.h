//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  Alperen Gezer
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along
//with this program; if not, write to the Free Software Foundation, Inc.,
//51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
//----------------------------------------------------------------------------
#ifndef __WindowsMediaDetection_h__
#define __WindowsMediaDetection_h__
//----------------------------------------------------------------------------
#include "Common/Required.h"
#include "MPRecognitionInterface.h"
#include "MediaPlayerList.h"
#include <Windows.h>
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	class WindowsMediaDetection : public MPRecognitionInterface
	{
	public:
		WindowsMediaDetection();
	//	void OnEvent(const QByteArray &eventType,void *message,long *);

	//	static BOOL CALLBACK EnumWindowProc(HWND hwnd,LPARAM lParam);

	//	void Detect();
	//	void StartTimer();
	//	void Tick();

	//	void OnMediaPlayerClosed();

	//	typedef std::pair<ChiString,ChiString> ClassValue;
	//	typedef std::map<HWND,ClassValue> WindowProperties;

	//	MediaPlayerList m_eDetectedMediaPlayer;

	//	QTimer* m_pTimer;
	//	bool m_bTimerRunning;

	//	bool m_bFoundMatch;

	//	HWND m_pHwnd;
	//	HWND GetHwnd();
	//	DWORD m_pThreadId;
	//	DWORD m_pProcessId;

	//	

	//private:
	//	void BsPlayerworkaround(); //Lol

	};
}


#endif // WINDOWSMEDIADETECTION_H
