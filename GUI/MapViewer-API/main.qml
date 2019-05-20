import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

Rectangle {
    visible: true
    width: 640
    height: 480

    Rectangle{
        id:rect1
        width: 471
        height: 480
        MapViewer{
            anchors.fill: parent
        }
    }

    Rectangle{
        anchors.left:rect1.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        SerialSetting{
            anchors.fill: parent
        }
    }

//    SpinBox {
//        id: spinbox
//        x: 485
//        y: 45
//        value: 0
//        from: -180 * 1000000
//        to: 180 * 1000000
//        stepSize: 100000

//        property int decimals: 6
//        property real realValue: value / 1000000

//        validator: DoubleValidator {
//            bottom: Math.min(spinbox.from, spinbox.to)
//            top:  Math.max(spinbox.from, spinbox.to)
//        }

//        textFromValue: function(value, locale) {
//            return Number(value / 1000000).toLocaleString(locale, 'f', spinbox.decimals)
//        }

//        valueFromText: function(text, locale) {
//            return Number.fromLocaleString(locale, text) * 1000000
//        }
//    }

//    SpinBox {
//        id: spinbox1
//        x: 485
//        y: 127
//        value: 0
//        from: -90 * 1000000
//        to: 90 * 1000000
//        stepSize: 100000

//        property int decimals: 6
//        property real realValue: value / 1000000

//        validator: DoubleValidator {
//            bottom: Math.min(spinbox1.from, spinbox1.to)
//            top:  Math.max(spinbox1.from, spinbox1.to)
//        }

//        textFromValue: function(value, locale) {
//            return Number(value / 1000000).toLocaleString(locale, 'f', spinbox1.decimals)
//        }

//        valueFromText: function(text, locale) {
//            return Number.fromLocaleString(locale, text) * 1000000
//        }
//    }

//    Button {
//        id: button
//        x: 505
//        y: 203
//        text: qsTr("Button")
//        onPressed: {
//            obj_testerMapViewer.send_Data(spinbox.realValue,spinbox1.realValue)
//        }
//    }

//    Label {
//        id: label
//        x: 485
//        y: 26
//        text: qsTr("lon")
//    }

//    Label {
//        id: label1
//        x: 485
//        y: 108
//        text: qsTr("lat")
//    }


}
