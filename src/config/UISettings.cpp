#include "UISettings.h"

unsigned int UISettings::getPaddingPercent() {
	return this->padding_percent;
}

unsigned int UISettings::getWindowWidth() {
	return this->window_width;
}

unsigned int UISettings::getWindowHeight() {
	return this->window_height;
}

void UISettings::setPaddingPercent(unsigned int padding_percent) {
	this->padding_percent = padding_percent;
}

void UISettings::setWindowWidth(unsigned int window_width) {
	this->window_width = window_width;
}

void UISettings::setWindowHeight(unsigned int window_height) {
	this->window_height = window_height;
}

unsigned int UISettings::getPaddingWidth() {
	return static_cast<unsigned int>((this->window_width * this->padding_percent) / 100.0);
}

unsigned int UISettings::getPaddingHeight() {
	return static_cast<unsigned int>((this->window_height * this->padding_percent) / 100.0);
}

unsigned int UISettings::getCentralWidth() {
	return static_cast<unsigned int>(this->window_width / 2);
}

unsigned int UISettings::getCentralHeight() {
	return static_cast<unsigned int>(this->window_height / 2);
}
