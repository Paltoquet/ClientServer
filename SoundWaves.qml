import QtQuick 2.0

import Server 1.0

Row {

    id: root
    spacing: 4

    width: childrenRect.width

    property var viewModel: SoundWavesViewModel {
        id: soundWavesViewModel
    }

    Repeater {

        id: repeater
        model: soundWavesViewModel.waves

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter

            color: "#858585"
            height: modelData.height
            width: 12
        }
    }
}
