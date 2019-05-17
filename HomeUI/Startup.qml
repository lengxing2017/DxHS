import QtQuick 2.12
import QtQuick.Controls 2.5

import Dx.Sequence 1.0
Page {
    id: start_page
    Image {
        id: appicon
        anchors.centerIn: parent

        source: "qrc:/image/Dxlogo.png"
    }
    Component.onCompleted: {
        home_page.titlemsg=qsTr("系统启动......");
        home_page.enableTabBar = false;
        Sequence.sequenceDo(Sequence.Sequence_SelfCheck);
    }

    Connections{
        target: Sequence
        onSequenceFinish:{
            if (result == Sequence.Result_SelfCheck_ok)
            {
                stackView.pop();
                stackView.push("qrc:/HomeUI/Login.qml");
            }
            console.log("Startup.qml,result:"+result);
        }
    }
}
