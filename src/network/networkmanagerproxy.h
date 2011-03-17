/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  nowrep
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef NETWORKMANAGERPROXY_H
#define NETWORKMANAGERPROXY_H

#if defined(QT_NO_DEBUG) & !defined(QT_NO_DEBUG_OUTPUT)
#define QT_NO_DEBUG_OUTPUT
#endif

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class WebView;
class WebPage;
class QupZilla;

class NetworkManagerProxy : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit NetworkManagerProxy(QupZilla* mainClass, QObject* parent = 0);
    void setView(WebView* view) { m_view = view; }
    void setPage(WebPage* page) { m_page = page; }

    void setPrimaryNetworkAccessManager(NetworkManagerProxy* manager);
    QNetworkReply* createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &request, QIODevice* outgoingData);

protected:
    virtual void populateNetworkRequest(QNetworkRequest &request);

private:
    QupZilla* p_QupZilla;
    WebView* m_view;
    WebPage* m_page;
    NetworkManagerProxy* m_manager;
};

#endif // NETWORKMANAGERPROXY_H
