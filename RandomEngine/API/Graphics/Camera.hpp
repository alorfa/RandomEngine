#pragma once

#include <SFML/Graphics/View.hpp>
#include <RandomEngine/API/Math.hpp>
#include <RandomEngine/API/Math/vec2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Window.hpp>

namespace random_engine
{
	class Camera
	{
		static Camera* default_camera;
		static const sf::Window* window;

		sf::View camera;
		vec2 size;

		friend class Application;
		Camera(const sf::Window& wnd);
	public:
		using NativeSizeHandler = vec2(*)(const vec2& size, const sf::Window& wnd);
		NativeSizeHandler native_size_handler = nullptr;
		
		Camera();

		void updateNativeSize();

		inline void setSize(float x, float y) {
			size.x = x;
			size.y = y;
			updateNativeSize();
		}
		inline void setSize(const vec2& size) {
			setSize(size.x, size.y);
		}
		inline void scale(float factor) {
			setSize(getSize().x * factor, getSize().y * factor);
		}
		inline void scale(float factorX, float factorY)
		{
			setSize(getSize().x * factorX, getSize().y * factorY);
		}
		inline void scale(const vec2& factor) {
			setSize(getSize().x * factor.x, getSize().y * factor.y);
		}
		inline const vec2& getSize() const {
			return size;
		}
		inline vec2 getNativeSize() const {
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

		static vec2 defaultSizeHandler(const vec2& size, const sf::Window& wnd);
	};
}