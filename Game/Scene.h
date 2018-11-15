#pragma once

// <シーン>
class Scene
{
	public:
		Scene() = default;
		virtual ~Scene() = default;

	public:
		virtual void Update() = 0;
		virtual void Render() = 0;
};
