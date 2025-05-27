#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <functional>


enum class EManagerType : char {
	NONE = 0,
	RESOURCES,
	SHADERS,
	EVENTS,
	INPUT,
	CAMERA
};

enum class ESystemType : char {
	NONE = 0,
	TASK
};


class Logger;
class GameApp;
class GameStorage;

namespace graphics {
	class Shader;
}
namespace events {
	class BaseEvent;
	enum class EEventType : char;
}

enum class EInputButtonType : char;
struct MouseMove;
struct MouseWheel;

struct ImageData;


class Globals {
public:
	~Globals();

	Globals(Globals const&) = delete;
	void operator=(Globals const&) = delete;

	static Globals* Get() {
		if (!m_instance) {
			m_instance.reset(new Globals());
		}
		return m_instance.get();
	}

	template<class T>
	static T* GetManager(const EManagerType& managerType);

	template<class T>
	static T* GetSystem(const ESystemType& systemType);

	static std::string ReadTextFile(const std::string& path, bool dontSave = false);
	static void AsyncReadTextFile(const std::string& path, std::function<void(const std::string&)> callback, bool dontSave = false);
	static const std::shared_ptr<graphics::Shader> GetShader(const std::string& shaderName);
	static std::vector<std::shared_ptr<graphics::Shader>> GetAllShaders();
	static ImageData* GetImageData(const std::string& imagePath);
	static void AsyncGetImageData(const std::string& imagePath, std::function<void(ImageData*)> callback);

	static void AddEventListener(const events::EEventType& type, void* owner, std::function<void(const events::BaseEvent&)> callback);
	static void RemoveEventListener(void* owner, const events::EEventType& type = (events::EEventType)0);
	static void DispatchEvent(const events::BaseEvent& event);

	static bool KeyIsPressed(int key, const EInputButtonType& type);
	static const MouseMove& MouseMoveDelta();
	static const MouseWheel& MouseWheelDelta();

	static float GetTime();
	static float GetDeltaTime();
	static void ExitGame();

	void SetLogger(Logger* ptr);
	Logger* GetLogger() const { return m_logger; }

	void SetGame(GameApp* ptr);
	GameApp* GetGame() const { return m_game; }

private:
	Globals();
	static const GameStorage* GetGS();

private:
	static inline std::unique_ptr<Globals> m_instance = nullptr;

	Logger* m_logger;
	GameApp* m_game;

};


template<class T>
inline T* Globals::GetManager(const EManagerType& managerType)
{
	void* ptr = nullptr;
	switch (managerType) {
	case EManagerType::RESOURCES: ptr = GetGS()->GetResourcesManager(); break;
	case EManagerType::SHADERS: ptr = GetGS()->GetShadersManager(); break;
	case EManagerType::EVENTS: ptr = GetGS()->GetEventsManager(); break;
	case EManagerType::INPUT: ptr = GetGS()->GetInputManager(); break;
	case EManagerType::CAMERA: ptr = GetGS()->GetCameraManager(); break;
	}
	if (ptr == nullptr) {
		char errorMsg[130];
		sprintf_s(errorMsg, "Globals::GetManager pointer for EManagerType(%d) is nullptr!", (char)managerType);
		throw std::runtime_error(errorMsg);
	}
	return reinterpret_cast<T*>(ptr);
}

template<class T>
inline T* Globals::GetSystem(const ESystemType& systemType)
{
	void* ptr = nullptr;
	switch (systemType) {
	case ESystemType::TASK: ptr = GetGS()->GetTaskSystem(); break;
	}
	if (ptr == nullptr) {
		char errorMsg[130];
		sprintf_s(errorMsg, "Globals::GetSystem pointer for ESystemType(%d) is nullptr!", (char)systemType);
		throw std::runtime_error(errorMsg);
	}
	return reinterpret_cast<T*>(ptr);
}
