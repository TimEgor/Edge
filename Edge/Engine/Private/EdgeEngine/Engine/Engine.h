#pragma once

#include "EdgeEngine/Core/Clock.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Plugin/PluginHandle.h"
#include "EdgeEngine/Window/WindowHandle.h"

namespace Edge {
	class WindowGraphicPresenter;
}

namespace Edge {
	class RenderController;
}

namespace Edge
{
	class FileName;
	class MessageController;
	class PluginController;
	class EventController;
	class WindowController;

	class Engine final : public IEngine
	{
	private:
		MessageController* m_messageController = nullptr;
		PluginController* m_pluginController = nullptr;

		EventController* m_eventController = nullptr;

		IPlatform* m_platform = nullptr;
		WindowController* m_windowController = nullptr;

		IGraphicPlatform* m_graphicPlatform = nullptr;
		RenderController* m_renderController = nullptr;

		PluginHandleReference m_platformPluginHandle;
		PluginHandleReference m_graphicPlatformPluginHandle;

		WindowHandleReference m_mainWindowHandle;
		WindowGraphicPresenter* m_windowGraphicPresenter = nullptr;

		ClockTimePoint m_startTime;
		ClockTimePoint m_currentFrameTime;
		ClockTimePoint m_prevFrameStartTime;

		float m_deltaTime = 0.0f;

		bool m_isStopped = false;
		bool m_isPaused = false;

		void parseArgsParams(FileName& platformPluginPath, FileName& graphicPluginPath, FileName& renderPluginPath);

		bool initPlatform(const FileName& platformPluginPath);
		bool initGraphicPlatform(const FileName& graphicPlatformPluginPath);

		bool initGraphic(const FileName& graphicPluginPath, const FileName& renderPluginPath);
		void releaseGraphic();

		void beginFrame();
		void endFrame();

		void updateFrame();

	public:
		Engine() = default;

		virtual bool init(const InitData& initData) override;
		virtual void release() override;

		virtual void run() override;
		virtual void stop() override;
		virtual void pause() override;
		virtual void unpause() override;

		virtual float getDeltaTime() const override;

		virtual bool isStopped() const override;
		virtual bool isPaused() const override;

		virtual IMessageController& getMessageController() const override;
		virtual IPluginController& getPluginController() const override;
		virtual IEventController& getEventController() const override;

		virtual IPlatform& getPlatform() const override;
		virtual IWindowController& getWindowController() const override;

		virtual IGraphicPlatform& getGraphicPlatform() const override;
		virtual IRenderController& getRenderController() const override;
	};
}
