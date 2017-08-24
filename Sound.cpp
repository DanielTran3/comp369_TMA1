#include "Sound.h"

Sound::Sound() {
	_panning = 128;
	_pitch = 1000;
	_volume = 128;
	
	_bgm = load_sample(BGM);
	if (!_bgm) {
		allegro_message("Error Loading Background Music");
	}
	playMusic();
	_soundEffect = load_sample(CORRECT_SOUND);
	if (!_soundEffect) {
		allegro_message("Error Loading Correct Sound Effect");
	}
}

Sound::~Sound() {
	destroy_sample(_bgm);
	destroy_sample(_soundEffect);
}
void Sound::setPanning(int panning) {
	_panning = panning;
}

int Sound::getPanning() {
	return _panning;
}

void Sound::setPitch(int pitch) {
	_pitch = pitch;
}

int Sound::getPitch() {
	return _pitch;
}

void Sound::setVolume(int volume) {
	_volume = volume;	
}

int Sound::getVolume() {
	return _volume;
}

void Sound::setBGM(const char *bgmName) {
	_bgm = load_sample(bgmName);
	if (!_bgm) {
		allegro_message("Error Loading Music");
	}
}

SAMPLE *Sound::getBGM() {
	return _bgm;
}

void Sound::setSoundEffect(const char *soundEffectName) {
	_soundEffect = load_sample(soundEffectName);
	if (!_soundEffect) {
		allegro_message("Error Loading Sound Effect");
	}
}

SAMPLE *Sound::getSoundEffect() {
	return _soundEffect;
}

void Sound::playMusic() {
	play_sample(_bgm, _volume, _panning, _pitch, TRUE);
}

void Sound::stopMusic() {
	stop_sample(_bgm);
}

void Sound::playSoundEffect() {
	play_sample(_soundEffect, _volume, _panning, _pitch, FALSE);	
}

void Sound::stopSoundEffect() {
	stop_sample(_soundEffect);
}

void Sound::updateSound(SAMPLE *sound) {
	adjust_sample(sound, _volume, _panning, _pitch, TRUE);
}

void Sound::updateAllSounds() {
	adjust_sample(_bgm, _volume, _panning, _pitch, TRUE);
	adjust_sample(_soundEffect, _volume, _panning, _pitch, FALSE);
}
