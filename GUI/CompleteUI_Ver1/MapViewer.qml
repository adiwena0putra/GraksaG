import QtQuick 2.0
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Controls 1.6

Item {
    id: root_MapViewer


    Plugin{
        id: mapPlugin
        name: "esri"
    }

    Rectangle{
        id: placeholder_MapViewer
        anchors.fill: parent

        Rectangle{
            id: placeholder_Button
            width: parent.width
            height: 0.1 * parent.height
            anchors.top: parent.top

            Button{
                id: button_setHome
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: parent.left
                text: qsTr("Set Home")
                onPressedChanged: {
                    obj_MapViewer.set_home()
                }
            }

            Button{
                id: button_clear
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: button_setHome.right
                text: qsTr("Clear")
                onPressedChanged: {
                    id_map.start_tracing = false;
                    obj_MapViewer.set_clear();
                    id_map.clearData()
                    id_map.clearMapItems();
                    id_map.clearMapParameters()
                }
            }

            Button{
                id: button_zoomIn
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: button_clear.right
                text: qsTr("Zoom In")
                onPressedChanged: id_map.zoomLevel += 0.1
            }

            Button{
                id: button_zoomOut
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: button_zoomIn.right
                text: qsTr("Zoom Out")
                onPressedChanged: id_map.zoomLevel -= 0.1
            }

        }

        Rectangle{
            id: placeholder_Map
            width: parent.width
            anchors.top: placeholder_Button.bottom
            anchors.bottom: placeholder_coordinate.top

            Map{
                id: id_map
                anchors.fill: parent
                plugin: mapPlugin
                property double lon: 0
                property double lat: 0
                property bool start_tracing : false
                property bool add_line: false
                center: QtPositioning.coordinate(lon, lat)



                MapPolyline{
                    id:tracer
                    line.width: 5
                    line.color: 'green'
                }

                MapQuickItem{
                    id: home
                    zoomLevel: id_map.zoomLevel
                    anchorPoint.x: circle.width/2
                    anchorPoint.y: circle.height/2
                    sourceItem: Rectangle{
                        id:circle
                        width: 16
                        height: 16
                        radius: 16
                        color: "red"
                    }

                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        label_infolon.text = qsTr("%1").arg(id_map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)
                        label_infolat.text = qsTr("%1").arg(id_map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude)
                    }
                }

            }

            Connections{
                target: obj_MapViewer
                onUpdate_UI: {
                    id_map.center = QtPositioning.coordinate(latitude,longitude)

                    if (isHome) {
                        id_map.start_tracing = true
                        home.coordinate = QtPositioning.coordinate(latitude,longitude)
                        id_map.add_line = true
                    }

                    if (id_map.start_tracing) {
                        if (id_map.add_line) {
                            id_map.addMapItem(tracer)
                            id_map.addMapItem(home)
                            id_map.add_line = false
                            for (var i=tracer.pathLength()-1;i>=0;i--) {
                                tracer.removeCoordinate(i)
                            }
                        }

                        tracer.addCoordinate(QtPositioning.coordinate(latitude,longitude))
                    }

                    label_infolon.text = qsTr("%1").arg(longitude)
                    label_infolat.text = qsTr("%2").arg(latitude)

                }
            }

        }

        Rectangle{
            id: placeholder_coordinate
            width: parent.width
            anchors.bottom: parent.bottom
            height: 0.1*parent.height

            Label{
                id: label_longitude
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: parent.left
                text: qsTr("Longitude: ")
                lineHeight: 1
                fontSizeMode: Text.FixedSize
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Label{
                id: label_infolon
                height: parent.height
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                width: 0.25 * parent.width
                anchors.left: label_longitude.right
            }

            Label{
                id: label_latitude
                height: parent.height
                width: 0.25 * parent.width
                anchors.left: label_infolon.right
                text: qsTr("Latitude: ")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            Label{
                id: label_infolat
                height: parent.height
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                width: 0.25 * parent.width
                anchors.left: label_latitude.right
            }
        }

    }

}
