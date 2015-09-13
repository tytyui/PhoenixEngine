#ifndef PHOENIX_AUDIO_ENGINE_H
#define PHOENIX_AUDIO_ENGINE_H

#include "ExternalLib/IrrKlangIncludes.h"
#include "Utility/Misc/Primitives.h"
#include "Utility/Misc/String.h"
#include "Math/Vector3D.h"

namespace Phoenix
{
	class FAudioEngine {
	public:
		static const Float32 MinVolume;
		static const Float32 MaxVolume;

		FAudioEngine() = default;

		FAudioEngine(const FAudioEngine&) = delete;
		FAudioEngine& operator=(const FAudioEngine&) = delete;

		FAudioEngine(FAudioEngine&&) = delete;
		FAudioEngine& operator=(FAudioEngine&&) = delete;

		~FAudioEngine();

		void Init();

		bool IsValid() const;

		void DeInit();

		void SetListenerDirection(const FVector3D& Direction);

		void SetListenerPosition(const FVector3D& Position);

		void SetMasterVolume(const Float32 Volume);

		FVector3D GetListenerDirection() const;

		FVector3D GetListenerPosition() const;

		Float32 GetMasterVolume() const;

		void Play2D(const FString& File, const Float32 Volume);

		void Play3D(const FString& File, const Float32 Volume, const FVector3D& Position);

		void PauseAllSounds();

		void UnpauseAllSounds();

		void StopAllSounds();

	protected:
	private:
		irrklang::ISoundEngine* SoundEngine { nullptr };
	};
}

#endif