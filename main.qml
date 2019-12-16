import QtQuick 2.9
import QtQuick.Window 2.2

import Server 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Server")

    HttpServer {
        id: server
    }

    Rectangle {
        id: backGround
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#f2f2f2" }
            GradientStop { position: 1.0; color: "#ededed" }
        }
    }

    SoundWaves {
        id: waves
        anchors.centerIn: parent
    }

    Connections {
        target: server
        onStartAnimation: {
            waves.viewModel.increaseAmplitude();
        }
    }

    Connections {
        target: server
        onStopAnimation: {
            waves.viewModel.decreaseAmplitude();
        }
    }

    Text {
        id: message
        y: parent.height - 400
        anchors.horizontalCenter: parent.horizontalCenter

        text: server.message
        font.pixelSize: 25
    }
}
