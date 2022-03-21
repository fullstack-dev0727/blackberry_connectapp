import bb.cascades 1.4
import bb.system 1.2
import bb.device 1.4
import "../custom"

Page {
    resizeBehavior: PageResizeBehavior.None

    attachedObjects: [
        SystemToast {
            id: myQmlToast
            body: "Message has been sent!"
        }
    ]

    function finished() {
        sendingDialog.close();
    }

    function closeScreen() {
        _home.popScreen();
        finished();

        myQmlToast.show();

    }

    onCreationCompleted: {
        _control.ctMessageSent.connect(closeScreen)
        _control.ctFinished.connect(finished)
    }

    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        onTouch: {
            _control.onTouchFunc();
        }
        Container {
            preferredHeight: ui.sdu(14)
            background: Color.create("#1978bb")
            horizontalAlignment: HorizontalAlignment.Fill
            layout: DockLayout {
            }

            ConnectLabel {
                text: (_control.userId === "") ? "Contact UBT - Email" : " Contact Member - Email"
                textStyle.color: Color.White
                textStyle.fontSize: FontSize.Small
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center

            }
        }
        Container {
            layout: DockLayout {

            }
            visible: typeof _control.m_ContactInfo.ConnectConfig.Email === 'undefined' && (_control.userId === "") ? false : true

            ScrollView {
                Container {
                    verticalAlignment: VerticalAlignment.Top

                    Container {
                        visible: _control.error
                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }
                        margin.topOffset: ui.sdu(10)
                        horizontalAlignment: HorizontalAlignment.Fill

                        ImageView {
                            imageSource: "asset:///images/img/icon_warning.png"
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                        }

                        Label {
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center
                            multiline: true
                            margin.leftOffset: ui.sdu(5)
                            margin.rightOffset: ui.sdu(5)

                            text: "Message could not be sent. Please Check your internet connection."
                            textStyle {
                                base: SystemDefaults.TextStyles.PrimaryText
                                color: Color.DarkGray
                                textAlign: TextAlign.Center
                            }

                        }
                    }

                    ActivityIndicator {
                        id: contentLoadingIndicator
                        objectName: "contentLoadingIndicator"
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                        preferredWidth: 100
                        margin.topOffset: 20
                    }

                    Container {
                        margin.leftOffset: ui.sdu(6)
                        margin.rightOffset: ui.sdu(6)

                        visible: typeof _control.m_ContactInfo.ConnectConfig.Email === 'undefined' && (_control.userId === "") ? false : true
                        layout: StackLayout {
                            orientation: LayoutOrientation.TopToBottom
                        }

                        Container {
                            margin.topOffset: ui.sdu(8)
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }

                            ImageView {
                                verticalAlignment: VerticalAlignment.Center
                                imageSource: "asset:///images/tabicons/message.png"
                            }

                            ConnectLabel {
                                verticalAlignment: VerticalAlignment.Center
                                textStyle.fontSize: FontSize.Small
                                text: (! (_control.userId === "") ? "To: <b>" + (_control.userName).replace("&", "&amp;") + "</b>" : "To: <b>" + (_control.m_ContactInfo.ConnectConfig.Email).replace("&", "&amp;") + "</b>")

                            }

                        }

                        ConnectTextField {
                            id: tfSubject
                            margin.leftOffset: ui.sdu(1)
                            textStyle.fontSize: FontSize.Small
                            hintText: "Subject:"
                        }

                        ConnectTextArea {
                            id: tfBody
                            margin.leftOffset: ui.sdu(1)
                            editable: true
                            preferredHeight: 500
                            textStyle.fontSize: FontSize.Small
                            inputMode: TextAreaInputMode.Text

                            input.submitKey: SubmitKey.Next

                            input.submitKeyFocusBehavior: SubmitKeyFocusBehavior.Next

                            hintText: "Type message here..."
                        }

                        Container {
                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight
                            }
                            margin.bottomOffset: ui.sdu(25)
                            
                            margin.topOffset: ui.sdu(5)
                            
                            Container {
                                preferredWidth: maxWidth
                                preferredHeight: ui.sdu(12)
                                margin.rightOffset: ui.sdu(1)
                                horizontalAlignment: HorizontalAlignment.Fill
                                verticalAlignment: VerticalAlignment.Bottom
                                layout: DockLayout {
                                }
                                
                                onTouch: {
                                    if (event.touchType == TouchType.Down) {
                                        //Do something on down touch - e.g. change background color
                                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                        //Users finger has been lifted OR has left the element.
                                        onClicked: {
                                            _home.popScreen();
                                        }
                                    }
                                }
                                
                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    filterColor: Color.create("#d5dade")
                                }
                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    margin.bottomOffset: ui.sdu(0.3)
                                    margin.rightOffset: ui.sdu(0.3)
                                    margin.leftOffset: ui.sdu(0.3)
                                    margin.topOffset: ui.sdu(0.3)
                                    filterColor: Color.White
                                }
                                
                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center
                                    
                                    textStyle.color: Color.create("#90a3ab")
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.fontWeight: FontWeight.Bold
                                    text: "CANCEL"
                                
                                }
                            }
                            Container {
                                id: btSend
                                preferredWidth: maxWidth
                                preferredHeight: ui.sdu(12)
                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Bottom
                                layout: DockLayout {
                                }

                                onTouch: {
                                    if (event.touchType == TouchType.Down) {
                                        //Do something on down touch - e.g. change background color
                                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                                        //Users finger has been lifted OR has left the element.
                                        onClicked:
                                        {
                                            if (tfSubject.text === "" || tfBody.text === "") {
                                                noContentToast.show();
                                                return;
                                            } else {
                                                if (! (_control.userId === ""))
                                                    _control.sendUserEmail(_control.userId, tfSubject.text, tfBody.text);
                                                else
                                                    _control.sendContactEmail(tfSubject.text, tfBody.text);

                                                //OPEN DIALOG
                                                sendingDialog.open();
                                            }
                                        }
                                    }
                                }

                                ImageView {
                                    imageSource: "asset:///images/nineslice/rounded.amd"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill
                                    filterColor: Color.create("#1978bb")
                                }

                                ConnectLabel {
                                    horizontalAlignment: HorizontalAlignment.Center
                                    verticalAlignment: VerticalAlignment.Center

                                    textStyle.color: Color.White
                                    textStyle.fontSize: FontSize.XSmall
                                    textStyle.fontWeight: FontWeight.Bold
                                    text: "SEND"

                                }
                                attachedObjects: [
                                    SystemToast {
                                        id: noContentToast
                                        body: "Oops. Subject and Body cannot be empty."
                                    }
                                ]
                            }

                        }

                    }
                }
            }
            Container {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Bottom
                preferredWidth: maxWidth
                visible: (_control.userId === "")
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                ConnectLabel {

                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                    text: "Phone: <b>" + _control.m_ContactInfo.ConnectConfig.Phone + "</b>"
                    textStyle.fontSize: FontSize.Small

                }

                Container {
                    id: btCall
                    preferredHeight: ui.sdu(12)
                    preferredWidth: maxWidth
                    background: Color.create("#2EC6C9")
                    verticalAlignment: VerticalAlignment.Bottom

                    layout: DockLayout {

                    }

                    ImageView {
                        imageSource: "asset:///images/buttonimages/call.png"
                        preferredHeight: ui.sdu(6)
                        preferredWidth: ui.sdu(6)
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center
                    }

                    gestureHandlers: [
                        TapHandler {
                            onTapped: {
                                _control.tCallNumber(_control.m_ContactInfo.ConnectConfig.Phone);
                            }
                        }
                    ]

                }

            }

            attachedObjects: [
                Dialog {
                    id: sendingDialog

                    Container {
                        layout: DockLayout {

                        }
                        preferredWidth: maxWidth
                        preferredHeight: displayInfo.resolution.height

                        onCreationCompleted: {
                            actvIndicator.start();
                        }

                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill
                            verticalAlignment: VerticalAlignment.Fill
                            background: Color.create("#AA0000000")

                            layout: DockLayout {

                            }

                            Container {
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight

                                }

                                horizontalAlignment: HorizontalAlignment.Center
                                verticalAlignment: VerticalAlignment.Center

                                Container {
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 0.2
                                    }

                                }

                                Container {
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 1
                                    }
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    verticalAlignment: VerticalAlignment.Fill

                                    Container {
                                        layout: DockLayout {

                                        }

                                        ImageView {
                                            preferredWidth: maxWidth

                                            imageSource: "asset:///images/nineslice/rounded.amd"
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill
                                            filterColor: Color.LightGray
                                        }

                                        Container {
                                            horizontalAlignment: HorizontalAlignment.Fill
                                            verticalAlignment: VerticalAlignment.Fill

                                            layout: StackLayout {
                                                orientation: LayoutOrientation.TopToBottom
                                            }
                                            ConnectLabel {
                                                margin.topOffset: ui.sdu(3)
                                                margin.leftOffset: ui.sdu(4)

                                                text: "Sending message."
                                                textStyle.color: Color.Black
                                                textStyle.fontSize: FontSize.Medium
                                            }

                                            Container {
                                                layout: StackLayout {
                                                    orientation: LayoutOrientation.LeftToRight
                                                }
                                                margin.topOffset: ui.sdu(3)
                                                margin.bottomOffset: ui.sdu(3)
                                                margin.leftOffset: ui.sdu(4)

                                                ActivityIndicator {

                                                    verticalAlignment: VerticalAlignment.Center
                                                    id: actvIndicator
                                                    enabled: true

                                                    preferredHeight: ui.sdu(8)
                                                    preferredWidth: ui.sdu(8)
                                                }

                                                ConnectLabel {
                                                    margin.leftOffset: ui.sdu(2)
                                                    verticalAlignment: VerticalAlignment.Center
                                                    text: "Please wait..."
                                                    textStyle.color: Color.DarkGray
                                                    textStyle.fontSize: FontSize.Small

                                                }
                                            }

                                        }

                                    }

                                }

                                Container {
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 0.2
                                    }

                                }

                            }
                        }

                        attachedObjects: [
                            DisplayInfo {
                                id: displayInfo
                            }
                        ]
                    }

                }
            ]
        }

    }
}
