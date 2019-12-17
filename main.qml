import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.1

import Server 1.0

Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("Xavier")

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

    Image {
        id: image1
        source: "xaviccc.jpg";
        y: parent.height / 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: 360
        height: 360
    }

    SequentialAnimation {
        id: startAnimation
        ParallelAnimation {
            id: fadeOut

            NumberAnimation {
                target: image1
                duration: 1200
                properties: "opacity"
                from: 1.0
                to: 0.0;
                easing.type: Easing.OutExpo;
            }

            NumberAnimation {
                target: startWaves
                duration: 1200
                properties: "opacity"
                from: 1.0
                to: 0.0
                easing.type: Easing.OutExpo;
            }
        }

        NumberAnimation {
            target: waves
            duration: 1200
            properties: "opacity"
            from: 0.0
            to: 1.0
            easing.type: Easing.OutExpo;
        }

        onStopped: {
            startWaves.visible = false;
        }
    }

    Button {
        id: startWaves
        anchors.top: image1.bottom
        anchors.topMargin: 12

        property var clicked: false
        property var firstGradient: clicked ? "#3bb853" : "#079423"
        property var secondGradient: clicked ? "#38c253" : "#2ca844"

        anchors.horizontalCenter: parent.horizontalCenter
        width: 150
        height: 60
        text: "Launch"
        font.pixelSize: 32
        background: Rectangle {
            radius: 12
            //color: startWaves.clicked ? "#38c253" : "#239e3b"
            gradient: Gradient {
                GradientStop { position: 0.0; color: startWaves.firstGradient }
                GradientStop { position: 1.0; color: startWaves.secondGradient }
            }
        }

        contentItem: Text {
            text: startWaves.text
            font: startWaves.font
            color: "#dddddd"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        onClicked: {
            startWaves.clicked = true;
            startAnimation.start();
            //startWaves.source = "xav.jpg"
        }
    }



    SoundWaves {
        id: waves
        opacity: 0.0
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
        y: parent.height / 5
        anchors.horizontalCenter: parent.horizontalCenter

        text: server.message
        font.pixelSize: 42
    }
}
