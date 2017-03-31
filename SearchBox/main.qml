import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("                                     Search Box                              ")
    property var stringList:[]
    property bool isFileLoaded:false
    property bool isFileAccepted:false

    TextField {

        id:textFieldId
        anchors.centerIn: parent
        width: 80 *(parent.width/100)
        onTextChanged: stringList = searchObj.getSearchList(textFieldId.text)//console.log(textFieldId.text)
        placeholderText: "Enter String for Search"
        visible: isFileLoaded

    }

    ComboBox{
        id:searchListCombo
        anchors.top: textFieldId.bottom
        anchors.left: textFieldId.left
        width:textFieldId.width
        height:textFieldId.height
        model:stringList
        onCurrentIndexChanged: textFieldId_Output.text = searchObj.getEnumLiteralValue(searchListCombo.currentText)
        onCurrentTextChanged: textFieldId_Output.text = searchObj.getEnumLiteralValue(searchListCombo.currentText)
        visible: isFileLoaded
    }

    TextField {

        id:textFieldId_Output
        anchors.bottom:textFieldId.top
        anchors.left:searchListCombo.left
        width: 80 *(parent.width/100)
        placeholderText: "Output Value"
        visible: isFileLoaded

    }

    Button {

        id:buttonId
        anchors.top: searchListCombo.bottom
        anchors.centerIn: parent
        anchors.topMargin: buttonId.height
        width:60
        height:30
        text:"LoadFile"
        onClicked: fileDialog.visible = true
        visible: !isFileLoaded

    }

    Button {

        id:reload_buttonId
        x: parent.width - reload_buttonId.width
        y: parent.height - reload_buttonId.height
        width:60
        height:30
        text:"ReloadFile"
        onClicked: fileDialog.visible = true
        visible: isFileAccepted

    }



    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "HeaderFile (Gciproxy.h)"]

        onAccepted: {

            console.log("You chose: " + fileDialog.fileUrl)
            searchObj.readFile(fileDialog.fileUrl)
            isFileLoaded = true;
            isFileAccepted = true;
            fileDialog.close();

        }
        onRejected: {

            console.log("Canceled")
            fileDialog.close();

        }
    }


}
