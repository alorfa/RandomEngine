#pragma once

#include <SFML/Graphics/View.hpp>
#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Math/vec2.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace random_engine
{
	class Camera
	{
		sf::View camera;

		static Camera* default_camera;
	public:
		inline void setSize(float x, float y) {
			camera.setSize(x, -y);
		}
		inline void setSize(const vec2& size) {
			camera.setSize(size.x, -size.y);
		}
		inline void zoom(float factor) {
			camera.zoom(factor);
		}
		inline void zoom(const vec2& factor) {
			camera.setSize(camera.getSize().x * factor.x, camera.getSize().y * factor.y);
		}
		inline vec2 getSize() const {
			return { camera.getSize().x, -camera.getSize().y };
		}

		inline void setPosition(float x, float y) {
			camera.setCenter(x, y);
		}
		inline void setPosition(const vec2& pos) {
			camera.setCenter(pos);
		}
		inline void move(const vec2& offset) {
			camera.move(offset);
		}
		inline const vec2& getPosition() const {
			return reinterpret_cast<const vec2&>(camera.getCenter());
		}

		inline void setRotation(float rad) {
			camera.setRotation(Math::deg(rad));
		}
		inline void rotate(float rad) {
			setRotation(getRotation() + rad);
		}
		inline float getRotation() const {
			Math::rad(camera.getRotation());
		}

		inline void setTransform(const sf::Transformable& transform) {
			setPosition(transform.getPosition());
			setSize(transform.getScale());
			setRotation(transform.getRotation());
		}

		static const Camera& getDefault();

		inline const sf::View& getSFMLView() const {
			return camera;
		}
	};
}