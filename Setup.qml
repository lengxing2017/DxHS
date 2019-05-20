import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    property string titlemsg: qsTr("设置")
    id: setup_page
    Image {
        id: appicon
        anchors.centerIn: parent

        source: "qrc:/image/Dxlogo.png"
    }
    onTitlemsgChanged: headerMsg.text = titlemsg;
}
