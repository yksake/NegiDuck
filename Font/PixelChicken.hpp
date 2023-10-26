#pragma once
#include <Siv3D.hpp>

class PixelChicken
{
public:
	static uint8 DefaultSize;


	static RectF Region(const String& text, const uint8 size, const Vec2& pos = Vec2{ 0, 0 });

	static RectF Draw(const String& text, const uint8 size, const Vec2& pos, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const Vec2& pos, const ColorF& color = Palette::White);

	static RectF Draw(const String& text, const uint8 size, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, const uint8 size, Arg::center_<Vec2> center, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White);
	static RectF Draw(const String& text, Arg::center_<Vec2> center, const ColorF& color = Palette::White);


private:
	static const String m_FontAssetName;
	static constexpr uint8 m_BaseSize = 40;
	static constexpr uint8 m_RightMargin = 5;
	static constexpr uint8 m_BottomMargin = 5;


	PixelChicken();
};
