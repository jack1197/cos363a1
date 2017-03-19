#pragma once
#include "common.h"

void cameraMatrix();
void camTargeted(bool target);
void camSetTarget(float point[3], bool snap = false, bool relative = false);
void camSetPos(float point[3], bool snap = false, bool relative = false);
void camSetUp(float vector[3], bool snap = false, bool relative = false);
void camSetAngle(float azimuth, float elevation, bool snap, bool relative);
void camSetTarget(float x, float y, float z, bool snap = false, bool relative = false);
void camSetPos(float x, float y, float z, bool snap = false, bool relative = false);
void camSetUp(float x, float y, float z, bool snap = false, bool relative = false);
void camSetSmoothing(float targetTime, float posTime, float upTime);
void camSmoothingStep(float dt);