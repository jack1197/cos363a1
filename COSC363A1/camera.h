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
void camGetDirection(float output[3], bool targetMode);
void camGetDirection(float output[3]);
void camGetAngles(float output[2]);
void camGetPos(float output[3]);
void camSmoothingStep(float dt);