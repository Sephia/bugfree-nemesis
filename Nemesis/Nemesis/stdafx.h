// stdafx.h

#pragma once

#include <sdkddkver.h>

#include <stdio.h>
#include <tchar.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

const int WORLDSIZE = 150;
const int TILESIZE = 64;

#pragma warning(disable:4099)
#if defined(_DEBUG)
#pragma comment(lib, "debug/sfml-window-d.lib")
#pragma comment(lib, "debug/sfml-graphics-d.lib")
#pragma comment(lib, "debug/sfml-system-d.lib")
#pragma comment(lib, "debug/sfml-audio-d.lib")
#else
#pragma comment(lib, "release/sfml-window.lib")
#pragma comment(lib, "release/sfml-graphics.lib")
#pragma comment(lib, "release/sfml-system.lib")
#pragma comment(lib, "release/sfml-audio.lib")
#endif
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>