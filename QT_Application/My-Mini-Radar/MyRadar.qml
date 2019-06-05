import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    function clearAllPoint()
    {
        device.clear()
    }

    function radarPoint(value, angle)
    {
        var centerX, centerY, posX, posY
        //angle = Math.random()*360
        centerX = radar.radius
        centerY = radar.radius
        if(value < 0) {
            posX = -1*value
        }
        else {
            posX = value
        }

        //100 consider as max value
        posX = (100-posX)
        var radius = centerX - (centerX * (posX/100))
        //posX = centerX + radius * Math.cos(angle* 0.017453292519)
        //posY = centerY + radius * Math.sin(angle* 0.017453292519)
        //radius = value //radius,
        radius -= 10
        posX = centerX + Math.cos(Math.PI * angle / 180) * radius
        posY = centerY - Math.sin(Math.PI * angle / 180) * radius

        device.append({ "distance_CM": value, "x": posX, "y": posY, "a": angle })
        for(var i = 0 ; i < device.count ; i++ )
        {
            if( angle > device.get(i).a)
            {
                if((angle - device.get(i).a)  > 90 ) device.remove(i)
            }
            else
            {
                 if((device.get(i).a - angle)  > 90 ) device.remove(i)
            }


        }

    }

    Rectangle{
        anchors.fill: parent
        color: "black"
    }

    Item {
        id: root
        anchors.fill: parent
        Rectangle {
            id: radar
            width: 300
            height: 300
            anchors.centerIn: parent
            radius: width*0.5
            color: "#00000000"
            border.width: 2
            border.color: "green"

            property int rotationSpeed: 25
            /*
            Timer {
                  repeat: true
                  running: true
                  interval: radar.rotationSpeed
                  onTriggered: handle.angle++
              }
            */
            Rectangle {
                anchors.fill: parent
                color: parent.border.color
                radius: parent.radius
                opacity: 0.15
            }
            Rectangle {
                anchors.centerIn: parent
                width: parent.width*0.5
                height: width
                radius: width*0.5
                color: parent.color
                border.width: parent.border.width
                border.color: parent.border.color
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.border.width
                height: parent.height
                color: parent.border.color
            }

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                height: parent.border.width
                width: parent.width
                color: parent.border.color
            }
            ConicalGradient {
                id: handle
                anchors.fill: parent
                angle: ( myNetwork.angle * -1 ) + 90
                source: Rectangle {
                    width: handle.width
                    height: handle.height
                    radius: width*0.5
                }
                gradient:  Gradient {
                    GradientStop { position: myNetwork.rightToLeft ? 1.0 : 0.0 ; color: "#00000000" }
                    GradientStop { position: myNetwork.rightToLeft ? 0.15: 0.85 ; color: "#00000000" }
                    GradientStop { position: myNetwork.rightToLeft ? 0.0 : 1.0; color: "green" }
                }
            }

            Repeater {
                Rectangle {
                    x: model.x
                    y: model.y
                    width: 10
                    height: width
                    radius: width*0.5
                }
                model: device
            }

            ListModel {
                id: device
            }

        }

    }

}
