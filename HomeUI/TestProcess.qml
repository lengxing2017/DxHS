import QtQuick 2.12
import QtQuick.Controls 2.5

import Dx.Sequence 1.0
Page {
    id: boxready_page
    Image {
        id: startbutton
        anchors.centerIn: parent

        source: "qrc:/image/start.png"
    }
    Text{
        id: panelName

        text:"上呼吸道测试"
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: -30
    }
    Text{
        id: panelLot

        text:"Lot# 0180434"
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: -300
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: +30
    }
    Text{
        id: sampleNo

        text:"SLX 01079"
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: +200
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: -30
    }
    Text{
        id: sampleInfo

        text:"华山11"
        font.pixelSize: 30
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: +200
        anchors.verticalCenter: startbutton.verticalCenter
        anchors.verticalCenterOffset: +30
    }
    Image {
        id: editsample
        anchors.horizontalCenter: startbutton.horizontalCenter
        anchors.horizontalCenterOffset: +300
        anchors.verticalCenter: startbutton.verticalCenter
        source: "qrc:/image/editInfo.png"
    }

    Text{
        id: userName

        text:"user001"
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

