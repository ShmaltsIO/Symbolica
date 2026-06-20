#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

class UISettings {
private:
	unsigned int padding_percent = 5;
	unsigned int window_width = 50;
	unsigned int window_height = 150;

public:
	UISettings() = default;
	UISettings(unsigned int padding_percent, unsigned int window_width, unsigned int window_height) : padding_percent(padding_percent), 
		window_width(window_width), window_height(window_height) {}

	~UISettings() = default;

	unsigned int getPaddingPercent();
	unsigned int getWindowWidth();
	unsigned int getWindowHeight();

	void setPaddingPercent(unsigned int padding_percent);
	void setWindowWidth(unsigned int window_width);
	void setWindowHeight(unsigned int window_height);

	unsigned int getPaddingWidth();
	unsigned int getPaddingHeight();
	unsigned int getCentralWidth();
	unsigned int getCentralHeight();
};

#endif // UI_SETTINGS_H