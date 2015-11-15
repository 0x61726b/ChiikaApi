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
#include "RequestManager.h"
#include "curl.h"
#include "Request/MalManager.h"
#include "Settings/Settings.h"
#include "pugixml.hpp"
#include "ParsingManager.h"
#include "Database/LocalDataManager.h"
#include "Logging/LogManager.h"

#include "AccountVerify.h"
//----------------------------------------------------------------------------
namespace ChiikaApi
{
	struct FtpFile {
		const char* filename;
		FILE *stream;
	};
	//----------------------------------------------------------------------------
	//void RequestBase::Work()
	//{
		//struct FtpFile ftpfile;
		//try
		//{
		//	CURLcode m_CurlRes;
		//	CURL* m_pCurl = curl_easy_init();
		//	m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_HTTPAUTH,CURLAUTH_BASIC);
		//	m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_USERPWD,m_sUsrPwd.c_str());

		//	m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_TIMEOUT,7L);
		//	if(Options.find("Image") != Options.end())
		//	{
		//		CurlConfigOptionMap::iterator it = Options.find("Image");
		//		ftpfile ={
		//			it->second.Value.c_str(), /* name to store the file as if successful */
		//			NULL
		//		};

		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,Curlfwrite);
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,&ftpfile);
		//	}
		//	else
		//	{
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,&m_sBuffer);
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,CallbackFunc);
		//	}

		//	if(Options.find("Ua") != Options.end())
		//	{
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_USERAGENT,Options.find("Ua")->second.Value.c_str());
		//		LOG(INFO) << "Setting User-Agent to : " << Options.find("Ua")->second.Value.c_str();
		//	}
		//	else
		//	{
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_USERAGENT,"ChiikaMalApi");
		//		LOG(INFO) << "Setting User-Agent to:	ChiikaMalApi";
		//	}

		//	m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_URL,m_sUrl.c_str());
		//	LOG(INFO) << "Setting URL :	" << std::endl << m_sUrl.c_str();
		//	/*curl_easy_setopt(m_pCurl,CURLOPT_VERBOSE,1L);*/
		//	curl_easy_setopt(m_pCurl,CURLOPT_TIMEOUT,100);


		//	if(m_iMethod == 10024)
		//	{
		//		LOG(INFO) << "Setting method :	POST";

		//		if(xmlData.size() > 0)
		//		{
		//			const char* data = xmlData.c_str();
		//			ChiString append = "data=";
		//			append.append(data);

		//			curl_easy_setopt(m_pCurl,CURLOPT_POST,1L);
		//			curl_easy_setopt(m_pCurl,CURLOPT_POSTFIELDS,append.c_str());
		//			curl_easy_setopt(m_pCurl,CURLOPT_POSTFIELDSIZE,append.length());
		//			m_CurlRes = curl_easy_perform(m_pCurl);
		//		}
		//	}
		//	else
		//	{
		//		LOG(INFO) << "Setting method :	GET";
		//		m_CurlRes = curl_easy_setopt(m_pCurl,CURLOPT_URL,m_sUrl.c_str());
		//		m_CurlRes = curl_easy_perform(m_pCurl);
		//	}

		//	long http_code = 0;
		//	curl_easy_getinfo(m_pCurl,CURLINFO_RESPONSE_CODE,&http_code);

		//	if((http_code == 200 || http_code == 201 || http_code == 204) && m_CurlRes != CURLE_ABORTED_BY_CALLBACK)
		//	{
		//		//Success
		//		LOG(INFO) << "Request " << Name.c_str() << " has ben successful with the HTTP code " << http_code << "!";
		//		if(Options.find("Image") != Options.end())
		//		{
		//			fclose(ftpfile.stream);
		//			LOG(INFO) << "Closed image stream.";
		//		}

		//	}
		//	else
		//	{
		//		LOG(WARNING) << "CURL Request has returned " << http_code << ". There is something wrong.";
		//	}
		//	OnWorkFinished();

		//	curl_easy_cleanup(m_pCurl);

		//	delete this; // ?
		//}
		//catch(Exception&)
		//{
		//	CHIKA_EXCEPTION(Exception::ERR_THREADING,"Thread failed to execute.","ThreadedRequest::Work")
		//}

	/*}*/
	//----------------------------------------------------------------------------
	RequestManager::RequestManager()
	{

	}
	//----------------------------------------------------------------------------
	RequestManager::~RequestManager()
	{

	}
	//----------------------------------------------------------------------------
	void RequestManager::Initialize()
	{
		curl_global_init(CURL_GLOBAL_ALL);
	}
	//----------------------------------------------------------------------------
	void RequestManager::Destroy()
	{
		curl_global_cleanup();
	}
	//----------------------------------------------------------------------------
	void RequestManager::ProcessRequest(ThreadedRequest* request)
	{

	}
	//----------------------------------------------------------------------------
	void RequestManager::VerifyUser(const UserInfo& info)
	{
		//AccountVerifyRequest req(NULL);
		//req.SetUserInfo(info);
		//req.Initialize();
		//req.SetOptions();
		//req.Initiate();
	}
	//----------------------------------------------------------------------------
	//void RequestManager::CreateVerifyRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption userName;
	//	CurlConfigOption passWord;

	//	url.Name = "Url";
	//	url.Value = "http://myanimelist.net/api/account/verify_credentials.xml";

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	userName.Name = "UserName";
	//	userName.Value = LocalDataManager::Get().GetUserInfo().UserName;

	//	passWord.Name = "PassWord";
	//	passWord.Value = LocalDataManager::Get().GetUserInfo().Pass;

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(userName.Name,userName));
	//	options.insert(CurlConfigOptionMap::value_type(passWord.Name,passWord));


	//	RequestThread r = CreateRequest;
	//	r->AddListener(l);
	//	r->SetParameters(options,"Verify");
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateAnimeSearchRequest(RequestListener* l,ChiString keyword)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption userName;
	//	CurlConfigOption passWord;

	//	url.Name = "Url";
	//	ChiString k = (keyword);
	//	/*k.replace(" ","+");*/
	//	url.Value = "http://myanimelist.net/api/anime/search.xml?q=" + k;

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	userName.Name = "UserName";
	//	userName.Value = LocalDataManager::Get().GetUserInfo().UserName;

	//	passWord.Name = "PassWord";
	//	passWord.Value = LocalDataManager::Get().GetUserInfo().Pass;

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(userName.Name,userName));
	//	options.insert(CurlConfigOptionMap::value_type(passWord.Name,passWord));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"SearchAnime");
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateGetAnimeListRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption userName;
	//	CurlConfigOption passWord;

	//	url.Name = "Url";


	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	userName.Name = "UserName";
	//	userName.Value = LocalDataManager::Get().GetUserInfo().UserName;

	//	passWord.Name = "PassWord";
	//	passWord.Value = LocalDataManager::Get().GetUserInfo().Pass;

	//	url.Value = "http://myanimelist.net/malappinfo.php?u=" + userName.Value + "&type=anime&status=all";

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(userName.Name,userName));
	//	options.insert(CurlConfigOptionMap::value_type(passWord.Name,passWord));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"GetAnimeList");
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateCRUDRequest(RequestListener* l,const UserAnimeEntry& anime,const MangaInfo& manga,CRUDOp operation,CRUDTarget target)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption userName;
	//	CurlConfigOption passWord;
	//	CurlConfigOption xmlData;
	//	ChiString animeId = std::to_string(anime.Anime.Id);
	//	ChiString mangaId = std::to_string(manga.Mango.Id);

	//	ChiString op;
	//	ChiString sTarget;

	//	userName.Name = "UserName";
	//	userName.Value = LocalDataManager::Get().GetUserInfo().UserName;

	//	passWord.Name = "PassWord";
	//	passWord.Value = LocalDataManager::Get().GetUserInfo().Pass;

	//	xmlData.Name = "XML";

	//	url.Name = "Url";
	//	if(target == CRUDTarget::ANIME)
	//	{
	//		sTarget = "Anime";
	//		xmlData.Value = GetAnimeXML(anime);
	//		if(operation == CRUDOp::Create)
	//		{
	//			url.Value = "http://myanimelist.net/api/animelist/add/" + animeId + ".xml";
	//			op = "Create";
	//		}
	//		if(operation == CRUDOp::Update)
	//		{
	//			url.Value = "http://myanimelist.net/api/animelist/update/" + animeId + ".xml";
	//			op = "Update";
	//		}
	//		if(operation == CRUDOp::Delete)
	//		{
	//			url.Value = "http://myanimelist.net/api/animelist/delete/" + animeId + ".xml";
	//			op = "Delete";
	//		}
	//	}
	//	if(target == CRUDTarget::MANGA)
	//	{
	//		sTarget = "Manga";
	//		xmlData.Value = GetMangaXML(manga);
	//		if(operation == CRUDOp::Create)
	//		{
	//			url.Value = "http://myanimelist.net/api/mangalist/add/" + mangaId + ".xml";
	//			op = "Create";
	//		}
	//		if(operation == CRUDOp::Update)
	//		{
	//			url.Value = "http://myanimelist.net/api/mangalist/update/" + mangaId + ".xml";
	//			op = "Update";
	//		}
	//		if(operation == CRUDOp::Delete)
	//		{
	//			url.Value = "http://myanimelist.net/api/mangalist/delete/" + mangaId + ".xml";
	//			op = "Delete";
	//		}
	//	}

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPPOST;





	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(userName.Name,userName));
	//	options.insert(CurlConfigOptionMap::value_type(passWord.Name,passWord));
	//	options.insert(CurlConfigOptionMap::value_type(xmlData.Name,xmlData));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,op + sTarget);
	//	r->m_Result.AnimeResult = anime;
	//	r->m_Result.MangaResult = manga;
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateGetMangaListRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption userName;
	//	CurlConfigOption passWord;

	//	url.Name = "Url";


	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;
	//	userName.Name = "UserName";
	//	userName.Value = LocalDataManager::Get().GetUserInfo().UserName;

	//	passWord.Name = "PassWord";
	//	passWord.Value = LocalDataManager::Get().GetUserInfo().Pass;

	//	url.Value = "http://myanimelist.net/malappinfo.php?u=" + userName.Value + "&type=manga&status=all";

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(userName.Name,userName));
	//	options.insert(CurlConfigOptionMap::value_type(passWord.Name,passWord));


	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"GetMangaList");
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateAnilistRequest()
	//{
	//	/*
	//	AnilistAuth aa = ConfigManager::Get().GetAnilistAuth();

	//	if(aa.AccessToken == "")
	//	{
	//	CreateAnilistAuthRequest(0);
	//	ThreadedRequest* f = m_vRequests[m_vRequests.size()-1];
	//	f->m_pThread->join();
	//	ConfigManager::Get().SetAnilistToken(f->m_Result.AnilistAuthCode);
	//	return;
	//	}
	//	struct tm *pTime;
	//	time_t ctTime; time(&ctTime);
	//	pTime = localtime(&ctTime);

	//	int hour = pTime->tm_hour;
	//	int day = pTime->tm_mday;

	//	if(hour - aa.Hour != 0)
	//	{
	//	CreateAnilistAuthRequest(0);
	//	ThreadedRequest* f = m_vRequests[m_vRequests.size()-1];
	//	f->m_pThread->join();
	//	ConfigManager::Get().SetAnilistToken(f->m_Result.AnilistAuthCode);
	//	}
	//	*/
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateAnilistAuthRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPPOST;

	//	//Take these out of here probably
	//	ChiString grant_type = "client_credentials";
	//	ChiString client_id = "arkenthera-71vj2";
	//	ChiString client_secret = "T4a8AMEyk389ENC6RwysxIRYTdHI1p";

	//	CurlConfigOption grant_typeOpt;
	//	CurlConfigOption client_idOpt;
	//	CurlConfigOption client_secretOp;

	//	grant_typeOpt.Name = "GrantType";
	//	grant_typeOpt.Value = grant_type;

	//	client_idOpt.Name = "ClientID";
	//	client_idOpt.Value = client_id;

	//	client_secretOp.Name = "SecretID";
	//	client_secretOp.Value = client_secret;

	//	url.Name = "Url";
	//	url.Value = "http://anilist.co/api/auth/access_token";

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(grant_typeOpt.Name,grant_typeOpt));
	//	options.insert(CurlConfigOptionMap::value_type(client_idOpt.Name,client_idOpt));
	//	options.insert(CurlConfigOptionMap::value_type(client_secretOp.Name,client_secretOp));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"AnilistAuth",RequestType::Anilist);
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateAnilistSearchAnime(RequestListener* l,ChiString keyword)
	//{
	//	CreateAnilistRequest();

	//	CurlConfigOption url;
	//	CurlConfigOption method;



	//	url.Name = "Url";
	//	url.Value = "http://anilist.co/api/anime/search/" + keyword;


	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));


	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"AnilistSearchAnime",RequestType::Anilist);
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateImageDownloadRequest(RequestListener* l,ChiString imageUrl,ChiString fileName,const UserAnimeEntry& anime)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption misc;

	//	url.Name = "Url";
	//	url.Value = imageUrl;

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	misc.Name = "Image";
	//	misc.Value = fileName;

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(misc.Name,misc));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"ImageDownload");
	//	r->m_Result.AnimeResult = anime;
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateAnimePageScrapeRequest(RequestListener* l,const UserAnimeEntry& anime)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption misc;
	//	CurlConfigOption userAgent;

	//	url.Name = "Url";
	//	url.Value = "http://myanimelist.net/anime/";
	//	url.Value.append(std::to_string(anime.Anime.Id));

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	userAgent.Name = "Ua";
	//	userAgent.Value = "api-taiga-32864c09ef538453b4d8110734ee355b";

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(misc.Name,misc));
	//	options.insert(CurlConfigOptionMap::value_type(userAgent.Name,userAgent));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"AnimeScrape");
	//	r->AddListener(l);
	//	r->m_Result.AnimeResult = anime;
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateUserPageScrapeRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;
	//	CurlConfigOption misc;
	//	CurlConfigOption userAgent;

	//	url.Name = "Url";
	//	url.Value = "http://myanimelist.net/profile/";
	//	url.Value.append(LocalDataManager::Get().GetUserInfo().UserName);

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	userAgent.Name = "Ua";
	//	//Found this ChiString at https://github.com/djh3315. Seems like abandoned so I pulled the ChiString. (pun intended)
	//	//I could not find any information about the person
	//	//So I could not mail him/her to get approval
	//	//Please dont ban me incapsula!
	//	userAgent.Value = "api-indiv-BDF02918341A555C9108D3AC352A2432";

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));
	//	options.insert(CurlConfigOptionMap::value_type(misc.Name,misc));
	//	options.insert(CurlConfigOptionMap::value_type(userAgent.Name,userAgent));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"UserPageScrape");
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//void RequestManager::CreateSenpaiMoeDataRequest(RequestListener* l)
	//{
	//	CurlConfigOption url;
	//	CurlConfigOption method;

	//	url.Name = "Url";

	//	//All hail Senpai
	//	url.Value = "http://www.senpai.moe/export.php?type=json&src=raw";
	//	/*url.Value = "http://www.google.com";*/

	//	method.Name = "Method";
	//	method.cUrlOpt = CURLOPT_HTTPGET;

	//	CurlConfigOptionMap options;

	//	options.insert(CurlConfigOptionMap::value_type(url.Name,url));
	//	options.insert(CurlConfigOptionMap::value_type(method.Name,method));

	//	RequestThread r = CreateRequest;
	//	r->SetParameters(options,"SenpaiMoeData");
	//	r->AddListener(l);
	//	r->Initialize();
	//}
	////----------------------------------------------------------------------------
	//ChiString RequestManager::GetAnimeXML(const UserAnimeEntry& anime)
	//{
	//	pugi::xml_document doc;
	//	pugi::xml_node entry = doc.append_child("entry");
	//	pugi::xml_node episode = entry.append_child("episode");
	//	pugi::xml_node status = entry.append_child("status");
	//	pugi::xml_node score = entry.append_child("score");
	//	pugi::xml_node downloaded_episodes = entry.append_child("downloaded_episodes");
	//	pugi::xml_node storage_type = entry.append_child("storage_type");
	//	pugi::xml_node storage_value = entry.append_child("storage_value");
	//	pugi::xml_node times_rewatched = entry.append_child("times_rewatched");
	//	pugi::xml_node rewatch_value = entry.append_child("rewatch_value");
	//	pugi::xml_node date_start = entry.append_child("date_start");
	//	pugi::xml_node date_finish = entry.append_child("date_finish");
	//	pugi::xml_node priority = entry.append_child("priority");
	//	pugi::xml_node enable_discussion = entry.append_child("enable_discussion");
	//	pugi::xml_node enable_rewatching = entry.append_child("enable_rewatching");
	//	pugi::xml_node comments = entry.append_child("comments");
	//	pugi::xml_node fansub_group = entry.append_child("fansub_group");
	//	pugi::xml_node tags = entry.append_child("tags");

	//	pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
	//	decl.append_attribute("version") = "1.0";
	//	decl.append_attribute("encoding") = "UTF-8";


	//	episode.text().set(anime.WatchedEpisodes);
	//	status.text().set(anime.Status);
	//	score.text().set(anime.Score);
	//	ChiStringStream str;
	//	doc.save(str);
	//	return str.str();
	//}
	////----------------------------------------------------------------------------
	//ChiString RequestManager::GetMangaXML(const MangaInfo& manga)
	//{
	//	pugi::xml_document doc;
	//	pugi::xml_node entry = doc.append_child("entry");
	//	pugi::xml_node chapters = entry.append_child("chapters");
	//	pugi::xml_node volume = entry.append_child("volume");
	//	pugi::xml_node status = entry.append_child("status");
	//	pugi::xml_node score = entry.append_child("score");
	//	pugi::xml_node downloaded_chapters = entry.append_child("downloaded_chapters");
	//	pugi::xml_node times_reread = entry.append_child("times_reread");
	//	pugi::xml_node reread_value = entry.append_child("reread_value");
	//	pugi::xml_node date_start = entry.append_child("date_start");
	//	pugi::xml_node date_finish = entry.append_child("date_finish");
	//	pugi::xml_node priority = entry.append_child("priority");
	//	pugi::xml_node enable_discussion = entry.append_child("enable_discussion");
	//	pugi::xml_node enable_rereading = entry.append_child("enable_rereading");
	//	pugi::xml_node comments = entry.append_child("comments");
	//	pugi::xml_node scan_group = entry.append_child("scan_group");
	//	pugi::xml_node tags = entry.append_child("tags");
	//	pugi::xml_node retail_volumes = entry.append_child("retail_volumes");

	//	pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
	//	decl.append_attribute("version") = "1.0";
	//	decl.append_attribute("encoding") = "UTF-8";

	//	SetXMLValue(status,MangaUserStatus::PlanToRead);
	//	SetXMLValue(chapters,manga.ReadChapters);
	//	SetXMLValue(volume,manga.ReadVolumes);
	//	SetXMLValue(score,manga.Score);

	//	ChiStringStream str;
	//	doc.save(str);
	//	return str.str();
	//}
	//----------------------------------------------------------------------------
	template<> RequestManager* Singleton<RequestManager>::msSingleton = 0;
	RequestManager& RequestManager::Get(void)
	{
		/*assert(msSingleton); */ return (*msSingleton);
	}
	//----------------------------------------------------------------------------
	RequestManager* RequestManager::GetPtr(void)
	{
		return msSingleton;
	}
}
