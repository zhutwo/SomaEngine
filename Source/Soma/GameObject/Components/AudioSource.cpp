#include "AudioSource.h"
#include "../../Utilities/ResourceHolder.h"

std::string AudioSource::g_Name = "AudioSource";

AudioSource::AudioSource()
{
}

bool AudioSource::VInit(Json data)
{
	if (!data)
	{
		return false;
	}

	m_isMusic = data["isMusic"].get<bool>();
	m_autoplay = data["autoplay"].get<bool>();
	auto loop = data["loop"].get<bool>();
	SetLoop(loop);
	auto volume = data["volume"].get<float>();
	SetVolume(volume);
	auto pitch = data["pitch"].get<float>();
	SetPitch(pitch);

	auto name = data["defaultClip"].get<std::string>();
	m_defaultClip = ResourceHolder::GetSingleton().GetSoundBuffer(name);
	m_sound.setBuffer(*m_defaultClip);

	if (!m_defaultClip)
	{
		return false;
	}

	return true;
}

void AudioSource::Start()
{
	if (m_autoplay)
	{
		Play();
	}
}
