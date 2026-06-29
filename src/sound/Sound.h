// Copyright © 2008-2026 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef __SOUND_H
#define __SOUND_H

#include "vector3.h"

#include <cstdint>
#include <string>
#include <vector>

class Body;

namespace Sound {

	enum {
		OP_REPEAT = (1 << 0),
		OP_STOP_AT_TARGET_VOLUME = (1 << 1)
	};
	typedef uint32_t Op;

	class Event {
	public:
		Event() :
			eid(0) {}
		void Play(const char *fx, const float volume = 1.f, Op op = 0);
		void PlayMusic(const char *fx, float volume, float fadeDelta, bool repeat, Event *fadeOut = nullptr);
		bool Stop();
		bool IsPlaying() const;
		bool SetOp(Op op);
		bool VolumeAnimate(const float targetVol, const float dv_dt);
		bool SetVolume(const float vol);
		bool FadeOut(float dv_dt, Op op = 0);

	private:
		uint32_t eid;
	};

	std::vector<std::string_view> GetAvailableBackends();
	std::string_view GetBackend();

	bool Init(std::string_view backend);
	void Uninit();
	/**
	 * Silence all active sound events.
	 */
	void DestroyAllEvents();
	void DestroyAllEventsExceptMusic();
	void Pause(int on);
	void PlaySfx(const char *fx, const float volume = 1.F, const Op op = 0);
	void CalculateStereo(const Body *b, float vol, float *volLeftOut, float *volRightOut);
	void BodyMakeNoise(const Body *b, const char *fx, float vol);
	void SetMasterVolume(const float vol);
	float GetMasterVolume();
	void SetSfxVolume(const float vol);
	float GetSfxVolume();
	const std::vector<std::string> GetMusicFiles();
	void Update(float delta_t);

	bool IsBinauralSupported();
	void EnableBinaural(bool enabled);
} /* namespace Sound */

#endif /* __SOUND_H */
