/*
  ==============================================================================

    AdsrData.cpp
    Created: 2 Sep 2024 11:40:29pm
    Author:  Dario

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}