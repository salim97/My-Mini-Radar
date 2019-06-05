import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("My Mini Radar")
    Timer{
        running: false
        repeat: true
        interval: 500
        onTriggered:
        {
            var d, a= 0
            var min=1;
             var max=100;
             var random = Math.random() * (+max - +min)  +min;
            d = random.toFixed(0)
            a = myNetwork.angle + 5
            if(a > 180) {
                radar.clearAllPoint()
                a = 0
            }
            myNetwork.distance_CM = d
            myNetwork.angle = a

            console.log(d + " " + a)
        }
    }

    Connections{
        target: myNetwork

        onAngleChanged:
        {
            if(myNetwork.angle >= 180 )
            {
                radar.clearAllPoint()
            }

            if(myNetwork.angle <= 0 )
            {
                radar.clearAllPoint()
            }

            if(myNetwork.distance_CM < 50)
            {
                var tmp = myNetwork.distance_CM*4
                if(tmp > 100) tmp = 100;
                if( tmp < 10) return ;
                radar.radarPoint(tmp, myNetwork.angle)
            }
        }
    }

    MyRadar{
        id: radar
        anchors.fill: parent
    }

}
