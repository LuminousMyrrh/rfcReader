#include "rfcworker.h"
#include "logger.h"
#include <QRegularExpression>

RfcWorker::RfcWorker(QObject *parent) : QObject(parent) {
    plainRfcText = QString();
    rfcPages = QVector<QString>();

    regexSeparator.setPattern("\\[Page \\d+\\]");
}

void RfcWorker::setCurrentRfcNumber(const int number) {
    currentRfcNumber = number;
    emit currentRfcNumberChanged();
}

void RfcWorker::setCurrentRfcPage(const int page) {
    currentRfcPage = page;
    emit currentRfcPageChanged();
}

void RfcWorker::setRfcText(const QString &text) {
    Logger::info("Setting rfc text");
    plainRfcText = text;
    parseToPages();
}

void RfcWorker::parseToPages() {
    rfcPages.clear();

    if (plainRfcText.isEmpty()) {
        Logger::info("No text to parse");
        emit pagesChanged();
        return;
    }

    QStringList pages = plainRfcText.split(regexSeparator, Qt::SkipEmptyParts);

    for (QString &page : pages) {
        page = page.trimmed();
        if (!page.isEmpty()) {
            rfcPages.push_back(page);
        }
    }

    Logger::info(QString("Parsed %1 pages").arg(rfcPages.length()).toStdString());

    emit pagesChanged();
}

int RfcWorker::getCurrentRfcNumber() const {
    return currentRfcNumber;
}

int RfcWorker::getCurrentRfcPage() const {
    return currentRfcPage;
}

QString RfcWorker::getCurrentPageText() const {
    return rfcPages.length() > 0 && currentRfcPage < rfcPages.length() ? rfcPages[currentRfcPage] : "No pages available";
}
