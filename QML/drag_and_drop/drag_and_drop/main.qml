import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true

    function randomColor() {
        return Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
    }

    ListModel {
        id: tiles

        ListElement {}
        ListElement {}
        ListElement {}
        ListElement {}
        ListElement {}
    }

    Item {
        id: root
        anchors.fill: parent

        Row {
            spacing: 2
            padding: 10

            Repeater {
                model: tiles

                Tile {
                    color: randomColor()
                    index: model.index

                    onMoveTile: {
                        console.log(dragged.index, dropped.index)
                        tiles.move(dragged.index, dropped.index, 1)
                    }

                    onDragging: {
                        draggingWidget.setTile(root, tile)
                    }
                }
            }
        }

        DraggingWidget {
            id: draggingWidget
        }
    }
}
