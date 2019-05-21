import QtQuick 2.12
import QtQuick.Controls 2.5

import Dx.Sequence 1.0
import Dx.Global 1.0

Page {
    id: boxready_page
    Image {
        id: startbutton
        anchors.centerIn: parent

        source: "qrc:/image/line.png"
    }
    Text{
        id: panelName

        text:ExGlobal.panelName
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: -30
    }
    Text{
        id: panelLot

        text:ExGlobal.panelCode
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: +30
    }
    Text{
        id: sampleNo

        text:ExGlobal.sampleCode
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: +300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: -30
    }
    Text{
        id: sampleInfo

        text:ExGlobal.sampleInfo
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: +300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: +30
    }    

    Text{
        id: userName

        text:ExGlobal.user
        font.pixelSize: 30
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
    }

    Button {
        id: btCannel
        x: 523
        y: 426
        text: qsTr("取消测试")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        onClicked: {
            Sequence.sequenceCancel();
            stackView.pop();
            stackView.push("qrc:/HomeUI/Idle.qml");
        }
    }

    Component.onCompleted: {
        Sequence.sequenceDo(Sequence.Sequence_Test);
    }

    Connections{
        target: Sequence
        onProcessFinish:{
            console.log("TestProcess.qml,total:"+total+",finish:"+finish);
            home_page.testprocess = finish;
        }

        onSequenceFinish:{
            if (result == Sequence.Result_SelfCheck_ok)
            {
                stackView.pop();
                stackView.push("qrc:/HomeUI/Login.qml");
            }
            console.log("TestProcess.qml,result:"+result);
        }
    }
}

