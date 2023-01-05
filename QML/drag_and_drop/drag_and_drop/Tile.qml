import QtQuick 2.15
import QtQuick.Window 2.15

Item {
    id: root
    property string color
    property int index
    property alias background: background
    property alias dragPoint: mouseArea.dragPoint

    width: 64
    height: 64

    signal moveTile(var dragged, var dropped)
    signal dragging(var tile)

    DropArea {
        anchors.fill: parent
        enabled: !mouseArea.drag.active

        onEntered: {
            root.moveTile(drag.source.tile, root)
        }
    }

    Rectangle {
        id: background
        width: parent.width
        height: parent.height
        color: root.color

        property alias tile: root

        z: mouseArea.drag.active ? 2 : 1
        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: mouseArea.dragPoint.x
        Drag.hotSpot.y: mouseArea.dragPoint.y

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        states: State {
            when: mouseArea.drag.active
            AnchorChanges {
                target: background
                anchors.verticalCenter: undefined
                anchors.horizontalCenter: undefined
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: background

        property bool dragActive: drag.active
        property point dragPoint: Qt.point(32, 32)

        onDragActiveChanged: {
            if (!dragActive) {
                root.moveTile(root, root)
                root.dragging(null)
                root.opacity = 1
            }

            else {
                root.opacity = 0
            }
        }

        onPositionChanged: {
            if (drag.active) {
                root.dragging(root)
            }
        }

        onPressed: {
            dragPoint = Qt.point(mouseX, mouseY)
        }
    }
}
