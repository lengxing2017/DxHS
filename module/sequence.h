#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QObject>
#include <QQmlEngine>
#include <QtCore>

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

signals:
    void sequenceFinish(SequenceResult result);
    void processFinish(int total,int finish);

public slots:
    void SequenceTimeout();

private:
    bool ReadTestProcess(QString panel);
    QTimer *timer;
    SequenceId currSequenceId;
    int nFinishCount;
};

static QObject *sequence_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    Sequence *sequence = new Sequence();
    return sequence;
}
#endif // SEQUENCE_H
