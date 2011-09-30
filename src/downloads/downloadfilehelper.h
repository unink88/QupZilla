#ifndef DOWNLOADFILEHELPER_H
#define DOWNLOADFILEHELPER_H

#include <QObject>
#include <QTime>
#include <QNetworkReply>
#include <QPixmap>
#include <QListWidget>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QFileIconProvider>
#include <QFileDialog>

class DownloadItem;
class DownloadFileHelper : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFileHelper(const QString &lastDownloadPath, const QString &downloadPath, bool useNativeDialog);
    ~DownloadFileHelper();

    void setListWidget(QListWidget* tw) { m_listWidget = tw; }
    void handleUnsupportedContent(QNetworkReply* reply, bool askWhatToDo);

signals:
    void itemCreated(QListWidgetItem* item, DownloadItem* downItem);

private slots:
    void optionsDialogAccepted(int finish);
    void fileNameChoosed(const QString &name, bool fileNameAutoGenerated = false);

private:
    QString getFileName(QNetworkReply* reply);

    QString m_lastDownloadPath;
    QString m_downloadPath;
    bool m_useNativeDialog;

    QTime* m_timer;
    QString m_path;
    QString m_fileName;
    QString m_userFileName;
    QString m_h_fileName;
    QNetworkReply* m_reply;
    QPixmap m_fileIcon;
    QUrl m_downloadPage;
    bool m_openFileChoosed;

    QListWidget* m_listWidget;
    QFileIconProvider* m_iconProvider;

};

#endif // DOWNLOADFILEHELPER_H
