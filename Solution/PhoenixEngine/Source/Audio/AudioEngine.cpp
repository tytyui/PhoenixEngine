#include "Audio/AudioEngine.h"

#include "Utility/Debug/Assert.h"
#include "Utility/Debug/Debug.h"

using namespace Phoenix;

const Float32 FAudioEngine::MinVolume = 0.f;
const Float32 FAudioEngine::MaxVolume = 1.f;

FAudioEngine::~FAudioEngine()
{
	DeInit();
}

void FAudioEngine::Init()
{
	F_Assert(!SoundEngine, "You must call DeInit prior to calling Init when already initialized.");
	SoundEngine = irrklang::createIrrKlangDevice();

	if (!SoundEngine)
	{
		F_LogError("Failed to create IrrKlang device.");
		return;
	}

	F_Log("AudioEngine initialized.");
}

bool FAudioEngine::IsValid() const
{
	const bool IsHandleValid = SoundEngine != nullptr;
	return IsHandleValid;
}

void FAudioEngine::DeInit()
{
	if (SoundEngine)
	{
		if (!SoundEngine->drop())
		{
			F_LogError("AudioEngine was shut down but an asset still has a strong reference.");
		}

		SoundEngine = nullptr;

		F_Log("AudioEngine deinitialized.");
	}
}

void FAudioEngine::SetListenerDirection(const FVector3D& Direction)
{
	F_Assert(IsValid(), "This class must be valid.");
	// #FIXME: Code this.
}

void FAudioEngine::SetListenerPosition(const FVector3D& Position)
{
	F_Assert(IsValid(), "This class must be valid.");
	// #FIXME: Code this
}
void FAudioEngine::SetMasterVolume(const Float32 Volume)
{
	F_Assert(IsValid(), "This class must be valid.");
	F_Assert(Volume >= FAudioEngine::MinVolume, "Volume is invalid.");
	F_Assert(Volume <= FAudioEngine::MaxVolume, "Volume is invalid.");

	SoundEngine->setSoundVolume(Volume);
}

FVector3D FAudioEngine::GetListenerDirection() const
{
	F_Assert(IsValid(), "This class must be valid.");
	// #FIXME: Code this.
	return FVector3D();
}

FVector3D FAudioEngine::GetListenerPosition() const
{
	F_Assert(IsValid(), "This class must be valid.");
	// #FIXME: Code this.
	return FVector3D();
}

Float32 FAudioEngine::GetMasterVolume() const
{
	F_Assert(IsValid(), "This class must be valid.");
	const Float32 MasterVolume = SoundEngine->getSoundVolume();
	return MasterVolume;
}

void FAudioEngine::Play2D(const FString& File, const Float32 Volume)
{
	F_Assert(IsValid(), "This class must be valid.");

	irrklang::ISoundSource* SoundSource = SoundEngine->getSoundSource(File.c_str());

	if (!SoundSource)
	{
		SoundSource = SoundEngine->addSoundSourceFromFile(File.c_str());
	}

	if (!SoundSource)
	{
		F_LogError("Failed to get/add sound source for file: {" << File.c_str() << "}");
		return;
	}

	SoundSource->setDefaultVolume(Volume);
	irrklang::ISound* Sound2D = SoundEngine->play2D(SoundSource);

	if (Sound2D)
	{
		Sound2D->drop();
	}
}

void FAudioEngine::Play3D(const FString& File, const Float32 Volume, const FVector3D& Position)
{
	F_Assert(IsValid(), "This class must be valid.");
	FConsoleColor::Set(EConsoleColor::LightBlue); // #FIXME: Should be in a macro.

	irrklang::ISoundSource* SoundSource = SoundEngine->getSoundSource(File.c_str());

	if (!SoundSource)
	{
		SoundSource = SoundEngine->addSoundSourceFromFile(File.c_str());
	}

	if (!SoundSource)
	{
		F_LogError("Failed to get/add sound source for file: {" << File.c_str() << "}");
		return;
	}

	SoundSource->setDefaultVolume(Volume);
	const irrklang::vec3df IrrPosition(Position.x, Position.y, Position.z);
	irrklang::ISound* Sound3D = SoundEngine->play3D(SoundSource, IrrPosition);

	if (Sound3D)
	{
		Sound3D->drop();
	}
}

void FAudioEngine::PauseAllSounds()
{
	F_Assert(IsValid(), "This class must be valid.");
	SoundEngine->setAllSoundsPaused(true);
}

void FAudioEngine::UnpauseAllSounds()
{
	F_Assert(IsValid(), "This class must be valid.");
	SoundEngine->setAllSoundsPaused(false);
}

void FAudioEngine::StopAllSounds()
{
	F_Assert(IsValid(), "This class must be valid.");
	SoundEngine->stopAllSounds();
}
