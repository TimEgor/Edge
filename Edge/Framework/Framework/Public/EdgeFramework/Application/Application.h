#pragma once

#include "EdgeCommon/Clock.h"
#include "EdgeCommon/Patterns/NonCopyable.h"

#include "EdgeCommon/Job/JobGraph.h"

#include "EdgeFramework/PluginController/PluginHandle.h"
#include "EdgeFramework/WindowController/WindowHandle.h"

namespace Edge
{
	class FileName;
	class EventController;
	class PluginController;
	class Platform;
	class InputDeviceController;
	class WindowController;
	class JobController;

	class AssetsDirectoryController;

	class GraphicPlatform;
	class RenderController;
	class WindowGraphicPresenter;

	class Application : public NonCopyable
	{
	private:
		ClockTimePoint m_startTime;
		ClockTimePoint m_currentFrameTime;
		ClockTimePoint m_prevFrameStartTime;

		EventController* m_eventController = nullptr;
		PluginController* m_pluginController = nullptr;
		Platform* m_platform = nullptr;
		InputDeviceController* m_inputDeviceController = nullptr;
		WindowController* m_windowController = nullptr;
		JobController* m_jobController = nullptr;

		AssetsDirectoryController* m_assetsDirectoryController = nullptr;

		GraphicPlatform* m_graphicPlatform = nullptr;
		RenderController* m_renderController = nullptr;
		WindowGraphicPresenter* m_windowGraphicPresenter = nullptr;

		PluginHandleReference m_platformPluginHandle;
		PluginHandleReference m_graphicPlatformPluginHandle;

		WindowHandleReference m_mainWindowHandle;

		float m_deltaTime = 0.0f;
		float m_timeScale = 1.0f;

		bool m_isStopped = false;
		bool m_isPaused = false;

		void parseArgsParams(FileName& platformPluginPath, FileName& graphicPluginPath, FileName& rendererPluginPath);

		bool initPlatform(const FileName& platformPluginPath);
		bool initGraphicPlatform(const FileName& graphicPlatformPluginPath);

		bool initGraphic(const FileName& graphicPluginPath, const FileName& rendererPluginPath);
		void releaseGraphic();

		void beginFrame();
		void endFrame();

	protected:
		virtual JobGraphReference getMainLoopJobGraph() = 0;

	public:
		Application() = default;
		virtual ~Application() = default;

		virtual bool init();
		virtual void release();

		void run();
		void stop();
		void pause();
		void unpause();

		float getDeltaTime() const;
		void setTimeScale(float scale);

		bool isStopped() const;
		bool isPaused() const;

		EventController& getEventController() const;
		PluginController& getPluginController() const;
		Platform& getPlatform() const;
		InputDeviceController& getInputDeviceController() const;
		WindowController& getWindowController() const;
		JobController& getJobController() const;

		AssetsDirectoryController& getAssetsDirectoryController() const;

		GraphicPlatform& getGraphicPlatform() const;
		RenderController& getRenderController() const;
		WindowGraphicPresenter& getWindowGraphicPresenter() const;
	};
}
