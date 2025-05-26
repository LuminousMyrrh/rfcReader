#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings() = default;

    void setLastRfc(int rfc);
    void setLastPage(int page);

    int getLastRfc() const;
    int getLastPage() const;

private:
    QSettings mainSettings;
};

#endif // SETTINGS_H
