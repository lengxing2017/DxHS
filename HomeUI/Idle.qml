import QtQuick 2.12
import QtQuick.Controls 2.5

import Dx.Sequence 1.0
import Dx.Global 1.0

Page {
    id: idle_page
    Image {
        id: openDoor
        //anchors.horizontalCenter: parent.horizontalCenter

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -60

        source: "qrc:/image/openDoor.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                Sequence.sequenceDo(Sequence.Sequence_OpenBox);
            }            
        }
    }
    Text{
        id: boxstate

        text:"未检测到试剂盒"
        font.pixelSize: 30
        anchors.top: openDoor.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: openDoor.horizontalCenter
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
        id: btClose
        x: 523
        y: 426
        text: qsTr("关机")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        onClicked: Qt.quit()
    }

    Button {
        id: btExit
        x: 523
        y: 379
        text: qsTr("退出登录")
        anchors.bottom: btClose.top
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        onClicked: {
            stackView.pop();
            stackView.push("qrc:/HomeUI/Login.qml");
        }
    }

    Component.onCompleted: {
        home_page.titlemsg=qsTr("待机");
        home_page.enableTabBar = true;
    }

    Connections{
        target: Sequence
        onSequenceFinish:{
            if (result == Sequence.Result_OpenBox_ok)
            {
                stackView.pop();
                stackView.push("qrc:/HomeUI/BoxReady.qml");
            }
            console.log("idle.qml,result:"+result);
        }
    }
}
