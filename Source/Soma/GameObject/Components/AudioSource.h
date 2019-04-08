#pragma once

#include "SomaStd.h"
#include "../Component.h"
#include "SFML/Audio.hpp"

class AudioSource : public Component
{
private:
	sf::Sound				m_sound;
	sf::Music				m_music;
	sf::SoundBuffer&		m_defaultClip;
public:
	AudioSource() = default;
	~AudioSource() = default;

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(Json data) override;

	AudioSource(sf::SoundBuffer& defaultClip)
		: m_sound(defaultClip)
		, m_defaultClip(defaultClip)
	{}

	void Play(bool repeat = false)
	{
		m_sound.setBuffer(m_defaultClip);
		m_sound.setLoop(repeat);
		m_sound.play();
	}

	void PlayClip(sf::SoundBuffer& clip, bool repeat = false)
	{
		m_sound.setBuffer(clip);
		m_sound.setLoop(repeat);
		m_sound.play();
	}

	void Pause()
	{
		m_sound.pause();
	}

	void Stop()
	{
		m_sound.stop();
	}

	void SetDefaultClip(sf::SoundBuffer& clip)
	{
		m_defaultClip = clip;
	}

	void SetVolume(float volume)
	{
		m_sound.setVolume(volume);
	}

	void SetPitch(float pitch)
	{
		m_sound.setPitch(pitch);
	}

	void PlayMusic(bool repeat = false)
	{
		m_music.setLoop(repeat);
		m_music.play();
	}

	void PauseMusic()
	{
		m_music.pause();
	}

	void StopMusic()
	{
		m_music.stop();
	}

	void LoadMusicFile(std::string path)
	{
		m_music.openFromFile(path);
	}

	void SetMusicVolume(float volume)
	{
		m_music.setVolume(volume);
	}

	void SetMusicPitch(float pitch)
	{
		m_music.setPitch(pitch);
	}
};