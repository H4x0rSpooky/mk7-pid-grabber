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
			struct base
			{
				struct rainbow
				{
					float hue_amount{ 1.f / 600.f };
					float saturation{ 1.f };
					float value{ 1.f };
				}
				rainbow;
			}
			base;
		}
		m_options{};

	private:
		bool load_impl();
	};

	inline settings g_settings;
}
