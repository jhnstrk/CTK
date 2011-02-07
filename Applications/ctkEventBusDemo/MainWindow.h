#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>

#define mafList QList
#define mafVariant QVariant

class ctkEventBus;

namespace Ui {
    class MainWindow;
}

class ctkEventDemo : public QObject {
    Q_OBJECT

signals:
    void receiveEventSignal(mafList<mafVariant> l);
    void updateMessageSignal(QString message);

public slots:
    void receiveEvent(mafList<mafVariant> l);
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    MainWindow(ctkEventBus *bus, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sendEvent();
    void updateMessage(QString message);
    void connectClient();

protected:
    void changeEvent(QEvent *e);
    void connectEvents();

private:
    Ui::MainWindow *ui;
    ctkEventBus *m_EventBus;

    ctkEventDemo *handler;
};

#endif // MAINWINDOW_H
