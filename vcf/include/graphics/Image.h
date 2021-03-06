/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

/* Generated by Together */

#ifndef IMAGE_H
#define IMAGE_H



namespace VCF{


class ImageListener;

class ImageBits;

class GraphicsContext;

enum ImageBitDepth{
	BD_8BP=0,
	BD_16BP,
	BD_24BP,
	BD_32BP,//default - RGBA
	BD_48BP,
	BD_64BP,
};

/**
*interface Image
*/
class GRAPHICSKIT_API Image {
public:	
	virtual ~Image(){};

    virtual ImageBitDepth getBitDepth() = 0;    

    virtual void setWidth(const unsigned long & width)=0;

    virtual unsigned long getWidth()=0;

    virtual void setHeight(const unsigned long & height)=0;

    virtual unsigned long getHeight()=0;

    virtual void addImageSizeChangedHandler( EventHandler* handler ) = 0;

    virtual void removeImageSizeChangedHandler( EventHandler* handler ) = 0;

	virtual ImageBits* getImageBits() = 0;

	virtual GraphicsContext* getImageContext() = 0;

	/**
	*returns the color that is used to blend with the contents of
	*a GraphicsContext when the Image is drawn. Only used when the 
	*Image is set to Transparent
	*/
	virtual Color* getTransparencyColor() = 0;

	virtual void setTransparencyColor( Color* transparencyColor ) = 0;

	/**
	*Indicates whether or not the Image is using a transparent
	*color.
	*@return bool if this is true then the Image is transparent
	*and the contents of the underlying GraphicsContext will show through
	*wherever a pixel in the image is found that is the transparency color
	*/
	virtual bool isTransparent() = 0;

	virtual void setIsTransparent( const bool& transparent ) = 0;
};

};
#endif //IMAGE_H