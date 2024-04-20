import QtQuick 2.0
import QtQuick.Controls

Item {
    Rectangle {
        id: taskTitleContainer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        height: 30
        color: Qt.color("white")

        TextEdit {
            id: taskTitle
            anchors.fill: parent
            anchors.margins: 5
            font.pointSize: 11
            text: selectedTask?.id ? selectedTask.title : ""
        }
    }

    TextArea {
        id: taskComments
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: taskTitleContainer.bottom
        anchors.bottom: createTaskBtn.top
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        text: selectedTask?.id ? selectedTask.comments : ""
    }

    Button {
        id: createTaskBtn
        text: selectedTask?.id ? "Update" : "Create"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right
        onClicked: {
            if (selectedTask?.id) {
                backend.updateTask(selectedTask.id, taskTitle.text, taskComments.text)
            } else {
                backend.createTask(taskTitle.text, taskComments.text)
            }
        }
    }
}
