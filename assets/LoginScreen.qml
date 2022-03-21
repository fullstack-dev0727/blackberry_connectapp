import bb.cascades 1.4
import bb.device 1.4
import bb.system 1.2
import "DetailScreens"
import "custom"


Sheet {
    id: homeSheet
    
    peekEnabled: false
    
    
    onOpened: {
        password.text = "";
    }
    
    Page {
        resizeBehavior: PageResizeBehavior.None
        
        
        
        
        
        Container {
            
            function isSquare() {
                var height = displayInfo.pixelSize.height;
                var width = displayInfo.pixelSize.width;
                if (height == width)
                    return true;
                return false;
            }
            
            
            background: isSquare() ? backSquare.imagePaint : back.imagePaint  
            
            layout: DockLayout {
            
            }
            
            ConnectTextArea {
                margin.leftOffset: ui.sdu(10)
                margin.topOffset: ui.sdu(35)
                horizontalAlignment: HorizontalAlignment.Center
                editable: false
                visible: _control.error
                preferredWidth: maxWidth
                text: _control.errorMessage
                textStyle {
                    base: SystemDefaults.TextStyles.BodyText
                    color: Color.Red
                }
            }
            
            
            ScrollView {
                verticalAlignment: VerticalAlignment.Top
                horizontalAlignment: HorizontalAlignment.Center
                pivotY: -50.0
                margin.leftOffset: ui.sdu(10)
                
                function setup() {
                    if (displayInfo.pixelSize.height == displayInfo.pixelSize.width)
                        margin.topOffset =  ui.sdu(25)
                    else    
                        margin.topOffset =  ui.sdu(45)
                }
                
                
                onCreationCompleted: {
                    setup()
                }
                
                
                Container {

                    background: Color.Transparent
                    Container {
                        topPadding: ui.sdu(2.5)
                        bottomPadding: ui.sdu(2.5)
                        background: Color.White
                        layout: DockLayout {

                        }
                        ConnectTextField {
                            leftPadding: ui.sdu(10)
                            margin.rightOffset: ui.sdu(1.3)
                            verticalAlignment: VerticalAlignment.Center
                            id: email
                            text: "zonaid.sharafi@ubteam.com"
                            hintText: "Email address"
                            backgroundVisible: false
                            textStyle.fontSize: FontSize.Default
                            inputMode: TextFieldInputMode.EmailAddress
                        }
                        ImageView {
                            verticalAlignment: VerticalAlignment.Center
                            imageSource: "asset:///images/textfieldicons/user.png"
                            margin.leftOffset: ui.sdu(3.8)
                            scalingMethod: ScalingMethod.AspectFit
                        }
                    }
                    Container {
                        topPadding: ui.sdu(2.5)
                        bottomPadding: ui.sdu(2.5)
                        topMargin: ui.sdu(3)
                        layout: DockLayout {

                        }
                        background: Color.White
                        ConnectTextField {
                            leftPadding: ui.sdu(10)
                            margin.rightOffset: ui.sdu(1.3)
                            verticalAlignment: VerticalAlignment.Center
                            id: password
                            text: ""
                            hintText: "Password"
                            backgroundVisible: false
                            inputMode: TextFieldInputMode.Password
                            input.submitKey: SubmitKey.Submit
                            input.onSubmitted: {
                                if (email.text == "" || password.text == "") { //display error
                                    myQmlToast.show();
                                    return;
                                }
                                if (! termsNconditions.checked) {
                                    myQmlToast2.show();
                                    return;
                                }
                                if (! _control.isConnectedToInternet()) {
                                    myQmlToast3.show();
                                    return;
                                }
                                loadingDialog.open();
                                _control.requestLogin(email.text, password.text);
                            }
                            input.flags: TextInputFlag.SpellCheck
                            input.submitKeyFocusBehavior: SubmitKeyFocusBehavior.Next
                        }
                        ImageView {
                            verticalAlignment: VerticalAlignment.Center
                            imageSource: "asset:///images/textfieldicons/password.png"
                            margin.leftOffset: ui.sdu(3.8)
                            scalingMethod: ScalingMethod.AspectFit
                        }
                    }
                    Container {
                        topMargin: ui.sdu(3)
                        layout: StackLayout {
                            orientation: LayoutOrientation.LeftToRight
                        }
                        CheckBox {
                            id: termsNconditions
                            horizontalAlignment: HorizontalAlignment.Left
                            checked: false
                        }
                        ConnectLabel {
                            leftMargin: ui.sdu(3.5)
                            text: "I accept the <b><u>Terms and Conditions</u></b>"
                            textStyle.color: Color.White
                            textFormat: TextFormat.Html
                            textStyle.fontSize: FontSize.Small
                            multiline: true
                            gestureHandlers: [
                                TapHandler {
                                    onTapped: { 
                                         _control.openSheet("terms");
                                    }
                                }
                            ]
                        }
                    }
                    ConnectLabel {
                        horizontalAlignment: HorizontalAlignment.Center
                        text: "<b><u>Forgot Password?</u></b>"
                        textStyle.color: Color.White
                        textStyle.fontSize: FontSize.XSmall
                        textFormat: TextFormat.Html
                        gestureHandlers: [
                            TapHandler {
                                onTapped: {
                                    _control.launchForgotPassword();
                                }
                            }
                        ]
                    }

                }
            }

            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Bottom
                
                background: Color.create("#2d85c2")  
                
                onTouch: {
                    if (event.touchType == TouchType.Down) {
                        //Do something on down touch - e.g. change background color
                    } else if (event.touchType == TouchType.Up || event.touchType == TouchType.Cancel) {
                        //Users finger has been lifted OR has left the element.
                        onClicked:
                        {
                            if (email.text == "" || password.text == "") {
                                //display error
                                myQmlToast.show();
                                return;
                            }

                            if (! termsNconditions.checked) {
                                myQmlToast2.show();
                                return;
                            }
                            
                            if (! _control.isConnectedToInternet()) {
                                myQmlToast3.show();
                                return;
                            }
                            
                            loadingDialog.open();
                            _control.requestLogin(email.text, password.text);
                        }
                    }
                }

                ConnectLabel {
                    horizontalAlignment: HorizontalAlignment.Center
                    margin.bottomOffset: ui.sdu(3.5)
                    margin.topOffset: ui.sdu(3.5)

                    textStyle.color: Color.White
                    textStyle.fontSize: FontSize.Medium
                    textStyle.fontWeight: FontWeight.Bold
                    text: "Login"
                
                }
            
            
            }
            
            attachedObjects: [
                ImagePaintDefinition {
                    id: back
                    repeatPattern: RepeatPattern.XY
                    imageSource: "asset:///images/img/bg_login_screen.jpg"
                },
                ImagePaintDefinition {
                    id: backSquare
                    repeatPattern: RepeatPattern.XY
                    imageSource: "asset:///images/img/bg_login_screen_square.jpg"
                },
                SystemToast {
                    id: myQmlToast
                    body: "Enter a valid username and password."
                },
                SystemToast {
                    id: myQmlToast2
                    body: "Please accept the Terms and Conditions."
                },   
                SystemToast {
                    id: myQmlToast3
                    body: "Please connect to the internet to login."
                }              
            ]        
        }
    
    
    
    
    }
    
    attachedObjects: [
        DisplayInfo {
            id: displayInfo
        }
    ]

}