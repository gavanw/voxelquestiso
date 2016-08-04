
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#define _CRT_SECURE_NO_DEPRECATE 1

const static int DEF_SCALE_FACTOR = 2;
const static int MAX_LAYERS = 2;






const static int DEF_WIN_W = 1920;
const static int DEF_WIN_H = 1080;




const static int MAX_LIGHTS = 24;
const static int MAX_EVAL_LIGHTS = 1024;
const static int FLOATS_PER_LIGHT = 16;



const static float UI_SCALE_FACTOR = 1.0f;

const static int MAX_PLANT_GEN = 16;

const static int MAX_TER_TEX = 9;

const static int MAX_NODE_DIRS = 6;
const static int MAX_NODE_VALS = 4;
const static int TOT_NODE_VALS =
	MAX_NODE_DIRS * MAX_NODE_VALS;

const static int TOT_MAP_DIRS = 4;

const static int MAX_BLOCK_STACK = 10;
const static int MAX_UI_LAYERS = 4;


bool LAST_COMPILE_ERROR = false;

char *BUF_NAMES[] =
{
	"ublock0",
	"ublock1",
	"ublock2",
	"ublock3",
	"ublock4",
	"ublock5",
	"ublock6",
	"ublock7",
	"ublock8",
	"ublock9",
	"ublock10",
	"ublock11",
	"ublock12",
	"ublock13"
};


const static int MAX_VG_FBOS = 16;
int CUR_VG_FBO = 0;
int PAGE_COUNT = 0;


// set to 0 to disable
int MAX_HOLDERS = 1024;


float MAX_GPU_MEM = 2560.0f;
float TOT_GPU_MEM_USAGE = 0.0f;

float MAX_CPU_MEM = 4096.0f;
float TOT_CPU_MEM_USAGE = 0.0f;

bool TRACE_ON = false;
//#define DEBUG_MODE 1

#ifdef WIN32
#include <SDKDDKVer.h>
#endif


#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <list>
#include <cstddef>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <ios>
#include <algorithm>
#include <cstdlib>

#include <iomanip>
#include <map>
#include <ctime>


#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <float.h>
#ifdef WIN32
#include <tchar.h>
#include <io.h>
#include <conio.h>
#endif

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#ifdef WIN32
#pragma comment(lib, "glew32.lib")
#endif



#ifdef USE_POCO

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include "Poco/Runnable.h"
#include "Poco/ThreadPool.h"
#include "Poco/Base64Decoder.h"


using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::SystemException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::Runnable;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;

using Poco::Base64Decoder;

#else

/* 
   base64.cpp and base64.h

   Copyright (C) 2004-2008 René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/


static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}


#endif

/*
#pragma comment (lib, "olepro32.lib")   // for IPicture COM interface support
#include <windows.h>
#include <olectl.h.>    // for OleLoadPicture() and IPicture COM interface
*/






struct charArr {
	long size;
	char *data;
};

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


#if defined(_DEBUG)
#include <crtdbg.h>
#endif

using namespace std;


#define _USE_MATH_DEFINES

typedef unsigned int uint;


static inline int newcasecmp(const char *s1, const char *s2, size_t n)
{
	int lc1  = 0;
	int lc2  = 0;

	while (n--)
	{
		lc1 = towlower (*s1);
		lc2 = towlower (*s2);

		if (lc1 != lc2)
			return (lc1 - lc2);

		if (!lc1)
			return 0;

		++s1;
		++s2;
	}

	return 0;
}

// todo: this define of wcsncasecmp should not be here

//Win32 incompatibilities
#if defined(WIN32) && !defined(__GNUC__)
static inline bool isnan(double x) {
	return x != x;
}
static inline bool isinf(double x) {
	return !isnan(x) && isnan(x - x);
}
#endif

// Linux compile fix - from quaker66
#ifdef __GNUC__
// #include <cstring>
// #include <cstdlib>
#endif

// Mac compile fixes - from quaker66, Lion fix by dabrahams
#if defined(__APPLE__) && __DARWIN_C_LEVEL < 200809L || (defined(WIN32) && defined(__GNUC__))
#include <wctype.h>
#include <wchar.h>

#endif

// Simple function to check a string 's' has at least 'n' characters
static inline bool simplejson_wcsnlen(const char *s, size_t n) {
	if (s == 0)
		return false;

	const char *save = s;
	while (n-- > 0)
	{
		if (*(save++) == 0) return false;
	}

	return true;
}

struct membuf : std::streambuf
{
	membuf(char *begin, char *end) {
		this->setg(begin, begin, end);
	}
};



bool PROG_ACTIVE = true;

#define glError() { \
		GLenum err = glGetError(); \
		while (err != GL_NO_ERROR) { \
			printf("glError: %s caught at %s:%u", \
						 (char*)gluErrorString(err), __FILE__, __LINE__); \
			err = glGetError(); \
			exit(-1); \
		} \
	}





