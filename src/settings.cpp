#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject(parent), mainSettings("FOSS", "RfcReader") {
    // Set default values only if keys don't exist
    if (!mainSettings.contains("lastRfc")) {
        mainSettings.setValue("lastRfc", -1);
    }
    if (!mainSettings.contains("lastPage")) {
        mainSettings.setValue("lastPage", -1);
    }
}

void Settings::setLastRfc(int rfc) {
    mainSettings.setValue("lastRfc", rfc);
    mainSettings.sync();
}

void Settings::setLastPage(int page) {
    mainSettings.setValue("lastPage", page);
    mainSettings.sync();
}

int Settings::getLastRfc() const {
    return mainSettings.value("lastRfc", -1).toInt();
}

int Settings::getLastPage() const {
    return mainSettings.value("lastPage", -1).toInt();
}
