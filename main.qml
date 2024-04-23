import QtQuick
import QtQuick.Controls
import Qt.labs.platform

import io.chronos.backend 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Chronos")
    onClosing: {
        window.hide()
    }

    property var tasksData: backend.loadTasks()
    property var lastEvent: backend.loadLastEvent()
    property var currentTrackedTime: (lastEvent?.passed || "00:00:00")
    property var selectedTask: (tasksData || []).find((task) => task && lastEvent && task?.id === lastEvent?.taskId)

    Menu {
        id: trayMenu
        MenuItem {
            text: qsTr("Quit")
            onTriggered: {
                Qt.quit()
            }
        }
    }

    SystemTrayIcon {
        visible: true
        icon.source: "qrc:/icons/countdown.png"
        menu: trayMenu

        onActivated: {
            window.show()
            window.raise()
            window.requestActivate()
        }
    }

    TaskList {
        id: taskList
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: parent.width / 2
    }

    TimerForm {
        id: timerContainer
        anchors.left: taskList.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        height: 50
    }

    TaskForm {
        id: taskForm
        anchors.left: taskList.right
        anchors.top: timerContainer.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }

    Backend {
        id: backend
        onTasksUpdated: {
            tasksData = backend.loadTasks()
            lastEvent = backend.loadLastEvent()
            selectedTask = (tasksData || []).find((task) => task && lastEvent && task?.id === lastEvent?.taskId)
        }
        onStateChanged: {
            tasksData = backend.loadTasks()
            lastEvent = backend.loadLastEvent()
            selectedTask = (tasksData || []).find((task) => task && lastEvent && task?.id === lastEvent?.taskId)
        }
    }

    Timer {
        interval: 500;
        running: true;
        repeat: true
        onTriggered: currentTrackedTime = (lastEvent?.passed || "00:00:00")
    }
}
