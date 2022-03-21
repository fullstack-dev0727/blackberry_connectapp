/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef AppUi_HPP_
#define AppUi_HPP_

#include <QObject>

namespace bb
{
    namespace cascades
    {
        class LocaleHandler;
        class TouchEvent;
    }
}

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class AppUi : public QObject
{
    Q_OBJECT
public:
    AppUi();
    virtual ~AppUi() {}


private slots:
    void onSystemLanguageChanged();

private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
};

#endif /* AppUi_HPP_ */
