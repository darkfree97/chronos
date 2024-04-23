import QtQuick
import QtQuick.Controls

Item {
    Rectangle {
        width: 188
        anchors.fill: parent
        anchors.margins: 10
        color: Qt.color("white")

        ListView {
            id: historyDisplay
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: addNewTaskBtn.top
            anchors.bottomMargin: 10
            model: tasksData
            delegate: Item {
                width: historyDisplay.width
                height: 40

                Text {
                    text: modelData.title
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    font.bold: true
                    anchors.margins: 10
                }

                Text {
                    text: modelData.trackedTime
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: taskTimerTrigger.left
                    anchors.margins: 10
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: (evt) => {
                        if (evt.button === Qt.RightButton) {
                            taskContextMenu.popup()
                        } else {
                            selectedTask = modelData
                        }
                    }
                    onPressAndHold: {
                        taskContextMenu.popup()
                    }

                    Menu {
                        id: taskContextMenu
                        MenuItem {
                            text: "Delete"
                            onClicked: {
                                backend.deleteTask(modelData.id)
                            }
                        }
                    }
                }

                ToolButton {
                    id: taskTimerTrigger
                    text: (lastEvent?.state === "R" && lastEvent?.taskId === modelData.id) ? "\u23f8" : "\u23f5"
                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.margins: 10
                    width: 30
                    height: 30
                    onClicked: backend.triggerTaskTimer(modelData.id)
                }
            }
        }

        Button {
            id: addNewTaskBtn
            text: "Add"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            onClicked: selectedTask = null
        }
    }
}
