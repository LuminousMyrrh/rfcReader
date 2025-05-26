#ifndef RFCWORKER_H
#define RFCWORKER_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QRegularExpression>

class RfcWorker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList pages READ getRfcPages NOTIFY pagesChanged)
    Q_PROPERTY(int currentPage READ getCurrentRfcPage NOTIFY currentRfcPageChanged)
    Q_PROPERTY(QString currentPageText READ getCurrentPageText NOTIFY currentRfcPageChanged)
public:
    RfcWorker(QObject *parent = nullptr);

    Q_INVOKABLE void setCurrentRfcNumber(const int number);
    Q_INVOKABLE void setCurrentRfcPage(const int page);
    void setRfcText(const QString &text);

    QString getRfcText() const { return plainRfcText; }
    QVector<QString> getRfcPages() const { return rfcPages; }
    int getCurrentRfcNumber() const;
    int getCurrentRfcPage() const;
    QString getCurrentPageText() const;


signals:
    void textChanged();
    void pagesChanged();
    void currentRfcNumberChanged();
    void currentRfcPageChanged();

private:
    QString plainRfcText;
    QStringList rfcPages;
    QRegularExpression regexSeparator;
    int currentRfcNumber;
    int currentRfcPage;

    void parseToPages();
};

#endif // RFCWORKER_H
