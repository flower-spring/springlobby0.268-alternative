/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

/// \file uiutils.h

#ifndef SPRINGLOBBY_HEADERGUARD_UIUTILS_H
#define SPRINGLOBBY_HEADERGUARD_UIUTILS_H

#include <lslutils/misc.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/intl.h>
#include <vector>
class wxColour;
class wxImage;
class wxIcon;
class wxBitmap;

bool AreColoursSimilar(const LSL::lslColor& col1, const LSL::lslColor& col2, int mindiff = 10);

void ColourDelta(int& r, int& g, int& b, const int& delta);
wxColour ColourDelta(const wxColour& colour, const int& delta);

//! takes best fitting size of original inside bounds keeping aspect ratio
wxSize MakeFit(const wxSize& original, const wxSize& bounds);

//! apply standard alpha blending to images
wxImage BlendImage(const wxImage& foreground, const wxImage& background, bool blend_alpha = true);
wxBitmap BlendBitmaps(const wxBitmap& background, const wxBitmap& overlay, const int dim = 16);
//! used to load png data into a wxImage
wxImage charArr2wxImage(const unsigned char* arg, int size);
//! used to load png data into a wxBitmap
wxBitmap charArr2wxBitmap(const unsigned char* arg, int size);
wxBitmap charArr2wxBitmapWithBlending(const unsigned char* arg, int size,
				      const unsigned char* text, int text_size);
//! png array data to Icon
wxIcon charArr2wxIcon(const unsigned char* arg, int size);

wxBitmap getColourIcon(const wxColour& colour);

//! shrinks/expands image by removing/duplicating rows/columns from the center of the image
wxImage BorderInvariantResizeImage(const wxImage& image, int width, int height);


wxImage ReplaceChannelStatusColour(wxBitmap img, const wxColour& colour);

std::vector<LSL::lslColor>& GetBigFixColoursPalette(int numteams);


void CopyToClipboard(const wxString& text);

//! open either platform default browser or binary saved in settings with given url
void OpenWebBrowser(const wxString& url);

inline wxString bool2yn(const bool b)
{
	return b ? _("Yes") : _("No");
}

//! when querying for a color, always use this (it'll autosave/retrieve custom defined colors)
wxColour GetColourFromUser(wxWindow* parent, const wxColour& colInit);

DECLARE_EVENT_TYPE(REFRESH_EVENT, wxID_ANY)

#endif
// SPRINGLOBBY_HEADERGUARD_UIUTILS_H
