//----------------------------------------------------------------------------
//Chiika Api
//Copyright (C) 2015  arkenthera
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
//authors:arkenthera
//Date: 2.4.2016
//----------------------------------------------------------------------------
#ifndef __UpdateAnime_h__
#define __UpdateAnime_h__
//----------------------------------------------------------------------------
#include "Common\Required.h"
#include "RequestInterface.h"
//---------------------------------------------------------------------------
namespace ChiikaApi
{
	class MalApiExport UpdateAnimeRequest : public RequestInterface, public CurlEventListener
	{
	public:
		UpdateAnimeRequest();
		virtual ~UpdateAnimeRequest();
		void OnSuccess();
		void OnError();

		void Initialize();
		void Initiate();
		void SetOptions();

		void SetAnimeId(int Id);
		void UpdateScore(int newScore);
		void UpdateStatus(int newStatus);
		void UpdateProgress(int newProgress);
		
		int m_Anime;
		int m_NewScore;
		int m_NewStatus;
		int m_NewProgress;
	};
}

//----------------------------------------------------------------------------
#endif
