#include "musicplayer.h"
#include "dirent.h"
#include <sys/types.h>

Musicplayer::Musicplayer() //¶ÁÈ¡ÒôÀÖÎÄ¼þ
{
	DIR* dir;
	struct dirent* ptr;
	dir = opendir("resources\\music");
	while ((ptr = readdir(dir)) != NULL) {
		std::string s = ptr->d_name;
		if (s.length() <= 4) continue;
		if (s.substr(s.length() - 4, s.length()) != ".mp3" && s.substr(s.length() - 4, s.length()) != ".wav") continue;
		MUSIC* m = new MUSIC;
		m->OpenFile((std::string("resources\\music\\") + s).c_str());
		s = s.erase(s.length() - 4, s.length());
		musics[std::string("music-") + s] = m;
	}
	dir = opendir("resources\\sound");
	while ((ptr = readdir(dir)) != NULL) {
		std::string s = ptr->d_name;
		if (s.length() <= 4) continue;
		if (s.substr(s.length() - 4, s.length()) != ".mp3" && s.substr(s.length() - 4, s.length()) != ".wav") continue;
		MUSIC* m = new MUSIC;
		m->OpenFile((std::string("resources\\sound\\") + s).c_str());
		s = s.erase(s.length() - 4, s.length());
		musics[std::string("sound-") + s] = m;
	}
}

bool Musicplayer::play(std::string s)
{
	auto p = musics.find(s);
	if (p == musics.end()) return false;
	p->second->Play(0);
	return true;
}

bool Musicplayer::stop(std::string s)
{
	auto p = musics.find(s);
	if (p == musics.end()) return false;
	p->second->Stop();
	return true;
}

bool Musicplayer::checkend(std::string s)
{
	auto p = musics.find(s);
	if (p == musics.end()) return false;
	return p->second->GetPlayStatus() == MUSIC_MODE_STOP;
}

bool Musicplayer::isplay(std::string s)
{
	auto p = musics.find(s);
	if (p == musics.end()) return false;
	return p->second->GetPlayStatus() == MUSIC_MODE_PLAY;
}

bool Musicplayer::SetVolume(std::string s, double v)
{
	auto p = musics.find(s);
	if (p == musics.end()) return false;
	p->second->SetVolume(v);
	return true;
}
Musicplayer musicplayer;