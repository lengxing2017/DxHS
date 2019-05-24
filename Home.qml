import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    property string titlemsg: ""
    property bool enableTabBar: true
    property int testprocess: 0
    id: home_page

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: "./HomeUI/Startup.qml"
    }
    onTitlemsgChanged: {
        testCompleted.width = 0;
        testunCompleted.width = 0;
        headerMsg.text = titlemsg;
    }
    onEnableTabBarChanged: tabBar.enabled = enableTabBar;

    onTestprocessChanged: {
        if (testprocess <= 0 || testprocess >= 100)
        {
            testCompleted.width = 0;
            testunCompleted.width = 0;            
        }
        else
        {
            testCompleted.width = testprocess*headerRec.width/100;
            testunCompleted.x = testCompleted.width;
            testunCompleted.width = (100-testprocess)*headerRec.width/100;

        }        
    }
}
