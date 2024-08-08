#pragma once

namespace base
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		bool load();
		bool store();
		bool reset();

		struct options
		{
			bool render_optimizations{ false };
			bool session_logger{ false };
		}
		m_options{};

	private:
		bool load_impl();
	};

	inline settings g_settings;
}
