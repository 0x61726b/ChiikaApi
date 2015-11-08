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
#include "Stable.h"
#include "Recognition/WindowsMediaDetection.h"
#include "Recognition/AnimeRecognition.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	typedef Map<MediaPlayerList,ChiString>::type MediaPlayerClassNameMap;
	MediaPlayerClassNameMap ClassNames =
	{
		MediaPlayerClassNameMap::value_type(MPC,"MediaPlayerClassicW"),
		MediaPlayerClassNameMap::value_type(VLC,"QWidget"),
		MediaPlayerClassNameMap::value_type(BSPlayer,"TApplication"),
		MediaPlayerClassNameMap::value_type(BSPlayerWindow,"CabinetWClass")
	};
}
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	////Globals
	//HWND g_pDetectedWindow = NULL;
	//HWINEVENTHOOK g_hook = NULL;
	//WindowsMediaDetection* m_pThis = NULL;
	////----------------------------------------------------------------------------
	//void CALLBACK WinEventProc(
	//	HWINEVENTHOOK hWinEventHook,
	//	DWORD         event,
	//	HWND          hwnd,
	//	LONG          idObject,
	//	LONG          idChild,
	//	DWORD         idEventThread,
	//	DWORD         dwmsEventTime)
	//{
	//	if(event == EVENT_OBJECT_DESTROY &&
	//		hwnd == g_pDetectedWindow &&
	//		idObject == OBJID_WINDOW &&
	//		idChild == INDEXID_CONTAINER)
	//	{
	//		UnhookWinEvent(g_hook);
	//		m_pThis->OnMediaPlayerClosed(); //call this before NULLing the window
	//		g_hook = NULL;
	//		g_pDetectedWindow = NULL;
	//		qDebug() << "Detected Window exited.";
	//	}
	//}
	////----------------------------------------------------------------------------
	//BOOL CALLBACK FindBSPlayer(HWND hwnd,LPARAM lParam)
	//{
	//	char text[128];
	//	::GetClassNameA(hwnd,text,sizeof(text));
	//	if(!strcmp(text,QToChar(ClassNames.find(BSPlayerWindow)->second)))
	//	{
	//		*(HWND*)lParam = hwnd;
	//		return FALSE;
	//	}
	//	return TRUE;
	//}
	////----------------------------------------------------------------------------
	//BOOL CALLBACK WindowsMediaDetection::EnumWindowProc(HWND hwnd,LPARAM lParam)
	//{
	//	char className[64];
	//	::GetClassNameA(hwnd,className,sizeof(className));

	//	char windowValue[256];
	//	GetWindowTextA(hwnd,windowValue,256);

	//	ClassValue cv;
	//	cv = std::make_pair(className,windowValue);


	//	WindowProperties* list = (WindowProperties*)lParam;
	//	list->insert(WindowProperties::value_type(hwnd,cv));
	//	lParam = (LPARAM)list;


	//	return true;
	//}
	//----------------------------------------------------------------------------
	WindowsMediaDetection::WindowsMediaDetection()
	{
		//m_bTimerRunning = false;
		//m_bFoundMatch = false;
		//m_pThis = this;
	}
	//----------------------------------------------------------------------------
	//void WindowsMediaDetection::Detect()
	//{
	//	if(g_pDetectedWindow)
	//	{
	//		char className[256];
	//		GetClassNameA(g_pDetectedWindow,className,256);

	//		char windowValue[256];
	//		GetWindowTextA(g_pDetectedWindow,windowValue,256);

	//		//Check if we know this window
	//		StdIt(MediaPlayerClassNameMap) It;
	//		ForEachOnStd(It,ClassNames)
	//		{
	//			if(It->second == ChiString::fromStdChiString(className))
	//			{
	//				if(ChiString::fromStdChiString(windowValue) == "BS.Player")
	//				{
	//					BsPlayerworkaround();
	//					qDebug() << "BS Player detected";
	//				}
	//				else
	//				{
	//					qDebug() << It->second << " detected " << windowValue;
	//				}
	//			}
	//		}

	//		//~


	//		ClassValue cv;
	//		cv = std::make_pair(className,windowValue);

	//		ShrPtr<WindowProperties> list = MakeShared<WindowProperties>();
	//		list->insert(WindowProperties::value_type(g_pDetectedWindow,cv));
	//		EnumChildWindows(g_pDetectedWindow,EnumWindowProc,(LPARAM)list.get());

	//		g_hook = SetWinEventHook(
	//			EVENT_OBJECT_DESTROY,EVENT_OBJECT_DESTROY,
	//			NULL,WinEventProc,
	//			m_pProcessId,m_pThreadId,WINEVENT_OUTOFCONTEXT); //No injection here
	//	}
	//	else
	//	{
	//		qDebug() << "Invalid HWND";
	//	}
	//}
	////----------------------------------------------------------------------------
	//void WindowsMediaDetection::StartTimer()
	//{
	//	if(!m_bTimerRunning)
	//	{
	//		m_pTimer = new QTimer(this);
	//		connect(m_pTimer,&QTimer::timeout,this,&WindowsMediaDetection::Tick);
	//		m_pTimer->start(1000);
	//		m_bTimerRunning = true;
	//	}
	//}
	////----------------------------------------------------------------------------
	//void WindowsMediaDetection::Tick()
	//{
	//	if(m_bFoundMatch)
	//	{
	//		m_pTimer->stop();
	//	}
	//	else
	//	{
	//		Detect();
	//	}
	//}
	////----------------------------------------------------------------------------
	//void WindowsMediaDetection::OnEvent(const QByteArray &eventType,void *message,long *)
	//{
	//	if(eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
	//	{
	//		MSG* msg = (MSG*)message;

	//		if(msg->message == WM_CREATE)
	//		{
	//			m_pHwnd = msg->hwnd;
	//			if(m_pHwnd)
	//			{
	//				RegisterWindowMessage(TEXT("SHELLHOOK"));
	//				if(RegisterShellHookWindow(m_pHwnd))
	//				{
	//					qDebug() << "ShellHook registered";
	//				}
	//			}
	//		}
	//		if(msg->wParam == HSHELL_WINDOWCREATED && msg->message != WM_TIMER) //WM_TIMER
	//		{
	//			DWORD handle;
	//			m_pThreadId = GetWindowThreadProcessId((HWND)msg->lParam,&m_pProcessId);

	//			if(!m_bFoundMatch)
	//			{
	//				g_pDetectedWindow = (HWND)msg->lParam;

	//				Detect();
	//				StartTimer();
	//			}
	//		}
	//	}
	//}
	////----------------------------------------------------------------------------
	//void WindowsMediaDetection::BsPlayerworkaround()
	//{
	//	LPARAM lParam;
	//	HWND hwnd = NULL;
	//	EnumWindows(FindBSPlayer,(LPARAM)&hwnd);

	//	if(hwnd)
	//	{
	//		char className[256];
	//		GetClassNameA(hwnd,className,256);

	//		char windowValue[256];
	//		GetWindowTextA(hwnd,windowValue,256);

	//		m_bFoundMatch = true;
	//	}

	//}
	//void WindowsMediaDetection::OnMediaPlayerClosed()
	//{
	//	m_bFoundMatch = false;
	//	m_bTimerRunning = false;
	//	m_pTimer->stop();
	//}
	////----------------------------------------------------------------------------
	//HWND WindowsMediaDetection::GetHwnd()
	//{
	//	return m_pHwnd;
	//}
	////----------------------------------------------------------------------------
}

