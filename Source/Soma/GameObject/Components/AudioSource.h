#pragma once

#include "SomaStd.h"
#include "../Component.h"
#include "SFML/Audio.hpp"

class AudioSource : public Component
{
private:
	sf::Sound								m_sound;
	sf::Music								m_music;
	std::shared_ptr<sf::SoundBuffer>		m_defaultClip;
	bool									m_isMusic;
	bool									m_autoplay;
	bool									m_loop;
	float									m_volume;
	float									m_pitch;

public:

	AudioSource();
	~AudioSource() = default;

	static std::string g_Name;
	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;

	virtual void Start() override;

	AudioSource(std::shared_ptr<sf::SoundBuffer> defaultClip)
		: m_sound(*defaultClip)
		, m_defaultClip(defaultClip)
	{}

	void Play() 
	{
		if (m_isMusic)
		{
			m_music.play();
		}
		else
		{
			m_sound.play();
		}
	}

	void SetLoop(bool loop)
	{
		m_loop = loop;
		m_sound.setLoop(loop);
		m_music.setLoop(loop);
	}

	void SetVolume(float volume)
	{
		m_volume = volume;
		m_sound.setVolume(volume);
		m_music.setVolume(volume);
	}

	void SetPitch(float pitch)
	{
		m_pitch = pitch;
		m_sound.setPitch(pitch);
		m_music.setPitch(pitch);
	}

	void Play(bool repeat)
	{
		m_sound.setBuffer(*m_defaultClip);
		m_sound.setLoop(repeat);
		m_sound.play();
	}

	void PlayClip(std::shared_ptr<sf::SoundBuffer> clip, bool repeat = false)
	{
		m_sound.setBuffer(*clip);
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

	void SetDefaultClip(std::shared_ptr<sf::SoundBuffer> clip)
	{
		m_defaultClip = clip;
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