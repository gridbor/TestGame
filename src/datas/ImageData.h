#pragma once

#include "tools/Logger.h"


struct ImageData {

	int width;
	int height;
	int channels;
	unsigned char* data;

	ImageData():
		width{ 0 }, height{ 0 },
		channels{ 0 },
		data{ nullptr }
	{
		LOG("ImageData::constructor");
	}

	~ImageData()
	{
		LOG("ImageData::~destructor");
		if (data) free(data);
		data = nullptr;
	}

};
