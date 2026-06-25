#include "NameComponent.h"

std::string NameComponent::getName() {
	return name;
}

std::string NameComponent::getTitle() {
	return title;
}

std::string NameComponent::getName() const {
	return name;
}

std::string NameComponent::getTitle() const {
	return title;
}

std::string NameComponent::getFullName() {
	return (getName() + " " + getTitle());
}

std::string NameComponent::getFullName() const {
	return (getName() + " " + getTitle());
}

void NameComponent::setName(std::string name) {
	this->name = name;
}

void NameComponent::setTitle(std::string title) {
	this->title = title;
}
