#pragma once
bool isSpecialDown(int key);
bool isKeyDown(unsigned char key);
bool isKeyDown(char key);
void specialPressed(int key, int x, int y);
void specialReleased(int key, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void keyReleased(unsigned char key, int x, int y);