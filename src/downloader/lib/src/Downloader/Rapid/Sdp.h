/* This file is part of pr-downloader (GPL v2 or later), see the LICENSE file */

#ifndef _SDP_H
#define _SDP_H

#include "FileSystem/FileData.h"

#include <string>
#include <list>
#include <memory>
#include <string>

#include "FileSystem/FileData.h"

#define LENGTH_SIZE 4

class IDownload;
class CFile;

class CSdp
{
public:
	CSdp(const std::string& shortname, const std::string& md5,
	     const std::string& name, const std::string& depends,
	     const std::string& baseUrl);
	CSdp(CSdp&& sdp);

	~CSdp();
	/**
          download a game, we already know the host where to download from + the
     md5 of the sdp file
          we have to download the sdp + parse it + download associated files
  */
	bool download(IDownload* dl);
	/**
          download the sdp file if it doesn't exist yet
  */
	bool downloadSelf(IDownload* dl);
	/**
          returns md5 of a repo
  */
	const std::string& getMD5() const
	{
		return md5;
	}
	/**
          returns the descriptional name
  */
	const std::string& getName() const
	{
		return name;
	}
	/**
          returns the shortname, for example ba:stable
  */
	const std::string& getShortName() const
	{
		return shortname;
	}
	/**
          returns the shortname, for example ba:stable
  */
	const std::string& getDepends() const
	{
		return depends;
	}

	IDownload* m_download = nullptr;
	std::list<FileData>::iterator list_it;
	std::list<FileData> files; // list with all files of an sdp
	std::unique_ptr<CFile> file_handle;
	std::string file_name;

	unsigned int file_pos = 0;
	unsigned int skipped = 0;
	unsigned char cursize_buf[LENGTH_SIZE];
	unsigned int cursize = 0;

private:
	void parse();
	/**
          download files streamed
          streamer.cgi works as follows:
          * The client does a POST to /streamer.cgi?<hex>
            Where hex = the name of the .sdp
          * The client then sends a gzipped bitarray representing the files
            it wishes to download. Bitarray is formated in the obvious way,
            an array of characters where each file in the sdp is represented
            by the (index mod 8) bit (shifted left) of the (index div 8) byte
            of the array.
          * streamer.cgi then responds with <big endian encoded int32 length>
            <data of gzipped pool file> for all files requested. Files in the
            pool are also gzipped, so there is no need to decompress unless
            you wish to verify integrity. Note: The filesize here isn't the same
            as in the .sdp, the sdp-file contains the uncompressed size
          * streamer.cgi also sets the Content-Length header in the reply so
            you can implement a proper progress bar.

  T 192.168.1.2:33202 -> 94.23.170.70:80 [AP]
  POST /streamer.cgi?652e5bb5028ff4d2fc7fe43a952668a7 HTTP/1.1..Accept-Encodi
  ng: identity..Content-Length: 29..Host: packages.springrts.com..Content-Typ
  e: application/x-www-form-urlencoded..Connection: close..User-Agent: Python
  -urllib/2.6....
  ##
  T 192.168.1.2:33202 -> 94.23.170.70:80 [AP]
  ......zL..c`..`d.....K.n/....
  */
	bool downloadStream();

	std::string name;
	std::string md5;
	std::string shortname;
	std::string baseUrl;
	std::string depends;
	std::string sdpPath;
	bool downloaded = false;
};

#endif
