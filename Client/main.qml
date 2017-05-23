import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import extend.qt.ClientNetworkInterface 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("wereWolvesHollow")

    /*
    MainForm {
        anchors.fill: parent
        mouseArea.onClicked: {
            Qt.quit();
        }
    }
    */

    ClientNetworkInterface {
        id: clientNetworkInterface

    }

    Button {
        id: exitButton
        x: 270
        y: 294
        text: "exit"
        onClicked: {
            Qt.quit();
        }
    }

    Button {
        id: loginButton
        x: 270
        y: 232
        text: "login"
        onClicked: {
            console.log("login button pressed");
            console.log("now input userName:" + userNameField.text)
            if (userNameField.text != "") {
                console.log("validation OK");
                clientNetworkInterface.startLogin(userNameField.text);
            }
            else
                console.log("validation failed");
        }
    }

    Button {
        id: testButton
        text: "test"
        onClicked: {
            console.log("test result: " + clientNetworkInterface.test());
        }
    }

    TextField {
        id: userNameField
        x: 220
        y: 44
    }

    TextField {
        id: sayField
        x: 220
        y: 112
    }

    Label {
        id: userNameLabel
        x: 145
        y: 56
        text: "userName"
    }

    Label {
        id: sayLabel
        x: 166
        y: 124
        text: "say"
    }

    Button {
        id: sayButton
        x: 270
        y: 172
        text: "say"
        onClicked: {
            if (sayField.text == "")
                statusLabel.text = "You can't say nothing!";
            else
                clientNetworkInterface.addString(sayField.text);
        }
    }


    Label {
        id: statusLabel
        x: 285
        y: 0
        text: "Input your username to login."

    }

    //initialization
    Component.onCompleted: {
        sayButton.enabled = false;

    }

    Connections {
        target: clientNetworkInterface
        onReceiveCommand: {
            clientHandle(message);
        }
    }

    function clientHandle(message) {
        if (message != "")
            console.log("#Message received from server: " + message);
        if (message == "login ok") {
            console.log("login successfully");
            sayButton.enabled = true;
            statusLabel.text = "Login successfully...";
        }
    }
}
