import QtQuick
import QtQuick.Controls


Item {
    Text {
        id: currentTrackedTimeDisplay
        x: 325
        height: 44
        text: currentTrackedTime
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 10
        font.pixelSize: 29
        horizontalAlignment: Text.AlignHCenter
    }
}
