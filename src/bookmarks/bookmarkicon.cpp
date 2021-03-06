/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  David Rosca
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
#include "bookmarkicon.h"
#include "mainapplication.h"
#include "qupzilla.h"
#include "bookmarksmodel.h"
#include "bookmarkswidget.h"

BookmarkIcon::BookmarkIcon(QupZilla* mainClass, QWidget* parent)
    : ClickableLabel(parent)
    , p_QupZilla(mainClass)
    , m_bookmarksModel(0)
{
    setObjectName("locationbar-bookmarkicon");
    setCursor(Qt::PointingHandCursor);
    setToolTip(tr("Bookmark this Page"));
    setFocusPolicy(Qt::ClickFocus);

    m_bookmarksModel = mApp->bookmarksModel();
    connect(this, SIGNAL(clicked(QPoint)), this, SLOT(iconClicked()));
    connect(m_bookmarksModel, SIGNAL(bookmarkAdded(BookmarksModel::Bookmark)), this, SLOT(bookmarkAdded(BookmarksModel::Bookmark)));
    connect(m_bookmarksModel, SIGNAL(bookmarkDeleted(BookmarksModel::Bookmark)), this, SLOT(bookmarkDeleted(BookmarksModel::Bookmark)));
}

void BookmarkIcon::iconClicked()
{
    QUrl url = p_QupZilla->weView()->url();

    if (m_bookmarksModel->isBookmarked(url)) {
        BookmarksWidget* menu = new BookmarksWidget(m_bookmarksModel->bookmarkId(url), p_QupZilla->locationBar());
        menu->showAt(this);
    }
    else {
        m_bookmarksModel->saveBookmark(p_QupZilla->weView());
    }
}

void BookmarkIcon::checkBookmark(const QUrl &url)
{
    if (m_lastUrl == url) {
        return;
    }

    if (m_bookmarksModel->isBookmarked(url)) {
        setBookmarkSaved();
    }
    else {
        setBookmarkDisabled();
    }

    m_lastUrl = url;
}

void BookmarkIcon::bookmarkDeleted(const BookmarksModel::Bookmark &bookmark)
{
    if (bookmark.url == m_lastUrl) {
        setBookmarkDisabled();
    }
}

void BookmarkIcon::bookmarkAdded(const BookmarksModel::Bookmark &bookmark)
{
    if (bookmark.url == m_lastUrl) {
        setBookmarkSaved();
    }
}

void BookmarkIcon::setBookmarkSaved()
{
    setProperty("bookmarked", true);
    style()->unpolish(this);
    style()->polish(this);
    setToolTip(tr("Edit this bookmark"));
}

void BookmarkIcon::setBookmarkDisabled()
{
    setProperty("bookmarked", false);
    style()->unpolish(this);
    style()->polish(this);
    setToolTip(tr("Bookmark this Page"));
}
