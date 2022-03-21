/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef TERMSANDCONDITIONSCONTROL_HPP
#define TERMSANDCONDITIONSCONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <QtCore/QObject>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Sheet>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActivityIndicator>

#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>

#include <unistd.h>
#include "HomeControl.hpp"
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with the Login to the COnnectAPI.
 */
class TermsAndConditionsControl;

class TermsWorker : public QObject //TODO - JESSE This is where you should have the methods to download the image, you have to communicate with the DownloadManager class using SIGNAL and SLOT

{
    Q_OBJECT
    QThread termsThread;
    TermsAndConditionsControl * termsControl;
    public Q_SLOTS:
        void handleTerms();

    public:
        TermsWorker(TermsAndConditionsControl * control);
};
class TermsAndConditionsControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QVariantMap m_termsnConditions READ termsnConditions NOTIFY tncScreenStatusChanged )

public:
    TermsAndConditionsControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);
    void setRoot(Sheet *root = 0);

public Q_SLOTS:
    void requestTerms();
    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void tncScreenStatusChanged();

private Q_SLOTS:
    /*
     * Handles the complete signal from TermsRequest when
     * the request is complete
     * @see LoginRequest::complete()
     */
    void onTermsAndConditionsResponse(const QString &info, bool success);

private:
    /*
     * Parses the JSON response
     */
    void parseTermsAndConditionsResponse(const QString&);

    bool active() const;
    bool error() const;
    QString errorMessage() const;

    QVariantMap termsnConditions() const;

private:
    AbstractPane *homeSource;
    Page *rootSource;
    Sheet *sheetSource;
    ActivityIndicator* m_ActivityIndicator;
    bool m_error;
    QString m_errorMessage;
    QVariantMap m_termsnConditions;
public:
    bool m_active;
};

#endif
