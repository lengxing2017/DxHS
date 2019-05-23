#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QObject>
#include <QQmlEngine>
#include <QtCore>
#include <QtXml>

class Sequence : public QObject
{
    Q_OBJECT
public:
    explicit Sequence(QObject *parent = nullptr);
    enum class SequenceId{
        Sequence_Idle,
        Sequence_SelfCheck,
        Sequence_OpenBox,
        Sequence_CloseBox,
        Sequence_Test
    };
    Q_ENUM(SequenceId)

    enum class SequenceResult{
        Result_ok,
        Result_fail,
        Result_SelfCheck_ok,
        Result_SelfCheck_err1,
        Result_SelfCheck_err2,
        Result_OpenBox_ok,
        Result_OpenBox_err,
        Result_CloseBox_ok,
        Result_CloseBox_err,
        Result_Test_DataErr,
        Result_Test_ProcessErr
    };
    Q_ENUM(SequenceResult)

    Q_INVOKABLE void sequenceDo(SequenceId id);
    Q_INVOKABLE void sequenceCancel();
    Q_INVOKABLE QString sequenceMessage();

signals:
    void sequenceFinish(SequenceResult result);
    void processFinish(int total,int finish);

public slots:
    void SequenceTimeout();

private:
    bool ReadTestProcess(QString panel);
    bool WriteTestProcess(QString panel);
    bool DoAction(QDomElement action);
    bool FindAction(bool bFinishAction);
    int CalSteps(QDomElement element);
    bool FormatAction();
    QDomDocument doc;
    QTimer *timer;
    SequenceId currSequenceId;    
    QString message;
};

static QObject *sequence_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    Sequence *sequence = new Sequence();
    return sequence;
}
#endif // SEQUENCE_H
