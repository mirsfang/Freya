#include "FreyaFrameBufferCache.h"

#include <stdarg.h>
#include "utils/Log.h"
#include "FreyaFrameBuffer.h"

namespace FREYA {

	FreyaFrameBufferCache::FreyaFrameBufferCache()
	{
	}

	FreyaFrameBufferCache::~FreyaFrameBufferCache()
	{
	}

	std::shared_ptr<FreyaFrameBuffer> FreyaFrameBufferCache::fetchFramebufferForSize(FreyaSize framebufferSize, FreyaTextureOptions textureOptions, bool onlyTexture)
	{
		std::shared_ptr<FreyaFrameBuffer> framebufferFromeCache = nullptr;
		std::string lookupHash;
		hashForSize(lookupHash,framebufferSize, textureOptions, onlyTexture);
		int iter = framebufferTypeCounts[lookupHash];


		if (iter < 1)
		{
			framebufferFromeCache = std::make_shared<FreyaFrameBuffer>(framebufferSize.width,framebufferSize.height,textureOptions,onlyTexture);
		}
		else
		{
			int currentTextureID = iter - 1;
			while (framebufferFromeCache == nullptr && currentTextureID >= 0)
			{
				std::string textureHash;
				format_hash(textureHash, "%@-%ld", lookupHash, currentTextureID);
				framebufferFromeCache = framebufferCache[textureHash];
				if (framebufferFromeCache != nullptr)
				{
					framebufferCache.erase(textureHash);
				}
				currentTextureID --;
			}
			
			currentTextureID++;

			framebufferTypeCounts[lookupHash] = currentTextureID;

			if (framebufferFromeCache == nullptr)
			{
				framebufferFromeCache = std::make_shared<FreyaFrameBuffer>(framebufferSize.width, framebufferSize.height, textureOptions, onlyTexture);
			}
		}
		framebufferFromeCache->lock();
		return framebufferFromeCache;
	}

	std::shared_ptr<FreyaFrameBuffer> FreyaFrameBufferCache::fetchFramebufferForSize(FreyaSize framebufferSize, bool onlyTexture)
	{
		FreyaTextureOptions defaultTextureOptions;
		defaultTextureOptions.minFilter = GL_LINEAR;
		defaultTextureOptions.magFilter = GL_LINEAR;
		defaultTextureOptions.wrapS = GL_CLAMP_TO_EDGE;
		defaultTextureOptions.wrapT = GL_CLAMP_TO_EDGE;
		defaultTextureOptions.internalFormat = GL_RGBA8;
		defaultTextureOptions.format = GL_BGRA;
		defaultTextureOptions.type = GL_UNSIGNED_BYTE;

		return fetchFramebufferForSize(framebufferSize,defaultTextureOptions,onlyTexture);
	}

	void FreyaFrameBufferCache::returnFramebufferToCache(std::shared_ptr<FreyaFrameBuffer> buffer)
	{
		buffer->clearAllLocks();

		FreyaSize framebufferSize = FreyaSize::make((float)buffer->width, (float)buffer->height);
		FreyaTextureOptions framebufferTextureOptions = buffer->textureOptions;
		std::string lookupHash;
		hashForSize(lookupHash,framebufferSize, framebufferTextureOptions, buffer->missingFramebuffer);
		auto numberOfMatchingTextures = framebufferTypeCounts[lookupHash];

		std::string textureHash;
		format_hash(textureHash, "%@-%ld",lookupHash,numberOfMatchingTextures);

		framebufferCache[textureHash] = buffer;
		framebufferTypeCounts[lookupHash] = numberOfMatchingTextures + 1;
	}

	void FreyaFrameBufferCache::purgeAllUnassignedFramebuffers()
	{
		framebufferCache.clear();
		framebufferTypeCounts.clear();
	}

	void FreyaFrameBufferCache::addFramebufferToActiveImageCaptureList(std::shared_ptr<FreyaFrameBuffer> framebuffer)
	{
		activeImageCaptureList.push_back(framebuffer);
	}

	void FreyaFrameBufferCache::removeFramebufferFromActiveImageCaptureList(std::shared_ptr<FreyaFrameBuffer> framebuffer)
	{
		auto it = std::find(activeImageCaptureList.begin(),activeImageCaptureList.end(),framebuffer);
		if(it != activeImageCaptureList.end())activeImageCaptureList.erase(it);
	}

	std::string& FreyaFrameBufferCache::hashForSize(std::string& hash, FreyaSize size, FreyaTextureOptions textureOptions, bool onlyTexture)
	{
		if (onlyTexture)
		{
			format_hash(hash, "%.1fx%.1f-%d:%d:%d:%d:%d:%d:%d-NOFB", size.width, size.height, textureOptions.minFilter, textureOptions.magFilter, textureOptions.wrapS, textureOptions.wrapT, textureOptions.internalFormat, textureOptions.format, textureOptions.type);
		}
		else
		{
			format_hash(hash, "%.1fx%.1f-%d:%d:%d:%d:%d:%d:%d", size.width, size.height, textureOptions.minFilter, textureOptions.magFilter, textureOptions.wrapS, textureOptions.wrapT, textureOptions.internalFormat, textureOptions.format, textureOptions.type);
		}
		return hash;
	}

	std::string& FreyaFrameBufferCache::format_hash(std::string& hash_formatted, const char* str_hash, ...) {
		va_list arglist;
		va_start(arglist, str_hash);
		FLOG::format_str(hash_formatted, str_hash, arglist);
		va_end(arglist);
		return hash_formatted;
	};
};