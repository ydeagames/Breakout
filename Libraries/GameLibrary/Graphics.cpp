#include "Graphics.h"

namespace Graphics
{
	// <ƒxƒNƒgƒ‹‚ð•`‰æ>
	void DrawVector(const Vec2& vector, const Vec2& base, Color color, float Thickness = 1.f)
	{
		float arrow_length = 10 + Thickness * vector.Length()*.125f;
		float arrow_rota = vector.Angle();
		float arrow_rota1 = arrow_rota + MathUtils::ToRadians(-150);
		float arrow_rota2 = arrow_rota + MathUtils::ToRadians(150);
		DrawLineAA(base.x, base.y, base.x + x, base.y + y, color, Thickness);
		DrawLineAA(base.x + x, base.y + y, base.x + vector.x + (arrow_length * std::cosf(arrow_rota1)),
			base.y + vector.y + (arrow_length * std::sinf(arrow_rota1)), color, Thickness);
		DrawLineAA(base.x + x, base.y + y, base.x + vector.x + (arrow_length * std::cosf(arrow_rota2)),
			base.y + vector.y + (arrow_length * std::sinf(arrow_rota2)), color, Thickness);
	}
}