#include "ExperienceComponent.h"

ExperienceComponent::ExperienceComponent(): experience_(0), experience_limit_(10) {}

ExperienceComponent::ExperienceComponent(unsigned int experience, unsigned int experience_limit):
 experience_(experience), experience_limit_(experience_limit) {}

void ExperienceComponent::setExperience(unsigned int experience) {
    experience_ = experience;
}

unsigned int ExperienceComponent::getExperience() {
    return experience_;
}

unsigned int ExperienceComponent::getExperience() const {
    return experience_;
}

void ExperienceComponent::setExperienceLimit(unsigned int experience_limit) {
    experience_limit_ = experience_limit;
}

unsigned int ExperienceComponent::getExperienceLimit() {
    return experience_limit_;
}

unsigned int ExperienceComponent::getExperienceLimit() const {
    return experience_limit_;
}
