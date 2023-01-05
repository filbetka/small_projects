import QtQuick 2.15
import QtQuick.Window 2.15

Rectangle {
    id: root
    visible: false
    height: 48
    width: 48

    function setTile(root, tile) {
        draggingWidget.visible = !!tile
        if (tile) {
            var position = tile.background.mapToItem(root, tile.dragPoint.x, tile.dragPoint.y)
            draggingWidget.x = position.x - width/2
            draggingWidget.y = position.y - height/2
            draggingWidget.color = tile.color
        }
    }
}
