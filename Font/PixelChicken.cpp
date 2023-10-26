#include "PixelChicken.hpp"

const String PixelChicken::m_FontAssetName = U"font";
uint8 PixelChicken::DefaultSize = 2;


PixelChicken::PixelChicken()
{
	
}


RectF PixelChicken::Region(const String& text, const uint8 size, const Vec2& pos)
{
	const double fontSize = m_BaseSize * size;

	const double top = 0;
	const double right = -m_RightMargin * size;
	const double bottom = -m_BottomMargin * size;
	const double left = 0;

	RectF rect = FontAsset(m_FontAssetName)(text).region(fontSize, pos);
	rect = rect.stretched(top, right, bottom, left);

	return rect;
}


RectF PixelChicken::Draw(const String& text, const uint8 size, const Vec2& pos, const ColorF& color)
{
	const double fontSize = m_BaseSize * size;

	return FontAsset(m_FontAssetName)(text).draw(fontSize, pos, color);
}

RectF PixelChicken::Draw(const String& text, const Vec2& pos, const ColorF& color)
{
	return Draw(text, DefaultSize, pos, color);
}


RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::topLeft_<Vec2> topLeft, const ColorF& color)
{
	return Draw(text, size, *topLeft, color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::topCenter_<Vec2> topCenter, const ColorF& color)
{
	const double x = -Region(text, size).w * 0.5;

	return Draw(text, size, topCenter->movedBy(x, 0), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::topRight_<Vec2> topRight, const ColorF& color)
{
	const double x = -Region(text, size).w;

	return Draw(text, size, topRight->movedBy(x, 0), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color)
{
	const RectF textRegion = Region(text, size);

	return Draw(text, size, rightCenter->movedBy(-textRegion.w, -textRegion.h * 0.5), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color)
{
	return Draw(text, size, bottomRight->movedBy(-Region(text, size).size), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color)
{
	const RectF textRegion = Region(text, size);

	return Draw(text, size, bottomCenter->movedBy(-textRegion.w * 0.5, -textRegion.h), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color)
{
	return Draw(text, size, bottomLeft->movedBy(0, -Region(text, size).h), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color)
{
	return Draw(text, size, leftCenter->movedBy(0, -Region(text, size).h * 0.5), color);
}

RectF PixelChicken::Draw(const String& text, const uint8 size, const Arg::center_<Vec2> center, const ColorF& color)
{
	return Draw(text, size, center->movedBy(-Region(text, size).size * 0.5), color);
}


RectF PixelChicken::Draw(const String& text, const Arg::topLeft_<Vec2> topLeft, const ColorF& color)
{
	return Draw(text, DefaultSize, topLeft, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::topCenter_<Vec2> topCenter, const ColorF& color)
{
	return Draw(text, DefaultSize, topCenter, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::topRight_<Vec2> topRight, const ColorF& color)
{
	return Draw(text, DefaultSize, topRight, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color)
{
	return Draw(text, DefaultSize, rightCenter, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color)
{
	return Draw(text, DefaultSize, bottomRight, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color)
{
	return Draw(text, DefaultSize, bottomCenter, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color)
{
	return Draw(text, DefaultSize, bottomLeft, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color)
{
	return Draw(text, DefaultSize, leftCenter, color);
}

RectF PixelChicken::Draw(const String& text, const Arg::center_<Vec2> center, const ColorF& color)
{
	return Draw(text, DefaultSize, center, color);
}
